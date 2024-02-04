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

	m_first_back_hdl = LoadGraph("graphics/illust/background-green.jpg");
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

void CinemaBack::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_mediator->GetScreenType() == CinemaCamera::eCameraSplitType::e_all ||
		m_mediator->GetScreenType() == CinemaCamera::eCameraSplitType::e_third_left ||
		m_mediator->GetScreenType() == CinemaCamera::eCameraSplitType::e_third_right)
	{
		// ここでsecond_back_hdlを全画面用に描画
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_second_back_hdl, TRUE);
	}
	else
	{
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH
			, DXE_WINDOW_HEIGHT, m_first_back_hdl, TRUE);
	}
}