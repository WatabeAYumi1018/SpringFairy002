
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

void CinemaPlayer::MoveRoundFrontToBack(const float delta_time)
{
	// ���Ԍo�߂̍X�V
	m_elapsed_time_circle += delta_time;

	// ���S���W
	tnl::Vector3 pos = { 0, 0, 0 };

	// �~�^���̔��a�B�������W�ƒ��S���W����v�Z
	float radius
		= sqrt(pow(m_pos.x - pos.x, 2) + pow(m_pos.z - pos.z, 2));

	// �~�^���̍X�V
	float angle = (m_elapsed_time_circle / m_total_time) * tnl::ToRadian(360);

	// x���W�̈ʒu���v�Z
	if (angle >= tnl::ToRadian(360))
	{
		m_pos.x = pos.x - 50;
	}
	else
	{
		m_pos.x = pos.x + sin(angle) * radius;
	}

	// y���W�̈ʒu���v�Z
	if (angle >= tnl::ToRadian(360))
	{
		m_pos.y = pos.y - 150;
	}
	else
	{
		// ���݂̊p�x�ɉ�����Y���̈ʒu���v�Z
		m_pos.y = (1 - (angle / tnl::ToRadian(360))) * m_pos.y 
					+ (angle / tnl::ToRadian(360)) * pos.y;
	}

	// Z���W�̈ʒu���v�Z
	if (angle >= tnl::ToRadian(360))
	{
		m_pos.z = pos.z;
	}
	else
	{
		m_pos.z = pos.z + cos(angle) * radius;
	}

	// �~�^�����̈ړ��������������߂̉�]���v�Z
	tnl::Vector3 nextPos 
		= pos + tnl::Vector3(sin(angle + tnl::ToRadian(90)), 0
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

void CinemaPlayer::MoveRotUpDown(const float delta_time,float speed,bool up)
{
	// ����]�p�x
	static float total_rot = 0.0f; 
	const float rot_speed = speed;

	// ����]�p�x���X�V
	total_rot += rot_speed * delta_time;

	// 720�x�𒴂����烊�Z�b�g
	if (total_rot > tnl::ToRadian(720))
	{
		total_rot -= tnl::ToRadian(720);
	}

	// Y������̉�]�N�H�[�^�j�I���𐶐�
	tnl::Quaternion axis_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 1, 0), total_rot);

	if (up)
	{
		// ���炩�ɉ�]
		m_rot.slerp(axis_rot,0.5f);
	}
	else
	{
		// Z�������30�x�X����N�H�[�^�j�I���𐶐�
		tnl::Quaternion tilt_rot
			= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(30));

		// �����̉�]�ƌX�΂̉�]������
		tnl::Quaternion comb_rot = axis_rot * tilt_rot;

		m_rot.slerp(comb_rot, 0.5f);
	}
}

void CinemaPlayer::MoveBackCenter(const float delta_time)
{
	static tnl::Vector3 start_pos = m_pos;
	tnl::Vector3 end_pos = { 0, 0, 0 };
	static float total_time = 2.0f;
	static float elapsed_time = 0.0f;

	if (elapsed_time < total_time)
	{
		elapsed_time += delta_time * 5;
		float phase = elapsed_time / total_time;

		// Y���W���T�C���g�ŕ�ԁi�傫�Ȍʂ�`���j
		float amplitude = 20.0f; // �ʂ̍���
		m_pos.y = start_pos.y + sin(phase * tnl::ToRadian(180)) * amplitude; // �T�C���g�̗��p

		// �������^���ł̈ʒu�̕��
		m_pos.x = Lerp(start_pos.x, end_pos.x, phase);
		m_pos.y = Lerp(start_pos.y, end_pos.y, phase);
		m_pos.z = Lerp(start_pos.z, end_pos.z, phase);
	}
}

void CinemaPlayer::MoveRoundBackToFront(const float delta_time,float radian,bool up)
{
	// �ړ����x�̒�`
	const float speed = 5.0f;

	// �~�^���̒��S���W�i�X�^�[�g�ʒu�Ɠ����j
	tnl::Vector3 center_pos = { 0,0,0 };

	// �I���ʒu
	tnl::Vector3 end_pos = { -400,0,-400 };

	// �ړ����Ԃ̍X�V
	m_elapsed_time_circle += delta_time;

	// �S�̂̓��쎞��
	const float total_time = 3.0f;

	// ���݂̃t�F�[�Y�̐i�s�x�������v�Z
	float progress = m_elapsed_time_circle / total_time;

	// �p�x�̌v�Z
	float angle = progress * tnl::ToRadian(radian);

	// �~�^���̔��a�i�I���ʒu�ƒ��S���W����v�Z�j
	float radius = sqrt(pow(end_pos.x - center_pos.x, 2) 
					+ pow(end_pos.z - center_pos.z, 2));

	// �~�^��
	m_pos.x = center_pos.x + sin(angle) * radius;
	
	if (up)
	{
		m_pos.y = center_pos.y - cos(angle) * radius / 2;
	}
	else
	{
		m_pos.y = center_pos.y + cos(angle) * radius / 2;
	}

	m_pos.z = center_pos.z + cos(angle) * radius;

	tnl::Quaternion tilt_rot 
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(45));

	// �ړ��������������߂̉�]���v�Z
	tnl::Vector3 next_direction 
		= tnl::Vector3(sin(angle + tnl::ToRadian(90)), 0, cos(angle + tnl::ToRadian(90)));
	
	tnl::Quaternion direction_rot 
		= tnl::Quaternion::LookAt(m_pos, m_pos + next_direction, tnl::Vector3(0, 1, 0));
	
	// �i�s�����̉�]�Ƒ̂��X�����]��g�ݍ��킹��
	m_rot = tilt_rot * direction_rot;
}

