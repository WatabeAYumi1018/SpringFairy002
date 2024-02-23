#include "ButterflyLoad.h"


ButterflyLoad::ButterflyLoad()
{
	LoadModelInfo();

	LoadParameter();
}

ButterflyLoad::~ButterflyLoad()
{
	MV1DeleteModel(m_model_hdl);
	DeleteGraph(m_texture_hdl);
	DeleteGraph(m_texture_tip_hdl);
	DeleteGraph(m_tecxture_mask_hdl);

	m_csv_model_info.clear();
	m_csv_parameters.clear();
	m_parameters.clear();
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

void ButterflyLoad::LoadParameter()
{
	m_csv_parameters
		= tnl::LoadCsv<tnl::CsvCell>("csv/character/butterfly/butterfly_move.csv");

	// 0行目は説明文なので読み飛ばす
	// 0列目は見やすさのために記入しただけで不要な数値のため読み飛ばす
	// 2列目はパラメータ名、4列目はパラメータの内容となっており、今回は不要
	for (int y = 1; y < m_csv_parameters.size(); ++y)
	{
		Butterfly::sButterflyParameter butterfly_parameter;

		butterfly_parameter.s_id
			= m_csv_parameters[y][1].getInt();

		butterfly_parameter.s_num
			= m_csv_parameters[y][3].getFloat();

		m_parameters.emplace_back(butterfly_parameter);
	}
}
