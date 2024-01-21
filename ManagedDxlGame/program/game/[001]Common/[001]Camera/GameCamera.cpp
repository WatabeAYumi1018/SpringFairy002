#include "../../../wta_library/wta_Convert.h"
#include "GameCamera.h"
#include "../[002]Mediator/Mediator.h"
#include "../[000]Object/[001]Character/[000]Player/Player.h"


GameCamera::GameCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT){}

void GameCamera::update(const float delta_time)
{
	//// �J�����̎p�����X�V
	//target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rot);
	//// �J�����̃A�b�p�[�x�N�g�����X�V
	//up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_rot);

	dxe::Camera::update(delta_time);

	tnl_sequence_.update(delta_time);

	//for (int i = 0; i < 6; ++i)
	//{
	//	tnl::Vector3 player_pos = m_mediator->GetPlayerPos();
	//	float size = m_mediator->GetPlayerCollisionSize();

	//	tnl::Vector3 v = getFlustumNormal(static_cast<dxe::Camera::eFlustum>(i));
	//	tnl::Vector3 np = tnl::GetNearestPointPlane(player_pos, v, pos_);
	//	float length = (np - player_pos).length();
	//	if (length < size)
	//	{
	//		tnl::Vector3 pos = np + (v * size);
	//		m_mediator->SetPlayerPos(pos);
	//	}
	//}


	//m_mediator->IsIntersectCameraFlustum(delta_time);
	
	//m_mediator->UpdateCameraFrustum();
	//
	//// ���W�f�o�b�O�p
	//DrawStringEx(0, 100, -1, "CameraPos_x:%f", pos_.x);
	//DrawStringEx(0, 120, -1, "CameraPos_y:%f", pos_.y);
	//DrawStringEx(0, 140, -1, "CameraPos_z:%f", pos_.z);
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
		case eCameraType::e_bottom:
		{
			tnl_sequence_.change(&GameCamera::SeqBottom);
		
			break;
		}
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

void GameCamera::Fixed()
{
	target_ = m_mediator->GetCameraTargetPlayerPos();

	pos_.x = target_.x;
	pos_.y = target_.y;
	pos_.z = target_.z + m_offset.z;
}

void GameCamera::Side(float offset)
{
	target_ = m_mediator->GetCameraTargetPlayerPos();

	pos_.x = target_.x + offset;
	pos_.y = target_.y;
	pos_.z = target_.z;
}

void GameCamera::ToSide(const float delta_time, float offset)
{
	// �ړI�̈ʒu���v�Z
	tnl::Vector3 target_pos
		= tnl::Vector3(target_.x + offset, target_.y, target_.z);

	// ��Ԃ��g�p���ăJ�����ʒu���X�V
	pos_ = Lerp(pos_, target_pos, delta_time * 5);
}

void GameCamera::ToFix(const float delta_time)
{
	// �ړI�̈ʒu���v�Z
	tnl::Vector3 target_pos
		= m_mediator->GetCameraTargetPlayerPos() + m_offset;

	// ��Ԃ��g�p���ăJ�����ʒu���X�V
	pos_ = Lerp(pos_, target_pos, delta_time * 2);
}

void GameCamera::Front()
{
	target_ = m_mediator->GetCameraTargetPlayerPos();

	pos_.x = target_.x;
	pos_.y = target_.y;
	pos_.z = target_.z - m_offset.z * 2;
}

void GameCamera::rotate(const float delta_time)
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
	pos_.y = target_.y + 400;
	pos_.z = target_.z + sin(m_rot_angle) * orbit_radius;
}

bool GameCamera::SeqFixed(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_mediator->SetPlayerLookSideRight(false);
		m_mediator->SetPlayerLookSideLeft(false);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	ConditionType();

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed();
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqRightSide(const float delta_time)
{
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqRightSideToFix);
	}

	// �T�C�h�փJ�������ړ�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		ToSide(delta_time,400);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Side(400);
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqRightSideToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		Side(400);
	});

	// �J���������̈ʒu�ɖ߂�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);
	
	TNL_SEQ_CO_END;
}

