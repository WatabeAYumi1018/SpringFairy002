#include <random>
#include "../../../../wta_library/wta_Convert.h"
#include "../../[002]Mediator/Mediator.h"
#include "Gimmick.h"


// 最初は茶色のため、idは0で統一
Gimmick::Gimmick()
{
	m_scale = { 1.5f };
}

Gimmick::~Gimmick()
{
	MV1DeleteModel(m_gimmick_data.s_model_hdl);
	DeleteGraph(m_gimmick_data.s_texture_a_hdl);
	DeleteGraph(m_gimmick_data.s_texture_b_hdl);
}

void Gimmick::Initialize()
{
	SetLight(m_gimmick_data.s_model_hdl);

	//SetLight();

	// モデル読み取り
	//ここですべてのモデルの情報を元に読み込み処理(GetItemLoadInfoById関数でfor分で各モデルを回すべき？)
	//m_gimmick_data = m_mediator->GetGimmickLoadInfoById(0);
	//m_plants = m_mediator->GetGimmickPlants();

	//m_trees = m_mediator->GetGimmickTrees();

	//m_sky_flowers = m_mediator->GetGimmickSkyFlowers();

	//// アイテムの種類の総数を取得
	//m_id_num = m_mediator->GetGimmickIdNum();
}

void Gimmick::Update(const float delta_time)
{
	m_matrix = GetTransformMatrix();

	// マトリックス
	MV1SetMatrix(m_gimmick_data.s_model_hdl, m_matrix);

	tnl_sequence_.update(delta_time);

	// 毎フレームあかん
	//MoveFlower(delta_time);
}

void Gimmick::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_is_not_active)
	{		
		MV1DrawModel(m_gimmick_data.s_model_hdl);
	}
}

void Gimmick::LoadGimmickData(const Gimmick::sGimmickTypeInfo& gimmick_info)
{
	m_gimmick_data.s_model_hdl 
		= MV1LoadModel(gimmick_info.s_model_path.c_str());
		
	m_gimmick_data.s_texture_a_hdl 
		= LoadGraph(gimmick_info.s_texture_a_path.c_str());

	m_gimmick_data.s_texture_b_hdl
		= LoadGraph(gimmick_info.s_texture_b_path.c_str());
		
	MV1SetTextureGraphHandle(m_gimmick_data.s_model_hdl, 0
								, m_gimmick_data.s_texture_a_hdl, FALSE);
}

void Gimmick::Reset()
{
	m_pos = { 0,0,0 };
	m_is_not_active = false;
	m_is_draw_change = false;
	m_is_collision = false;
	m_emissive_value = 0.0f;
	//m_time_elapsed = 0.0f;
	m_emissive = { 0.3f,0.3f,0.3f,1 };
	// テクスチャを元に戻す
	MV1SetTextureGraphHandle(m_gimmick_data.s_model_hdl, 0
							 , m_gimmick_data.s_texture_a_hdl, FALSE);
}

void Gimmick::MoveFlower(const float delta_time)
{
	if (m_mediator->GetIsGimmickFlowerActive())
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
		tnl::Vector3 rot = { tnl::ToRadian( tnl::GetRandomDistributionFloat(0, 360))
							 ,tnl::ToRadian(tnl::GetRandomDistributionFloat(0, 360))
							 ,tnl::ToRadian(tnl::GetRandomDistributionFloat(0, 360)) };

		// 回転をランダムで決定
		tnl::Quaternion target_rot 
			= tnl::Quaternion::RotationRollPitchYawFromVector(rot);

		// 回転を適用
		m_rot.slerp(target_rot, 1);
	}
}

void Gimmick::MoveButterfly(const float delta_time)
{

}

bool Gimmick::SeqNormal(const float delta_time)
{
	if (m_is_hit)
	{
		tnl_sequence_.change(&Gimmick::SeqHit);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqHit(const float delta_time)
{
	// 射程内を出たらNormalに戻る
	if (!m_is_hit)
	{
		tnl_sequence_.change(&Gimmick::SeqNormal);
	}

	// 衝突発生
	if (m_is_collision)
	{
		m_mediator->SetIsScoreAdd(true);

		m_emissive_value = 0.6f;

		tnl_sequence_.change(&Gimmick::SeqLightUp);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() 
	{
		// ギミックをほんのり光らせる
		m_emissive_value += delta_time;

		m_emissive.r = m_emissive_value;
		m_emissive.g = m_emissive_value;
		m_emissive.b = m_emissive_value;

		m_emissive.a = 1.0f;

		if (m_emissive_value >= 0.6f)
		{
			m_emissive_value = 0.6f;
		}
	});

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqLightUp(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_collision = false;
	}

	if (m_emissive_value == 1)
	{		
		tnl_sequence_.change(&Gimmick::SeqLightDown);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		// ギミックをほんのり光らせる
		m_emissive_value += delta_time;

		m_emissive.r = m_emissive_value;
		m_emissive.g = m_emissive_value;
		m_emissive.b = m_emissive_value;

		m_emissive.a = 1.0f;

		if (m_emissive_value >= 1)
		{
			m_emissive_value = 1;
		}
	});

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqLightDown(const float delta_time)
{
	if (m_emissive_value == 0.5f)
	{
		tnl_sequence_.change(&Gimmick::SeqChangeEnd);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		// ギミックをほんのり光らせる
		m_emissive_value -= delta_time;

		m_emissive.r = m_emissive_value;
		m_emissive.g = m_emissive_value;
		m_emissive.b = m_emissive_value;

		m_emissive.a = 1.0f;

		if (m_emissive_value <= 0.5f)
		{
			m_emissive_value = 0.5f;
		}
	});

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqChangeEnd(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		// テクスチャを変える
		MV1SetTextureGraphHandle(m_gimmick_data.s_model_hdl, 0
								, m_gimmick_data.s_texture_b_hdl, FALSE);
	}

	if (!m_mediator->GetIsGimmickGroundActive())
	{
		tnl_sequence_.change(&Gimmick::SeqNormal);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}


//int Gimmick::RandomTexture()
//{
//	// ID 0 は除外
//	return tnl::GetRandomDistributionInt(1, m_id_num);
//}
//
//void Gimmick::ChangeTexture()
//{
//	int new_texture = RandomTexture();
//
//	// 新しいテクスチャ情報を取得
//	//Gimmick::sGimmickTypeInfo new_texture_id
//	//		= m_mediator->GetGimmickLoadInfoById(new_texture);
//
//	// 古いテクスチャを削除
//	DeleteGraph(m_gimmick_data.s_texture_a_hdl);
//
//	// 新しいテクスチャを読み込み
//	//m_gimmick_data.s_texture_hdl 
//	//	= LoadGraph(new_texture_id.s_texture_path.c_str());
//
//	//// テクスチャをモデルに適用
//	//MV1SetTextureGraphHandle(m_gimmick_data.s_model_hdl, 0, m_gimmick_data.s_texture_hdl, FALSE);
//}