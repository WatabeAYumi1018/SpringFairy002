#include "../[002]Mediator/Mediator.h"
#include "CinemaCamera.h"



CinemaCamera::CinemaCamera(eCameraSplitType type)
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT), m_type(type)
{
	// �g�p�����ʂ̍쐬
	m_all_hdl = MakeScreen(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, TRUE);

	// �J�����ɉf��͈͂̍ŋߋ���(�h�A�b�v�̂��ߌ���Ȃ�0�ɋ߂����l��)
	near_ = 200;
}

CinemaCamera::CinemaCamera(int screen_w, int screen_h, eCameraSplitType type)
	: dxe::Camera(screen_w, screen_h), m_type(type)
{
	// �g�p�����ʂ̍쐬
	CreateScreen();

	// �J�����ɉf��͈͂̍ŋߋ���(�h�A�b�v�̂��ߌ���Ȃ�0�ɋ߂����l��)
	near_ = 200;
}

void CinemaCamera::SetCanvas(int screen_hdl)
{
	// ��ʂɕ`��
	SetDrawScreen(screen_hdl);
	ClearDrawScreen();
}

void CinemaCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

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
}

void CinemaCamera::Render(int screen_hdl)
{
	// �`��Ώۂ�\��ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	switch (m_type)
	{
	case eCameraSplitType::e_all:

		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH
						, DXE_WINDOW_HEIGHT, screen_hdl, FALSE);

	break;

	case eCameraSplitType::e_half_right:

		DrawExtendGraph(DXE_WINDOW_WIDTH / 2, 0, DXE_WINDOW_WIDTH
						, DXE_WINDOW_HEIGHT, screen_hdl, FALSE);

	break;

	case eCameraSplitType::e_third_left:

		DrawExtendGraph(0, 0, m_split_width_left
						, DXE_WINDOW_HEIGHT, screen_hdl, FALSE);
	
	break;

	case eCameraSplitType::e_third_right:

		DrawExtendGraph(m_split_width_right, 0, DXE_WINDOW_WIDTH
						, DXE_WINDOW_HEIGHT, screen_hdl, FALSE);
	}	
}

void CinemaCamera::CreateScreen()
{	
	m_half_right
		= MakeScreen(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT, TRUE);

	m_third_left
		= MakeScreen(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT, TRUE);

	m_third_right
		= MakeScreen(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT, TRUE);
}

void CinemaCamera::UpdateSplit(const float delta_time)
{
	// �����䗦�̕ύX
	split_rate += delta_time * 10;

	// �����䗦��1�𒴂�����1�ɂ���
	if (split_rate > 1.0f)
	{
		split_rate = 1.0f;
	}
}

tnl::Vector3 CinemaCamera::Lerp(const tnl::Vector3& start
								, const tnl::Vector3& end, float t)
{
	return start + (end - start) * t;
}

void CinemaCamera::Fixed(const tnl::Vector3& offset)
{
	target_ = m_mediator->GetCinemaPlayerPos();

	pos_.x = target_.x + offset.x;
	pos_.y = target_.y + offset.y;
	pos_.z = target_.z + offset.z;
}

void CinemaCamera::ToSlide(const float delta_time,const tnl::Vector3& offset,float speed)
{
	// �ړI�̈ʒu���v�Z
	tnl::Vector3 target_pos
		= tnl::Vector3(target_.x + offset.x, target_.y + offset.y, target_.z + offset.z);

	// ��Ԃ��g�p���ăJ�����ʒu���X�V
	pos_ = Lerp(pos_, target_pos, delta_time * speed);
}

bool CinemaCamera::SeqTrigger(const float delta_time)
{
	// �P�Ԃ̃C�x���g�̏ꍇ�i�o��J�����j
	if (m_mediator->GetEventLane().s_id == 1)
	{
		// �ŏ��̏Љ�
		tnl_sequence_.change(&CinemaCamera::SeqFirst);
	}
	if (m_mediator->GetEventLane().s_id == 5)
	{
		// �G���A�Q�ֈڍs
		tnl_sequence_.change(&CinemaCamera::SeqSecond);
	}
	if (m_mediator->GetEventLane().s_id == 9)
	{
		// �G���A�R�ֈڍs
		tnl_sequence_.change(&CinemaCamera::SeqThird);
	}

	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqFirst(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(7, delta_time, [&]()
	{
		Fixed({0,0,-300});
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		ToSlide(delta_time, {0,0,-50},10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		Fixed({ 0,0,-50 });
	});

	tnl_sequence_.change(&CinemaCamera::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqSecond(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		Fixed({ 0,0,-100 });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		ToSlide(delta_time, { 0,0,-50 }, 5);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
		Fixed({ 0,0,-50 });
	});

	tnl_sequence_.change(&CinemaCamera::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqThird(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(7, delta_time, [&]()
	{
		Fixed({ 0,0,-100 });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		ToSlide(delta_time, { 100,0,-50 }, 2);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
		Fixed({ 100,0,-50 });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		ToSlide(delta_time, { 100,0,-500 }, 10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		Fixed({ 100,0,-500 });
	});

	tnl_sequence_.change(&CinemaCamera::SeqTrigger);

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

