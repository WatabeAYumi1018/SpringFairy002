#include "CharaGraphLoad.h"


CharaGraphLoad::CharaGraphLoad()
{
	LoadGraphInfo();
}

CharaGraphLoad::~CharaGraphLoad()
{
	m_csv_graph_info.clear();
	m_graph_info.clear();
}

// テキストデータを読み取る
void CharaGraphLoad::LoadGraphInfo()
{
	// csvファイルの読み込み
	m_csv_graph_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/character/character.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_graph_info.size();

	m_graph_total_num = max_num - 1;

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		CharaGraph::sGraphInfo graph_info;

		graph_info.s_id = m_csv_graph_info[y][0].getInt();

		graph_info.s_graph_side = m_csv_graph_info[y][1].getInt();

		if (graph_info.s_graph_side == 0)
		{
			graph_info.s_graph_pos = tnl::Vector3(900, 400, 0);
		}
		else
		{
			graph_info.s_graph_pos = tnl::Vector3(100, 250, 0);
		}

		graph_info.s_graph_path = m_csv_graph_info[y][2].getString();

		m_graph_info.emplace_back(graph_info);
	}
}