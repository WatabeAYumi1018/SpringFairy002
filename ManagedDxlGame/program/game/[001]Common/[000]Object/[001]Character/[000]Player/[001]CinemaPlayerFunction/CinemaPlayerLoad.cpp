#include "CinemaPlayerLoad.h"



CinemaPlayerLoad::CinemaPlayerLoad()
{
	LoadCinemaPlayerParameter();
}

CinemaPlayerLoad::~CinemaPlayerLoad()
{
	m_csv_cinemaPlayer_parameters.clear();
	m_cinemaPlayer_parameters.clear();
}

void CinemaPlayerLoad::LoadCinemaPlayerParameter()
{
	m_csv_cinemaPlayer_parameters
		= tnl::LoadCsv<tnl::CsvCell>("csv/character/player/cinemaPlayer_move.csv");

	// 0行目は説明文なので読み飛ばす
	// 0列目は見やすさのために記入しただけで不要な数値のため読み飛ばす
	// 2列目はパラメータ名、4列目はパラメータの内容となっており、今回は不要
	for (int y = 1; y < m_csv_cinemaPlayer_parameters.size(); ++y)
	{
		CinemaPlayer::sCinemaPlayerParameter cinemaPlayer_parameter;

		cinemaPlayer_parameter.s_id
			= m_csv_cinemaPlayer_parameters[y][1].getInt();

		cinemaPlayer_parameter.s_num
			= m_csv_cinemaPlayer_parameters[y][3].getFloat();

		m_cinemaPlayer_parameters.emplace_back(cinemaPlayer_parameter);
	}
}