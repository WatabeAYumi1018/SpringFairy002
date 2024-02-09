#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PlayerMove.h"


void PlayerMove::Update(float delta_time)
{
	m_game_pos = m_mediator->GetPlayerPos();
	m_rot = m_mediator->GetPlayerRot();

	tnl_sequence_.update(delta_time);

	m_mediator->SetPlayerPos(m_game_pos);
	m_mediator->SetPlayerRot(m_rot);
}

bool PlayerMove::PushButton()
{
	// �����L�[���͂�ϐ��ɑ��
	bool up = tnl::Input::IsKeyDown(eKeys::KB_UP);
	bool down = tnl::Input::IsKeyDown(eKeys::KB_DOWN);
	bool right = tnl::Input::IsKeyDown(eKeys::KB_RIGHT);
	bool left = tnl::Input::IsKeyDown(eKeys::KB_LEFT);

	// ��
	if (up)
	{
		direction = eDirection::e_front;

		if (right)
		{
			direction = eDirection::e_front_right;
		}
		else if (left)
		{
			direction = eDirection::e_front_left;
		}

		return true;
	}
	// ��
	else if (down)
	{
		direction = eDirection::e_back;

		if (right)
		{
			direction = eDirection::e_back_right;
		}
		else if (left)
		{
			direction = eDirection::e_back_left;
		}

		return true;
	}
	// �E
	else if (right)
	{
		direction = eDirection::e_right;

		if (up)
		{
			direction = eDirection::e_front_right;
		}
		else if (down)
		{
			direction = eDirection::e_back_right;
		}

		return true;
	}
	// ��
	else if (left)
	{
		direction = eDirection::e_left;

		if (up)
		{
			direction = eDirection::e_front_left;
		}
		else if (down)
		{
			direction = eDirection::e_back_left;
		}

		return true;
	}

	return false;
}

void PlayerMove::MoveMatrix(float delta_time)
{
	// �����o�H�ɂ��ړ��Ɖ�]�̍X�V
	m_mediator->MoveAstarCharaUpdatePos(delta_time, m_game_pos);
	m_mediator->MoveAstarCharaUpdateRot(delta_time, m_game_pos, m_rot);

	if (PushButton())
	{
		ControlMoveMatrix(delta_time);
	}
}

void PlayerMove::ControlMoveMatrix(float delta_time)
{
	float move_speed = m_mediator->GetPlayerMoveSpeed();
	float move_rot = m_mediator->GetPlayerMoveRot();

	// �ړ�������������
	tnl::Vector3 move_direction = { 0, 0, 0 };
	// �J�����̑O�����ƉE�������擾
	tnl::Vector3 camera_forward = m_mediator->GetCameraForward();
	tnl::Vector3 camera_right = m_mediator->GetCameraRight();

	// �X�������Z�b�g�i���������ɖ߂��j
	m_target_rot 
		= tnl::Quaternion::LookAtAxisY(m_game_pos, m_game_pos + tnl::Vector3(0, 0, 1));
	// �X�΂̏�����
	tnl::Quaternion tilt_rotation;
	// �X����p�x
	float tilt_angle = 0.05f;

	if (tnl::Input::IsKeyDown(eKeys::KB_UP))
	{
		move_direction.y += delta_time * 10;

		// ���ɌX����
		tilt_rotation
			= tnl::Quaternion::RotationAxis(camera_right, -tilt_angle);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT))
	{
		move_direction += camera_right;

		// �E�����ɌX����
		tilt_rotation 
			= tnl::Quaternion::RotationAxis(camera_forward, -tilt_angle);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT))
	{
		move_direction -= camera_right;

		// �������ɌX����
		tilt_rotation 
			= tnl::Quaternion::RotationAxis(camera_forward, tilt_angle);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN))
	{
		if (m_mediator->GetPlayerLookSideRight()
			|| m_mediator->GetPlayerLookSideLeft())
		{
			move_direction.y -= delta_time / 10;

			// �X���x����傫������
			tilt_rotation
				= tnl::Quaternion::RotationAxis(camera_right, tilt_angle * 3);
		}
		else
		{
			move_direction.y -= delta_time * 10;

			// �O�ɌX��
			tilt_rotation
				= tnl::Quaternion::RotationAxis(camera_right, tilt_angle);
		}
	}

	// �ړ������̐��K���Ƒ��x�̓K�p
	if (move_direction.length() > 0)
	{
		// �ړ������𐳋K�����đ��x����Z
		move_direction
			= tnl::Vector3::Normalize(move_direction) * move_speed * delta_time;
	}
	// �v���C���[�̈ʒu���X�V
	m_game_pos += move_direction;

	// ���݂̎p���ɌX�΂�K�p
	m_target_rot = m_rot * tilt_rotation;
	// ���炩�ȉ�]���X�V
	m_rot.slerp(m_target_rot, delta_time * move_rot);
}

