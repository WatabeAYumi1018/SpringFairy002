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

	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	// 0��ڂ͌��₷���̂��߂ɋL�����������ŕs�v�Ȑ��l�̂��ߓǂݔ�΂�
	// 2��ڂ̓p�����[�^���A4��ڂ̓p�����[�^�̓��e�ƂȂ��Ă���A����͕s�v
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