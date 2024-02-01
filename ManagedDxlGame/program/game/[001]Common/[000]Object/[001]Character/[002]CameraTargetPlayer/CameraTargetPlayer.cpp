#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "CameraTargetPlayer.h"


void CameraTargetPlayer::Initialize()
{
	m_collision_size = 50;

	StartPos();
}

void CameraTargetPlayer::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);

	DrawStringEx(500, 0, -1, "�J����ID�ԍ� : %d", m_camera_info.s_id);
	DrawStringEx(500, 20, -1, "�C�x���gID�ԍ� : %d", m_event.s_id);

	// �v���C���[�̃A�j���[�V�������������t���O�ݒ�
	if (m_event.s_id == 6)
	{
		m_mediator->SetIsPlayerEventDance(true);
	}

	//if (m_gimmick.s_id == 1)
	//{
	//	Gimmick::sGimmickTypeInfo gimmick_type
	//		= m_mediator->GetGimmickLoadInfoById(m_gimmick.s_id);
	//}
}

void CameraTargetPlayer::Draw(std::shared_ptr<dxe::Camera> camera)
{
	////// �����蔻��f�o�b�O�p
	//VECTOR pos = wta::ConvertToVECTOR(m_pos);
	//pos.y += m_collision_size;
	//DrawSphere3D(pos, m_collision_size, 32, -1, -1, true);

	//// ���W�f�o�b�O�p
	//DrawStringEx(1000, 100, -1, "TargetPos_x:%f", m_pos.x);
	//DrawStringEx(1000, 120, -1, "TargetPos_y:%f", m_pos.y);
	//DrawStringEx(1000, 140, -1, "TargetPos_z:%f", m_pos.z);
}

void CameraTargetPlayer::MoveMatrix(const float delta_time)
{
	// �����o�H�ɂ��ړ��̍X�V
	m_mediator->MoveAstarTargetPos(delta_time, m_pos);

	// �J�������[���̎擾
	m_camera_info = CurrentCameraType();

	m_event = CurrentEventLane();
}

bool CameraTargetPlayer::SeqNormal(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_speed_up = false;
		m_is_move_up = false;
		m_is_move_down = false;
	}

	if (m_event.s_id == 4)
	{
		tnl_sequence_.change(&CameraTargetPlayer::SeqStop);
	}

	if (m_event.s_id == 7)
	{
		tnl_sequence_.change(&CameraTargetPlayer::SeqDownMove);
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		m_mediator->SetIsCinemaCameraActive(true);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool CameraTargetPlayer::SeqStop(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
		// ���b�ԍ��W�X�V���~
	});

	tnl_sequence_.change(&CameraTargetPlayer::SeqUpMove);

	TNL_SEQ_CO_END;
}

bool CameraTargetPlayer::SeqUpMove(const float delta_time)
{
	if(m_pos.y > 500)
	{
		tnl_sequence_.change(&CameraTargetPlayer::SeqNormal);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
	{
		// 1�t���[���Ńt���O���s
		m_is_speed_up = true;

		m_is_move_up = true;
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
		// y���W���㏸
		m_pos.y += delta_time * 50;
	});

	TNL_SEQ_CO_END;
}

bool CameraTargetPlayer::SeqDownMove(const float delta_time)
{
	if( m_pos.y == 0 )
	{
		tnl_sequence_.change(&CameraTargetPlayer::SeqNormal);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
	{
		// 1�t���[���Ńt���O���s
		m_is_speed_up = true;

		m_is_move_down = true;
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
		// y���W�����~
		m_pos.y -= delta_time * 100;

	});
}