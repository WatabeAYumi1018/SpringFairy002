#include "CharaGraphLoad.h"



CharaGraphLoad::CharaGraphLoad()
{
	LoadGraphInfo();
}

CharaGraphLoad::~CharaGraphLoad()
{
	m_csv_graph_info.clear();
	m_graph_info.clear();

	for (CharaGraph::sGraphInfo& graph : m_graph_info)
	{
		DeleteGraph(graph.s_graph_hdl);
	}
}

// テキストデータを読み取る
void CharaGraphLoad::LoadGraphInfo()
{
	// csvファイルの読み込み
	m_csv_graph_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/character/character.csv");

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < m_csv_graph_info.size(); ++y)
	{
		CharaGraph::sGraphInfo graph_info;

		graph_info.s_id = m_csv_graph_info[y][0].getInt();

		graph_info.s_graph_hdl 
			= LoadGraph(m_csv_graph_info[y][1].getString().c_str());

		graph_info.s_slide_speed = m_csv_graph_info[y][2].getFloat();

		graph_info.s_start_pos_x = m_csv_graph_info[y][3].getFloat();

		graph_info.s_current_pos_x = m_csv_graph_info[y][4].getFloat();

		graph_info.s_end_pos_x = m_csv_graph_info[y][5].getFloat();

		graph_info.s_pos_y = m_csv_graph_info[y][6].getFloat();

		m_graph_info.emplace_back(graph_info);
	}
}