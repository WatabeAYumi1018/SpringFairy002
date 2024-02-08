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

void LaneMove::MoveAstarTarget(const float delta_time, tnl::Vector3& pos) 
{	
	// ゴールまでの経路を取得し、最後のグリッドかどうかを確認
	if (m_now_step >= m_goal_process.size()) 
	{
		m_goal_process.clear();
	
		return; // 処理を終了
	}
	
	// ゴールまでの経路を取得
	m_current_grid = m_goal_process[m_now_step];
	m_next_grid = m_goal_process[m_now_step + 1];

	// 次のグリッドの中心座標を取得
	tnl::Vector3 next_center_pos
		= wta::ConvertGridIntToFloat(m_next_grid, Lane::LANE_SIZE)
		+ tnl::Vector3(Lane::LANE_SIZE / 2, 0, Lane::LANE_SIZE / 2);

	// 現在の位置から中心座標への方向ベクトルを計算
	m_target_direction = next_center_pos - pos;

	// 中心座標までの距離を計算
	float distance_to_center = abs(m_target_direction.length());
	
	// 中心付近に到達したらステップ更新
	StepUpdate(delta_time, distance_to_center, pos);
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

	// 斜め移動の場合
	if (m_current_grid.first != m_next_grid.first
		&& m_current_grid.second != m_next_grid.second)
	{
		// ターゲットが次のグリッドの中心に近づくまで直進
		// 中心座標までの距離を計算
		float distance_to_center = abs(m_target_direction.length());
		
		// ターゲットが中心に近づくまで直進
		if (distance_to_center <= Lane::LANE_SIZE / 100)
		{
			m_chara_direction = m_target_direction;

			m_chara_direction.normalize();
		}
		// 次のグリッドの中心へ向かって直進
		else
		{
			m_chara_direction= m_target_direction;
			
			m_chara_direction.normalize();
		}
	}

	// 直線の場合
	else
	{
		// 両グリッドの中心座標を計算
		tnl::Vector3 current_grid_pos
			= wta::ConvertGridIntToFloat(m_current_grid, Lane::LANE_SIZE);

		tnl::Vector3 next_grid_pos
			= wta::ConvertGridIntToFloat(m_next_grid, Lane::LANE_SIZE);

		// 次のグリッドへの方向ベクトルを計算
		m_chara_direction = (next_grid_pos - current_grid_pos);
		m_chara_direction.normalize();
	}

	// 方向ベクトルが存在する場合
	if (m_chara_direction.length() > 0)
	{
		if (m_mediator->GetIsTargetSpeedUp())
		{
			// 移動速度を上げる
			pos += m_chara_direction * m_move_speed * delta_time * 5;
		}
		else
		{
			// プレイヤーの移動
			pos += m_chara_direction * m_move_speed * delta_time * 2;
		}
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

	// 回転速度を算出
	float rot_speed = delta_time * m_move_rotation / 4;
	// 滑らかに回転を更新
	rot.slerp(new_rot, rot_speed);
}

void LaneMove::StepUpdate(const float delta_time, float distance, tnl::Vector3& pos)
{
	// 中心座標までの距離が一定以下になったら
	if (distance <= Lane::LANE_SIZE / 100)
	{
		// 次のグリッドに進む
		m_now_step++;

		// ステップ更新後のグリッドを設定
		UpdateGrids();
	}
	else
	{
		// 単位ベクトルに変換
		m_target_direction.normalize();

		if (m_mediator->GetIsTargetSpeedUp())
		{
			// 移動速度を上げる
			pos += m_target_direction * m_move_speed * delta_time * 5;
		}
		else
		{
			// 現在のグリッドの中心へ向かって移動
			pos += m_target_direction * m_move_speed * delta_time * 2;
		}
	}
}

void LaneMove::UpdateGrids()
{
	// 次のグリッド位置を更新
	if (m_now_step < m_goal_process.size())
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
		if (goal.s_id == 2)
		{
			return goal;
		}
	}
}



