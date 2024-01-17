#include "LaneMove.h"
#include "../../../../[002]Mediator/Mediator.h"



LaneMove::~LaneMove()
{
	m_goal_process.clear();
}

void LaneMove::GetAutoMove()
{
	// csvのレーン情報を取得
	std::vector<Lane::sLane> lanes = m_mediator->GetStageLane();
	// ゴールのレーンIDを取得
	Lane::sLane goal_tile = GoalTile();
	// レーンの幅を取得
	int width = m_mediator->GetStageLaneWidth();
	// レーンの高さを取得
	int height = m_mediator->GetStageLaneHeight();
	// プレイヤーの座標を取得
	tnl::Vector3 pos = m_mediator->GetPlayerPos();
	// プレイヤーの初期位置から算出
	m_astar->SearchTileID_AStar(pos, goal_tile, Lane::LANE_SIZE, lanes, width, height);
	// ゴールまでの経路を取得
	m_goal_process = m_astar->GetGoalProcess();
}

void LaneMove::MoveAstar(const float delta_time
						 , tnl::Vector3& pos
						 , tnl::Quaternion& rot)
{
	if (m_now_step < m_goal_process.size())
	{
		// ゴールまでの経路を取得
		std::pair<int, int> process_pos = m_goal_process[m_now_step];
		//ゴールまでの経路をワールド座標に変換
		tnl::Vector3 goal_process_pos
			= wta::ConvertGridIntToFloat(process_pos, Lane::LANE_SIZE);
		// プレイヤーの座標と回転の更新
		AutoMoveMatrix(delta_time, goal_process_pos, pos,rot);
	}
}

void LaneMove::MoveAstarPos(const float delta_time, tnl::Vector3& pos)
{
	if (m_now_step < m_goal_process.size())
	{
		// ゴールまでの経路を取得
		std::pair<int, int> process_pos = m_goal_process[m_now_step];
		//ゴールまでの経路をワールド座標に変換
		tnl::Vector3 goal_process_pos
			= wta::ConvertGridIntToFloat(process_pos, Lane::LANE_SIZE);
		// ターゲットの座標と回転の更新
		AutoMovePos(delta_time, goal_process_pos, pos);
		// ターゲットが目標地点に到達した場合
		if (ReachedNextLane(goal_process_pos, pos))
		{
			// 次のステップに進む
			m_now_step++;
		}
	}
	else
	{
		// ゴールに到達したら終了
		m_goal_process.clear();
	}
}

void LaneMove::AutoMoveMatrix(const float delta_time
							  , tnl::Vector3& goal_pos
							  , tnl::Vector3& pos
							  , tnl::Quaternion& rot)
{
	AutoMovePos(delta_time, goal_pos, pos);
	// 新しい回転を算出（direction方向を向くように）
	tnl::Quaternion new_rot;

	if (m_look_side_right)
	{
		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(-1, 0, 0));
	}
	else if (m_look_side_left)
	{
		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(1, 0, 0));
	}
	else
	{
		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + m_new_pos);
	}
	// 回転速度を算出
	float rot_speed = delta_time * m_move_rotation / 4;
	// 滑らかに回転を更新
	rot.slerp(new_rot, rot_speed);
}

void LaneMove::AutoMovePos(float delta_time
							, tnl::Vector3& goal_pos
							, tnl::Vector3& pos)
{
	// 現在の座標とゴールまでの座標の差を算出
	m_new_pos = goal_pos - pos;
	// 正規化
	m_new_pos.normalize();
	// 座標を更新
	pos += m_new_pos * m_move_speed * delta_time;
}


Lane::sLane LaneMove::GoalTile()
{
	for (const auto& goal : m_mediator->GetStageLane())
	{
		if (goal.s_id == 2)
		{
			return goal;
		}
	}
}

bool LaneMove::ReachedNextLane(tnl::Vector3& goal_pos,tnl::Vector3& pos)
{
	// プレイヤー座標とゴールの差を算出
	float distance_pos = (goal_pos - pos).length();
	// 比較のために型変換
	int distance = static_cast<int>(distance_pos);

	return distance < Lane::LANE_SIZE;
}

//bool LaneMove::NextLane()
//{
//	// 次のステップに進んだ場合
//	if (m_now_step != m_old_step)
//	{
//		// 新しいレーンに移動したことを検出
//		m_old_step = m_now_step;
//
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}