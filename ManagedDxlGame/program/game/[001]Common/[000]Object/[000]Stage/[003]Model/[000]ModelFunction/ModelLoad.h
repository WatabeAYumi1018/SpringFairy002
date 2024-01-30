#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Model.h"
//#include "../../../[003]Phase/StagePhase.h"


class ModelLoad
{

public:

	ModelLoad();

	~ModelLoad();

private:

	// ステージモデルの総数
	int m_model_total_num = 3;

	// ステージモデルの情報読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_model_type_info;
	// ステージモデルの情報格納用
	std::vector<Model::sModelInfo> m_model_type;

	// ステージモデルの情報読み込み
	void LoadModelTypeInfo();

public:

	// ステージモデルのid取得
	//Model::sStageModelType GetModelInfoById(int id);

	int GetModelTotalNum() const { return m_model_total_num; }

	//int GetModelVecHeight() const { return m_model_vec_height; }

	//int GetModelVecWidth() const { return m_model_vec_width; }

	//const std::vector<Model::sStageModel>& GetTreeVector() const
	//{
	//	return m_stage_tree;
	//}

	//const std::vector<Model::sStageModel>& GetGrassVector() const
	//{
	//	return m_stage_grass;
	//}

	const std::vector<Model::sModelInfo>& GetModelTypeInfo() const
	{
		return m_model_type;
	}
};