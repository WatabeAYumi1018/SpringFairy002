#include "BackLoad.h"


BackLoad::BackLoad()
{
	LoadCinemaGraphInfo();
	LoadSkyBoxInfo();
}

BackLoad::~BackLoad()
{
	m_csv_cinemaBack_info.clear();
	m_cinemaBack_info.clear();
	m_csv_skyBox_info.clear();
	m_skyBox_info.clear();
}

void BackLoad::LoadCinemaGraphInfo()
{
	// csvファイルの読み込み
	m_csv_cinemaBack_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/stage/back/cinemaBack_info.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_cinemaBack_info.size();

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		CinemaBack::sCinemaBackInfo cinema_info;

		cinema_info.s_id = m_csv_cinemaBack_info[y][0].getInt();

		cinema_info.s_back_hdl
			= LoadGraph(m_csv_cinemaBack_info[y][1].getString().c_str());

		m_cinemaBack_info.emplace_back(cinema_info);
	}
}

void BackLoad::LoadSkyBoxInfo()
{
	// csvファイルの読み込み
	m_csv_skyBox_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/stage/back/skyBox_info.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_skyBox_info.size();

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		SkyBox::sSkyBoxInfo sky_info;

		sky_info.s_id = m_csv_skyBox_info[y][0].getInt();

		sky_info.s_texture_path 
			= m_csv_skyBox_info[y][1].getString().c_str();

		sky_info.s_material_path 
			= m_csv_skyBox_info[y][2].getString().c_str();

		sky_info.s_screen_effect_path 
			= m_csv_skyBox_info[y][3].getString().c_str();

		m_skyBox_info.emplace_back(sky_info);
	}
}