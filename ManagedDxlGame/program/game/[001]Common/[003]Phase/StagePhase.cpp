#include "../dxlib_ext/dxlib_ext.h"
#include "StagePhase.h"
#include "../[002]Mediator/Mediator.h"


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

	// プレイヤーがダンスしたら変更
	if (m_mediator-> GetIsPlayerEventDance())
	{
		tnl_sequence_.change(&StagePhase::SeqWood);
	}

	// 再生が終了するまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		DrawStringEx(0,0,1,"fly");
	});

	TNL_SEQ_CO_END;
}

bool StagePhase::SeqWood(const float delta_time)
{
	// 再び会話が終了したら
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		tnl_sequence_.change(&StagePhase::SeqFancy);
	}

	//TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]() 
	//{
	//		
	//});

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() 
	{
		m_now_stage_phase = eStagePhase::e_wood;
	});

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
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		DrawStringEx(0, 0, 1, "fancy");
	});

	TNL_SEQ_CO_END;
}
