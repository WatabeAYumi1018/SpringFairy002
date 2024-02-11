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

	// �o�ߎ���
	float m_elapsed_time = 0.0f;

	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	std::shared_ptr<Mediator> m_mediator = nullptr;

public:

	// �L�����摜�̃X���C�h����
	void UpdateCharaSlideGraph(const float delta_time,int graph_id);

	// �L�����摜�̕`��
	void Draw();

	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}
};