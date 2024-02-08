#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Model.h"


class ModelLoad
{

public:

	ModelLoad();

	~ModelLoad();

private:

	// ステージモデルの情報読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_model_info;
	// ステージモデルの情報格納用
	std::vector<Model::sModelInfo> m_model_info;

	// ステージモデルの情報読み込み
	void LoadModelTypeInfo();

	void SetTextureIndex(Model::sModelInfo model_info, int a, int b, int c);

	void SetLight(Model::sModelInfo model_info, int i);

public:

	const std::vector<Model::sModelInfo>& GetModelInfo() const
	{
		return m_model_info;
	}
};