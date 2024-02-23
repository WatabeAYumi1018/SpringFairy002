#include "../../../../[000]GameEngine/[001]Music/MusicManager.h"
#include "../../../[001]Camera/CinemaCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "CinemaPlayer.h"


CinemaPlayer::CinemaPlayer()
{
	m_rot
		= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, -1));
}

CinemaPlayer::~CinemaPlayer()
{
	MV1DeleteModel(m_model_hdl);
	m_paras.clear();
}

void CinemaPlayer::Initialize()
{
	m_mediator->InitializePlayerDraw();

	m_model_hdl = m_mediator->GetPlayerModelCinemaHdl();

	SetLight(m_model_hdl);

	m_paras = m_mediator->GetCinemaPlayerParameters();
	
	m_pos = { m_paras[1].s_num,m_paras[2].s_num,m_paras[3].s_num };
}

void CinemaPlayer::Update(const float delta_time)
{
	tnl_sequence_.update(delta_time);

	if (m_is_idle)
	{
		m_mediator->CinemaPlayerAnimIdle(delta_time);
	}
	else if (m_is_dance)
	{
		m_mediator->CinemaPlayerAnimDance(delta_time);
	}
	
	// ��]�ƍ��W����s����v�Z
	m_matrix = CalcMatrix();

	// ���f���ɍs���K�p
	MV1SetMatrix(m_model_hdl, m_matrix);
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
	tnl::Vector3 pos 
		= { m_paras[5].s_num,m_paras[6].s_num , m_paras[7].s_num };

	// �~�^���̔��a�B�������W�ƒ��S���W����v�Z
	// pow : �ׂ���̌v�Z
	// sqrt : �������̌v�Z
	// 2 : 2��(�ύX�Ȃ�)
	float radius
		= sqrt(pow(m_pos.x - pos.x, 2) + pow(m_pos.z - pos.z, 2));

	// �~�^���̍X�V
	float angle 
		= (m_elapsed_time_circle / m_paras[4].s_num) 
		* tnl::ToRadian(m_paras[8].s_num);

	// x���W�̈ʒu���v�Z
	// 360 : 360�x�𒴂�����߂�(�ύX�Ȃ�)
	if (angle >= tnl::ToRadian(m_paras[8].s_num))
	{
		m_pos.x = pos.x + m_paras[9].s_num;
	}
	else
	{
		m_pos.x = pos.x + sin(angle) * radius;
	}

	// y���W�̈ʒu���v�Z
	// 360�x�𒴂�����߂�
	if (angle >= tnl::ToRadian(m_paras[8].s_num))
	{
		m_pos.y = pos.y + m_paras[10].s_num;
	}
	else
	{
		// ���݂̊p�x�ɉ�����Y���̈ʒu���v�Z
		m_pos.y = (1 - (angle / tnl::ToRadian(m_paras[8].s_num))) * m_pos.y
					+ (angle / tnl::ToRadian(m_paras[8].s_num)) * pos.y;
	}

	// Z���W�̈ʒu���v�Z
	// 360�x�𒴂�����߂�
	if (angle >= tnl::ToRadian(m_paras[8].s_num))
	{
		m_pos.z = pos.z;
	}
	else
	{
		m_pos.z = pos.z + cos(angle) * radius;
	}

	// �~�^�����̈ړ��������������߂̉�]���v�Z(��ɒ��S�������悤��)
	// 90 : �ǂ̂悤�ȉ~�^�����ɂ��܂����A
	//		��{�I�ɂ̓��f���̃f�t�H���g�ɋN�����邽�ߌŒ�l
	tnl::Vector3 nextPos 
		= pos + tnl::Vector3(sin(angle + tnl::ToRadian(90.0f)), 0
		, cos(angle + tnl::ToRadian(90.0f)));
	
	// ������ς���
	tnl::Quaternion direction_rot
		= tnl::Quaternion::LookAt(m_pos, nextPos, tnl::Vector3(0, 1, 0));

	// X������Ɉ��p�x�X����
	// 50 : 50�x(�ύX�̉\������B�j
	tnl::Quaternion tilt_rot 
		= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(m_paras[12].s_num));

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
	if (total_rot > tnl::ToRadian(m_paras[19].s_num))
	{
		total_rot -= tnl::ToRadian(m_paras[19].s_num);
	}

	// Y������̉�]�N�H�[�^�j�I���𐶐�
	tnl::Quaternion axis_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 1, 0), total_rot);

	if (up)
	{
		// ���炩�ɉ�]
		m_rot.slerp(axis_rot, m_paras[0].s_num);
	}
	else
	{
		// Z�������30�x�X����N�H�[�^�j�I���𐶐�
		tnl::Quaternion tilt_rot
			= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1)
											, tnl::ToRadian(m_paras[16].s_num));

		// �����̉�]�ƌX�΂̉�]������
		tnl::Quaternion comb_rot = axis_rot * tilt_rot;

		m_rot.slerp(comb_rot, m_paras[0].s_num);
	}
}

