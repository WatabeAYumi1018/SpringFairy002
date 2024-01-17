#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Lane.h"


class LaneLoad
{

public:
	
	LaneLoad();

	~LaneLoad();

private:

	// レーン配列の高さ
	int m_lane_height = 0;
	// レーン配列の幅
	int m_lane_width = 0;

	//// イベントタイプの総数
	//int m_lane_event_total_num = 0;

	// レーン配列読み取り専用（csvファイル）
	std::vector<std::vector<int>> m_csv_lane;
	// レーン配列情報格納用
	std::vector<Lane::sLane> m_lanes;

	//// イベント読み取り専用（csvファイル）
	//std::vector<std::vector<int>> m_csv_lane_event;
	//// イベント情報格納用
	//std::vector<Lane::sLane> m_lane_event;

	//// イベント情報読み取り専用（csvファイル）
	//std::vector<std::vector<tnl::CsvCell>> m_csv_lane_event_info;
	//// イベント情報格納用
	//std::vector<Lane::sLaneEventInfo> m_lane_event_info;


	// レーン配列の座標取得と格納
	void LoadLaneVector();
	//// イベント配列の座標取得と格納
	//void LoadLaneEventVector();
	//// イベント配列の情報取得
	//void LoadLaneEventInfo();

public:

	// レーン配列の高さ取得
	int GetLaneHeight() const { return m_lane_height; }

	// レーン配列の幅取得
	int GetLaneWidth() const {	return m_lane_width; }

	//// イベントタイプの総数取得
	//int GetLaneEventTotalNum() const { return m_lane_event_total_num; }

	// レーン配列の情報取得
	const std::vector<Lane::sLane>& GetLane() const { return m_lanes; }

	//// イベント配列の情報取得
	//const std::vector<Lane::sLane>& GetLaneEvent() const
	//{
	//	return m_lane_event; 
	//}

	//// イベント情報取得
	//const std::vector<Lane::sLaneEventInfo>& GetLaneEventInfo() const
	//{
	//	return m_lane_event_info;
	//}
};