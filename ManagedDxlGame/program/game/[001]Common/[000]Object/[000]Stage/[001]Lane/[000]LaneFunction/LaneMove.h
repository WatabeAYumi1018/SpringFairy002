#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../Lane.h"

class Mediator;

/////////////////////////////////////////////////////////////////////////////////////////
// 
// 自動運転による移動処理のクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class LaneMove
{

public:
	
	//--------------------------コンストラクタ、デストラクタ--------------------------//

	LaneMove() {}
	~LaneMove() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

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

	// ターゲットプレイヤーの進行方向
	tnl::Vector3 m_target_direction;
	// キャラクターの進行方向
	tnl::Vector3 m_chara_direction;
	// 現在のグリッドの中心点
	tnl::Vector3 m_current_center_pos;

	// 現在のグリッド位置
	std::pair<int, int> m_current_grid;
	// 次のグリッド位置
	std::pair<int, int> m_next_grid;
	// A*からの経路
	std::vector<std::pair<int, int>> m_goal_process;

	// Astarのポインタ
	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// 座標更新の速度調整
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... 進行方向のベクトル
	// arg3 ... 該当オブジェクトの座標
	void MoveSpeed(const float delta_time, tnl::Vector3& direction, tnl::Vector3& pos);
	
	// ターゲットが中心に到達したか判定
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... 次のグリッドまでの距離
	// arg3 ... ターゲットの座標
	void StepUpdate(const float delta_time,float distance, tnl::Vector3& pos);
	
	// グリッドの更新処理
	void UpdateGrids();
	
	// ゴールのレーンIDを取得
	Lane::sLane GoalTile();

public:

	// ゴールまでの経路を取得
	void GetAutoMove();

	// キャラクターの座標更新
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... キャラクターの座標
	void MoveAstarCharaPos(const float delta_time, tnl::Vector3 & pos);
	
	// キャラクターの回転更新
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... キャラクターの座標
	// arg3 ... キャラクターの回転
	void MoveAstarCharaRot(const float delta_time, tnl::Vector3& pos, tnl::Quaternion& rot);
	
	// ターゲットの座標とレーン更新
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... ターゲットの座標
	void MoveAstarTarget(const float delta_time, tnl::Vector3& pos);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 右回転のフラグを設定
	// arg ... 右回転のフラグ
	void SetLookSideRight(bool look_side_right) { m_look_side_right = look_side_right; }

	// 右回転のフラグを取得
	bool GetLookSideRight() const { return m_look_side_right; }

	// 左回転のフラグを設定
	// arg ... 左回転のフラグ
	void SetLookSideLeft(bool look_side_left) { m_look_side_left = look_side_left; }

	// 左回転のフラグを取得
	bool GetLookSideLeft() const { return m_look_side_left; }

	// キャラの進行方向を取得
	const tnl::Vector3& GetCharaDirection() const
	{
		return m_chara_direction;
	}

	// Astarのポインタを設定
	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>>& astar)
	{
		m_astar = astar;
	}

	// メディエータのポインタを設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};