//void LaneMove::MoveAstarTarget(const float delta_time, tnl::Vector3& pos)
//{
//	// ゴールまでの経路を取得し、最後のグリッドかどうかを確認
//	if (m_now_step >= m_goal_process.size())
//	{
//		m_goal_process.clear();
//
//		return; // 処理を終了
//	}
//	// ゴールまでの経路を取得
//	std::pair<int, int> current_grid = m_goal_process[m_now_step];
//	// 現在のグリッドの中心座標を取得
//	tnl::Vector3 current_center_pos
//		= wta::ConvertGridIntToFloat(current_grid, Lane::LANE_SIZE)
//		+ tnl::Vector3(Lane::LANE_SIZE / 2, 0, Lane::LANE_SIZE / 2);
//
//	// 現在の位置から中心座標への方向ベクトルを計算
//	m_target_direction = current_center_pos - pos;
//
//	// 中心座標までの距離を計算
//	float distance_to_center = abs(m_target_direction.length());
//
//	// 中心座標までの距離が一定以下になったら
//	if (distance_to_center <= Lane::LANE_SIZE / 100)
//	{
//		// 次のグリッドに進む
//		m_now_step++;
//	}
//	else
//	{
//		// 単位ベクトルに変換
//		m_target_direction.normalize();
//
//		if (m_mediator->GetIsTargetSpeedUp())
//		{
//			// 移動速度を上げる
//			pos += m_target_direction * m_move_speed * delta_time * 5;
//		}
//		else
//		{
//			// 現在のグリッドの中心へ向かって移動
//			pos += m_target_direction * m_move_speed * delta_time * 2;
//		}
//	}
//}
//
//void LaneMove::MoveAstarCharaPos(const float delta_time, tnl::Vector3& pos)
//{
//	if (m_now_step >= m_goal_process.size())
//	{
//		// 既にゴールプロセスが終了している場合は何もしない
//		return;
//	}
//
//	// 現在のグリッド位置
//	std::pair<int, int> current_grid = m_goal_process[m_now_step];
//	// 次のグリッド位置
//	std::pair<int, int> next_grid;
//
//	if (m_now_step + 1 < m_goal_process.size())
//	{
//		// 次のグリッドが存在する場合は、それを取得
//		next_grid = m_goal_process[m_now_step + 1];
//	}
//	else
//	{
//		// 最後のグリッドにいる場合は、現在のグリッドを次のグリッドとして扱う
//		// 現在の方向を維持
//		next_grid = current_grid;
//	}
//	// 両グリッドの中心座標を計算
//	tnl::Vector3 current_grid_pos
//		= wta::ConvertGridIntToFloat(current_grid, Lane::LANE_SIZE);
//
//	tnl::Vector3 next_grid_pos
//		= wta::ConvertGridIntToFloat(next_grid, Lane::LANE_SIZE);
//
//	// 次のグリッドへの方向ベクトルを計算
//	m_chara_direction = (next_grid_pos - current_grid_pos);
//	m_chara_direction.normalize();
//
//	// 方向ベクトルが存在する場合
//	if (m_chara_direction.length() > 0)
//	{
//		if (m_mediator->GetIsTargetSpeedUp())
//		{
//			// 移動速度を上げる
//			pos += m_chara_direction * m_move_speed * delta_time * 5;
//		}
//		else
//		{
//			// プレイヤーの移動
//			pos += m_chara_direction * m_move_speed * delta_time * 2;
//		}
//	}
//	else
//	{
//		// ここでゲーム終了処理
//		pos.z += m_move_speed * delta_time;
//	}
//
//	// 斜め移動の判定
//	if (current_grid.first != next_grid.first
//		&& current_grid.second != next_grid.second)
//	{
//		// current_timeを更新
//		m_current_time += delta_time;
//
//		// current_timeがblend_timeを超えないように制限
//		if (m_current_time > m_blend_time) m_current_time = m_blend_time;
//
//		// UniformLerpを使用して現在の方向と目標の方向を補間
//		m_chara_direction
//			= tnl::Vector3::UniformLerp(m_chara_direction, m_target_direction, m_blend_time, m_current_time);
//	}
//	else
//	{
//		// 斜め移動でない場合はcurrent_timeをリセット
//		m_current_time = 0.0f;
//	}
//}



//void LaneMove::UpdateRotation(const tnl::Vector3& direction, tnl::Quaternion& rot, const float delta_time) {
//	// 新しい回転を算出
//	tnl::Quaternion new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + direction);
//
//	// 滑らかに回転を更新
//	rot.slerp(new_rot, delta_time * m_move_rotation);
//}

