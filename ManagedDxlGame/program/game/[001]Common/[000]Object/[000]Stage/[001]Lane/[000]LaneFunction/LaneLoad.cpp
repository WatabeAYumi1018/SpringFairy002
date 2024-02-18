#include "LaneLoad.h"


LaneLoad::LaneLoad()
{
	LoadLaneVector();
	
	LoadLaneEventVector();
}

LaneLoad::~LaneLoad()
{
	m_csv_lane.clear();
	m_lanes.clear();
	m_csv_lane_event.clear();
	m_lane_event.clear();
}

void LaneLoad::LoadLaneVector()
{
	// csvファイルの読み込み
	m_csv_lane 
		//= tnl::LoadCsv<int>("csv/stage/move/move_lane.csv");
		= tnl::LoadCsv<int>("csv/stage/move/move_lane0219.csv");

	// レーン配列の高さ
	m_lane_height = m_csv_lane.size();
	// レーン配列の幅
	m_lane_width = m_csv_lane[0].size();

	Lane::sLane lane;

	// レーン配列の情報取得と格納
	for (int y = 0; y < m_lane_height; y++)
	{
		for (int x = 0; x < m_lane_width; x++)
		{
			// −1は除外
			if (m_csv_lane[y][x] == -1)
			{
				continue;
			}

			lane.s_id = m_csv_lane[y][x];
			// ワールド座標に変換(配列数削減のため１マスを大きめに設定)
			lane.s_pos 
				= tnl::Vector3(x * Lane::LANE_SIZE, 0, y * Lane::LANE_SIZE);

			m_lanes.emplace_back(lane);
		}
	}
}

void LaneLoad::LoadLaneEventVector()
{
	// csvファイルの読み込み
	m_csv_lane_event 
		//= tnl::LoadCsv<int>("csv/stage/event/event_lane.csv");
		= tnl::LoadCsv<int>("csv/stage/event/event_lane0219.csv");

	Lane::sLaneEvent lane_event;

	// レーン配列の情報取得と格納
	for (int y = 0; y < m_lane_height; y++)
	{
		for (int x = 0; x < m_lane_width; x++)
		{
			// −1は除外
			if (m_csv_lane_event[y][x] == -1)
			{
				continue;
			}

			lane_event.s_id = m_csv_lane_event[y][x];

			lane_event.s_pos 
				= tnl::Vector3(x * Lane::LANE_SIZE, 0, y * Lane::LANE_SIZE);

			m_lane_event.emplace_back(lane_event);
		}
	}
}