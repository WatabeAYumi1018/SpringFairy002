#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"

///////////////////////////////////////////////////////////////////////////
//
// ステージのエリア管理を行うクラス
//
///////////////////////////////////////////////////////////////////////////

class Mediator;

class StagePhase
{

public:

	enum class eStagePhase
	{
		e_flower,
		e_wood,
		e_fancy,
		e_end
	};

private:

	eStagePhase m_now_stage = eStagePhase::e_flower;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(StagePhase, &StagePhase::SeqFlower);

	std::shared_ptr<Mediator> m_mediator = nullptr;

	void PhaseChange();

	// お花エリア
	bool SeqFlower(const float delta_time);
	// 森林エリア
	bool SeqWood(const float delta_time);
	// 花の世界
	bool SeqFancy(const float delta_time);

public:

	void Update(float delta_time);

	const eStagePhase& GetNowStagePhase() const { return m_now_stage; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};