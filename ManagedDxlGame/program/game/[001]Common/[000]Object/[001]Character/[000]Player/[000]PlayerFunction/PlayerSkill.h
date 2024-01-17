#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../[000]GamEngine/[000]Engine/Engine.h"

class Mediator;

class PlayerSkill
{

public:

	enum class ePlayerSkill
	{
		// 能力無し
		e_normal,
		// 浄化能力
		e_bouquet,
		// 癒しの舞（ボス戦用）
		e_dance,
	};

private:

	ePlayerSkill m_now_player_skill = ePlayerSkill::e_normal;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(PlayerSkill, &PlayerSkill::SeqNormal);

	// メディエーターポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;


	// ノーマル
	bool SeqNormal(const float delta_time);
	// 浄化能力
	bool SeqBouquet(const float delta_time);
	// 癒しの舞
	bool SeqDance(const float delta_time);

public:

	void Update(float delta_time);

	ePlayerSkill GetNowPlayerSkill() { return m_now_player_skill; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}	
};