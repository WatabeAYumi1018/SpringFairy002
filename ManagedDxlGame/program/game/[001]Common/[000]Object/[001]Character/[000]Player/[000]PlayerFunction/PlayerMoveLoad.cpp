#include "PlayerMoveLoad.h"


PlayerMoveLoad::PlayerMoveLoad()
{
	LoadPlayerMoveInfo();
}

PlayerMoveLoad::~PlayerMoveLoad()
{
	m_csv_player_move.clear();
}

void PlayerMoveLoad::LoadPlayerMoveInfo()
{
	m_csv_player_move 
		= tnl::LoadCsv<float>("csv/player/player_move.csv");

	// 各パラメータの値を格納
	m_move_speed = m_csv_player_move[1][1];
	m_move_rot = m_csv_player_move[2][1];
	m_move_change_speed = m_csv_player_move[3][1];
	m_salto_move_speed = m_csv_player_move[4][1];
	m_salto_rot = m_csv_player_move[5][1];
	m_salto_radius = m_csv_player_move[6][1];
	m_salto_total_time = m_csv_player_move[7][1];
}
