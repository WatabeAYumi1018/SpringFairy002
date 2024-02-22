#include "../../[000]GameEngine/[001]Music/MusicManager.h"
#include "../[002]Mediator/Mediator.h"
#include "StagePhase.h"



void StagePhase::Update(const float delta_time)
{
	PhaseChange();

	tnl_sequence_.update(delta_time);
}

void StagePhase::PhaseChange()
{
	if (m_mediator->GetCurrentEventLane().s_id == 7)
	{
		m_now_stage = eStagePhase::e_wood;
	}
	else if (m_mediator->GetCurrentEventLane().s_id == 10)
	{
		m_now_stage = eStagePhase::e_fancy;
	}
}

// �X�g�[���[���
bool StagePhase::SeqFlower(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		SetDefaultLightParameter("directional_light001.bin");
	}

	// ��Ԃ̉f�����J�n������
	if (m_now_stage == eStagePhase::e_wood)
	{
		tnl_sequence_.change(&StagePhase::SeqWood);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}

bool StagePhase::SeqWood(const float delta_time)
{
	if (m_now_stage == eStagePhase::e_fancy)
	{
		tnl_sequence_.change(&StagePhase::SeqFancy);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}

bool StagePhase::SeqFancy(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		SetDefaultLightParameter("directional_light001.bin");
	}

	// 14�ɓ�������ED��
	if (m_mediator->GetPlayerPos().y > 2000
		&& m_mediator->GetPartnerPos().y > 2000)
	{
		m_now_stage = eStagePhase::e_end;
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}