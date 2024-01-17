#include <random>
#include "../../../../wta_library/wta_Convert.h"
#include "../../[002]Mediator/Mediator.h"
#include "Item.h"


// 最初は茶色のため、idは0で統一
Item::Item()
{
	m_collision_size = { 50 };
}

Item::~Item()
{
	MV1DeleteModel(m_item_data.s_model_hdl);
	DeleteGraph(m_item_data.s_texture_hdl);
}

void Item::Initialize()
{
	// モデル読み取り
	//ここですべてのモデルの情報を元に読み込み処理(GetItemLoadInfoById関数でfor分で各モデルを回すべき？)
	m_item_data = m_mediator->GetItemLoadInfoById(0);

	// モデルの読み込み
	m_item_data.s_model_hdl = MV1LoadModel(m_item_data.s_model_path.c_str());

	// テクスチャ読み取り
	m_item_data.s_texture_hdl = LoadGraph(m_item_data.s_texture_path.c_str());

	// 材質の指定はないため引数は0
	MV1SetTextureGraphHandle(m_item_data.s_model_hdl, 0, m_item_data.s_texture_hdl, FALSE);

	// アイテムの種類の総数を取得
	m_id_num = m_mediator->GetItemIdNum();
}

void Item::Update(float delta_time)
{
	VECTOR pos_vec = wta::ConvertToVECTOR(m_pos);
	MV1SetPosition(m_item_data.s_model_hdl, pos_vec);

	tnl_sequence_.update(delta_time);

	MoveFlower(delta_time);
}

void Item::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	if (m_is_active)
	{
		SetLight();

		MV1DrawModel(m_item_data.s_model_hdl);
	}
}

void Item::Reset()
{
	m_pos = { 0,0,0 };
	m_is_active = false;
	m_is_draw_change = false;
	m_emissive_value = 0.0f;
	m_time_elapsed = 0.0f;
	m_emissive = { 0.5f,0.5f,0.5f,1 };
}

void Item::SetLight()
{
	// ライトの設定
	//環境光
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	//拡散光
	DxLib::COLOR_F diffuse = { 0.8f,0.8f,0.8f,1 };
	//メタリック
	DxLib::COLOR_F specular = { 0,0,0,1 };

	MV1SetMaterialEmiColor(m_item_data.s_model_hdl, 0, m_emissive);
	MV1SetMaterialAmbColor(m_item_data.s_model_hdl, 0, ambient);
	MV1SetMaterialDifColor(m_item_data.s_model_hdl, 0, diffuse);
	MV1SetMaterialSpcColor(m_item_data.s_model_hdl, 0, specular);
	// 強いほど光が鋭くなる
	MV1SetMaterialSpcPower(m_item_data.s_model_hdl, 0, 0.5f);
}

int Item::RandomTexture()
{
	// ID 0 は除外
	return tnl::GetRandomDistributionInt(1, m_id_num);
}

void Item::ChangeTexture()
{
	int new_texture = RandomTexture();

	// 新しいテクスチャ情報を取得
	Item::sItemType new_texture_id 
			= m_mediator->GetItemLoadInfoById(new_texture);

	// 古いテクスチャを削除
	DeleteGraph(m_item_data.s_texture_hdl);

	// 新しいテクスチャを読み込み
	m_item_data.s_texture_hdl 
		= LoadGraph(new_texture_id.s_texture_path.c_str());

	// テクスチャをモデルに適用
	MV1SetTextureGraphHandle(m_item_data.s_model_hdl, 0, m_item_data.s_texture_hdl, FALSE);
}

void Item::MoveFlower(const float delta_time)
{
	if (m_mediator->GetIsItemFlowerActive())
	{
		static float elapsed_time = 0.0f;

		elapsed_time += delta_time * 10;

		// 左右にゆらゆら揺れながらゆっくり落下
		m_pos.x += sin(elapsed_time) * 10;
		m_pos.y -= elapsed_time * 5;

		if (m_pos.y < m_mediator->GetPlayerPos().y - 750)
		{
			elapsed_time = 0.0f;
		}

		// 乱数を使って回転をランダムで決定(ラジアンで指定)
		// 0~360度 : ランダムな回転角度の決定
		tnl::Vector3 rot = { tnl::GetRandomDistributionFloat(0,DirectX::XMConvertToRadians(360))
							 ,tnl::GetRandomDistributionFloat(0, DirectX::XMConvertToRadians(360))
							 ,tnl::GetRandomDistributionFloat(0, DirectX::XMConvertToRadians(360)) };

		// 回転をランダムで決定
		tnl::Quaternion target_rot 
			= tnl::Quaternion::RotationRollPitchYawFromVector(rot);

		// 回転を適用
		m_rot.slerp(target_rot, delta_time * 100);
	}
}

void Item::MoveButterfly(const float delta_time)
{

}

bool Item::SeqNormal(const float delta_time)
{
	if (m_is_draw_change)
	{
		tnl_sequence_.change(&Item::SeqLightUp);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}

bool Item::SeqLightUp(const float delta_time)
{
	m_time_elapsed += delta_time;

	// 0.5 : サイン関数（-1~1）を（0~1）に変換
	m_emissive_value = sin(m_time_elapsed) * 0.5f + 0.5f;

	m_emissive = { m_emissive_value, m_emissive_value, m_emissive_value, 1.0f };

	if (m_time_elapsed >= 1.0f)
	{
		m_time_elapsed = 0.0f;

		tnl_sequence_.change(&Item::SeqLightDown);
	}

	TNL_SEQ_CO_END;
}

bool Item::SeqLightDown(const float delta_time)
{
	m_time_elapsed += delta_time;

	m_emissive_value = 1.0f - (sin(m_time_elapsed) * 0.5f + 0.5f);

	m_emissive = { m_emissive_value, m_emissive_value, m_emissive_value, 1.0f };

	if (m_time_elapsed <= 1.0f)
	{
		m_time_elapsed = 0.0f;

		tnl_sequence_.change(&Item::SeqChangeEnd);
	}

	TNL_SEQ_CO_END;
}

bool Item::SeqChangeEnd(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		ChangeTexture();
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}