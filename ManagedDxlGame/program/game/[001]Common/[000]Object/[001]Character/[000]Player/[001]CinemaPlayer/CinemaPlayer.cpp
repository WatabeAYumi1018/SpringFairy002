
#include "../../../../[001]Camera/CinemaCamera.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "CinemaPlayer.h"


CinemaPlayer::CinemaPlayer()
{
	m_pos = { -400,0,0 };

	m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, -1));
}

CinemaPlayer::~CinemaPlayer()
{

}

void CinemaPlayer::Initialize()
{
	m_mediator->InitializePlayerDraw();

	m_model_hdl = m_mediator->GetPlayerModelCinemaHdl();

	SetLight(m_model_hdl);
}

void CinemaPlayer::Update(const float delta_time)
{
	tnl_sequence_.update(delta_time);

	if (!m_mediator->GetIsActiveGameCamera())
	{
		if (m_is_idle)
		{
			m_mediator->CinemaPlayerAnimIdle(delta_time);
		}
		else if (m_is_move)
		{
			m_mediator->CinemaPlayerAnimMove(delta_time);
		}
		else if (m_is_dance)
		{
			m_mediator->CinemaPlayerAnimDance(delta_time);
		}
	}
	
	// 回転と座標から行列を計算
	m_matrix = CalcMatrix();

	// モデルに行列を適用
	MV1SetMatrix(m_model_hdl, m_matrix);

	// プレイヤーの座標をデバッグ表示
	DrawStringEx(0, 0, -1, "PlayerPos_x:%f", m_pos.x);
	DrawStringEx(0, 20, -1, "PlayerPos_y:%f", m_pos.y);
	DrawStringEx(0, 40, -1, "PlayerPos_z:%f", m_pos.z);

}

void CinemaPlayer::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// モデル描画処理
	MV1DrawModel(m_model_hdl);
}

// Lerp関数の定義（線形補間）
float CinemaPlayer::Lerp(float start, float end, float t)
{
	return start + (end - start) * t;
}

void CinemaPlayer::MoveRound(const float delta_time)
{
	// 時間経過の更新
	m_elapsed_time_circle += delta_time;

	// 中心座標
	tnl::Vector3 center_pos = { 0, 0, 0 };

	tnl::Vector3 end_pos = { -50, -150, 0 };

	// 円運動の半径。初期座標と中心座標から計算
	float radius
		= sqrt(pow(m_pos.x - center_pos.x, 2) + pow(m_pos.z - center_pos.z, 2));

	// 円運動の更新
	float angle 
		= (m_elapsed_time_circle / m_total_time) * tnl::ToRadian(360);

	// x座標の位置を計算
	if (angle >= tnl::ToRadian(360))
	{
		m_pos.x = end_pos.x;
	}
	else
	{
		m_pos.x = center_pos.x + sin(angle) * radius;
	}
	// y座標の位置を計算
	if (angle >= tnl::ToRadian(360))
	{
		m_pos.y = end_pos.y;
	}
	else
	{
		// 現在の角度に応じてY軸の位置を計算
		m_pos.y = (1 - (angle / tnl::ToRadian(360))) * m_pos.y 
					+ (angle / tnl::ToRadian(360)) * end_pos.y;
	}

	// Z座標の位置を計算
	if (angle >= tnl::ToRadian(360))
	{
		m_pos.z = end_pos.z;
	}
	else
	{
		m_pos.z = center_pos.z + cos(angle) * radius;
	}

	// 円運動中の移動方向を向くための回転を計算
	tnl::Vector3 nextPos 
		= center_pos + tnl::Vector3(sin(angle + tnl::ToRadian(90)), 0
									, cos(angle + tnl::ToRadian(90)));
	// 向きを変える
	tnl::Quaternion direction_rot
		= tnl::Quaternion::LookAt(m_pos, nextPos, tnl::Vector3(0, 1, 0));

	// X軸周りに一定角度傾ける
	tnl::Quaternion tilt_rot 
		= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(50));

	// 回転の組み合わせ
	m_rot = direction_rot * tilt_rot;
}

void CinemaPlayer::MoveDown(const float delta_time)
{
	static float total_rot = 0.0f; // 総回転角度
	const float rot_speed = 5; 

	// 総回転角度を更新
	total_rot += rot_speed * delta_time;

	// 720度（4πラジアン）を超えたらリセット
	if (total_rot > tnl::ToRadian(720))
	{
		total_rot -= tnl::ToRadian(720);
	}

	// Y軸周りの回転クォータニオンを生成
	tnl::Quaternion axis_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 1, 0), total_rot);

	// Z軸周りに30度傾けるクォータニオンを生成
	tnl::Quaternion tilt_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(30));

	// 既存の回転と傾斜の回転を合成
	tnl::Quaternion comb_rot = axis_rot * tilt_rot;

	// Slerpで滑らかに回転を適用
	m_rot.slerp(comb_rot, 0.5f);
}

