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

	// 樹木モデルの情報読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_tree_info;
	// 樹木モデルの情報格納用
	std::vector<Model::sTreeInfo> m_trees_info;

	// ステージモデルの情報読み込み
	void LoadModelTypeInfo();
	// 樹木モデルの情報読み込み
	void LoadTreeTypeInfo();

	// ステージ3以外のモデル画像設定
	void SetTextureIndex(Model::sModelInfo model_info, int a, int b, int c);
	// ステージ3のモデル画像設定
	void SetTextureIndex(Model::sModelInfo model_info, int a, int b, int c, int d, int e);
	// ライト設定
	void SetLight(Model::sModelInfo model_info, int i);
	// 樹木モデルの画像設定
	void SetTextureTreeIndex(Model::sTreeInfo& model);


public:

	// ステージモデルの情報取得
	const std::vector<Model::sModelInfo>& GetModelInfo() const
	{
		return m_model_info;
	}
	// 樹木モデルの情報取得
	const std::vector<Model::sTreeInfo>& GetTreeInfo() const
	{
		return m_trees_info;
	}
};