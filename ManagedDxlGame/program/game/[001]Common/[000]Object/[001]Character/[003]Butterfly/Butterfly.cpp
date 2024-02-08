#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Butterfly.h"


Butterfly::Butterfly()
{
	m_pos = { 0,0,0 };

	// モデルをカメラ座標に反映させるため、目にみえないメッシュを生成
	m_mesh = dxe::Mesh::CreateSphereMV(0.001f);

	m_scale = { 5 };
}

Butterfly::~Butterfly()
{
	// モデルのアンロード
	MV1DeleteModel(m_model_hdl);
}

void Butterfly::Initialize()
{
	m_model_hdl = m_mediator->GetButterflyModelHdl();

	m_anim_index = MV1AttachAnim(m_model_hdl, 0);

	m_time_count = MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_index);

	SetLight(m_model_hdl);

	m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));

	//// エミッシブカラーを設定してモデルを発光させる
	//DxLib::COLOR_F emissive = {10.0f, 10.0f, 10.0f, 1 }; // 強い発光
	//
	//MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);

	//DxLib::COLOR_F diffuse = { 10,10,10,1 };

	//MV1SetMaterialDifColor(m_model_hdl, 0, diffuse);
}

void Butterfly::Update(const float delta_time)
{	
	AnimMove(delta_time);

	if (m_is_cinema_active)
	{
		tnl_sequence_.update(delta_time);
	}

	m_mesh->pos_ = m_pos;

	// 回転と座標から行列を計算
	m_matrix = CalcMatrix();

    // モデルに行列を適用
    MV1SetMatrix(m_model_hdl, m_matrix);
}

void Butterfly::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_is_op_active || m_is_cinema_active)
	{
		m_mesh->render(camera);

		// 描画モードを変更して、発光を強調
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		MV1DrawModel(m_model_hdl);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Butterfly::AnimMove(const float delta_time)
{
	// idleアニメーション更新処理
	m_elapsed_time += m_anim_speed * delta_time;

	if (m_elapsed_time > m_time_count)
	{
		m_elapsed_time -= m_time_count;
	}

	MV1SetAttachAnimTime(m_model_hdl, 0, m_elapsed_time);
}

void Butterfly::MoveRound(const float delta_time)
{
	// プレイヤーの位置を取得して中心座標とする
	tnl::Vector3 center_pos = m_mediator->GetCinemaPlayerPos();

	// 円運動の半径
	float radius = 200.0f;

	// 移動時間の更新
	m_elapsed_time_circle += delta_time;

	// 全体の動作時間
	const float total_time = 3.0f;

	// 現在のフェーズの進行度合いを計算
	float progress = m_elapsed_time_circle / total_time;

	// 角度の計算
	float angle = progress * tnl::ToRadian(360);

	// 円運動
	m_pos.x = center_pos.x + sin(angle) * radius;
	m_pos.z = center_pos.z + cos(angle) * radius;
	// Y軸上昇の処理
	m_pos.y += delta_time * 30 ; 

	// 進行方向を算出
	tnl::Vector3 next_direction 
		= tnl::Vector3(sin(angle + delta_time * m_speed), 0
					  , cos(angle + delta_time * m_speed));
	
	// 進行方向に向かって回転
	tnl::Quaternion direction_rot
		= tnl::Quaternion::LookAt(m_pos, m_pos + next_direction, tnl::Vector3(0, 1, 0));

	// 体を傾ける回転の適用
	tnl::Quaternion tilt_rot 
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(45));

	// 進行方向の回転と体を傾ける回転を組み合わせる
	m_rot = direction_rot * tilt_rot;
}

void Butterfly::MoveStraightHeight(const float delta_time)
{
	// 速度を計算
	float move_speed = m_speed * delta_time;

	m_pos.z += move_speed;
}

void Butterfly::MoveStraightWidth(const float delta_time)
{
	// 速度を計算
	float move_speed = m_speed * delta_time;

	m_pos.x -= move_speed;
}

bool Butterfly::SeqMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_pos = {500,0,0};

		m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));
	}

	if (abs(m_pos.x - m_mediator->GetCinemaPlayerPos().x) < 100)
	{
		tnl_sequence_.change(&Butterfly::SeqRound);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveStraightWidth(delta_time);	
	});

	TNL_SEQ_CO_END;
}

bool Butterfly::SeqRound(const float delta_time)
{
	if (m_pos.y > 150)
	{
		// フェードアウト処理
		// 透明度を下げる速度を定義（例: 0.5fは1秒間に半分の透明度になる）
		float fade_out_speed = 0.5f * delta_time; // フレームごとの透明度の減少量

		// 現在の透明度を取得
		float current_opacity = MV1GetOpacityRate(m_model_hdl);

		// 透明度を更新
		float new_opacity = current_opacity - fade_out_speed;
		// 透明度が負の値にならないように調整
		if (new_opacity < 0) new_opacity = 0; 

		// 新しい透明度をモデルに適用
		MV1SetOpacityRate(m_model_hdl, new_opacity);

		// 透明度が0になったら、シネマアクティブをfalseにしてフェードアウト完了
		if (new_opacity <= 0)
		{
			m_is_cinema_active = false;

			TNL_SEQ_CO_END;
		}
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveRound(delta_time);
	});

	TNL_SEQ_CO_END;
}