bool GameCamera::SeqLeftSide(const float delta_time)
{
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqLeftSideToFix);
	}

	// �T�C�h�փJ�������ړ�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		ToSide(delta_time, -400);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Side(-400);
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqLeftSideToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		Side(-400);
	});

	// �J���������̈ʒu�ɖ߂�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqFront(const float delta_time)
{
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqFrontToFix);
	}

	// ���ʂփJ�������ړ�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.5f, delta_time, [&]()
	{
		// �ړI�̈ʒu���v�Z
		tnl::Vector3 target_pos
			= tnl::Vector3(target_.x, target_.y, target_.z - m_offset.z);
		
		// ��Ԃ��g�p���ăJ�����ʒu���X�V
		pos_ = Lerp(pos_, target_pos, delta_time * 3);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Front();
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqFrontToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		Front();
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqRotate(const float delta_time)
{
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqRotateToFix);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		rotate(delta_time);
	});

	TNL_SEQ_CO_END;
}

// �v���C���[����̉�]����fix�ֈڍs
bool GameCamera::SeqRotateToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		rotate(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(0.6f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

	m_rot_angle = 0;

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}


//-----------//

void GameCamera::Bottom()
{
	target_ = m_mediator->GetCameraTargetPlayerPos();

	pos_.y = target_.y + 500;
	pos_.z = target_.z;

	//up_ = tnl::Vector3(0, 0, 1);
}

bool GameCamera::SeqBottom(const float delta_time)
{
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqBottomToFix);
	}

	// ��փJ�������ړ�
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		// �ړI�̈ʒu���v�Z
		tnl::Vector3 target_pos
			= tnl::Vector3(target_.x, target_.y + 500, target_.z);

		// ��Ԃ��g�p���ăJ�����ʒu���X�V
		pos_ = Lerp(pos_, target_pos, delta_time * 5);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Bottom();
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqBottomToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		Bottom();
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

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

//bool GameCamera::SeqCinematic(const float delta_time)
//{
//	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
//	{
//		tnl_sequence_.change(&GameCamera::SeqFixed);
//	}
//
//	//TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	//{
//	//	MoveRotation(delta_time);
//	//});
//
//	TNL_SEQ_CO_END;
//
//}


//UpdateFrustumPlane();	

//// �ǂ̎��J������؂�ւ��邩�A���̎��ɂǂ�ȓ����ɂ��邩���L�q
//// ��Ԃ��g�p���ăJ�����ʒu�ƃ^�[�Q�b�g���X�V
//float lerpRate = delta_time * 0.5f;
//pos_ = Lerp(pos_, m_mediator->GetPlayerPos(), lerpRate);
//target_ = Lerp(target_, m_mediator->GetPlayerPos(), lerpRate);

//for (int i = 0; i < 6; i++) {
//	DrawFrustumPlane(m_frustum_param[i].s_normal, m_frustum_param[i].s_d);
//}

//void OriginalCamera::DrawFrustumPlane(const tnl::Vector3& normal, float d)
//{
//	// ���ʂ̒��S�_���v�Z
//	tnl::Vector3 center = normal * d;
//
//	// �l�p�`�̒��_���v�Z�i�ȒP���̂��߁A���̃T�C�Y������j
//	float size = 100.0f; // �l�p�`�̃T�C�Y
//	// ���_�̌v�Z...
//
//	VECTOR center_vec = wta::ConvertToVECTOR(center);
//	
//	DrawSphere3D(center_vec, size, 32, -1, 1, true);
//}

