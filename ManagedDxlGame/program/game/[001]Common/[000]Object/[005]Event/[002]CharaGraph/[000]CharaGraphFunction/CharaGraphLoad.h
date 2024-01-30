#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../CharaGraph.h"


class CharaGraphLoad
{

public:

	CharaGraphLoad();

	~CharaGraphLoad();

private:

	int m_graph_total_num = 0;

	
	// キャラ画像の読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_graph_info;
	// キャラ画像データを格納
	std::vector<CharaGraph::sGraphInfo> m_graph_info;


	// キャラ画像データを読み取る
	void LoadGraphInfo();

public:

	const std::vector<CharaGraph::sGraphInfo>& GetGraphInfo() const
	{
		return m_graph_info; 
	}
};