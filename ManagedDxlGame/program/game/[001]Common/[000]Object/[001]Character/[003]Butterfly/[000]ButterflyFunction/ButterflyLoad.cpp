#include "ButterflyLoad.h"


ButterflyLoad::ButterflyLoad()
{
	LoadModelInfo();
}

ButterflyLoad::~ButterflyLoad()
{
	MV1DeleteModel(m_model_hdl);
	DeleteGraph(m_texture_hdl);
}

void ButterflyLoad::LoadModelInfo()
{
	m_csv_model_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/character/butterfly/butterfly_model.csv");

	m_model_hdl
		= MV1LoadModel(m_csv_model_info[1][1].getString().c_str());

	m_texture_hdl
		= LoadGraph(m_csv_model_info[2][1].getString().c_str());

	m_texture_tip_hdl
		= LoadGraph(m_csv_model_info[3][1].getString().c_str());

	m_tecxture_mask_hdl
		= LoadGraph(m_csv_model_info[4][1].getString().c_str());

	MV1SetTextureGraphHandle(m_model_hdl, 0, m_texture_hdl, FALSE);
	MV1SetTextureGraphHandle(m_model_hdl, 1, m_texture_tip_hdl, true);
	MV1SetTextureGraphHandle(m_model_hdl, 2, m_tecxture_mask_hdl, true);
}

void ButterflyLoad::LoadMoveInfo()
{
	m_csv_move
		= tnl::LoadCsv<float>("csv/character/butterfly/butterfly_move.csv");

	//// 各パラメータの値を格納
	//m_move_speed = m_csv_butterfly_move[1][1];
	//m_move_rot = m_csv_butterfly_move[2][1];
	//m_move_change_speed = m_csv_butterfly_move[3][1];
	//m_salto_move_speed = m_csv_butterfly_move[4][1];
	//m_salto_rot = m_csv_butterfly_move[5][1];
	//m_salto_radius = m_csv_butterfly_move[6][1];
	//m_salto_total_time = m_csv_butterfly_move[7][1];
}