//void LaneMove::MoveAstar(const float delta_time
//						 , tnl::Vector3& pos
//						 , tnl::Quaternion& rot)
//{
//	if (m_now_step < m_goal_process.size())
//	{
//		// ゴールまでの経路を取得
//		std::pair<int, int> process_pos = m_goal_process[m_now_step];
//		//ゴールまでの経路をワールド座標に変換
//		tnl::Vector3 goal_process_pos
//			= wta::ConvertGridIntToFloat(process_pos, Lane::LANE_SIZE);
//		// プレイヤーの座標と回転の更新
//		AutoMoveMatrix(delta_time, goal_process_pos, pos,rot);
//	}
//}
//
//void LaneMove::MoveAstarPos(const float delta_time, tnl::Vector3& pos)
//{
//	if (m_now_step < m_goal_process.size())
//	{
//		// ゴールまでの経路を取得
//		std::pair<int, int> process_pos = m_goal_process[m_now_step];
//		//ゴールまでの経路をワールド座標に変換
//		tnl::Vector3 goal_process_pos
//			= wta::ConvertGridIntToFloat(process_pos, Lane::LANE_SIZE);
//		// ターゲットの座標と回転の更新
//		AutoMovePos(delta_time, goal_process_pos, pos);
//		// ターゲットが目標地点に到達した場合
//		if (ReachedNextLane(goal_process_pos, pos))
//		{
//			// 次のステップに進む
//			m_now_step++;
//		}
//		else
//		{
//			// 進行不可エリア（-1）に入ったかどうかのチェック
//			int current_tile_id = m_astar->getTileID(wta::ConvertFloatToGridInt(pos, Lane::LANE_SIZE), m_mediator->GetStageLane(), Lane::LANE_SIZE);
//			
//			// 現在地が進行不可エリアなら
//			if (current_tile_id == -1) 
//			{
//				// 修正するために次の進行可能なタイルを探す
//				int next_step = m_now_step + 1;
//				if (next_step < m_goal_process.size())
//				{
//					std::pair<int, int> next_process_pos = m_goal_process[next_step];
//					tnl::Vector3 next_goal_process_pos = wta::ConvertGridIntToFloat(next_process_pos, Lane::LANE_SIZE);
//
//					// 次に進むべきタイルへの方向ベクトルを計算
//					tnl::Vector3 correction_direction = next_goal_process_pos - pos;
//					correction_direction.normalize();
//
//					// 座標を即座に修正
//					pos += correction_direction * m_move_speed * delta_time;
//				}
//			}
//		}
//	}
//	else
//	{
//		// ゴールに到達したら終了
//		m_goal_process.clear();
//	}
//}

//void LaneMove::AutoMoveMatrix(const float delta_time
//							  , tnl::Vector3& goal_pos
//							  , tnl::Vector3& pos
//							  , tnl::Quaternion& rot)
//{
//	AutoMovePos(delta_time, goal_pos, pos);
//	// 新しい回転を算出（direction方向を向くように）
//	tnl::Quaternion new_rot;
//
//	// 現在の位置から目標位置への方向ベクトルを計算
//	tnl::Vector3 direction = pos - goal_pos;
//	// 必要に応じて正規化
//	direction.normalize();
//
//	// 回転を算出
//	new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + direction);
//
//	if (m_look_side_right || m_look_side_left)
//	{
//		tnl::Vector3 camera_direction = m_mediator->GetCameraForward();
//
//		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos - camera_direction);
//	}
//
//	// 回転速度を算出
//	float rot_speed = delta_time * m_move_rotation / 4;
//	// 滑らかに回転を更新
//	rot.slerp(new_rot, rot_speed);
//}
//
//void LaneMove::AutoMovePos(float delta_time
//							, tnl::Vector3& goal_pos
//							, tnl::Vector3& pos)
//{
//	// 現在の座標とゴールまでの座標の差を算出
//	m_new_pos = goal_pos - pos;
//	// 正規化
//	m_new_pos.normalize();
//	// 座標を更新
//	pos += m_new_pos * m_move_speed * delta_time;
//}
//
//

//
//bool LaneMove::ReachedNextLane(tnl::Vector3& goal_pos,tnl::Vector3& pos)
//{
//	// プレイヤー座標とゴールの差を算出
//	float distance_pos = (goal_pos - pos).length();
//	// 比較のために型変換
//	int distance = static_cast<int>(distance_pos);
//
//	return distance < Lane::LANE_SIZE;
//}

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