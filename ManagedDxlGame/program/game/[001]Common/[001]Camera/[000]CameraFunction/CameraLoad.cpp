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
	// IDが見つからなかった場合のデフォルト値
	return GameCamera::sCameraInfo();
}

void CameraLoad::LoadCameraVector()
{
	// csvファイルの読み込み
	m_csv_camera_lane 
		= tnl::LoadCsv<int>("csv/stage/camera/camera_lane.csv");

	GameCamera::sCamera camera;

	// レーン配列の高さ
	m_lane_height = m_csv_camera_lane.size();
	// レーン配列の幅
	m_lane_width = m_csv_camera_lane[0].size();

	// レーン配列の情報取得と格納
	for (int y = 0; y < m_lane_height; y++)
	{
		for (int x = 0; x < m_lane_width; x++)
		{
			// －1は除外
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
	// csvファイルの読み込み
	m_csv_camera_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/stage/camera/camera_info.csv");

	// カメラタイプの総数を取得
	int max_num = m_csv_camera_info.size();

	m_camera_type = max_num - 1;

	// 0行目は説明文なので読み飛ばす
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
	for (int i = 1; i < m_camera_type; ++i)
	{
		if (i < m_csv_camera_info.size() 
			&& type == m_csv_camera_info[i][1].getString())
		{
			return static_cast<GameCamera::eCameraType>(i);
		}
	}

	return GameCamera::eCameraType::e_none;
}
