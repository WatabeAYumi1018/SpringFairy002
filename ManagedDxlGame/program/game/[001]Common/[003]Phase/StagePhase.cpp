#include "../[002]Mediator/Mediator.h"
#include "StagePhase.h"


void StagePhase::Update(float delta_time)
{
	PhaseChange();

	tnl_sequence_.update(delta_time);
}

void StagePhase::PhaseChange()
{
	if (m_mediator->GetEventLane().s_id == 6)
	{
		m_now_stage = eStagePhase::e_wood;
	}
	else if (m_mediator->GetEventLane().s_id == 9)
	{
		m_now_stage = eStagePhase::e_fancy;
	}
}

// ストーリー画面
bool StagePhase::SeqFlower(const float delta_time)
{
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
	// メッセージ終わったら
	//if ()
	//{
		//エンディングフラグon
	//}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}
