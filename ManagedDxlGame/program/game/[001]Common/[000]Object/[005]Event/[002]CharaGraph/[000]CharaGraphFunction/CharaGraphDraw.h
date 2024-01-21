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

	// 経過時間
	float m_elapsed_time = 0.0f;

	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	std::shared_ptr<Mediator> m_mediator = nullptr;

public:

	// キャラ画像の読み取り
	void LoadCharaGraph();
	// キャラ画像のスライド処理
	void UpdateCharaSlideGraph(const float delta_time,int graph_id);
	// キャラ画像の描画
	void DrawCharaGraph(int graph_id);

	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}
};