//// �t���X�^���̊e���ʂ̖@���x�N�g�����v�Z���A
//// �萔���ł��̕��ʂ̈ʒu����肷�邱�Ƃɂ��A�t���X�^���̋��E���`
//void Camera::UpdateFrustumPlane()
//{
//	// �r���[�s��Ǝˉe�s�������
//	// �I�u�W�F�N�g�̐��E���W�n����2D��ʋ�Ԃւ̒��ړI�ȕϊ�
//	tnl::Matrix view_proj = view_ * proj_;
//
//	// ���s��̏�Z : ���W�ϊ��i��]�A�g��k���A���s�ړ��j
//	// ���s��̉��Z : ���W�ϊ��̍����i�����̍��W�ϊ�����x�ɍs���A�V�����x�N�g�������j
//
//	// ������
//	// �����ʂ̖@���x�N�g��(���ʂɑ΂��鐂���x�N�g��)���Z�o
//	// view_proj._11 �` view_proj._31 : �����s���1�s�ځi�J������Ԃɂ�����E�����x�N�g���j
//	// view_proj._12 �` view_proj._32 : �����s���2�s�ځi�J������Ԃɂ����������x�N�g���j
//	// view_proj._13 �` view_proj._33 : �����s���3�s�ځi�J������Ԃɂ�����O�����x�N�g���j
//	// view_proj._14 �` view_proj._34 : �����s���4�s�ځi�J������Ԃ̌��_����̕ϊ��x�N�g���j
//	// ���Z���邱�Ƃō����ʂ̖@���x�N�g�����Z�o�i�t���X�^���̍����ʂƑ��̕����Ƃ̋��E�j
//	m_frustum_param[0].s_normal = tnl::Vector3(view_proj._14 + view_proj._11,
//												view_proj._24 + view_proj._21,
//												view_proj._34 + view_proj._31);
//
//	// �t���X�^�����ʍ����ʂ̕������ɂ�����萔�����Z�o
//	// ������ : Ax+By+Cz+D=0 (A,B,C : �@���x�N�g���̐��� �E�@D : �萔��)
//	// ���ʂ� 0 ���傫���ꍇ: �_�͕��ʂ̈���̑��i�ʏ�́u�����v�j
//	// ���ʂ� 0 ��菬�����ꍇ: �_�͕��ʂ̑����̑��i�ʏ�́u�O���v�j
//	// ���ʂ� 0 �̏ꍇ: �_�͕��ʏ�
//	// _44 : Z���ɉ������[�x�i���s���j�̏����X�P�[��
//	// _41 : X���ɉ����������̈ʒu�����X�P�[��
//	// ���Z���邱�Ƃō����ʂ�3D��ԓ��łǂ̂悤�Ɉʒu���邩�����i�J�������猩�Ăǂꂾ���������j
//	m_frustum_param[0].s_d = view_proj._44 + view_proj._41;
//
//	// �E����
//	m_frustum_param[1].s_normal = tnl::Vector3(view_proj._14 - view_proj._11,
//												view_proj._24 - view_proj._21,
//												view_proj._34 - view_proj._31);
//	m_frustum_param[1].s_d = view_proj._44 - view_proj._41;
//
//	// �㕽��
//	m_frustum_param[2].s_normal = tnl::Vector3(view_proj._14 - view_proj._12,
//												view_proj._24 - view_proj._22,
//												view_proj._34 - view_proj._32);
//	m_frustum_param[2].s_d = view_proj._44 - view_proj._42;
//
//	// ������
//	m_frustum_param[3].s_normal = tnl::Vector3(view_proj._14 + view_proj._12,
//												view_proj._24 + view_proj._22,
//												view_proj._34 + view_proj._32);
//	m_frustum_param[3].s_d = view_proj._44 + view_proj._42;
//
//	// �ߕ���
//	// �ߕ��ʂ̓J�����̖@���x�N�g���͑O�����x�N�g���ƕ��s
//	m_frustum_param[4].s_normal = tnl::Vector3(view_proj._13,
//												view_proj._23,
//												view_proj._33);
//	m_frustum_param[4].s_d = view_proj._43;
//
//	// ������
//	m_frustum_param[5].s_normal = tnl::Vector3(view_proj._14 - view_proj._13,
//												view_proj._24 - view_proj._23,
//												view_proj._34 - view_proj._33);
//	m_frustum_param[5].s_d = view_proj._44 - view_proj._43;
//
//	// �e���ʂ̖@���x�N�g���𐳋K��
//	// �@���x�N�g���̒��������i�ʏ��1�j�ł��邱�Ƃ�ۏ؂��邱�ƂŁA
//	// �t���X�^���̕��ʂƃI�u�W�F�N�g�Ƃ̋����v�Z����т������̂ɂȂ�
//	// �_�ƕ��ʂƂ̋����́A�_�̈ʒu�x�N�g���Ɩ@���x�N�g���̓���
//	// �����Ē萔�������Z���邾���ŎZ�o�ł���
//	for (int i = 0; i < m_frustum_plane_num; i++)
//	{
//		m_frustum_param[i].s_normal.normalize();
//	}
//}
//
//bool Camera::IsInFrustum(const tnl::Vector3& pos)
//{
//	for (int i = 0; i < m_frustum_plane_num; i++)
//	{
//		// ���ς��v�Z���A�萔�������Z
//		// �_�ƕ��ʂƂ̋������Z�o
//		// �_�ƕ��ʂƂ̋�����0��菬�����ꍇ�A�_�͕��ʂ̊O���ɂ���
//		float dot = tnl::Vector3::Dot(m_frustum_param[i].s_normal, pos);
//
//		dot += m_frustum_param[i].s_d;
//
//		if (dot < 0)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//void Camera::ReturnPlayerPos(const tnl::Vector3& pos)
//{
//	// �t���X�^�����E�O�Ƀv���C���[�̍��W���ړ������ꍇ
//	if (!IsInFrustum(pos))
//	{
//		// �t���X�^���̊e�ʂƃv���C���[�̋������i�[����z��
//		float distance[4];
//		// �t���X�^���̊e�ʂƃv���C���[�̋������v�Z
//		for (int i = 0; i < m_frustum_plane_num; i++)
//		{
//			distance[i] = tnl::Vector3::Dot(m_frustum_param[i].s_normal, pos)
//						+ m_frustum_param[i].s_d;
//		}
//		// ��ԋ߂��t���X�^���̖ʂɃv���C���[��߂�
//		  // �t���X�^���̋��E�ɍł��߂����ʂ�������
//		int min_index 
//			= std::min_element(distance, distance + m_frustum_plane_num) - distance;
//		// �v���C���[�̍��W���t���X�^���̖ʂɖ߂�
//		tnl::Vector3 return_pos 
//			= pos - m_frustum_param[min_index].s_normal * distance[min_index];
//
//		m_mediator->SetPlayerPos(return_pos);
//	}
//}

