#include "OtherGraphLoad.h"


OtherGraphLoad::OtherGraphLoad()
{
	LoadOtherGraph();
}

OtherGraphLoad::~OtherGraphLoad()
{
	m_csv_graph_info.clear();
	m_graph_info.clear();
}

void OtherGraphLoad::LoadOtherGraph()
{
	m_csv_graph_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/other/otherGraph.csv");

	// 0çsñ⁄ÇÕê‡ñæï∂Ç»ÇÃÇ≈ì«Ç›îÚÇŒÇ∑
	for (int y = 1; y < m_csv_graph_info.size(); ++y)
	{
		ChangeGraph::sChangeGraphInfo graph_info;

		graph_info.s_id = m_csv_graph_info[y][0].getInt();

		graph_info.s_graph_hdl
			= LoadGraph(m_csv_graph_info[y][1].getString().c_str());

		graph_info.s_pos = { m_csv_graph_info[y][2].getFloat()
							,m_csv_graph_info[y][3].getFloat()
							,0 };

		graph_info.s_speed = m_csv_graph_info[y][4].getFloat();

		m_graph_info.emplace_back(graph_info);
	}
}