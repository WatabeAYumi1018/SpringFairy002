#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"

class Mediator;


// フェーズ管理クラス
// ゲームの進行状況を管理する

class StagePhase
{

public:

	enum class eStagePhase
	{
		e_flower,
		e_wood,
		e_fancy
	};

private:

	eStagePhase m_now_stage_phase = eStagePhase::e_flower;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(StagePhase, &StagePhase::SeqFlower);

	// メディエータのスマートポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;


	// お花エリア
	bool SeqFlower(const float delta_time);
	// 森林エリア
	bool SeqWood(const float delta_time);
	// 花の世界
	bool SeqFancy(const float delta_time);

public:

	void Update(float delta_time);

	eStagePhase GetNowStagePhase() { return m_now_stage_phase; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};