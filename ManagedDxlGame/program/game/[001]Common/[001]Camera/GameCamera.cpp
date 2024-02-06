#include "../../../wta_library/wta_Convert.h"
#include "GameCamera.h"
#include "../[002]Mediator/Mediator.h"
#include "../[000]Object/[001]Character/[000]Player/Player.h"


GameCamera::GameCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT){}


void GameCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	//// �C�x���g���̏ꍇ�`��𐧌��i�o��J�����j
	//if (m_mediator->GetEventLane().s_id == 1
	//	|| m_mediator->GetEventLane().s_id == 5
	//	|| m_mediator->GetEventLane().s_id == 9)
	//{
	//	m_is_active_game = false;
	//}

	tnl_sequence_.update(delta_time);
}

void GameCamera::IsInFlustum()
{
	int max = static_cast<int>(eFlustum::Max);

	for (int i = 0; i < max; ++i)
	{
		tnl::Vector3 player_pos = m_mediator->GetPlayerPos();
				
		float size = m_mediator->GetPlayerCollisionSize();

		tnl::Vector3 v 
			= getFlustumNormal(static_cast<dxe::Camera::eFlustum>(i));

		 // �t���X�^�����ʂƍŋߓ_�̌v�Z
		tnl::Vector3 nearest_point 
			= tnl::GetNearestPointPlane(player_pos, v, pos_);

		// �v���C���[�ƍŋߓ_�Ƃ̋������v�Z
		float distance = (nearest_point - player_pos).length();

		if (distance < size)
		{
			tnl::Vector3 direction;

			// �����ʂƂ̏Փ˂̏ꍇ
			if (i == static_cast<int>(dxe::Camera::eFlustum::Left))
			{
				// �J�����̉E�����ɕ␳
				direction = right();
			}
			// �E���ʂƂ̏Փ˂̏ꍇ
			else if (i == static_cast<int>(dxe::Camera::eFlustum::Right))
			{
				// �J�����̍������ɕ␳
				direction = left();
			}
			// �����ʂƂ̏Փ˂̏ꍇ
			else if (i == static_cast<int>(dxe::Camera::eFlustum::Bottom))
			{
				// �J�����̏�����ɕ␳
				direction = up();
			}
			// �㕽�ʂƂ̏Փ˂̏ꍇ
			else if (i == static_cast<int>(dxe::Camera::eFlustum::Top))
			{
				// �J�����̉������ɕ␳
				direction = -up();
			}

			// �v���C���[�ʒu��␳
			tnl::Vector3 new_pos = player_pos + direction * (size - distance);

			// ���W�X�V
			m_mediator->SetPlayerPos(new_pos);
		}
	}
}

tnl::Vector3 GameCamera::Lerp(const tnl::Vector3& start
							, const tnl::Vector3& end, float t)
{
	return start + (end - start) * t;
}

void GameCamera::ConditionType()
{
	switch (m_mediator->GetTargetCameraInfo().s_type)
	{
		case eCameraType::e_right_side:
		{
			tnl_sequence_.change(&GameCamera::SeqRightSide);
		
			break;
		}
		case eCameraType::e_left_side:
		{
			tnl_sequence_.change(&GameCamera::SeqLeftSide);

			break;
		}
		case eCameraType::e_right_side_back:
		{
			m_mediator->SetPlayerLookSideRight(true);

			tnl_sequence_.change(&GameCamera::SeqRightSide);

			break;
		}
		case eCameraType::e_left_side_back:
		{
			m_mediator->SetPlayerLookSideLeft(true);

			tnl_sequence_.change(&GameCamera::SeqLeftSide);

			break;
		}
		//case eCameraType::e_bottom:
		//{
		//	tnl_sequence_.change(&GameCamera::SeqBottom);
		//
		//	break;
		//}
		case eCameraType::e_rotate:
		{
			tnl_sequence_.change(&GameCamera::SeqRotate);
		
			break;
		}
		case eCameraType::e_front:
		{
			tnl_sequence_.change(&GameCamera::SeqFront);
		
			break;
		}
	}
}

void GameCamera::Fixed(const tnl::Vector3& offset)
{
	target_ = m_mediator->GetCameraTargetPlayerPos();

	pos_.x = target_.x + offset.x;
	pos_.y = target_.y + offset.y;
	pos_.z = target_.z + offset.z;
}

void GameCamera::ToSlide(const float delta_time, const tnl::Vector3& offset, float speed)
{
	// �ړI�̈ʒu���v�Z
	tnl::Vector3 target_pos
		= m_mediator->GetCameraTargetPlayerPos() + offset;

	// ��Ԃ��g�p���ăJ�����ʒu���X�V
	pos_ = Lerp(pos_, target_pos, delta_time * speed);
}

void GameCamera::Rotate(const float delta_time)
{
	// �O�����a
	float orbit_radius = 300.0f;
	// �O������
	float orbit_height = 400.0f;

	target_ = m_mediator->GetPlayerPos();

	// ��]�p�x�̍X�V
	m_rot_angle += delta_time;

	// �J�����ʒu�̌v�Z�i�v���C���[�̎�����~�O���ŉ�]�j
	pos_.x = target_.x + cos(m_rot_angle) * orbit_radius;
	pos_.y = target_.y + orbit_height;
	pos_.z = target_.z + sin(m_rot_angle) * orbit_radius;
}

