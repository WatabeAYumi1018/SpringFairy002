#include "LaneMove.h"
#include "../../../../[002]Mediator/Mediator.h"


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

void LaneMove::MoveAstarTarget(const float delta_time, tnl::Vector3& pos) 
{	
	// ゴールまでの経路を取得し、最後のグリッドかどうかを確認
	if (m_now_step >= m_goal_process.size()) 
	{
		// ゴールまでの経路をクリア
		m_goal_process.clear();
		// 処理を終了
		return; 
	}
	
	// 現在のグリッドを設定
	m_current_grid = m_goal_process[m_now_step];
	// 次のグリッドを設定
	UpdateGrids();

	// 次のグリッドの中心座標を取得
	// 2 : 中心座標を取得するための定数
	tnl::Vector3 next_center_pos
		= wta::ConvertGridIntToFloat(m_next_grid, Lane::LANE_SIZE)
		+ tnl::Vector3(Lane::LANE_SIZE / 2, 0, Lane::LANE_SIZE / 2);

	// 現在の位置から中心座標への方向ベクトルを計算
	m_target_direction = next_center_pos - pos;

	// 中心座標までの距離を計算
	float distance_to_center = m_target_direction.length();
	
	// 中心付近に到達したらステップ更新
	StepUpdate(delta_time, distance_to_center, pos);

	// 移動のためベクトル正規化
	m_target_direction.normalize();
	// 移動速度を更新
	MoveSpeed(delta_time, m_target_direction, pos);
}

void LaneMove::MoveAstarCharaPos(const float delta_time, tnl::Vector3& pos)
{
	if (m_now_step >= m_goal_process.size())
	{
		// 既にゴールプロセスが終了している場合は何もしない
		return;
	}

	// 現在のグリッド位置
	UpdateGrids();

	// 両グリッドの座標を計算
	tnl::Vector3 current_grid_pos
			= wta::ConvertGridIntToFloat(m_current_grid, Lane::LANE_SIZE);

	tnl::Vector3 next_grid_pos
		= wta::ConvertGridIntToFloat(m_next_grid, Lane::LANE_SIZE);

	// 次のグリッドへの方向ベクトルを計算
	m_chara_direction = next_grid_pos - current_grid_pos;
	m_chara_direction.normalize();
	
	// 方向ベクトルが存在する場合
	if (m_chara_direction.length() > 0)
	{
		// 移動速度を更新
		MoveSpeed(delta_time, m_chara_direction, pos);
	}
	else
	{
		// ここでゲーム終了処理
		pos.z += m_move_speed * delta_time;
	}
}

void LaneMove::MoveAstarCharaRot(const float delta_time, tnl::Vector3& pos, tnl::Quaternion& rot)
{
	// 新しい回転を算出
	tnl::Quaternion new_rot
		= tnl::Quaternion::LookAtAxisY(pos, pos + m_chara_direction);

	if (m_look_side_right || m_look_side_left)
	{
		tnl::Vector3 camera_direction = m_mediator->GetCameraForward();

		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + camera_direction);
	}

	if (m_chara_direction.length() < 0)
	{
		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(0, 0, 1));
	}

	// 回転速度を算出
	float rot_speed = delta_time * m_move_rotation / 4;
	// 滑らかに回転を更新
	rot.slerp(new_rot, rot_speed);
}

void LaneMove::MoveSpeed(const float delta_time, tnl::Vector3& direction,tnl::Vector3& pos)
{
	float max_move_speed = 5;
	float normal_move_speed = 2;

	if (m_mediator->GetIsTargetSpeedUp())
	{
		// 移動速度を上げる
		pos += direction * m_move_speed * delta_time * max_move_speed;
	}
	else
	{
		// 現在のグリッドの中心へ向かって移動
		pos += direction * m_move_speed * delta_time * normal_move_speed;
	}
}

void LaneMove::StepUpdate(const float delta_time, float distance, tnl::Vector3& pos)
{
	// 中心座標までの距離が一定以下になったら
	// 100 : 中心点からの距離（殆ど変更予定ないため固定値）
	if (distance <= Lane::LANE_SIZE / 100)
	{
		// 次のグリッドに進む
		m_now_step++;

		// ステップ更新後のグリッドを設定
		UpdateGrids();
	}
}

void LaneMove::UpdateGrids()
{
	// 次のグリッド位置を更新
	if (m_now_step + 1 < m_goal_process.size())
	{
		m_next_grid = m_goal_process[m_now_step + 1];
	}
	else
	{
		// 最後のグリッドにいる場合は、現在のグリッドを次のグリッドとして扱う
		// 現在の方向を維持
		m_next_grid = m_current_grid;
	}
}

Lane::sLane LaneMove::GoalTile()
{
	std::vector<Lane::sLane> goal_process
					= m_mediator->GetStageLane();

	for (Lane::sLane& goal : goal_process)
	{
		// ゴールのレーンIDを取得
		if (goal.s_id == 2)
		{
			return goal;
		}
	}
}