#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../Lane.h"

class Mediator;


class LaneMove
{

public:
	
	LaneMove() {}

	~LaneMove();

private:

	// 現在のステップインデックス
	int m_now_step = 0;
	int m_old_step = 0;

	// 移動速度
	float m_move_speed = 200;
	// 移動回転速度
	float m_move_rotation = 10;

	// 右からのサイド視点(視線先は左)
	bool m_look_side_right = false;
	// 左からのサイド視点(視線先は右)
	bool m_look_side_left = false;

	tnl::Vector3 m_new_pos;


	// A*からの経路
	std::vector<std::pair<int, int>> m_goal_process;


	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;


	// 自動運転による行列更新
	void AutoMoveMatrix(const float delta_time
						, tnl::Vector3& goal_pos
						, tnl::Vector3& pos
						, tnl::Quaternion& rot);

	// 自動運転による座標更新
	void AutoMovePos(float delta_time
					 , tnl::Vector3& goal_pos
					 , tnl::Vector3& pos);

	// ゴールのレーンIDを取得
	Lane::sLane GoalTile();
	// 次のレーンに到達したか判定
	bool ReachedNextLane(tnl::Vector3& goal_pos, tnl::Vector3& pos);


public:

	// ゴールまでの経路を取得
	void GetAutoMove();
	// Aスターによる自動運転行列更新処理
	void MoveAstar(const float delta_time
					, tnl::Vector3& pos
					, tnl::Quaternion& rot);

	void MoveAstarPos(const float delta_time, tnl::Vector3& pos);

	//// 次のレーンに到達したか判定(他クラスでの使用のための簡易条件関数)
	//bool NextLane();

	void SetLookSideRight(bool look_side_right) { m_look_side_right = look_side_right; }

	void SetLookSideLeft(bool look_side_left) { m_look_side_left = look_side_left; }


	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>> astar)
	{
		m_astar = astar;
	}

	void SetMediator(std::shared_ptr<Mediator> mediator)
	{
		m_mediator = mediator;
	}
};

//std::vector<std::pair<int, int>> GetGoalProcess()
//{
//	return m_goal_process;
//}

//void SetNowPos(tnl::Vector3 pos) { m_now_pos = pos; }

//tnl::Vector3 GetNewPos() const { return m_new_pos; }

//void SetNowRot(tnl::Quaternion rot) { m_now_rot = rot; }

//tnl::Quaternion GetNewRot() const { return m_new_rot; }