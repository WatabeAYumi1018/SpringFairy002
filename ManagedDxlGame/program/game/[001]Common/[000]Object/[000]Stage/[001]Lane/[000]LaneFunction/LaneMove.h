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

	// 移動速度
	float m_move_speed = 200;
	// 移動回転速度
	float m_move_rotation = 10;

	// 補間が完了するまでの時間（秒）
	float m_blend_time = 1.0f; 
	// 現在の補間時間
	float m_current_time = 0.0f;

	// 斜め移動開始のフラグ
	bool m_is_diagonal = false;
	// 右からのサイド視点(視線先は左)
	bool m_look_side_right = false;
	// 左からのサイド視点(視線先は右)
	bool m_look_side_left = false;

	tnl::Vector3 m_target_direction;
	tnl::Vector3 m_chara_direction;
	// 現在のグリッドの中心点
	tnl::Vector3 m_current_center_pos;

	// 現在のグリッド位置
	std::pair<int, int> m_current_grid;
	// 次のグリッド位置
	std::pair<int, int> m_next_grid;


	// A*からの経路
	std::vector<std::pair<int, int>> m_goal_process;

	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ターゲットが中心に到達したか判定
	void StepUpdate(const float delta_time,float distance, tnl::Vector3& pos);
	// 座標更新の速度調整
	void MoveSpeed(const float delta_time, tnl::Vector3& pos);
	// グリッドの更新処理
	void UpdateGrids();

	// ゴールのレーンIDを取得
	Lane::sLane GoalTile();


public:

	// ゴールまでの経路を取得
	void GetAutoMove();

	// キャラクターの座標更新
	void MoveAstarCharaPos(const float delta_time, tnl::Vector3 & pos);
	
	void MoveAstarCharaRot(const float delta_time, tnl::Vector3& pos, tnl::Quaternion& rot);
	// ターゲットの座標とレーン更新
	void MoveAstarTarget(const float delta_time, tnl::Vector3& pos);



	void SetLookSideRight(bool look_side_right) { m_look_side_right = look_side_right; }

	bool GetLookSideRight() const { return m_look_side_right; }

	void SetLookSideLeft(bool look_side_left) { m_look_side_left = look_side_left; }

	bool GetLookSideLeft() const { return m_look_side_left; }

	const tnl::Vector3& GetCharaDirection() const
	{
		return m_chara_direction;
	}

	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>>& astar)
	{
		m_astar = astar;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};


//void SetNowPos(tnl::Vector3 pos) { m_now_pos = pos; }

//tnl::Vector3 GetNewPos() const { return m_new_pos; }

//void SetNowRot(tnl::Quaternion rot) { m_now_rot = rot; }

//tnl::Quaternion GetNewRot() const { return m_new_rot; }


	//// 自動運転による行列更新
	//void AutoMoveMatrix(const float delta_time
	//					, tnl::Vector3& goal_pos
	//					, tnl::Vector3& pos
	//					, tnl::Quaternion& rot);

	//// 自動運転による座標更新
	//void AutoMovePos(float delta_time
	//				 , tnl::Vector3& goal_pos
	//				 , tnl::Vector3& pos);

	// Aスターによる自動運転行列更新処理
	//void MoveAstar(const float delta_time
	//				, tnl::Vector3& pos
	//				, tnl::Quaternion& rot);


	//void MoveToGridCenter(const float delta_time, tnl::Vector3& pos, tnl::Quaternion& rot);

	//// 次のレーンに到達したか判定(他クラスでの使用のための簡易条件関数)
	//bool NextLane();

	//// 次のレーンに到達したか判定
	//bool ReachedNextLane(tnl::Vector3& goal_pos, tnl::Vector3& pos);

	//void UpdateRotation(const tnl::Vector3& direction, tnl::Quaternion& rot, const float delta_time);
