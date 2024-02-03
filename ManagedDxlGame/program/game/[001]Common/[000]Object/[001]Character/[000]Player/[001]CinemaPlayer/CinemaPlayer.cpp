#include "../../../../[001]Camera/CinemaCamera.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "CinemaPlayer.h"


CinemaPlayer::CinemaPlayer()
{
	m_pos = { 0, 0, 0 };

	m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, -1));

	m_mesh = dxe::Mesh::CreateSphereMV(50);
}

CinemaPlayer::~CinemaPlayer()
{

}

void CinemaPlayer::Initialize()
{
	m_mediator->InitializePlayerDraw();

	m_model_hdl = m_mediator->GetPlayerModelHdl();

	SetLight(m_model_hdl);
}

void CinemaPlayer::Update(const float delta_time)
{
	if (m_is_idle)
	{
		m_mediator->CinemaPlayerAnimIdle(delta_time);
	}
	else
	{
		if (m_is_move)
		{
			m_mediator->CinemaPlayerAnimMove(delta_time);
		}
		else if (m_is_dance)
		{
			m_mediator->CinemaPlayerAnimDance(delta_time);
		}
	}

	// ��]�ƍ��W����s����v�Z
	m_matrix = CalcMatrix();

	m_mesh->pos_ = m_pos;
	m_mesh->pos_.y += 100;

	// ���f���ɍs���K�p
	MV1SetMatrix(m_model_hdl, m_matrix);
}

void CinemaPlayer::Draw(std::shared_ptr<dxe::Camera> camera)
{
	 m_mesh->render(camera);
	
	// ���f���`�揈��
	m_mediator->DrawPlayerModel();
}

void CinemaPlayer::MoveRound(const float delta_time)
{
	m_elapsed_time_circle += delta_time;

	// ���Ԃ�̑S�̂̐i�s���ԂɊ�Â����p�x�v�Z
	float angle = (m_elapsed_time_circle / m_total_time) * tnl::ToRadian(360);

	// ����]�ɂ��X�������̈ړ�
	m_pos.x = m_pos.x + sin(angle) * m_radius;
	// ����]�ɂ��Z�������̈ړ�
	m_pos.z = m_pos.z + cos(angle) * m_radius;

	// ��]����Y���ɕύX
	tnl::Quaternion target_rot
		= tnl::Quaternion::LookAtAxisY(m_pos, tnl::Vector3(0, 0, 0));

	// ���݂̉�]����ڕW�̉�]�Ɍ�����slerp���s��
	m_rot.slerp(target_rot, delta_time * m_speed);
}

bool CinemaPlayer::SeqTrigger(const float delta_time)
{
	// �P�Ԃ̃C�x���g�̏ꍇ�i�o��J�����j
	if (m_mediator->GetEventLane().s_id == 1)
	{
		// �ŏ��̏Љ�
		tnl_sequence_.change(&CinemaPlayer::SeqFirst);
	}
	if (m_mediator->GetEventLane().s_id == 5)
	{
		// �G���A�Q�ֈڍs
		tnl_sequence_.change(&CinemaPlayer::SeqSecond);
	}
	if (m_mediator->GetEventLane().s_id == 9)
	{
		// �G���A�R�ֈڍs
		tnl_sequence_.change(&CinemaPlayer::SeqThird);
	}

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqFirst(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_idle = false;
		m_is_move = true;
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(7, delta_time, [&]()
	{
		MoveRound(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_is_move = false;
		m_is_dance = true;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		m_is_idle = true;
		m_is_dance = false;
		m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, -1));
	});

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqSecond(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		if (m_mediator->GetScreenType()
			== CinemaCamera::eCameraSplitType::e_all)
		{
			m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, -1));
		}
		else if (m_mediator->GetScreenType() 
				== CinemaCamera::eCameraSplitType::e_third_left)
		{
			m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));
		}
		else if (m_mediator->GetScreenType()
				== CinemaCamera::eCameraSplitType::e_third_right)
		{
			m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, 0));
		}

	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
		// emmisive����������������
		DxLib::COLOR_F emissive;

		emissive.r = delta_time * 5;
		emissive.g = delta_time * 5;
		emissive.b = delta_time * 5;


		if (emissive.r >= 0.9f && emissive.g >= 0.9f && emissive.b >= 0.9f)
		{
			emissive.r = 0.9f;
			emissive.g = 0.9f;
			emissive.b = 0.9f;
		}

		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	});

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