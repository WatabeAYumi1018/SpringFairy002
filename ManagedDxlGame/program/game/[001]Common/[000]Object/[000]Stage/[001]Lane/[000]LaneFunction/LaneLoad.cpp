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
	//m_csv_lane_event_info.clear();
	//m_lane_event_info.clear();
}

void LaneLoad::LoadLaneVector()
{
	// csv�t�@�C���̓ǂݍ���
	m_csv_lane = tnl::LoadCsv<int>("csv/stage/lane/stage_lane.csv");

	// ���[���z��̍���
	m_lane_height = m_csv_lane.size();
	// ���[���z��̕�
	m_lane_width = m_csv_lane[0].size();

	Lane::sLane lane;

	// ���[���z��̏��擾�Ɗi�[
	for (int y = 0; y < m_lane_height; y++)
	{
		for (int x = 0; x < m_lane_width; x++)
		{
			// �|1�͏��O
			if (m_csv_lane[y][x] == -1)
			{
				continue;
			}

			lane.s_id = m_csv_lane[y][x];
			// ���[���h���W�ɕϊ�(�z�񐔍팸�̂��߂P�}�X��傫�߂ɐݒ�)
			lane.s_pos 
				= tnl::Vector3(x * Lane::LANE_SIZE, 0, y * Lane::LANE_SIZE);

			m_lanes.emplace_back(lane);
		}
	}
}

void LaneLoad::LoadLaneEventVector()
{
	// csv�t�@�C���̓ǂݍ���
	m_csv_lane_event 
		= tnl::LoadCsv<int>("csv/stage/event/event_lane.csv");

	Lane::sLaneEvent lane_event;

	// ���[���z��̏��擾�Ɗi�[
	for (int y = 0; y < m_lane_height; y++)
	{
		for (int x = 0; x < m_lane_width; x++)
		{
			// �|1�͏��O
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


//void LaneLoad::LoadLaneEventInfo()
//{
//	// csv�t�@�C���̓ǂݍ���
//	m_csv_lane_event_info
//		= tnl::LoadCsv<tnl::CsvCell>("csv/stage_event_info.csv");
//
//	// �}�b�v�^�C���̑������擾
//	int max_num = m_csv_lane_event_info.size();
//
//	m_lane_event_total_num = max_num - 1;
//
//	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
//	for (int y = 1; y < max_num; ++y)
//	{
//		Lane::sLaneEventInfo event_info;
//
//		event_info.s_id = m_csv_lane_event_info[y][0].getInt();
//
//		event_info.s_type = m_csv_lane_event_info[y][1].getString();
//
//		m_lane_event_info.emplace_back(event_info);
//	}
//}