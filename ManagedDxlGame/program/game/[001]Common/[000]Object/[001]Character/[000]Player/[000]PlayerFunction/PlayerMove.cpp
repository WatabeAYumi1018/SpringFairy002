#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PlayerMove.h"


void PlayerMove::Update(float delta_time)
{
	m_pos = m_mediator->GetPlayerPos();
	m_rot = m_mediator->GetPlayerRot();

	tnl_sequence_.update(delta_time);

	m_mediator->SetPlayerPos(m_pos);
	m_mediator->SetPlayerRot(m_rot);
}

bool PlayerMove::PushButton()
{
	// 方向キー入力を変数に代入
	bool up = tnl::Input::IsKeyDown(eKeys::KB_UP);
	bool down = tnl::Input::IsKeyDown(eKeys::KB_DOWN);
	bool right = tnl::Input::IsKeyDown(eKeys::KB_RIGHT);
	bool left = tnl::Input::IsKeyDown(eKeys::KB_LEFT);

	// 上
	if (up)
	{
		direction = Character::eDirection::e_front;

		if (right)
		{
			direction = Character::eDirection::e_front_right;
		}
		else if (left)
		{
			direction = Character::eDirection::e_front_left;
		}

		return true;
	}
	// 下
	else if (down)
	{
		direction = Character::eDirection::e_back;

		if (right)
		{
			direction = Character::eDirection::e_back_right;
		}
		else if (left)
		{
			direction = Character::eDirection::e_back_left;
		}

		return true;
	}
	// 右
	else if (right)
	{
		direction = Character::eDirection::e_right;

		if (up)
		{
			direction = Character::eDirection::e_front_right;
		}
		else if (down)
		{
			direction = Character::eDirection::e_back_right;
		}

		return true;
	}
	// 左
	else if (left)
	{
		direction = Character::eDirection::e_left;

		if (up)
		{
			direction = Character::eDirection::e_front_left;
		}
		else if (down)
		{
			direction = Character::eDirection::e_back_left;
		}

		return true;
	}

	return false;
}

void PlayerMove::MoveMatrix(float delta_time)
{
	// 自動経路による移動と回転の更新
	m_mediator->MoveAstarCharaUpdatePos(delta_time, m_pos);
	m_mediator->MoveAstarCharaUpdateRot(delta_time, m_pos, m_rot);

	if (PushButton())
	{
		ControlMoveMatrix(delta_time);
	}
}

void PlayerMove::ControlMoveMatrix(float delta_time)
{
	float move_speed = m_mediator->GetPlayerMoveSpeed();
	float move_rot = m_mediator->GetPlayerMoveRot();

	// 移動方向を初期化
	tnl::Vector3 move_direction = { 0, 0, 0 };
	// カメラの前方向と右方向を取得
	tnl::Vector3 camera_forward = m_mediator->GetCameraForward();
	tnl::Vector3 camera_right = m_mediator->GetCameraRight();

	// 傾きをリセット（初期向きに戻す）
	m_target_rot 
		= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));
	// 傾斜の初期化
	tnl::Quaternion tilt_rotation;
	// 傾ける角度
	float tilt_angle = 0.05f;

	if (tnl::Input::IsKeyDown(eKeys::KB_UP))
	{
		move_direction.y += delta_time * 10;

		// 後ろに傾ける
		tilt_rotation
			= tnl::Quaternion::RotationAxis(camera_right, -tilt_angle);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT))
	{
		move_direction += camera_right;

		// 右方向に傾ける
		tilt_rotation 
			= tnl::Quaternion::RotationAxis(camera_forward, -tilt_angle);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT))
	{
		move_direction -= camera_right;

		// 左方向に傾ける
		tilt_rotation 
			= tnl::Quaternion::RotationAxis(camera_forward, tilt_angle);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN))
	{
		if (m_mediator->GetPlayerLookSideRight()
			|| m_mediator->GetPlayerLookSideLeft())
		{
			move_direction.y -= delta_time / 10;

			// 傾き度合を大きくする
			tilt_rotation
				= tnl::Quaternion::RotationAxis(camera_right, tilt_angle * 3);
		}
		else
		{
			move_direction.y -= delta_time * 10;

			// 前に傾く
			tilt_rotation
				= tnl::Quaternion::RotationAxis(camera_right, tilt_angle);
		}
	}

	// 移動方向の正規化と速度の適用
	if (move_direction.length() > 0)
	{
		// 移動方向を正規化して速度を乗算
		move_direction
			= tnl::Vector3::Normalize(move_direction) * move_speed * delta_time;
	}
	// プレイヤーの位置を更新
	m_pos += move_direction;

	// 現在の姿勢に傾斜を適用
	m_target_rot = m_rot * tilt_rotation;
	// 滑らかな回転を更新
	m_rot.slerp(m_target_rot, delta_time * move_rot);
}

void PlayerMove::SaltoActionMatrix(float delta_time)
{
	float salto_total_time = m_mediator->GetPlayerSaltoTotalTime();
	float salto_radius = m_mediator->GetPlayerSaltoRadius();
	float salt_move_speed = m_mediator->GetPlayerSaltoMoveSpeed();

	m_salto_elapsed_time += delta_time;

	// 宙返りの全体の進行時間
	float angle = (m_salto_elapsed_time / salto_total_time) 
					* 2 * tnl::ToRadian(180);

	// 宙返りの軌道に沿った座標更新
	m_pos.y = m_pos.y + sin(angle) * salto_radius;
	m_pos.z = m_pos.z + cos(angle) * salto_radius;

	// 傾きをリセット（初期向きに戻す）
	m_target_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));

	tnl::Quaternion salt_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(-1, 0, 0), angle);

	m_target_rot *= salt_rot;

	// 現在の回転から目標の回転に向けてslerpを行う
	m_rot.slerp(m_target_rot, delta_time * salt_move_speed);
}

bool PlayerMove::SeqNormal(const float delta_time)
{
	if (m_mediator->GetCurrentEventLane().s_id == 6)
	{
		tnl_sequence_.change(&PlayerMove::SeqStop);
	}

	if (m_mediator->GetCurrentEventLane().s_id == 14)
	{
		tnl_sequence_.change(&PlayerMove::SeqUpMove);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool PlayerMove::SeqStop(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
		// 数秒間座標更新を停止
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]()
	{
		MoveMatrix(delta_time);
	});

	tnl_sequence_.change(&PlayerMove::SeqNormal);

	TNL_SEQ_CO_END;
}

bool PlayerMove::SeqUpMove(const float delta_time)
{
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);

		// y座標を上昇
		m_pos.y += delta_time * 1000;
	});

	TNL_SEQ_CO_END;
}

bool PlayerMove::SeqDownMove(const float delta_time)
{
	if(m_pos.y <= 0)
	{
		m_pos.y = 0;

		tnl_sequence_.change(&PlayerMove::SeqNormal);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
		// y座標を下降
		m_pos.y -= delta_time * 50;
	});

	TNL_SEQ_CO_END;
}

bool PlayerMove::SeqSaltoAction(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_pos = m_mediator->GetPlayerPos();
		m_rot = m_mediator->GetPlayerRot();
	}

	float salto_total_time = m_mediator->GetPlayerSaltoTotalTime();

	// 押すまでループ
	TNL_SEQ_CO_TIM_YIELD_RETURN(salto_total_time, delta_time, [&]()
	{
		SaltoActionMatrix(delta_time);
	});

	m_salto_elapsed_time = 0;

	tnl_sequence_.change(&PlayerMove::SeqNormal);

	TNL_SEQ_CO_END;
}


