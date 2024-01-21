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

	void DrawCharaGraph(int graph_id);


	const std::vector<CharaGraph::sGraphInfo>& GetCharaGraph() const 
	{
		return m_chara_graph; 
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}
};