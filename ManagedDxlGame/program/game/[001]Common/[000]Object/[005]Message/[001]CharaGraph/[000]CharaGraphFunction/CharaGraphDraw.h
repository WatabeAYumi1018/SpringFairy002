#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../CharaGraph.h"

class Mediator;


class CharaGraphDraw
{

public:

	CharaGraphDraw() {}

	~CharaGraphDraw();

private:

	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	std::shared_ptr<Mediator> m_mediator = nullptr;

public:

	void LoadCharaGraph();

	void DrawCharaGraph(tnl::Vector3 pos, int graph_id);

	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}
};