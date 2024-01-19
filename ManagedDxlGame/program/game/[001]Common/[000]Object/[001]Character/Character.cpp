#include "../../../../wta_library/wta_Convert.h"
#include "../../[002]Mediator/Mediator.h"
#include "Character.h"


void Character::StartPos()
{
	for (const auto& start : m_mediator->GetStageLane())
	{
		if (start.s_id == 1)
		{
			m_pos = start.s_pos;

			m_pos.z = 0;
		}
	}
}

// プレイヤーの足元レーンを取得
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

Item::sItem Character::CurrentItemLane()
{
	// プレイヤー座標をグリッド座標に変換
	auto [chara_x, chara_z]
		= wta::ConvertFloatToGridInt(m_pos, Lane::LANE_SIZE);

	std::vector<Item::sItem> item_vec = m_mediator->GetItemLoadLane();

	// 配列を使用し、グリッド座標からタイルIDを取得
	for (Item::sItem& item_lane : item_vec)
	{
		auto [item_lane_x, item_lane_z]
			= wta::ConvertFloatToGridInt(item_lane.s_pos, Lane::LANE_SIZE);

		// キャラがタイルの領域内にいるかを判定
		if (chara_x == item_lane_x && chara_z == item_lane_z)
		{
			m_mediator->SetItemIsActive(true);

			return item_lane;
		}
	}
	// 該当なし
	return Item::sItem();
}

GameCamera::sCamera Character::CurrentCamera()
{
	// カメラ座標をグリッド座標に変換
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
			DrawStringEx(500, 50, -1, "レーン座標.x : %d", camera_lane_x);
			DrawStringEx(500, 70, -1, "レーン座標.z : %d", camera_lane_z);

			return camera_lane;
		}
	}
	// 該当なし
	return GameCamera::sCamera();
}

MATRIX Character::CalcMatrix()
{
	// 変換行列を取得
	return m_matrix = GetTransformMatrix();
}

GameCamera::sCameraInfo Character::CurrentCameraType()
{
	// 現在のカメラのタイプを取得
	return 	m_mediator->GetCameraTypeInfoById(CurrentCamera().s_id);
}