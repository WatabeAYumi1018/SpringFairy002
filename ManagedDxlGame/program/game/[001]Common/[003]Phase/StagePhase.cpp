#include "../[002]Mediator/Mediator.h"
#include "StagePhase.h"


void StagePhase::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

// ストーリー画面
bool StagePhase::SeqFlower(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_stage_phase = eStagePhase::e_flower;
	}

	// 二番の映像が開始したら
	if (m_mediator-> GetCinemaBackIsSecond())
	{
		tnl_sequence_.change(&StagePhase::SeqWood);
	}

	// 再生が終了するまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}

bool StagePhase::SeqWood(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_stage_phase = eStagePhase::e_wood;
	}

	// 三番の映像が開始したら
	if (m_mediator->GetCinemaBackIsThird())
	{
		tnl_sequence_.change(&StagePhase::SeqFancy);
	}

	// 押すまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}

bool StagePhase::SeqFancy(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_stage_phase = eStagePhase::e_fancy;
	}

	// 再び会話が終了したら
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		//エンディングフラグon
	}

	// 押すまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}
