#include "../../../../wta_library/wta_Convert.h"
#include "../../[002]Mediator/Mediator.h"
#include "Character.h"


void Character::StartPos()
{
	for (const Lane::sLane& start : m_mediator->GetStageLane())
	{
		if (start.s_id == 1)
		{
			// グリッドの中心座標に設定
			m_pos = start.s_pos + tnl::Vector3(Lane::LANE_SIZE / 2, 0, Lane::LANE_SIZE / 2);
		}
	}
}

// 足元レーンを取得
Lane::sLane Character::CurrentMoveLane()
{
	// プレイヤー座標をグリッド座標に変換
	auto [chara_x, chara_z]
		= wta::ConvertFloatToGridInt(m_pos, Lane::LANE_SIZE);

	std::vector<Lane::sLane> lane_vec = m_mediator->GetStageLane();

	// 配列を使用し、グリッド座標からタイルIDを取得
	for (Lane::sLane& lane : lane_vec)
	{
		auto [lane_x, lane_z]
			= wta::ConvertFloatToGridInt(lane.s_pos, Lane::LANE_SIZE);

		// キャラがタイルの領域内にいるかを判定
		if (chara_x == lane_x && chara_z == lane_z)
		{
			return lane;
		}
	}
	// 該当なし
	return Lane::sLane();
}

GameCamera::sCamera Character::CurrentCameraLane()
{
	// キャラ座標をグリッド座標に変換
	auto [chara_x, chara_z]
		= wta::ConvertFloatToGridInt(m_pos, Lane::LANE_SIZE);

	std::vector<GameCamera::sCamera> camera_lane_vec
		= m_mediator->GetCameraLaneVector();

	// 配列を使用し、グリッド座標からタイルIDを取得
	for (GameCamera::sCamera& camera_lane : camera_lane_vec)
	{
		auto [camera_lane_x, camera_lane_z]
			= wta::ConvertFloatToGridInt(camera_lane.s_pos, Lane::LANE_SIZE);

		// キャラがタイルの領域内にいるかを判定
		if (chara_x == camera_lane_x && chara_z == camera_lane_z)
		{			
			return camera_lane;
		}
	}
	// 該当なし(万一レーン反れてもfixedになるように)
	return GameCamera::sCamera();
}

// 足元のイベントレーンを取得
Lane::sLaneEvent Character::CurrentEventLane()
{
	// キャラ座標をグリッド座標に変換
	auto [chara_x, chara_z]
		= wta::ConvertFloatToGridInt(m_pos, Lane::LANE_SIZE);

	std::vector<Lane::sLaneEvent> event_lane_vec
		= m_mediator->GetStageLaneEvent();

	// 配列を使用し、グリッド座標からタイルIDを取得
	for (Lane::sLaneEvent& event_lane : event_lane_vec)
	{
		auto [event_lane_x, event_lane_z]
			= wta::ConvertFloatToGridInt(event_lane.s_pos, Lane::LANE_SIZE);

		// キャラがタイルの領域内にいるかを判定
		if (chara_x == event_lane_x && chara_z == event_lane_z)
		{
			return event_lane;
		}
	}
	// 該当なし
	Lane::sLaneEvent no_event;
	// idに-1を設定
	no_event.s_id = -1;
	// no_eventを返す
	return no_event; 
}

MATRIX Character::CalcMatrix()
{
	// 変換行列を取得
	return m_matrix = GetTransformMatrix();
}

GameCamera::sCameraInfo Character::CurrentCameraType()
{
	// 現在のカメラのタイプを取得
	return 	m_mediator->GetCameraTypeInfoById(CurrentCameraLane().s_id);
}