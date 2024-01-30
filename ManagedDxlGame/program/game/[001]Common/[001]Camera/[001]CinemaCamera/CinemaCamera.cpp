#include "../../[002]Mediator/Mediator.h"
#include "CinemaCamera.h"



CinemaCamera::CinemaCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT)
{
	// �J�����ɉf��͈͂̍ŋߋ���(�h�A�b�v�̂��ߌ���Ȃ�0�ɋ߂����l��)
	near_ = 1;
}

void CinemaCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	target_ = m_mediator->GetPlayerPos();

	pos_.x = target_.x;
	pos_.y = target_.y;
	pos_.z = target_.z - m_offset.z * 2;

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
	{
		m_move_mouse = true;
	}

	if(m_move_mouse)
	{
		Control(delta_time);
	}

	//// ���W�f�o�b�O�p
	//DrawStringEx(1000, 100, -1, "CameraPos_x:%f", pos_.x);
	//DrawStringEx(1000, 120, -1, "CameraPos_y:%f", pos_.y);
	//DrawStringEx(1000, 140, -1, "CameraPos_z:%f", pos_.z);
}


//bool CinemaCamera::SeqTrigger(const float delta_time)
//{
//
//}
//
//bool CinemaCamera::SeqUp(const float delta_time)
//{
//
//}
//
//bool CinemaCamera::SeqSide(const float delta_time)
//{
//
//}
//
//bool CinemaCamera::SeqBack(const float delta_time)
//{
//
//}




// -----�f�o�b�O�p----- //

void CinemaCamera::Control(const float delta_time)
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

tnl::Vector3 CinemaCamera::RotateAroundPlayer(const tnl::Vector3& point
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

