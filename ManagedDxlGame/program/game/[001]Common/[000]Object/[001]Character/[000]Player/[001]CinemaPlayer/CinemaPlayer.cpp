
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
	
	// ��]�ƍ��W����s����v�Z
	m_matrix = CalcMatrix();

	// ���f���ɍs���K�p
	MV1SetMatrix(m_model_hdl, m_matrix);

	// �v���C���[�̍��W���f�o�b�O�\��
	DrawStringEx(0, 0, -1, "PlayerPos_x:%f", m_pos.x);
	DrawStringEx(0, 20, -1, "PlayerPos_y:%f", m_pos.y);
	DrawStringEx(0, 40, -1, "PlayerPos_z:%f", m_pos.z);

}

void CinemaPlayer::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// ���f���`�揈��
	MV1DrawModel(m_model_hdl);
}

// Lerp�֐��̒�`�i���`��ԁj
float CinemaPlayer::Lerp(float start, float end, float t)
{
	return start + (end - start) * t;
}

void CinemaPlayer::MoveRound(const float delta_time)
{
	// ���Ԍo�߂̍X�V
	m_elapsed_time_circle += delta_time;

	// ���S���W
	tnl::Vector3 center_pos = { 0, 0, 0 };

	tnl::Vector3 end_pos = { -50, -150, 0 };

	// �~�^���̔��a�B�������W�ƒ��S���W����v�Z
	float radius
		= sqrt(pow(m_pos.x - center_pos.x, 2) + pow(m_pos.z - center_pos.z, 2));

	// �~�^���̍X�V
	float angle 
		= (m_elapsed_time_circle / m_total_time) * tnl::ToRadian(360);

	// x���W�̈ʒu���v�Z
	if (angle >= tnl::ToRadian(360))
	{
		m_pos.x = end_pos.x;
	}
	else
	{
		m_pos.x = center_pos.x + sin(angle) * radius;
	}
	// y���W�̈ʒu���v�Z
	if (angle >= tnl::ToRadian(360))
	{
		m_pos.y = end_pos.y;
	}
	else
	{
		// ���݂̊p�x�ɉ�����Y���̈ʒu���v�Z
		m_pos.y = (1 - (angle / tnl::ToRadian(360))) * m_pos.y 
					+ (angle / tnl::ToRadian(360)) * end_pos.y;
	}

	// Z���W�̈ʒu���v�Z
	if (angle >= tnl::ToRadian(360))
	{
		m_pos.z = end_pos.z;
	}
	else
	{
		m_pos.z = center_pos.z + cos(angle) * radius;
	}

	// �~�^�����̈ړ��������������߂̉�]���v�Z
	tnl::Vector3 nextPos 
		= center_pos + tnl::Vector3(sin(angle + tnl::ToRadian(90)), 0
									, cos(angle + tnl::ToRadian(90)));
	// ������ς���
	tnl::Quaternion direction_rot
		= tnl::Quaternion::LookAt(m_pos, nextPos, tnl::Vector3(0, 1, 0));

	// X������Ɉ��p�x�X����
	tnl::Quaternion tilt_rot 
		= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(50));

	// ��]�̑g�ݍ��킹
	m_rot = direction_rot * tilt_rot;
}

void CinemaPlayer::MoveDown(const float delta_time)
{
	static float total_rot = 0.0f; // ����]�p�x
	const float rot_speed = 5; 

	// ����]�p�x���X�V
	total_rot += rot_speed * delta_time;

	// 720�x�i4�΃��W�A���j�𒴂����烊�Z�b�g
	if (total_rot > tnl::ToRadian(720))
	{
		total_rot -= tnl::ToRadian(720);
	}

	// Y������̉�]�N�H�[�^�j�I���𐶐�
	tnl::Quaternion axis_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 1, 0), total_rot);

	// Z�������30�x�X����N�H�[�^�j�I���𐶐�
	tnl::Quaternion tilt_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(30));

	// �����̉�]�ƌX�΂̉�]������
	tnl::Quaternion comb_rot = axis_rot * tilt_rot;

	// Slerp�Ŋ��炩�ɉ�]��K�p
	m_rot.slerp(comb_rot, 0.5f);
}

void CinemaPlayer::MoveBackCenter(const float delta_time)
{
	// �ړ��̊J�n�ʒu�i�ŏ��̍��W�j
	static tnl::Vector3 start_pos = m_pos;
	// �ړI�n�̍��W
	tnl::Vector3 end_pos = { 0, 0, 0 }; 
	// �ړ��ɂ����鎞��
	static float total_time = 1.0f;
	// �o�ߎ��Ԃ�ێ�����ϐ�
	static float elapsed_time = 0.0f;

	// �o�ߎ��Ԃ��X�V
	elapsed_time += delta_time * 10;

	// �������^���ł̈ʒu�̕��
	m_pos.x = tnl::AccelLerp(start_pos.x, end_pos.x, total_time, elapsed_time, 5); 
	m_pos.y = tnl::AccelLerp(start_pos.y, end_pos.y, total_time, elapsed_time, 5);
	m_pos.z = tnl::AccelLerp(start_pos.z, end_pos.z, total_time, elapsed_time, 5);
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

		// ���f�����w��������悤�ɉ�]
		tnl::Quaternion backFacingRot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		// ���f����O�����݂ɌX����ǉ��̉�]
		tnl::Quaternion forwardTiltRot
			= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(45));

		// �w�ʂ��������]�ƑO�����݂̌X�΂�g�ݍ��킹��
		tnl::Quaternion combinedRot =  forwardTiltRot * backFacingRot;

		// Slerp�Ŋ��炩�ɓK�p
		m_rot.slerp(combinedRot, delta_time * 10);

		m_pos.y -= delta_time * 100;
		m_pos.z += delta_time * 500;	
	});

	m_mediator->SetIsActiveGameCamera(true);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqSecond(const float delta_time)
{
	if(tnl_sequence_.isStart())
	{
		m_pos = { 100,100,0 };
	}

	DxLib::COLOR_F emissive;

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		MoveDown(delta_time);
		m_pos.x -= delta_time * 150;
		m_pos.y -= delta_time * 150;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{	
		m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, -1));

		MoveBackCenter(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
		m_is_idle = false;
		m_is_dance = true;

		m_pos = { 0 };

		// emmisive����������������
		emissive.r = 0.5f * delta_time * 5;
		emissive.g = 0.5f * delta_time * 5;
		emissive.b = 0.5f * delta_time * 5;


		if (emissive.r >= 0.9f && emissive.g >= 0.9f && emissive.b >= 0.9f)
		{
			emissive.r = 0.9f;
			emissive.g = 0.9f;
			emissive.b = 0.9f;
		}

		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);

	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
	
	});

	emissive.r = 0.5f;
	emissive.g = 0.5f;
	emissive.b = 0.5f;

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