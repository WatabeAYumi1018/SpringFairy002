#include "../../[001]Lane/Lane.h"
#include "../../[002]Floor/Floor.h"
#include "ModelLoad.h"


ModelLoad::ModelLoad()
{
	LoadModelTypeInfo();
}

ModelLoad::~ModelLoad()
{
	m_csv_model_info.clear();

	for (Model::sModelInfo model_info : m_model_info)
	{
		MV1DeleteModel(model_info.s_model_hdl);
		DeleteGraph(model_info.s_texture_a_hdl);
		DeleteGraph(model_info.s_texture_b_hdl);
		DeleteGraph(model_info.s_texture_c_hdl);
	}

	m_model_info.clear();
}

void ModelLoad::LoadModelTypeInfo()
{
	// csvファイルの読み込み
	m_csv_model_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/stage/model/stage_area_model_info.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_model_info.size();

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		Model::sModelInfo model_info;

		model_info.s_id = m_csv_model_info[y][0].getInt();

		model_info.s_model_hdl
			= MV1LoadModel(m_csv_model_info[y][1].getString().c_str());

		model_info.s_texture_a_hdl
			= LoadGraph(m_csv_model_info[y][2].getString().c_str());

		model_info.s_texture_b_hdl
			= LoadGraph(m_csv_model_info[y][3].getString().c_str());

		model_info.s_texture_c_hdl
			= LoadGraph(m_csv_model_info[y][4].getString().c_str());

		model_info.s_texture_d_hdl
			= LoadGraph(m_csv_model_info[y][5].getString().c_str());

		model_info.s_texture_e_hdl
			= LoadGraph(m_csv_model_info[y][6].getString().c_str());

		model_info.s_texture_f_hdl
			= LoadGraph(m_csv_model_info[y][7].getString().c_str());

		model_info.s_material_count 
				= MV1GetMaterialNum(model_info.s_model_hdl);

		// ステージ毎のテクスチャ設定
		if (model_info.s_id == 0)
		{
			SetTextureIndex(model_info, 43, 73, 102);
		}
		else if (model_info.s_id == 1)
		{
			SetTextureIndex(model_info, 15, 33, 37);
		}
		else
		{
			SetTextureIndex(model_info, 22, 42, 62, 82, 102 );
		}

		m_model_info.emplace_back(model_info);
	}
}

void ModelLoad::SetTextureIndex(Model::sModelInfo model_info, int a, int b, int c)
{
	for (int i = 0; i < model_info.s_material_count; ++i)
	{
		if (i < a)
		{
			MV1SetTextureGraphHandle(model_info.s_model_hdl, i
				, model_info.s_texture_a_hdl, FALSE);
		}
		else if (i >= a && i < b)
		{
			MV1SetTextureGraphHandle(model_info.s_model_hdl, i
				, model_info.s_texture_b_hdl, FALSE);
		}
		else if (i >= b && i < c)
		{
			MV1SetTextureGraphHandle(model_info.s_model_hdl, i
				, model_info.s_texture_c_hdl, FALSE);
		}

		SetLight(model_info, i);
	}
}

void ModelLoad::SetTextureIndex(Model::sModelInfo model_info, int a, int b, int c, int d, int e)
{
	for (int i = 0; i < model_info.s_material_count; ++i)
	{
		if (i < a)
		{
			MV1SetTextureGraphHandle(model_info.s_model_hdl, i
				, model_info.s_texture_a_hdl, FALSE);
		}
		else if (i >= a && i < b)
		{
			MV1SetTextureGraphHandle(model_info.s_model_hdl, i
				, model_info.s_texture_b_hdl, FALSE);
		}
		else if (i >= b && i < c)
		{
			MV1SetTextureGraphHandle(model_info.s_model_hdl, i
				, model_info.s_texture_c_hdl, FALSE);
		}
		else if (i >= c && i < d)
		{
			MV1SetTextureGraphHandle(model_info.s_model_hdl, i
							, model_info.s_texture_d_hdl, FALSE);
		}
		else if (i >= d && i < e)
		{
			MV1SetTextureGraphHandle(model_info.s_model_hdl, i
							, model_info.s_texture_e_hdl, FALSE);
		}
		else
		{
			MV1SetTextureGraphHandle(model_info.s_model_hdl, i
							, model_info.s_texture_f_hdl, FALSE);
		}

		SetLight(model_info, i);
	}
}

void ModelLoad::SetLight(Model::sModelInfo model_info, int i)
{	
	DxLib::COLOR_F emissive = { 0.8f,0.8f,0.8f,1 };
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	DxLib::COLOR_F diffuse = { 0.8f,0.8f,0.8f,1 };
	DxLib::COLOR_F specular = { 0,0,0,1 };

	if (i == 2)
	{
		DxLib::COLOR_F emissive = { 1,1,1,1 };
		DxLib::COLOR_F ambient = { 1,1,1,1 };
		DxLib::COLOR_F diffuse = { 1,1,1,1 };
		DxLib::COLOR_F specular = { 0,0,0,1 };
	}

	MV1SetMaterialEmiColor(model_info.s_model_hdl, i, emissive);
	MV1SetMaterialAmbColor(model_info.s_model_hdl, i, ambient);
	MV1SetMaterialDifColor(model_info.s_model_hdl, i, diffuse);
	MV1SetMaterialSpcColor(model_info.s_model_hdl, i, specular);
	MV1SetMaterialSpcPower(model_info.s_model_hdl, i, 0.5f);
}

