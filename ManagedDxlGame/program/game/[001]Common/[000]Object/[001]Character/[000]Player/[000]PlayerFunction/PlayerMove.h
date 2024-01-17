#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../../../../../[000]GamEngine/[000]Engine/Engine.h"
#include "../../../../[003]Phase/StagePhase.h"
#include "../../../[000]Stage/[001]Lane/Lane.h"


class Mediator;

// Moverクラス（プレイヤー、エネミーなど移動に関する処理を行う）

class PlayerMove
{

private:

	//// 現在のステップインデックス
	//int m_current_step = 0;

	/// 移動速度
	//float m_move_speed = 0;
	//// 移動回転速度
	//float m_move_rotation = 0;
	//// 状況による移動速度変化
	//float m_move_change_speed = 1;

	//// 宙返りの移動速度
	//float m_salto_move_speed = 0;
	//// 宙返りの回転速度
	//float m_salto_rotation = 0;
	//// 宙返りの軌道半径
	//float m_salto_radius = 0;
	//// 宙返りの所要時間
	//float m_salto_total_time = 0;
	
	// 宙返りの経過時間
	float m_salto_elapsed_time = 0;

	// ロールの回転速度
	float m_rolling_rotation = 10;
	// 八の字の回転速度
	float m_figure_eight_rotation = 10;


	tnl::Vector3 m_pos;
	// ターゲット計算で一時的に使用
	tnl::Quaternion m_target_rot;
	//モデルの回転取得用
	tnl::Quaternion m_rot;

	//// 自動移動によるプレイヤーの新しい座標回転(カメラと連動)
	//tnl::Vector3 m_new_player_pos;
	//tnl::Quaternion m_new_player_rot;


	// 上下左右の方向
	eDirection direction = eDirection::none;
	// 現在のステージフェーズ
	StagePhase::eStagePhase m_stage_phase = StagePhase::eStagePhase::e_fly;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(PlayerMove, &PlayerMove::SeqFly);


	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	// プレイヤーメディエータのスマートポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 空中移動でのモデル回転定義
	void ControlMoveMatrix(float delta_time);
	// 宙返りアクションでのモデル回転定義
	void SaltoActionMatrix(float delta_time);
	// ロール回転アクションでのモデル回転定義
	void RollingActionMatrix(float delta_time);
	// 八の字アクションでのモデル回転定義
	void FigureEightActionMatrix(float delta_time);

	//// 地上でのモデル回転定義
	//void GroundMoveMatrix(float delta_time);

	// 足元のタイルIDを取得
	//int CurrentMoveLaneID();
	//// Aスターによる移動先定義
	//void MoveAstar(const float delta_time);
	//// 自動移動による座標と回転の更新
	//void AutoMoveMatrix(const float delta_time
	//					,tnl::Vector3& goal_pos);
	//// ゴール取得
	//Lane::sLane GoalTile();

	//// 次のレーンに到達したか判定
	//bool ReachedNextLane(const tnl::Vector3 goal_pos);

	// 空中
	bool SeqFly(const float delta_time);
	//// 地面
	//bool SeqGround(const float delta_time);
	// 宙返りアクション
	bool SeqSaltoAction(const float delta_time);
	// ロール回転アクション 
	bool SeqRollingAction(const float delta_time);
	// 八の字アクション
	bool SeqFigureEightAction(const float delta_time);

public:

	// ボタン操作定義
	bool PushButton();
	//// 自動経路の取得処理
	//void GetAutoMove();

	void Update(float delta_time);


	//int GetCurrentStep()
	//{
	//	return m_current_step;
	//}

	//tnl::Vector3 GetNewPlayerPos()
	//{
	//	return m_new_player_pos;
	//}

	//tnl::Quaternion GetNewPlayerRot()
	//{
	//	return m_new_player_rot;
	//}

	//// 移動速度変化を設定
	//void SetMoveChangeSpeed(float speed)
	//{
	//	m_move_change_speed = speed;
	//}

	//std::vector<std::pair<int, int>> GetGoalProcess()
	//{
	//	return m_goal_process;
	//}

	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>> astar)
	{
		m_astar = astar;
	}

	void SetMediator(std::shared_ptr<Mediator> mediator)
	{
		m_mediator = mediator;
	}
};