#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PartnerDraw.h"


PartnerDraw::~PartnerDraw()
{
	MV1DeleteModel(m_model_hdl);
	MV1DeleteModel(m_anim_bone_idle_hdl);
	MV1DeleteModel(m_anim_bone_move_hdl);
}

void PartnerDraw::Initialize()
{
	// ���f���ǂݎ��
	m_model_hdl = m_mediator->GetPartnerModelHdl();
	// idle�{�[��
	m_anim_bone_idle_hdl 
		= m_mediator->GetPartnerAnimBoneIdleHdl();
	// move�{�[��
	m_anim_bone_move_hdl 
		= m_mediator->GetPartnerAnimBoneMoveHdl();
}

void PartnerDraw::Update(const float delta_time)
{
	tnl_sequence_.update(delta_time);
}

void PartnerDraw::Draw()
{
	MV1DrawModel(m_model_hdl);
}

void PartnerDraw::AnimMove(const float delta_time)
{
	// move�A�j���[�V�����X�V����
	m_elapsed_time_move += m_anim_speed * delta_time;

	if (m_elapsed_time_move > m_time_count_move)
	{
		m_elapsed_time_move -= m_time_count_move;
	}

	MV1SetAttachAnimTime(m_model_hdl
						, m_anim_move_index
						, m_elapsed_time_move);
}

void PartnerDraw::AnimIdle(const float delta_time)
{
	// idle�A�j���[�V�����X�V����
	m_elapsed_time_idle += m_anim_speed * delta_time;

	if (m_elapsed_time_idle > m_time_count_idle)
	{
		m_elapsed_time_idle -= m_time_count_idle;
	}

	MV1SetAttachAnimTime(m_model_hdl, m_anim_idle_index, m_elapsed_time_idle);
}

bool PartnerDraw::SeqMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		MV1DetachAnim(m_model_hdl, m_anim_move_index);

		m_anim_move_index
			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_move_hdl);

		m_time_count_move
			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_move_index);
	}

	// �{�^���������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimMove(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool PartnerDraw::SeqIdle(const float delta_time)
{
	// �Ăяo�����O�Ƀf�^�b�`�i��x�������s�j
	if (tnl_sequence_.isStart())
	{
		MV1DetachAnim(m_model_hdl, m_anim_idle_index);

		m_anim_idle_index
			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_idle_hdl);

		m_time_count_idle
			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_idle_index);
	}

	// �{�^�����������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimIdle(delta_time);
	});

	TNL_SEQ_CO_END;
}