bool GameCamera::SeqFixed(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = true;

		m_mediator->SetPlayerLookSideRight(false);

		m_mediator->SetPlayerLookSideLeft(false);

		tnl::Vector3 pos = m_mediator->GetCameraTargetPlayerPos();

		m_mediator->SetPlayerPos(pos);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		m_is_fixed = false;

		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	ConditionType();

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed({ 0,0,-400 });
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqRightSide(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = false;
	}

	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqRightSideToFix);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	// �T�C�h�փJ�������ړ�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		ToSlide(delta_time, { 400, 0, 0 }, 5);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed({ 400, 0, 0 });
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqRightSideToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		Fixed({ 400, 0, 0 });
	});

	// �J���������̈ʒu�ɖ߂�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToSlide(delta_time, { 0, 200, -400 }, 2);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);
	
	TNL_SEQ_CO_END;
}

bool GameCamera::SeqLeftSide(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = false;
	}

	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqLeftSideToFix);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	// �T�C�h�փJ�������ړ�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		ToSlide(delta_time, { -400, 0, 0 }, 5);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed({ -400, 0, 0 });
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqLeftSideToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		Fixed({ -400, 0, 0 });
	});

	// �J���������̈ʒu�ɖ߂�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToSlide(delta_time, { 0, 200, -400 }, 2);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqFront(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = false;
	}

	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqFrontToFix);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	// ���ʂփJ�������ړ�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.5f, delta_time, [&]()
	{
		ToSlide(delta_time, { 0, 0, -400 }, 3);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed({ 0, 0, -800 });
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqFrontToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		Fixed({ 0, 0, -800 });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToSlide(delta_time, { 0, 200, -400 }, 2);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqRotate(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = false;
	}

	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqRotateToFix);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Rotate(delta_time);
	});

	TNL_SEQ_CO_END;
}

// �v���C���[����̉�]����fix�ֈڍs
bool GameCamera::SeqRotateToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		Rotate(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(0.6f, delta_time, [&]()
	{
		ToSlide(delta_time, { 0, 200, -400 }, 2);
	});

	m_rot_angle = 0;

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}

// -----�f�o�b�O�p----- //

void GameCamera::Control(const float delta_time)
{
	// �}�E�X�̈ړ��ʂ��擾
	tnl::Vector3 mouse_velocity = tnl::Input::GetMouseVelocity();
	// �}�E�X���x�̒���
	float mouse_sensitivity = 0.1f;
	// �J�����̉�]
	float yaw = mouse_velocity.x * mouse_sensitivity;
	float pitch = mouse_velocity.y * mouse_sensitivity;
	// �J�����̉���]�iY����]�j
	pos_ = RotateAroundPlayer(pos_, target_, tnl::Vector3(0, 1, 0), yaw);
	// �J�����̏c��]�iX����]�j
	pos_ = RotateAroundPlayer(pos_, target_, right(), pitch);
	// �J�����̑O��ړ�
	float scroll = tnl::Input::GetMouseWheel();
	// �Y�[�����x
	float zoom_sensitivity = 0.5f;

	pos_ += forward() * scroll * zoom_sensitivity;
	// �J�����̌������X�V
	view_ = tnl::Matrix::LookAtLH(pos_, target_, up_);
}

tnl::Vector3 GameCamera::RotateAroundPlayer(const tnl::Vector3& point
	, const tnl::Vector3& pivot
	, const tnl::Vector3& axis
	, float angle)
{
	// ��]
	tnl::Quaternion rotation
		= tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(angle));
	// ��]�s��𐶐�
	tnl::Matrix rotation_matrix = tnl::Matrix::RotationQuaternion(rotation);
	// �_����]�s��ŕϊ�
	tnl::Vector3 transformed_point
		= tnl::Vector3::Transform(point - pivot, rotation_matrix);
	// �ϊ������_�Ƀs�{�b�g�����Z���čŏI�I�Ȉʒu�𓾂�
	return transformed_point + pivot;
}

bool GameCamera::SeqFollow(const float delta_time)
{
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		target_ = m_mediator->GetPlayerPos();

		pos_ = target_ + m_offset;
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqControl(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		target_ = m_mediator->GetPlayerPos();
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
	{
		tnl_sequence_.change(&GameCamera::SeqFixed);
	}
	
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Control(delta_time);

		if(target_.y < 100)
		{
			target_.y = 100;
		}
	});
	
	TNL_SEQ_CO_END;
}

//void GameCamera::Bottom()
//{
//	target_ = m_mediator->GetCameraTargetPlayerPos();
//
//	pos_.y = target_.y + 500;
//	pos_.z = target_.z;
//
//	//up_ = tnl::Vector3(0, 0, 1);
//}
//
//bool GameCamera::SeqBottom(const float delta_time)
//{
//	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
//	{
//		tnl_sequence_.change(&GameCamera::SeqBottomToFix);
//	}
//
//	// ��փJ�������ړ�
//	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
//	{
//		// �ړI�̈ʒu���v�Z
//		tnl::Vector3 target_pos
//			= tnl::Vector3(target_.x, target_.y + 500, target_.z);
//
//		// ��Ԃ��g�p���ăJ�����ʒu���X�V
//		pos_ = Lerp(pos_, target_pos, delta_time * 5);
//	});
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		Bottom();
//	});
//
//	TNL_SEQ_CO_END;
//}
//
//bool GameCamera::SeqBottomToFix(const float delta_time)
//{
//	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
//	{
//		Bottom();
//	});
//
//	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
//	{
//		ToFix(delta_time);
//	});
//
//	tnl_sequence_.change(&GameCamera::SeqFixed);
//
//	TNL_SEQ_CO_END;
//}

//bool GameCamera::SeqBottom(const float delta_time)
//{
//	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
//	{
//		up_ = tnl::Vector3(0, 1, 0);
//
//		tnl_sequence_.change(&GameCamera::SeqFixed);
//	}
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		target_ = m_mediator->GetPlayerPos();
//
//		pos_.y = target_.y - 500;
//		pos_.z = target_.z;
//
//		up_ = tnl::Vector3(0, 0, 1);
//	});
//
//	TNL_SEQ_CO_END;
//}