#include "../../../../[002]Mediator/Mediator.h"
#include "CharaGraphDraw.h"



CharaGraphDraw::~CharaGraphDraw()
{
	m_chara_graph.clear();
}


void CharaGraphDraw::UpdateCharaSlideGraph(const float delta_time, int graph_id)
{
	m_elapsed_time += delta_time;

	// ������T�C�h����ꍇ
	if (m_chara_graph[graph_id].s_graph_side == 0)
	{
		// x=0����J�n
		// m_chara_graph[graph_id].s_graph_pos.x�܂ŃX���C�h
	}
	// �E����X���C�h
	else
	{
		// x=DXE_WINDOW_WIDTH����J�n
		// m_chara_graph[graph_id].s_graph_pos.x�܂ŃX���C�h
	}
}
