#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../../../../../[000]GameEngine/[000]Engine/Engine.h"
#include "../../../../[003]Phase/StagePhase.h"
#include "../../../[000]Stage/[001]Lane/Lane.h"


class Mediator;

// Moverクラス（プレイヤー、エネミーなど移動に関する処理を行う）

class PlayerMove
{

private:
	
	// 宙返りの経過時間
	float m_salto_elapsed_time = 0;

	// ロールの回転速度
	float m_rolling_rotation = 10;
	// 八の字の回転速度
	float m_figure_eight_rotation = 10;

	tnl::Vector3 m_game_pos;
	// ターゲット計算で一時的に使用
	tnl::Quaternion m_target_rot;
	//モデルの回転取得用
	tnl::Quaternion m_rot;

	// 上下左右の方向
	eDirection direction = eDirection::e_none;
	// 現在のステージフェーズ
	//StagePhase::eStagePhase m_stage_phase = StagePhase::eStagePhase::e_flower;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(PlayerMove, &PlayerMove::SeqNormal);


	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	// プレイヤーメディエータのスマートポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;


	void MoveMatrix(float delta_time);

	// 空中移動でのモデル回転定義
	void ControlMoveMatrix(float delta_time);
	// 宙返りアクションでのモデル回転定義
	void SaltoActionMatrix(float delta_time);
	// ロール回転アクションでのモデル回転定義
	void RollingActionMatrix(float delta_time);
	// 八の字アクションでのモデル回転定義
	void FigureEightActionMatrix(float delta_time);


	// 通常の移動処理
	bool SeqNormal(const float delta_time);
	// 停止処理
	bool SeqStop(const float delta_time);
	// 上昇処理
	bool SeqUpMove(const float delta_time);
	// 下降処理
	bool SeqDownMove(const float delta_time);

	// 宙返りアクション
	bool SeqSaltoAction(const float delta_time);
	// ロール回転アクション 
	bool SeqRollingAction(const float delta_time);
	// 八の字アクション
	bool SeqFigureEightAction(const float delta_time);

public:

	// ボタン操作定義
	bool PushButton();

	void Update(float delta_time);


	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>>& astar)
	{
		m_astar = astar;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};