void CinemaPlayer::MoveBackCenter(const float delta_time)
{
	static tnl::Vector3 start_pos = m_pos;
	tnl::Vector3 end_pos = { 0, 0, 0 };
	static float total_time = 2.0f;
	static float elapsed_time = 0.0f;

	if (elapsed_time < total_time)
	{
		elapsed_time += delta_time * 5;
		float phase = elapsed_time / total_time;

		// Y座標をサイン波で補間（大きな弧を描く）
		float amplitude = 20.0f; // 弧の高さ
		m_pos.y = start_pos.y + sin(phase * tnl::ToRadian(180)) * amplitude; // サイン波の利用

		// 等加速運動での位置の補間
		m_pos.x = Lerp(start_pos.x, end_pos.x, phase);
		m_pos.y = Lerp(start_pos.y, end_pos.y, phase);
		m_pos.z = Lerp(start_pos.z, end_pos.z, phase);
	}
}

bool CinemaPlayer::SeqTrigger(const float delta_time)
{
	// １番のイベントの場合（登場カメラ）
	if (m_mediator->GetEventLane().s_id == 1)
	{
		// 最初の紹介
		tnl_sequence_.change(&CinemaPlayer::SeqSecond);
	}
	if (m_mediator->GetEventLane().s_id == 5)
	{
		// エリア２へ移行
		tnl_sequence_.change(&CinemaPlayer::SeqSecond);
	}
	if (m_mediator->GetEventLane().s_id == 9)
	{
		// エリア３へ移行
		tnl_sequence_.change(&CinemaPlayer::SeqThird);
	}

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqFirst(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_dance = true;
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		MoveRound(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, 1));

		m_is_dance = false;
		m_is_idle = true;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]() 
	{
		//
		tnl::Quaternion target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		m_rot.slerp(target_rot, delta_time * 10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		tnl::Quaternion back_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		// モデルを前かがみに傾ける
		tnl::Quaternion tilt_rot
			= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(45));

		// 回転合成
		tnl::Quaternion comb_rot =  tilt_rot * back_rot;

		m_rot.slerp(comb_rot, delta_time * 10);

		m_pos.y -= delta_time * 100;
		m_pos.z += delta_time * 500;	
	});

	m_is_idle = false;

	m_mediator->SetIsActiveGameCamera(true);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqSecond(const float delta_time)
{
	if(tnl_sequence_.isStart())
	{
		m_is_idle= true;
		m_pos = { 100,100,0 };
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		MoveDown(delta_time);
		m_pos.x -= delta_time * 150;
		m_pos.y -= delta_time * 150;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{	
		m_is_idle = false;
		m_is_move = true;

		// X軸周りに45度傾ける（前方に45度傾斜）
		m_rot = tnl::Quaternion::RotationAxis(tnl::Vector3(0, -1, -1), tnl::ToRadian(70));

		MoveBackCenter(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		m_is_move = false;
		m_is_idle = true;

		tnl::Quaternion target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, -1));

		m_rot.slerp(target_rot,0.1f);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_pos = { 0 };

		// emmisiveを少しずつ強くする
		m_emissive.r += delta_time;
		m_emissive.g += delta_time;
		m_emissive.b += delta_time;
		m_emissive.a = 1;

		if (m_emissive.r >= 1 && m_emissive.g >= 1 && m_emissive.b >= 1)
		{
			m_emissive.r = 1;
			m_emissive.g = 1;
			m_emissive.b = 1;
		}

		MV1SetMaterialEmiColor(m_model_hdl, 0, m_emissive);

		m_mediator->SetIsCinemaBackFog(true);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&](){});

	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		m_is_idle = false;	
		m_is_dance = true;
	});

	SetDefaultLightParameter("directional_light_parameter.bin");

	m_mediator->SetIsActiveGameCamera(true);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqThird(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(7, delta_time, [&]()
	{
		m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, 0));
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		tnl::Quaternion m_target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, -1));

		m_rot.slerp(m_target_rot, delta_time * 10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
		tnl::Quaternion m_target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		m_rot.slerp(m_target_rot, delta_time * 3);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		tnl::Quaternion m_target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, -1));

		m_rot.slerp(m_target_rot, delta_time * 10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		m_is_idle = false;
		m_is_dance = true;
	});

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}