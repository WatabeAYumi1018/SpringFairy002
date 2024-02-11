#include "../../../../[002]Mediator/Mediator.h"
#include "CharaGraphDraw.h"



CharaGraphDraw::~CharaGraphDraw()
{
	m_chara_graph.clear();
}


void CharaGraphDraw::UpdateCharaSlideGraph(const float delta_time, int graph_id)
{
	m_elapsed_time += delta_time;

	// 左からサイドする場合
	if (m_chara_graph[graph_id].s_graph_side == 0)
	{
		// x=0から開始
		// m_chara_graph[graph_id].s_graph_pos.xまでスライド
	}
	// 右からスライド
	else
	{
		// x=DXE_WINDOW_WIDTHから開始
		// m_chara_graph[graph_id].s_graph_pos.xまでスライド
	}
}
