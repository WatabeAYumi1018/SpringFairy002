#pragma once
#include "../../../library/tnl_sequence.h"

class Mediator;


// フェーズ管理クラス
// ゲームの進行状況を管理する

class StagePhase
{

public:

	enum class eStagePhase
	{
		e_fly,
		e_ground
	};

private:

	eStagePhase m_now_stage_phase = eStagePhase::e_fly;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(StagePhase, &StagePhase::SeqFly);


	// 空中
	bool SeqFly(const float delta_time);
	// 地上
	bool SeqGround(const float delta_time);

public:

	void Update(float delta_time);

	eStagePhase GetNowStagePhase() { return m_now_stage_phase; }
};