void CinemaPlayer::MoveBackCenter(const float delta_time)
{
	// �J�n���W�����݂̍��W�ɐݒ�
	static tnl::Vector3 start_pos = m_pos;
	// �I�����W�𒆐S���W�ɐݒ�
	tnl::Vector3 end_pos
		= { m_paras[22].s_num, m_paras[23].s_num, m_paras[24].s_num };

	static float total_time = m_paras[25].s_num;
	static float elapsed_time = 0.0f;

	if (elapsed_time < total_time)
	{
		elapsed_time += delta_time * m_paras[26].s_num;
		float phase = elapsed_time / total_time;

		// Y���W���T�C���g�ŕ�ԁi�傫�Ȍʂ�`���j
		// �ʂ̍���
		float amplitude = m_paras[27].s_num;

		// �T�C���g�̗��p
		// 180 : 0�x����180�x�͈̔͂ŃT�C���g�̒l���v�Z�B�i�ύX�͂قږ����j
		// Y���W�͊J�n�ʒu�����Ɍʂ�`���Ȃ���ړ����A���S�ւƐi�ށB
		m_pos.y = start_pos.y + sin(phase * tnl::ToRadian(180.0f)) * amplitude; 

		// �������^���ł̈ʒu�̕��
		m_pos.x = Lerp(start_pos.x, end_pos.x, phase);
		m_pos.y = Lerp(start_pos.y, end_pos.y, phase);
		m_pos.z = Lerp(start_pos.z, end_pos.z, phase);
	}
}

void CinemaPlayer::MoveRoundBackToFront(const float delta_time,float radian,bool up)
{
	// �ړ����x�̒�`
	const float speed = m_paras[33].s_num;

	// �~�^���̒��S���W�i�X�^�[�g�ʒu�Ɠ����j
	tnl::Vector3 center_pos 
		= { m_paras[35].s_num,m_paras[36].s_num,m_paras[37].s_num };

	// �I���ʒu
	tnl::Vector3 end_pos 
		= { m_paras[38].s_num,m_paras[39].s_num,m_paras[40].s_num };

	// �ړ����Ԃ̍X�V
	m_elapsed_time_circle += delta_time;

	// �S�̂̓��쎞��
	const float total_time = m_paras[34].s_num;

	// ���݂̃t�F�[�Y�̐i�s�x�������v�Z
	float progress = m_elapsed_time_circle / total_time;

	// �p�x�̌v�Z
	float angle = progress * tnl::ToRadian(radian);

	// �~�^���̔��a�i�I���ʒu�ƒ��S���W����v�Z�j
	// 2 : 2��(�ύX�Ȃ�)
	float radius = sqrt(pow(end_pos.x - center_pos.x, 2) 
					+ pow(end_pos.z - center_pos.z, 2));

	// �~�^��
	m_pos.x = center_pos.x + sin(angle) * radius;
	
	if (up)
	{
		// 2 : 2�Ŋ��邱�Ƃł�莩�R�ȓ����A�U����\���B
		// ��Ɏ��o�I�ȓ�����\�����邽�߂Ɏg�p���A��{�I�ɂ͕ύX�Ȃ��B
		// �A���A���K�����l������ΕύX�̉\������B
		m_pos.y = center_pos.y - cos(angle) * radius / 2;
	}
	else
	{
		m_pos.y = center_pos.y + cos(angle) * radius / 2;
	}

	m_pos.z = center_pos.z + cos(angle) * radius;

	tnl::Quaternion tilt_rot 
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1)
										, tnl::ToRadian(m_paras[41].s_num));

	// �ړ��������������߂̉�]���v�Z
	// 90 : �ǂ̂悤�ȉ�]���ɂ��܂����A
	//		���f���̃f�t�H���g�ɋN�����邽�ߌŒ�l
	tnl::Vector3 next_direction 
		= tnl::Vector3(sin(angle + tnl::ToRadian(90.0f)), 0
					  , cos(angle + tnl::ToRadian(90.0f)));
	
	tnl::Quaternion direction_rot 
		= tnl::Quaternion::LookAt(m_pos, m_pos + next_direction, tnl::Vector3(0, 1, 0));
	
	// �i�s�����̉�]�Ƒ̂��X�����]��g�ݍ��킹��
	m_rot = tilt_rot * direction_rot;
}

