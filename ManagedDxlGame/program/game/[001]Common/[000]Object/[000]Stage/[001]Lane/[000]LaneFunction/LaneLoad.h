#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Lane.h"


class LaneLoad
{

public:
	
	LaneLoad();

	~LaneLoad();

private:

	// ���[���z��̍���
	int m_lane_height = 0;
	// ���[���z��̕�
	int m_lane_width = 0;

	//// �C�x���g�^�C�v�̑���
	//int m_lane_event_total_num = 0;

	// ���[���z��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<int>> m_csv_lane;
	// ���[���z����i�[�p
	std::vector<Lane::sLane> m_lanes;

	//// �C�x���g�ǂݎ���p�icsv�t�@�C���j
	//std::vector<std::vector<int>> m_csv_lane_event;
	//// �C�x���g���i�[�p
	//std::vector<Lane::sLane> m_lane_event;

	//// �C�x���g���ǂݎ���p�icsv�t�@�C���j
	//std::vector<std::vector<tnl::CsvCell>> m_csv_lane_event_info;
	//// �C�x���g���i�[�p
	//std::vector<Lane::sLaneEventInfo> m_lane_event_info;


	// ���[���z��̍��W�擾�Ɗi�[
	void LoadLaneVector();
	//// �C�x���g�z��̍��W�擾�Ɗi�[
	//void LoadLaneEventVector();
	//// �C�x���g�z��̏��擾
	//void LoadLaneEventInfo();

public:

	// ���[���z��̍����擾
	int GetLaneHeight() const { return m_lane_height; }

	// ���[���z��̕��擾
	int GetLaneWidth() const {	return m_lane_width; }

	//// �C�x���g�^�C�v�̑����擾
	//int GetLaneEventTotalNum() const { return m_lane_event_total_num; }

	// ���[���z��̏��擾
	const std::vector<Lane::sLane>& GetLane() const { return m_lanes; }

	//// �C�x���g�z��̏��擾
	//const std::vector<Lane::sLane>& GetLaneEvent() const
	//{
	//	return m_lane_event; 
	//}

	//// �C�x���g���擾
	//const std::vector<Lane::sLaneEventInfo>& GetLaneEventInfo() const
	//{
	//	return m_lane_event_info;
	//}
};