void PlayerMove::SaltoActionMatrix(float delta_time)
{
	float salto_total_time = m_mediator->GetPlayerSaltoTotalTime();
	float salto_radius = m_mediator->GetPlayerSaltoRadius();
	float salt_move_speed = m_mediator->GetPlayerSaltoMoveSpeed();

	m_salto_elapsed_time += delta_time;

	// ���Ԃ�̑S�̂̐i�s����
	float angle = (m_salto_elapsed_time / salto_total_time) 
					* 2 * tnl::ToRadian(180);

	// ���Ԃ�̋O���ɉ��������W�X�V
	m_game_pos.y = m_game_pos.y + sin(angle) * salto_radius;
	m_game_pos.z = m_game_pos.z + cos(angle) * salto_radius;

	// �X�������Z�b�g�i���������ɖ߂��j
	m_target_rot = tnl::Quaternion::LookAtAxisY(m_game_pos, m_game_pos + tnl::Vector3(0, 0, 1));

	tnl::Quaternion salt_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(-1, 0, 0), angle);

	m_target_rot *= salt_rot;

	// ���݂̉�]����ڕW�̉�]�Ɍ�����slerp���s��
	m_rot.slerp(m_target_rot, delta_time * salt_move_speed);
}

bool PlayerMove::SeqNormal(const float delta_time)
{
	if (m_mediator->GetEventLane().s_id == 5)
	{
		tnl_sequence_.change(&PlayerMove::SeqStop);
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
		// ���b�ԍ��W�X�V���~
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
	if(m_game_pos.y >= 500)
	{
		tnl_sequence_.change(&PlayerMove::SeqNormal);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
		// y���W���㏸
		m_game_pos.y += delta_time * 100;
	});

	TNL_SEQ_CO_END;
}

bool PlayerMove::SeqDownMove(const float delta_time)
{
	if(m_game_pos.y <= 0)
	{
		m_game_pos.y = 0;

		tnl_sequence_.change(&PlayerMove::SeqNormal);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
		// y���W�����~
		m_game_pos.y -= delta_time * 50;
	});

	TNL_SEQ_CO_END;
}

bool PlayerMove::SeqSaltoAction(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_game_pos = m_mediator->GetPlayerPos();
		m_rot = m_mediator->GetPlayerRot();
	}

	float salto_total_time = m_mediator->GetPlayerSaltoTotalTime();

	// �����܂Ń��[�v
	TNL_SEQ_CO_TIM_YIELD_RETURN(salto_total_time, delta_time, [&]()
	{
		SaltoActionMatrix(delta_time);
	});

	m_salto_elapsed_time = 0;

	tnl_sequence_.change(&PlayerMove::SeqNormal);

	TNL_SEQ_CO_END;
}


//bool PlayerMove::SeqGround(const float delta_time)
//{
//	if (tnl_sequence_.isStart())
//	{
//		m_stage_phase = m_mediator->GetNowStagePhaseState();
//	}
//
//	// �t�F�[�Y���ȍ~���A�󒆂ɂȂ�����󒆎��s������
//	if (m_stage_phase != m_mediator->GetNowStagePhaseState())
//	{
//		tnl_sequence_.change(&PlayerMove::SeqFly);
//	}
//
//	// �����܂Ń��[�v
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		DrawStringEx(0, 0, 1, "ground");
//
//		if (PushButton()) 
//		{
//			GroundMoveMatrix(delta_time);
//		}
//	});
//
//	TNL_SEQ_CO_END;
//}

// �v���C���[�̊�{�����͐���
// �������A�G�����鎞�͓G�̕����������B�i�E�ɓG������ΉE�ɂX�O�x��]�j
// �܂�A�G���o�ꂵ�������x�N�g�����v���C���[�̐��ʂƂ���

//void PlayerMove::GroundMoveMatrix(float delta_time)
//{
//	tnl::Vector3 pos = m_mediator->GetPlayerPos();
//	tnl::Quaternion rot = m_mediator->GetPlayerRot();
//
//	// �ړ��ɂ��o��
//	float move_elapsed = delta_time * m_move_speed;
//
//	if (direction == eDirection::front)
//	{
//		pos.z += move_elapsed;
//
//		m_target_rot
//			= tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(0, 0, 1));
//	}
//	else if (direction == eDirection::back)
//	{
//		pos.z -= move_elapsed;
//
//		m_target_rot
//			= tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(0, 0, -1));
//	}
//	else if (direction == eDirection::right)
//	{
//		pos.x += move_elapsed;
//
//		m_target_rot
//			= tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(1, 0, 0));
//	}
//	else if (direction == eDirection::left)
//	{
//		pos.x -= move_elapsed;
//
//		m_target_rot
//			= tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(-1, 0, 0));
//	}
//	else if (direction == eDirection::front_right)
//	{
//		pos.x += move_elapsed;
//		pos.z += move_elapsed;
//
//		m_target_rot
//			= tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(1, 0, 1));
//	}
//	else if (direction == eDirection::front_left)
//	{
//		pos.x -= move_elapsed;
//		pos.z += move_elapsed;
//
//		m_target_rot
//			= tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(-1, 0, 1));
//	}
//	else if (direction == eDirection::back_right)
//	{
//		pos.x += move_elapsed;
//		pos.z -= move_elapsed;
//
//		m_target_rot
//			= tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(1, 0, -1));
//	}
//	else if (direction == eDirection::back_left)
//	{
//		pos.x -= move_elapsed;
//		pos.z -= move_elapsed;
//
//		m_target_rot
//			= tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(-1, 0, -1));
//	}
//
//	// ���݂̉�]��ڕW�̉�]�Ɍ�����slerp�ŕ��
//	rot.slerp(m_target_rot, delta_time * m_move_rotation);
//
//	// ���W�A��]�̍X�V
//	m_mediator->SetPlayerPos(pos);
//	m_mediator->SetPlayerRot(rot);
//}

