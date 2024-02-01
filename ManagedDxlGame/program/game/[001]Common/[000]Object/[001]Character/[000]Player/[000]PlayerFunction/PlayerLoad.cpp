#include "PlayerLoad.h"


PlayerLoad::PlayerLoad()
{
	LoadPlayerMoveInfo();
}

PlayerLoad::~PlayerLoad()
{
	m_csv_move.clear();
}

void PlayerLoad::LoadPlayerMoveInfo()
{
	m_csv_move 
		= tnl::LoadCsv<float>("csv/character/player/player_move.csv");

	// 各パラメータの値を格納
	m_move_speed = m_csv_move[1][1];
	m_move_rot = m_csv_move[2][1];
	m_move_change_speed = m_csv_move[3][1];
	m_salto_move_speed = m_csv_move[4][1];
	m_salto_rot = m_csv_move[5][1];
	m_salto_radius = m_csv_move[6][1];
	m_salto_total_time = m_csv_move[7][1];
}

