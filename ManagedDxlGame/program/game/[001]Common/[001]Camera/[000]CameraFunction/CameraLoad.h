#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../GameCamera.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// カメラに関するcsvファイルの読み込みクラス
//
///////////////////////////////////////////////////////////////////////////


class CameraLoad
{

public:

	CameraLoad();

	~CameraLoad();

private:

	// カメラタイプの総数
	int m_camera_type = 0;
	// レーン配列の高さ
	int m_lane_height = 0;
	// レーン配列の幅
	int m_lane_width = 0;

	// カメラ読み取り専用(csvファイル)
	std::vector<std::vector<int>> m_csv_camera_lane;
	// カメラ配列情報格納用
	std::vector<GameCamera::sCamera> m_camera_lane;

	// カメラ情報読み取り専用(csvファイル)
	std::vector<std::vector<tnl::CsvCell>> m_csv_camera_info;
	// カメラ情報格納用
	std::vector<GameCamera::sCameraInfo> m_camera_info;


	std::shared_ptr<Mediator> m_mediator = nullptr;


	// カメラ配列の座標取得と格納
	void LoadCameraVector();
	// カメラの情報取得
	void LoadCameraInfo();
	// カメラ情報の文字列をenumに変換
	GameCamera::eCameraType ConvertStringToType(const std::string& type);

public:

	GameCamera::sCameraInfo GetCameraInfoById(int id);


	// カメラタイプの総数取得
	int GetCameraType() const { return m_camera_type; }
	// カメラ配列の高さ取得
	int GetLaneHeight() const { return m_lane_height; }
	// カメラ配列の幅取得
	int GetLaneWidth() const { return m_lane_width; }

	// カメラ配列の情報取得
	const std::vector<GameCamera::sCamera>& GetCameraLane() const
	{
		return m_camera_lane; 
	}

	// カメラ情報取得
	const std::vector<GameCamera::sCameraInfo>& GetCameraInfo() const
	{
		return m_camera_info;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};