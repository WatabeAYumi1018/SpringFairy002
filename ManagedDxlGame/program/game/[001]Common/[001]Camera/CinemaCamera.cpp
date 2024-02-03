#include "../[002]Mediator/Mediator.h"
#include "CinemaCamera.h"



CinemaCamera::CinemaCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT)
{
	// �g�p�����ʂ̍쐬
	CreateScreen();

	// �J�����ɉf��͈͂̍ŋߋ���(�h�A�b�v�̂��ߌ���Ȃ�0�ɋ߂����l��)
	near_ = 10;
}

CinemaCamera::CinemaCamera(int screen_w, int screen_h)
	: dxe::Camera(screen_w, screen_h)
{
	// �g�p�����ʂ̍쐬
	CreateScreen();

	// �J�����ɉf��͈͂̍ŋߋ���(�h�A�b�v�̂��ߌ���Ȃ�0�ɋ߂����l��)
	near_ = 10;
}

void CinemaCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	target_ = m_mediator->GetCinemaPlayerPos();

	pos_ = target_ + m_offset;

	// �����䗦�Ɋ�Â��Ċe�X�N���[���̕����v�Z���܂��B
	m_split_width_left
		= static_cast<int>(DXE_WINDOW_WIDTH * (1.0f - split_rate) / 2);

	m_split_width_right = DXE_WINDOW_WIDTH - m_split_width_left;

	tnl_sequence_.update(delta_time);

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

void CinemaCamera::Render(int x1, int y1, int x2, int y2, int screen_hdl)
{
	if (m_mediator->GetEventLane().s_id == 1)
	{
		// ��ʂɕ`��
		SetDrawScreen(screen_hdl);
		ClearDrawScreen();

		// �`��Ώۂ�\��ʂɐݒ�
		SetDrawScreen(DX_SCREEN_BACK);

		DrawExtendGraph(x1, y1, x2, y2, screen_hdl, FALSE);
	}
}

void CinemaCamera::CreateScreen()
{	
	m_all_hdl = MakeScreen(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, TRUE);

	m_half_right = MakeScreen(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT, TRUE);

	m_third_left = MakeScreen(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT, TRUE);

	m_third_right = MakeScreen(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT, TRUE);
}

void CinemaCamera::SplitAnimation(const float delta_time)
{
	// �����䗦�̕ύX
	split_rate += delta_time * 10;

	// �����䗦��1�𒴂�����1�ɂ���
	if (split_rate > 1.0f)
	{
		split_rate = 1.0f;
	}
}

bool CinemaCamera::SeqTrigger(const float delta_time)
{
	// �P�Ԃ̃C�x���g�̏ꍇ�i�o��J�����j
	if (m_mediator->GetEventLane().s_id == 1)
	{
		// �A�b�v�Ő��ʑS�̂ɉf��
		
	}
	if (m_mediator->GetEventLane().s_id == 5)
	{
		// ��ʂ��O�����ɂ���
		//�S�ăT�u�J�����ɂ��āA���ꂼ��̃J�����ŕ`��A�b�v�A�T�C�h�`��
	}
	if (m_mediator->GetEventLane().s_id == 9)
	{
		// ��ʂ�񕪊��ɂ���
		// ���ƃv���C���[���T�C�h���炻�ꂼ��A�b�v��
		// �v���C���[���A�b�v�őS���
	}
	
	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqUp(const float delta_time)
{
	// �C�x���g���I��������Trigger�ɖ߂�
	if(m_is_completed)
	{
		tnl_sequence_.change(&CinemaCamera::SeqTrigger);
	}

	TNL_SEQ_CO_END;

}

bool CinemaCamera::SeqSide(const float delta_time)
{
	// �C�x���g���I��������Trigger�ɖ߂�
	if (m_is_completed)
	{
		tnl_sequence_.change(&CinemaCamera::SeqTrigger);
	}

	TNL_SEQ_CO_END;


}

bool CinemaCamera::SeqBack(const float delta_time)
{
	// �C�x���g���I��������Trigger�ɖ߂�
	if (m_is_completed)
	{
		tnl_sequence_.change(&CinemaCamera::SeqTrigger);
	}

	TNL_SEQ_CO_END;


}




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

