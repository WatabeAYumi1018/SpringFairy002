#include "../../../[002]Mediator/Mediator.h"
#include "../../../[001]Camera/CinemaCamera.h"
#include "CinemaBack.h"


CinemaBack::CinemaBack()
{
	LoadCinemaBackInfo();
}

CinemaBack::~CinemaBack()
{
	DeleteGraph(m_first_back_hdl);
}

void CinemaBack::LoadCinemaBackInfo()
{
	m_fog_hdl = LoadGraph("graphics/illust/fog.png");
	m_first_back_hdl = LoadGraph("graphics/illust/background-green.jpg");
	//m_second_third_hdl = LoadGraph("graphics/illust/background-green_third.jpg");
	m_second_back_hdl = LoadGraph("graphics/illust/flower.jpg");
	//// csvファイルの読み込み
	//m_csv_skybox_info
	//	= tnl::LoadCsv<tnl::CsvCell>("csv/stage/sky/skyBox_Info.csv");

	//// マップタイルの総数を取得
	//int max_num = m_csv_skybox_info.size();

	//// 0行目は説明文なので読み飛ばす
	//for (int y = 1; y < max_num; ++y)
	//{
	//	sSkyBoxInfo sky_info;

	//	sky_info.s_id = m_csv_skybox_info[y][0].getInt();

	//	sky_info.s_texture_path = m_csv_skybox_info[y][1].getString();

	//	sky_info.s_material_path = m_csv_skybox_info[y][2].getString();

	//	sky_info.s_screen_effect_path = m_csv_skybox_info[y][3].getString();

	//	m_skybox_info.emplace_back(sky_info);
	//}
}

void CinemaBack::Update(const float delta_time)
{
	if (m_is_fog)
	{
		UpdateFogBlend();
	}
}

void CinemaBack::Draw(std::shared_ptr<dxe::Camera> camera)
{
	//レーンが1
	//DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_first_back_hdl, TRUE);
	// レーンが5
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_back_hdl, TRUE);

	if(m_is_fog)
	{
		// 画像の透明度を設定（0〜255）
		SetDrawBlendMode(DX_BLENDMODE_ADD, m_alpha);

		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_fog_hdl, TRUE);
	
		// ブレンドモードを通常に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void CinemaBack::UpdateFogBlend()
{
	// 透明度の増加（フレーム毎に呼ばれる想定）
	m_alpha += 5;
	
	if (m_alpha > 255)
	{
		m_alpha = 255;
	}
}


//void CinemaBack::LoadCinemaBackInfo()
//{
//
//	m_first_back_hdl = LoadGraph("graphics/illust/background-green.jpg");
//	m_second_third_hdl = LoadGraph("graphics/illust/background-green_third.jpg");
//	m_second_back_hdl = LoadGraph("graphics/illust/flower.jpg");
//	//// csvファイルの読み込み
//	//m_csv_skybox_info
//	//	= tnl::LoadCsv<tnl::CsvCell>("csv/stage/sky/skyBox_Info.csv");
//
//	//// マップタイルの総数を取得
//	//int max_num = m_csv_skybox_info.size();
//
//	//// 0行目は説明文なので読み飛ばす
//	//for (int y = 1; y < max_num; ++y)
//	//{
//	//	sSkyBoxInfo sky_info;
//
//	//	sky_info.s_id = m_csv_skybox_info[y][0].getInt();
//
//	//	sky_info.s_texture_path = m_csv_skybox_info[y][1].getString();
//
//	//	sky_info.s_material_path = m_csv_skybox_info[y][2].getString();
//
//	//	sky_info.s_screen_effect_path = m_csv_skybox_info[y][3].getString();
//
//	//	m_skybox_info.emplace_back(sky_info);
//	//}
//}
//
//void CinemaBack::Draw(std::shared_ptr<dxe::Camera> camera)
//{
//	//// アクティブなカメラタイプに基づいて背景を描画
//	//CinemaCamera::eCameraSplitType activeType = m_cinema_camera->GetActiveType();
//
//	//if (activeType == CinemaCamera::eCameraSplitType::e_all)
//	//{
//	// 
//
//	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_third_hdl, TRUE);
//
//	//}
//	//if (activeType == CinemaCamera::eCameraSplitType::e_half_right)
//	//{
//	//	DrawExtendGraph(DXE_WINDOW_WIDTH / 2, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_back_hdl, FALSE);
//	//}
//	//if (activeType == CinemaCamera::eCameraSplitType::e_third_left)
//	//{
//	//	DrawExtendGraph(0, 0, m_mediator->GetCinemaSplitWidthLeft(), DXE_WINDOW_HEIGHT, m_second_third_hdl, TRUE);
//	//}
//	//if (activeType == CinemaCamera::eCameraSplitType::e_third_right)
//	//{
//	//	DrawExtendGraph(m_mediator->GetCinemaSplitWidthRight(), 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_third_hdl, TRUE);
//	//}
//}