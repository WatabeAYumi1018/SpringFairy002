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

// ストーリー画面
bool StagePhase::SeqFlower(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		SetDefaultLightParameter("directional_light001.bin");
	}

	// 二番の映像が開始したら
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

	// 14に入ったらEDへ
	if (m_mediator->GetPlayerPos().y > m_goal_pos_y)
	{
		m_now_stage = eStagePhase::e_end;
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}