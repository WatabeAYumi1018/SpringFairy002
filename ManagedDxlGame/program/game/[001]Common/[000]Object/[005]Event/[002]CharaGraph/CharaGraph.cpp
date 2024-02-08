#include "../../../[002]Mediator/Mediator.h"
#include "CharaGraph.h"


CharaGraph::CharaGraph()
{
	m_window_hdl
		= LoadGraph("graphics/ui/message/window.png");
}

CharaGraph::~CharaGraph()
{
	DeleteGraph(m_window_hdl);

	for (CharaGraph::sGraphInfo& chara_graph : m_chara_graph)
	{
		DeleteGraph(chara_graph.s_graph_hdl);
	}
}

void CharaGraph::Initialize()
{
	LoadCharaGraph();
}


void CharaGraph::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

void CharaGraph::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_window_active)
	{
		DrawGraph(500, 400, m_window_hdl, TRUE);

		DrawCharaGraph(0);
		DrawCharaGraph(5);
	}
}

void CharaGraph::LoadCharaGraph()
{
	m_chara_graph = m_mediator->GetCharaGraphLoadInfo();

	for (CharaGraph::sGraphInfo& chara_graph : m_chara_graph)
	{
		chara_graph.s_graph_hdl
			= LoadGraph(chara_graph.s_graph_path.c_str());
	}
}

void CharaGraph::DrawCharaGraph(int graph_id)
{
	DrawGraph(m_chara_graph[graph_id].s_graph_pos.x
		, m_chara_graph[graph_id].s_graph_pos.y
		, m_chara_graph[graph_id].s_graph_hdl, TRUE);
}

bool CharaGraph::SeqSlideIn(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		float start_x = 0;
		float end_x = m_chara_graph[0].s_graph_pos.x;

		// 左からスライド
		if (m_chara_graph[0].s_graph_side == 0)
		{
			start_x = -200;
		}
		// 右からスライド
		else
		{
			start_x = DXE_WINDOW_WIDTH + 200;
		}

		// 現在のスライド位置を計算
		float current_x = start_x + (end_x - start_x) * delta_time * 5;

		// グラフィックの位置を更新
		m_chara_graph[0].s_graph_pos.x = current_x;
	});

	TNL_SEQ_CO_END;
}

bool CharaGraph::SeqDrawChange(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_window_active = true;
	}

	// テキスト終了フラグが経ったら
	//if ()
	//{
	//	tnl_sequence_.change(&Graph::SeqSlideOut);
	//}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		
		// 座標変更なし
	});

	TNL_SEQ_CO_END;
}

bool CharaGraph::SeqSlideOut(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_window_active = false;
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		float start_x = m_chara_graph[0].s_graph_pos.x;
		float end_x = 0;

		// 左からスライド
		if (m_chara_graph[0].s_graph_side == 0)
		{
			end_x = -200;
		}
		// 右からスライド
		else
		{
			end_x = DXE_WINDOW_WIDTH + 200;
		}

		// 現在のスライド位置を計算
		float current_x = start_x + (end_x - start_x) * delta_time * 5;

		// グラフィックの位置を更新
		m_chara_graph[0].s_graph_pos.x = current_x;
	});

	TNL_SEQ_CO_END;
}