bool CinemaPlayer::SeqTrigger(const float delta_time)
{
	// �P�Ԃ̃C�x���g�̏ꍇ�i�o��J�����j
	if (m_mediator->GetCurrentEventLane().s_id == 1)
	{
		// �ŏ��̏Љ�
		tnl_sequence_.change(&CinemaPlayer::SeqFirst);
	}
	if (m_mediator->GetCurrentEventLane().s_id == 7)
	{
		// �G���A�Q�ֈڍs
		tnl_sequence_.change(&CinemaPlayer::SeqSecond);
	}
	if (m_mediator->GetCurrentEventLane().s_id == 10)
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

	// 4�b�Ԃ̎��s
	// ���̂�����̃^�C�����f�o�b�O�Ǘ����D�܂�����������܂��񂪁A
	// ����͊ȈՓI�Ɏ������Ă��܂��B
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		MoveRoundFrontToBack(delta_time);

		MusicManager::GetInstance().PlaySE(3);
	});

	// 2�b�Ԃ̎��s
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_rot 
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(1, 0, 1));

		m_is_dance = false;
		m_is_idle = true;
	});

	// 1�b�Ԃ̎��s
	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]() 
	{
		tnl::Quaternion target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		m_rot.slerp(target_rot, m_paras[0].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		tnl::Quaternion back_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));

		// ���f����O�����݂ɌX����
		// 45 : 45�x(�ύX�̉\������)
		// �{���f�o�b�O�ōs���܂��BID�̕ύX���K�v�Ȃ��߁A��قǏC�����܂��B
		tnl::Quaternion tilt_rot
			= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(45));

		// ��]����
		tnl::Quaternion comb_rot =  tilt_rot * back_rot;

		m_rot.slerp(comb_rot, m_paras[0].s_num);

		// ���f���̑O�ւ̈ړ����x�B
		m_pos.y -= delta_time * m_paras[20].s_num;
		m_pos.z += delta_time * m_paras[21].s_num;

		m_mediator->SetChangeGraphIsFlower(true);
		m_mediator->SetChildGraphIsFlower(true);
	});

	m_is_idle = false;

	m_mediator->SetAnimElapsedTimeDance();

	MusicManager::GetInstance().StopSE(3);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqSecond(const float delta_time)
{
	if(tnl_sequence_.isStart())
	{
		m_is_idle= true;
		m_pos = { m_paras[13].s_num,m_paras[14].s_num,m_paras[15].s_num };
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		MoveRotUpDown(delta_time, m_paras[17].s_num,false);

		m_pos.x -= delta_time * m_paras[18].s_num;
		m_pos.y -= delta_time * m_paras[18].s_num;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{	
		m_is_idle = false;

		// �O����70�x�X��
		// 70 : 70�x(�ύX�̉\������)
		// �{���f�o�b�O�ōs���܂��BID�̕ύX���K�v�Ȃ��߁A��قǏC�����܂��B
		m_rot = tnl::Quaternion::RotationAxis(tnl::Vector3(0, -1, -1), tnl::ToRadian(70));

		MoveBackCenter(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		m_is_idle = true;

		tnl::Quaternion target_rot
			= tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, -1));

		m_rot.slerp(target_rot, m_paras[0].s_num);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_pos = { 0 };

		// emmisive����������������
		// 1: ��{�I��emmissive�̌��E�l��1�̂��߁A�ύX�͂قږ����B
		m_emissive.r += delta_time;
		m_emissive.g += delta_time;
		m_emissive.b += delta_time;
		m_emissive.a = 1;

		if (m_emissive.r >= m_emissive.a
			&& m_emissive.g >= m_emissive.a
			&& m_emissive.b >= m_emissive.a)
		{
			m_emissive.r = m_emissive.a;
			m_emissive.g = m_emissive.a;
			m_emissive.b = m_emissive.a;
		}

		MV1SetMaterialEmiColor(m_model_hdl, 0, m_emissive);

		m_mediator->SetIsCinemaBackFog(true);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&](){});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		m_is_idle = false;	
		m_is_dance = true;

		MusicManager::GetInstance().PlaySE(3);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		m_mediator->SetChangeGraphIsWood(true);
		m_mediator->SetChildGraphIsWood(true);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2.5f, delta_time, [&]()
	{
		m_mediator->SetChangeGraphIsActiveWhite(true);
		m_mediator->SetChildGraphIsActiveWhite(true);
	});

	MusicManager::GetInstance().StopSE(3);

	SetDefaultLightParameter("directional_light_parameter.bin");

	m_is_dance = false;

	m_mediator->SetAnimElapsedTimeDance();

	m_mediator->SetIsCinemaBackFog(false);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaPlayer::SeqThird(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_idle = true;

		m_pos = { m_paras[28].s_num,m_paras[29].s_num,m_paras[30].s_num };
		// ����Ȃ�1�ɋ߂��l�ɂ��Č��z�I�ȕ��͋C���o��
		DxLib::COLOR_F m_emissive = { 0.9f,0.9f,0.9f,1 };

		MV1SetMaterialEmiColor(m_model_hdl, 0, m_emissive);

		m_mediator->SetIsCinemaBackBubble(true);
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		MoveRotUpDown(delta_time, m_paras[31].s_num);
		
		m_pos.y += delta_time * m_paras[32].s_num;

		if (m_pos.y >= 0)
		{
			m_pos.y = 0;
		}
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		// 360�x��]
		MoveRoundBackToFront(delta_time, m_paras[42].s_num,false);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]() 
	{
		// -360�x��]
		MoveRoundBackToFront(delta_time, m_paras[43].s_num);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
	{
		// ��]�ɂ����W�̕ύX���������Z�b�g
		// 1�t���[���ł̕ύX�̂��߁A�Œ�l
		m_pos = tnl::Vector3( 0,0,0 );
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(11, delta_time, [&](){});

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() 
	{
		// 100 : y���W�␳(���܂茩�h���ɒ������Ȃ��␳�̂��ߌŒ�l)
		float offset = 100.0f;

		m_pos.y -= offset;
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]() 
	{
		m_is_idle = false;
		m_is_dance = true;

		MusicManager::GetInstance().PlaySE(4);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		m_mediator->SetEffectIsScreen(true);
		m_mediator->SetChangeGraphIsActiveWhite(true);
		m_mediator->SetChildGraphIsActiveWhite(true);
	});

	MusicManager::GetInstance().StopSE(4);

	m_is_dance = false;

	m_mediator->SetAnimElapsedTimeDance();

	m_mediator->SetEffectIsScreen(false);

	tnl_sequence_.change(&CinemaPlayer::SeqTrigger);

	TNL_SEQ_CO_END;
}