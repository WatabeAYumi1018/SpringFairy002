#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PlayerMove.h"


void PlayerMove::Update(const float delta_time)
{
	m_pos = m_mediator->GetPlayerPos();
	m_rot = m_mediator->GetPlayerRot();

	tnl_sequence_.update(delta_time);

	m_mediator->SetPlayerPos(m_pos);
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
		m_direction = Character::eDirection::e_front;

		if (right)
		{
			m_direction = Character::eDirection::e_front_right;
		}
		else if (left)
		{
			m_direction = Character::eDirection::e_front_left;
		}

		return true;
	}
	// ��
	else if (down)
	{
		m_direction = Character::eDirection::e_back;

		if (right)
		{
			m_direction = Character::eDirection::e_back_right;
		}
		else if (left)
		{
			m_direction = Character::eDirection::e_back_left;
		}

		return true;
	}
	// �E
	else if (right)
	{
		m_direction = Character::eDirection::e_right;

		if (up)
		{
			m_direction = Character::eDirection::e_front_right;
		}
		else if (down)
		{
			m_direction = Character::eDirection::e_back_right;
		}

		return true;
	}
	// ��
	else if (left)
	{
		m_direction = Character::eDirection::e_left;

		if (up)
		{
			m_direction = Character::eDirection::e_front_left;
		}
		else if (down)
		{
			m_direction = Character::eDirection::e_back_left;
		}

		return true;
	}

	return false;
}

void PlayerMove::MoveMatrix(const float delta_time)
{
	// �����o�H�ɂ��ړ��Ɖ�]�̍X�V
	m_mediator->MoveAstarCharaUpdatePos(delta_time, m_pos);
	m_mediator->MoveAstarCharaUpdateRot(delta_time, m_pos, m_rot);

	if (PushButton())
	{
		ControlMoveMatrix(delta_time);
	}
}

void PlayerMove::ControlMoveMatrix(const float delta_time)
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
		= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));
	// �X�΂̏�����
	tnl::Quaternion tilt_rotation;

	if (tnl::Input::IsKeyDown(eKeys::KB_UP))
	{
		move_direction.y += delta_time * m_move_high_and_low_speed;

		// ���ɌX����
		tilt_rotation
			= tnl::Quaternion::RotationAxis(camera_right, -m_rot_angle);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT))
	{
		move_direction += camera_right;

		// �E�����ɌX����
		tilt_rotation 
			= tnl::Quaternion::RotationAxis(camera_forward, -m_rot_angle);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT))
	{
		move_direction -= camera_right;

		// �������ɌX����
		tilt_rotation 
			= tnl::Quaternion::RotationAxis(camera_forward, m_rot_angle);
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN))
	{
		if (m_mediator->GetPlayerLookSideRight()
			|| m_mediator->GetPlayerLookSideLeft())
		{
			// �T�C�h�������Ă��鎞�͌X�����傫������
			move_direction.y -= delta_time / m_side_rot_rate;

			// 3 : �X����i�����ł����g�p���Ȃ����l)
			// ���{���̓f�o�b�O�ŊO������ݒ�ł���悤�ɂ���̂��D�܂���
			float tilt_rot_rate = 3.0f;

			// �X���x����傫������
			tilt_rotation
				= tnl::Quaternion::RotationAxis(camera_right, m_rot_angle * tilt_rot_rate);
		}
		else
		{
			move_direction.y -= delta_time * m_move_high_and_low_speed;

			// �O�ɌX��
			tilt_rotation
				= tnl::Quaternion::RotationAxis(camera_right, m_rot_angle);
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
	m_pos += move_direction;

	// ���݂̎p���ɌX�΂�K�p
	m_target_rot = m_rot * tilt_rotation;
	// ���炩�ȉ�]���X�V
	m_rot.slerp(m_target_rot, delta_time * move_rot);
}

void PlayerMove::SaltoActionMatrix(const float delta_time)
{
	float salto_total_time = m_mediator->GetPlayerSaltoTotalTime();
	float salto_radius = m_mediator->GetPlayerSaltoRadius();
	float salt_move_speed = m_mediator->GetPlayerSaltoMoveSpeed();

	m_salto_elapsed_time += delta_time;

	// ���Ԃ�̑S�̂̐i�s����
	// 180 : �����̊p�x��2�{�Ƃ���
	float angle = (m_salto_elapsed_time / salto_total_time) 
					* 2 * tnl::ToRadian(180.0f);

	// ���Ԃ�̋O���ɉ��������W�X�V
	m_pos.y = m_pos.y + sin(angle) * salto_radius;
	m_pos.z = m_pos.z + cos(angle) * salto_radius;

	// �X�������Z�b�g�i���������ɖ߂��j
	m_target_rot
		= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));

	tnl::Quaternion salt_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(-1, 0, 0), angle);

	m_target_rot *= salt_rot;

	// ���݂̉�]����ڕW�̉�]�Ɍ�����slerp���s��
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
		// 5�b�ԍ��W�X�V���~
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]()
	{
		// 10�b�Ԕ{���ō��W�X�V
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

		// y���W���㏸
		// 1000 : �㏸���x
		// ���{���̓f�o�b�O�ŊO������ݒ�ł���悤�ɂ���̂��D�܂���
		// �@�܂����������f���Ă��Ȃ����߁A���̂Ƃ���͒��ړ���
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

		// y���W�����~
		// 50 : ���~���x
		// ���{���̓f�o�b�O�ŊO������ݒ�ł���悤�ɂ���̂��D�܂���
		// �@�܂����������f���Ă��Ȃ����߁A���̂Ƃ���͒��ړ���
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

	// �����܂Ń��[�v
	TNL_SEQ_CO_TIM_YIELD_RETURN(salto_total_time, delta_time, [&]()
	{
		SaltoActionMatrix(delta_time);
	});

	m_salto_elapsed_time = 0;

	tnl_sequence_.change(&PlayerMove::SeqNormal);

	TNL_SEQ_CO_END;
}


