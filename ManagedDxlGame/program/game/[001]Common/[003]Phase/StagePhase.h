#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// ステージのエリア管理を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class StagePhase
{

public:

	//-----------------------------------enum class------------------------------------//

	// ステージのエリアフェーズ
	enum class eStagePhase
	{
		e_flower,
		e_wood,
		e_fancy,
		e_end
	};
	
	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ---------------------------//

	StagePhase() {}
	~StagePhase() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// 現在のステージフェーズ
	eStagePhase m_now_stage = eStagePhase::e_flower;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(StagePhase, &StagePhase::SeqFlower);

	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//

	
	//-----------------------------------メンバ関数-----------------------------------//

	// フェーズ遷移
	void PhaseChange();

	// お花エリア	
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFlower(const float delta_time);

	// 森林エリア
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqWood(const float delta_time);

	// 花の世界
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFancy(const float delta_time);

public:

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 現在のステージフェーズを取得
	const eStagePhase& GetNowStagePhase() const { return m_now_stage; }

	// メディエータのポインタ設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};