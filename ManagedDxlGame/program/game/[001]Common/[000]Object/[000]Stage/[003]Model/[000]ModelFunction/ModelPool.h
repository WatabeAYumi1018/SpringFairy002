#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Model.h"


class ModelPool
{

public:

	ModelPool() {}

	~ModelPool() {}

private:

	// 作成する各モデルのインスタンス数
	int m_model_create_num = 19;

	// モデルのベクター
	std::vector<std::shared_ptr<Model>> m_models;
	//// 世界ごとにフィルターされたモデルのベクター
	//std::vector<std::shared_ptr<Model>> m_filtered_models;

public:



	// モデルの格納
	void AddModel(std::shared_ptr<Model>& model);
	//// 世界遷移時、その世界タイプのモデルを全てアクティブにする
	//void IsActivateAllModels(Model::eWorldType world_type);

	int GetModelCreateNum()
	{
		return m_model_create_num;
	}

	// 現実世界のベクター取得
	std::vector<std::shared_ptr<Model>>& GetModels()
	{
		return m_models;
	}
};