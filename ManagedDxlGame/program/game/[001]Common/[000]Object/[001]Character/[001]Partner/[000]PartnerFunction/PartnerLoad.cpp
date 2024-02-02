#include "PartnerLoad.h"


PartnerLoad::PartnerLoad()
{
	LoadPartnerModelInfo();
}

PartnerLoad::~PartnerLoad()
{
	m_csv_model.clear();
	MV1DeleteModel(m_model_hdl);
	MV1DeleteModel(m_anim_bone_idle_hdl);
	MV1DeleteModel(m_anim_bone_move_hdl);
	DeleteGraph(m_texture_hdl);
}

void PartnerLoad::LoadPartnerModelInfo()
{
	m_csv_model
		= tnl::LoadCsv<std::string>("csv/character/partner/partner_model.csv");

	// 各パラメータの値を格納
	m_model_hdl = MV1LoadModel(m_csv_model[1][1].c_str());
	m_anim_bone_idle_hdl = MV1LoadModel(m_csv_model[2][1].c_str());
	m_anim_bone_move_hdl = MV1LoadModel(m_csv_model[3][1].c_str());
	m_texture_hdl = LoadGraph(m_csv_model[4][1].c_str());

	// 材質の指定はないため引数は0
	MV1SetTextureGraphHandle(m_model_hdl, 0, m_texture_hdl, FALSE);
}
