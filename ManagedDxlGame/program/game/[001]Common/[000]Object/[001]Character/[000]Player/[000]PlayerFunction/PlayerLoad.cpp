#include "PlayerLoad.h"


PlayerLoad::PlayerLoad()
{
	LoadPlayerMoveInfo();

	LoadPlayerModelInfo();
}

PlayerLoad::~PlayerLoad()
{
	m_csv_move.clear();
	m_csv_model.clear();
	MV1DeleteModel(m_model_game_hdl);
	MV1DeleteModel(m_model_cinema_hdl);
	MV1DeleteModel(m_anim_bone_idle_cinema_hdl);
	MV1DeleteModel(m_anim_bone_move_game_hdl);
	MV1DeleteModel(m_anim_bone_move_cinema_hdl);
	MV1DeleteModel(m_anim_bone_bloom_game_hdl);
	MV1DeleteModel(m_anim_bone_dance_game_hdl);
	MV1DeleteModel(m_anim_bone_dance_cinema_hdl);
	DeleteGraph(m_texture_game_hdl);
	DeleteGraph(m_texture_cinema_hdl);
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

void PlayerLoad::LoadPlayerModelInfo()
{
	m_csv_model
		= tnl::LoadCsv<std::string>("csv/character/player/player_model.csv");

	// 各パラメータの値を格納
	m_model_game_hdl = MV1LoadModel(m_csv_model[1][1].c_str());
	m_model_cinema_hdl = MV1LoadModel(m_csv_model[1][1].c_str());

	m_anim_bone_idle_cinema_hdl = MV1LoadModel(m_csv_model[2][1].c_str());
	
	m_anim_bone_move_game_hdl = MV1LoadModel(m_csv_model[3][1].c_str());
	m_anim_bone_move_cinema_hdl = MV1LoadModel(m_csv_model[3][1].c_str());
	
	m_anim_bone_bloom_game_hdl = MV1LoadModel(m_csv_model[4][1].c_str());
	
	m_anim_bone_dance_game_hdl = MV1LoadModel(m_csv_model[5][1].c_str());
	m_anim_bone_dance_cinema_hdl = MV1LoadModel(m_csv_model[5][1].c_str());
	
	m_texture_game_hdl = LoadGraph(m_csv_model[6][1].c_str());
	m_texture_cinema_hdl = LoadGraph(m_csv_model[6][1].c_str());

	// 材質の指定はないため引数は0
	MV1SetTextureGraphHandle(m_model_game_hdl, 0, m_texture_game_hdl, FALSE);
	MV1SetTextureGraphHandle(m_model_cinema_hdl, 0, m_texture_cinema_hdl, FALSE);
}
