#include "CameraLoad.h"
#include "../../[000]Object/[000]Stage/[001]Lane/Lane.h"
#include "../../[002]Mediator/Mediator.h"


CameraLoad::CameraLoad()
{
	LoadCameraVector();

	LoadCameraInfo();
}

CameraLoad::~CameraLoad()
{
	m_csv_camera_lane.clear();
	m_camera_lane.clear();
	m_csv_camera_info.clear();
	m_camera_info.clear();
}

GameCamera::sCameraInfo CameraLoad::GetCameraInfoById(int id)
{
	for (const GameCamera::sCameraInfo& camera_info : m_camera_info)
	{
		if (camera_info.s_id == id)
		{
			return camera_info;
		}
	}
	// ID��������Ȃ������ꍇ�̃f�t�H���g�l
	return GameCamera::sCameraInfo();
}

void CameraLoad::LoadCameraVector()
{
	// csv�t�@�C���̓ǂݍ���
	m_csv_camera_lane 
		//= tnl::LoadCsv<int>("csv/stage/camera/camera_lane.csv");
		= tnl::LoadCsv<int>("csv/stage/camera/camera_lane0219.csv");

	GameCamera::sCamera camera;

	// ���[���z��̍���
	m_lane_height = m_csv_camera_lane.size();
	// ���[���z��̕�
	m_lane_width = m_csv_camera_lane[0].size();

	// ���[���z��̏��擾�Ɗi�[
	for (int y = 0; y < m_lane_height; y++)
	{
		for (int x = 0; x < m_lane_width; x++)
		{
			// �|1�͏��O
			if (m_csv_camera_lane[y][x] == -1)
			{
				continue;
			}

			camera.s_id = m_csv_camera_lane[y][x];

			camera.s_pos
				= tnl::Vector3(x * Lane::LANE_SIZE, 0, y * Lane::LANE_SIZE);

			m_camera_lane.emplace_back(camera);
		}
	}
}

void CameraLoad::LoadCameraInfo()
{
	// csv�t�@�C���̓ǂݍ���
	m_csv_camera_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/stage/camera/camera_info.csv");

	// �J�����^�C�v�̑������擾
	int max_num = m_csv_camera_info.size();

	m_camera_type = max_num - 1;

	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	for (int y = 1; y < max_num; ++y)
	{
		GameCamera::sCameraInfo camera_info;

		camera_info.s_id = m_csv_camera_info[y][0].getInt();

		std::string type = m_csv_camera_info[y][1].getString();
		
		camera_info.s_type = ConvertStringToType(type);

		m_camera_info.emplace_back(camera_info);
	}
}

GameCamera::eCameraType CameraLoad::ConvertStringToType(const std::string& type)
{
	static const std::unordered_map<std::string, GameCamera::eCameraType> type_map 
		= {{"fixed", GameCamera::eCameraType::e_fixed}
			,{"right_side", GameCamera::eCameraType::e_right_side}
			,{"left_side", GameCamera::eCameraType::e_left_side}
			,{"right_side_back", GameCamera::eCameraType::e_right_side_back}
			,{"left_side_back", GameCamera::eCameraType::e_left_side_back}
			,{"front", GameCamera::eCameraType::e_front}
			,{"bottom", GameCamera::eCameraType::e_bottom}
			,{"rotate", GameCamera::eCameraType::e_rotate}
			,{"follow", GameCamera::eCameraType::e_follow}};

	auto itr = type_map.find(type);

	if (itr != type_map.end())
	{
		return itr->second;
	}

	return GameCamera::eCameraType::e_none;
}