bool CinemaPlayer::SeqTrigger(const float delta_time)
{
	// �P�Ԃ̃C�x���g�̏ꍇ�i�o��J�����j
	if (m_mediator->GetEventLane().s_id == 1)
	{
		// �ŏ��̏Љ�
		tnl_sequence_.change(&CinemaPlayer::SeqFirst);
	}
	if (m_mediator->GetEventLane().s_id == 6)
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
		MoveRoundFrontToBack(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, 1));

		m_is_dance = false;
		m_is_idle = true;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]() 
	{
		tnl::Quaternion target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		m_rot.slerp(target_rot, delta_time * 10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		tnl::Quaternion back_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		// ���f����O�����݂ɌX����
		tnl::Quaternion tilt_rot
			= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(45));

		// ��]����
		tnl::Quaternion comb_rot =  tilt_rot * back_rot;

		m_rot.slerp(comb_rot, delta_time * 10);

		m_pos.y -= delta_time * 100;
		m_pos.z += delta_time * 500;	
	});

	m_is_idle = false;

	m_mediator->SetAnimElapsedTimeDance(0);

	m_mediator->SetIsActiveGameCamera(true);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqSecond(const float delta_time)
{
	if(tnl_sequence_.isStart())
	{
		m_is_idle= true;
		m_pos = { 100,100,0 };
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		MoveRotUpDown(delta_time,5,false);
		m_pos.x -= delta_time * 150;
		m_pos.y -= delta_time * 150;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{	
		m_is_idle = false;
		m_is_move = true;

		// �O����45�x�X��
		m_rot = tnl::Quaternion::RotationAxis(tnl::Vector3(0, -1, -1), tnl::ToRadian(70));

		MoveBackCenter(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		m_is_move = false;
		m_is_idle = true;

		tnl::Quaternion target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, -1));

		m_rot.slerp(target_rot,0.1f);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_pos = { 0 };

		// emmisive����������������
		m_emissive.r += delta_time;
		m_emissive.g += delta_time;
		m_emissive.b += delta_time;
		m_emissive.a = 1;

		if (m_emissive.r >= 1 && m_emissive.g >= 1 && m_emissive.b >= 1)
		{
			m_emissive.r = 1;
			m_emissive.g = 1;
			m_emissive.b = 1;
		}

		MV1SetMaterialEmiColor(m_model_hdl, 0, m_emissive);

		m_mediator->SetIsCinemaBackFog(true);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&](){});

	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		m_is_idle = false;	
		m_is_dance = true;
	});

	SetDefaultLightParameter("directional_light_parameter.bin");

	DxLib::COLOR_F m_emissive = { 0.5f,0.5f,0.5f,1 };

	m_is_dance = false;

	m_mediator->SetAnimElapsedTimeDance(0);

	m_mediator->SetIsActiveGameCamera(true);

	m_mediator->SetIsCinemaBackFog(false);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqThird(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_idle = true;

		m_pos = { 0,-500,0 };

		DxLib::COLOR_F m_emissive = { 0.9f,0.9f,0.9f,1 };

		MV1SetMaterialEmiColor(m_model_hdl, 0, m_emissive);

		m_mediator->SetIsCinemaBackBubble(true);
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		MoveRotUpDown(delta_time,10,true);

		m_pos.y += delta_time * 200;

		if (m_pos.y >= 0)
		{
			m_pos.y = 0;
		}
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		MoveRoundBackToFront(delta_time,360,false);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]() 
	{
		MoveRoundBackToFront(delta_time, -360,true);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
	{
		// ��]�ɂ����W�̕ύX���������Z�b�g
		m_pos = tnl::Vector3( 0,0,0 );
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(11, delta_time, [&](){});

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() 
	{
		m_pos.y -= 100;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]() 
	{
		m_is_idle = false;
		m_is_dance = true;
	});

	m_is_dance = false;

	m_mediator->SetAnimElapsedTimeDance(0);

	m_mediator->SetIsActiveGameCamera(true);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}