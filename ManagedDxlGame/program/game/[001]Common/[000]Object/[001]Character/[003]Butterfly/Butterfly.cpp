#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Butterfly.h"


Butterfly::Butterfly()
{
	m_pos = { 0, 0, 0 };
	// モデルをカメラ座標に反映させるため、目にみえないメッシュを生成
	m_mesh = dxe::Mesh::CreateSphereMV(0.001f);
	// 5倍に拡大（変更頻度も少ないため固定値）
	m_scale = { 5 };
}

Butterfly::~Butterfly()
{
	// モデルのアンロード
	MV1DeleteModel(m_model_hdl);

	m_paras.clear();
}

void Butterfly::Initialize()
{
	m_model_hdl = m_mediator->GetButterflyModelHdl();

	m_anim_index = MV1AttachAnim(m_model_hdl, 0);

	m_time_count = MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_index);

	SetLight(m_model_hdl);

	m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));

	m_paras = m_mediator->GetButterflyParameters();
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
		// 255 : 完全な発光
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		MV1DrawModel(m_model_hdl);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Butterfly::AnimMove(const float delta_time)
{
	// idleアニメーション更新処理
	m_elapsed_time += m_paras[1].s_num * delta_time;

	if (m_elapsed_time > m_time_count)
	{
		m_elapsed_time -= m_time_count;
	}

	MV1SetAttachAnimTime(m_model_hdl, 0, m_elapsed_time);
}

void Butterfly::MoveStraightHeight(const float delta_time)
{
	m_pos.z += m_paras[0].s_num * delta_time;
}

void Butterfly::MoveStraightWidth(const float delta_time)
{
	m_pos.x -= m_paras[0].s_num * delta_time;
}

void Butterfly::MoveRound(const float delta_time)
{
	// プレイヤーの位置を取得して中心座標とする
	tnl::Vector3 center_pos = m_mediator->GetCinemaPlayerPos();

	// 移動時間の更新
	m_elapsed_time_circle += delta_time;

	// 現在のフェーズの進行度合いを計算
	float progress = m_elapsed_time_circle / m_paras[6].s_num;

	// 角度の計算
	// 360 : プレイヤーを中心とした円運動のため固定値
	float angle = progress * tnl::ToRadian(360.0f);

	// 円運動
	m_pos.x = center_pos.x + sin(angle) * m_paras[5].s_num;
	m_pos.z = center_pos.z + cos(angle) * m_paras[5].s_num;

	// Y軸上昇の処理
	m_pos.y += delta_time * m_paras[7].s_num;

	// 進行方向を算出
	m_next_direction
		= tnl::Vector3(sin(angle + delta_time * m_paras[0].s_num), 0
						, cos(angle + delta_time * m_paras[0].s_num));

	// 進行方向に向かって回転
	tnl::Quaternion direction_rot
		= tnl::Quaternion::LookAt(m_pos, m_pos + m_next_direction
									, tnl::Vector3(0, 1, 0));

	// 体を傾ける回転の適用
	tnl::Quaternion tilt_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1)
										, tnl::ToRadian(m_paras[8].s_num));

	// 進行方向の回転と体を傾ける回転を組み合わせる
	m_rot = direction_rot * tilt_rot;
}

bool Butterfly::SeqMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_pos = { m_paras[2].s_num,m_paras[3].s_num,m_paras[4].s_num };

		m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));
	}

	if (abs(m_pos.x - m_mediator->GetCinemaPlayerPos().x) < m_to_player_distance)
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
	if (m_pos.y > m_paras[9].s_num)
	{
		// フェードアウト処理
		// フレームごとの透明度の減少量
		// 例: 0.5fは1秒間に半分の透明度になる
		float fade_out_speed = m_paras[10].s_num * delta_time; 

		// 現在の透明度を取得
		float current_opacity = MV1GetOpacityRate(m_model_hdl);

		// 透明度を更新
		float new_opacity = current_opacity - fade_out_speed;

		if (new_opacity < m_paras[11].s_num)
		{
			// 透明フラグを立てる
			m_is_clear = true;
		}

		// 透明度が負の値にならないように調整
		if (new_opacity < 0)
		{
			new_opacity = 0;

			m_is_clear = false;

			m_is_cinema_active = false;
		}

		// 新しい透明度をモデルに適用
		MV1SetOpacityRate(m_model_hdl, new_opacity);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveRound(delta_time);
	});

	TNL_SEQ_CO_END;
}