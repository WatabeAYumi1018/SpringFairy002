#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../ChangeGraph.h"


///////////////////////////////////////////////////////////////////////////
//
// その他のイラストに関するcsvファイルの読み込みクラス
//
///////////////////////////////////////////////////////////////////////////


class OtherGraphLoad
{

public:

	OtherGraphLoad();
	~OtherGraphLoad();

private:

	// 画像の読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_graph_info;
	// 画像データを格納
	std::vector<ChangeGraph::sChangeGraphInfo> m_graph_info;

	void LoadOtherGraph();

public:

	// 画像データを取得
	const std::vector<ChangeGraph::sChangeGraphInfo>& GetGraphInfo() const
	{
		return m_graph_info;
	}
};