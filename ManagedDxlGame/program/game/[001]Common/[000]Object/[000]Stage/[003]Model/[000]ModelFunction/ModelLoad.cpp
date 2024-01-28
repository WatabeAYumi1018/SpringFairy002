#include "../../[001]Lane/Lane.h"
#include "../../[002]Floor/Floor.h"
#include "ModelLoad.h"


ModelLoad::ModelLoad()
{
	//LoadTreeVector();
	//
	//LoadGrassVector();
	
	LoadModelTypeInfo();
}

ModelLoad::~ModelLoad()
{
	//m_stage_tree.clear();
	//m_stage_grass.clear();
	m_model_type.clear();
}

void ModelLoad::LoadModelTypeInfo()
{
	// csvファイルの読み込み
	m_csv_model_type_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/stage/model/stage_group_model_info.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_model_type_info.size();

	m_model_total_num = max_num - 1;

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		Model::sMeshModelType model_info;

		model_info.s_id = m_csv_model_type_info[y][0].getInt();

		model_info.s_model_path = m_csv_model_type_info[y][1].getString();

		model_info.s_texture_path = m_csv_model_type_info[y][2].getString();

		model_info.s_create_count_x = m_csv_model_type_info[y][3].getInt();

		model_info.s_create_count_z = m_csv_model_type_info[y][4].getInt();

		model_info.s_scale = m_csv_model_type_info[y][5].getFloat();

		model_info.s_interval = m_csv_model_type_info[y][6].getFloat();

		tnl::Vector3 pos = { m_csv_model_type_info[y][7].getFloat(),0,m_csv_model_type_info[y][8].getFloat() };

		model_info.s_offset = pos;

		m_model_type.emplace_back(model_info);
	}
}

//if (!m_csv_model_type_info[y][3].getString().empty())
//{
//	model_info.s_texture_b_path = m_csv_model_type_info[y][3].getString();
//}

//if (!m_csv_model_type_info[y][4].getString().empty())
//{
//	model_info.s_texture_c_path = m_csv_model_type_info[y][4].getString();
//}

//model_info.s_material_a_name = m_csv_model_type_info[y][5].getString();

//if (!m_csv_model_type_info[y][6].getString().empty())
//{
//	model_info.s_material_b_name = m_csv_model_type_info[y][6].getString();
//}

//if (!m_csv_model_type_info[y][7].getString().empty())
//{
//	model_info.s_material_c_name = m_csv_model_type_info[y][7].getString();
//}

//Model::sStageModelType ModelLoad::GetModelInfoById(int id)
//{
//	for (const Model::sStageModelType& model : m_model_type)
//	{
//		if (model.s_id == id)
//		{
//			return model;
//		}
//	}
//	// IDが見つからなかった場合のデフォルト値
//	return Model::sStageModelType();
//}
//
//void ModelLoad::LoadTreeVector()
//{
//	// csvファイルの読み込み
//	m_csv_stage_tree = tnl::LoadCsv<int>("csv/stage/model/stage_tree.csv");
//
//	// レーン配列の高さ
//	m_model_vec_height = m_csv_stage_tree.size();
//	// レーン配列の幅
//	m_model_vec_width = m_csv_stage_tree[0].size();
//
//	Model::sStageModel model;
//
//	int size = Lane::LANE_SIZE;
//	float distance = static_cast<float> (Floor::DRAW_DISTANCE);
//
//	// レーン配列の情報取得と格納
//	for (int y = 0; y < m_model_vec_height; y++)
//	{
//		for (int x = 0; x < m_model_vec_width; x++)
//		{
//			model.s_id = m_csv_stage_tree[y][x];
//			// ワールド座標に変換(配列数削減のため１マスを大きめに設定)
//			model.s_pos	
//				= tnl::Vector3(x * size, distance, y * size);
//
//			m_stage_tree.emplace_back(model);
//		}
//	}
//}
//
//void ModelLoad::LoadGrassVector()
//{
//	// csvファイルの読み込み
//	m_csv_stage_grass = tnl::LoadCsv<int>("csv/stage/model/stage_grass.csv");
//
//	Model::sStageModel model;
//
//	float distance = static_cast<float> (Floor::DRAW_DISTANCE);
//
//	// レーン配列の情報取得と格納
//	for (int y = 0; y < m_model_vec_height; y++)
//	{
//		for (int x = 0; x < m_model_vec_width; x++)
//		{
//			model.s_id = m_csv_stage_grass[y][x];
//			// ワールド座標に変換(配列数削減のため１マスを大きめに設定)
//			model.s_pos = tnl::Vector3(x * 200, distance, y * 200);
//
//			m_stage_grass.emplace_back(model);
//		}
//	}
//}

