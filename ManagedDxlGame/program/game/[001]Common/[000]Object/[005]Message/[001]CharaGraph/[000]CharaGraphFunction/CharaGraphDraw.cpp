#include "../../../../[002]Mediator/Mediator.h"
#include "CharaGraphDraw.h"



CharaGraphDraw::~CharaGraphDraw()
{
	for (CharaGraph::sGraphInfo& chara_graph : m_chara_graph)
	{
		DeleteGraph(chara_graph.s_graph_hdl);
	}
}

void CharaGraphDraw::LoadCharaGraph()
{
	m_chara_graph = m_mediator->GetCharaGraphLoadInfo();

	for(CharaGraph::sGraphInfo& chara_graph : m_chara_graph)
	{
		chara_graph.s_graph_hdl 
			= LoadGraph(chara_graph.s_graph_path.c_str());
	}
}

void CharaGraphDraw::DrawCharaGraph(int graph_id)
{
	DrawGraph(m_chara_graph[graph_id].s_graph_pos.x
			  , m_chara_graph[graph_id].s_graph_pos.y
			  ,m_chara_graph[graph_id].s_graph_hdl,TRUE);
}