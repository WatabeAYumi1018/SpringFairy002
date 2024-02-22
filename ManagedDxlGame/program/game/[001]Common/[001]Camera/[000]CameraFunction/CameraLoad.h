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

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	CameraLoad();
	~CameraLoad();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// カメラタイプの総数
	int m_camera_type = 0;
	// レーン配列の高さ
	int m_lane_height = 0;
	// レーン配列の幅
	int m_lane_width = 0;

	// カメラレーンの読み取り専用(csvファイル)
	std::vector<std::vector<int>> m_csv_camera_lane;
	// カメラレーン情報格納用
	std::vector<GameCamera::sCamera> m_camera_lane;

	// カメラ情報読み取り専用(csvファイル)
	std::vector<std::vector<tnl::CsvCell>> m_csv_camera_info;
	// カメラ情報格納用
	std::vector<GameCamera::sCameraInfo> m_camera_info;

	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// カメラ配列の座標取得と格納
	// tips ... 初期化時に一度だけ呼び出す
	void LoadCameraVector();

	// カメラの情報取得
	// tips ... 初期化時に一度だけ呼び出す
	void LoadCameraInfo();

	// カメラ情報の文字列をenumに変換
	// arg ... カメラ情報の文字列
	// ※stringではなくint型にした方が使いやすいと思うため、改善予定。
	GameCamera::eCameraType ConvertStringToType(const std::string& type);

public:

	// 該当するカメラ情報の取得
	// arg ... カメラID
	GameCamera::sCameraInfo GetCameraInfoById(int id);

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

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

	// メディエータの設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//
};