//
//void OriginalCamera::DrawFrustumPlane()
//{
//	// �t�s��𐶐�
//	// �t�s��𐶐����邱�ƂŁA�r���[���W�n���烏�[���h���W�n�ւ̕ϊ����s��
//	tnl::Matrix inv_view_proj = tnl::Matrix::Inverse(view_ * proj_);
//	// �t���X�^���J�����O�̃R�[�i�[�v�Z
//	std::vector<tnl::Vector3> frustum_corners = CalculateFrustumCorners(inv_view_proj);
//
//	// �ߕ��ʂƉ����ʂ̃R�[�i�[������
//	for (int i = 0; i < 4; i++) 
//	{
//		// �ߕ���(0,1,2,3)
//		// �ߕ��ʂ̊e�R�[�i�[�����̃R�[�i�[�Ɛڑ�
//		// % 4 : �C���f�b�N�X��3�̂Ƃ��Ɏ��̃R�[�i�[��0�ɖ߂邱�Ƃ�ۏ�
//		// 3 + 1 = 4 ,4 % 4 = 0
//		DrawLine3DEx(m_debug_camera, frustum_corners[i], frustum_corners[(i + 1) % 4], 1);
//		// ������(4,5,6,7)
//		DrawLine3DEx(m_debug_camera, frustum_corners[i + 4], frustum_corners[((i + 1) % 4) + 4], 1);
//		// �ߕ��ʂƉ����ʂ�����
//		// �ߕ���(0,1,2,3)�Ɖ�����(4,5,6,7)������
//		// �e�X�Ή�����R�[�i�[�Ɛڑ�
//		DrawLine3DEx(m_debug_camera, frustum_corners[i], frustum_corners[i + 4], 1);
//	}
//}
//
//std::vector<tnl::Vector3> OriginalCamera::CalculateFrustumCorners(const tnl::Matrix& inv_view_proj)
//{
//	// �t���X�^���J�����O�̃R�[�i�[���i�[����z��𐶐�
//	std::vector<tnl::Vector3> corners(8);
//
//	// �r���[���W�n��8�̃R�[�i�[���v�Z
//	// �r���[���W�n�̃R�[�i�[�́A���ׂẴR�[�i�[�����_�𒆐S�Ƃ����P�ʗ����̂ɂ���
//	// �P�ʗ����� : ���ׂĂ̕ӂ̒�����1�̗�����
//
//	// �����O
//	corners[0] = tnl::Vector3(-1, 1, 0);
//	// �E���O
//	corners[1] = tnl::Vector3(1, 1, 0);
//	// �E����O
//	corners[2] = tnl::Vector3(1, -1, 0);
//	// ������O
//	corners[3] = tnl::Vector3(-1, -1, 0);
//	// ���㉜
//	corners[4] = tnl::Vector3(-1, 1, 1);
//	// �E�㉜
//	corners[5] = tnl::Vector3(1, 1, 1);
//	// �E����
//	corners[6] = tnl::Vector3(1, -1, 1);
//	// ������
//	corners[7] = tnl::Vector3(-1, -1, 1);
//
//	for (int i = 0; i < corners.size(); i++)
//	{
//		// �r���[���W�n��8�̃R�[�i�[�����[���h���W�n�ɕϊ�
//		corners[i] = tnl::Vector3::Transform(corners[i], inv_view_proj);
//	}
//
//	return corners;
//}