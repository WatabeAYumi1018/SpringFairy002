#include "../../../[002]Mediator/Mediator.h"
#include "CharaGraph.h"


CharaGraph::CharaGraph()
{
}

CharaGraph::~CharaGraph()
{
	m_chara_graph.clear();
}

void CharaGraph::Initialize()
{
	m_chara_graph = m_mediator->GetCharaGraphLoadInfo();
}

void CharaGraph::Update(float delta_time)
{
	//tnl_sequence_.update(delta_time);
}

void CharaGraph::Draw(std::shared_ptr<dxe::Camera> camera)

{
	if (!m_mediator->GetIsTextDrawEnd())
	{
		DrawCharaGraph();
	}
}

void CharaGraph::DrawCharaGraph()
{
	std::vector <Text::sTextData> texts_data
					= m_mediator->GetLaneTextDrawData();

	// テキストデータが空の場合は処理を終了
	if (texts_data.empty())
	{
		return;
	}

	int now_id = m_mediator->GetNowTextDrawID();

	int player_id = texts_data[now_id].s_player_graph_id;

	int partner_id = texts_data[now_id].s_partner_graph_id;

	if (player_id != -1)
	{
		DrawGraph(m_chara_graph[player_id].s_graph_pos.x
			, m_chara_graph[player_id].s_graph_pos.y
			, m_chara_graph[player_id].s_graph_hdl, TRUE);
	}

	if (partner_id != -1)
	{
		DrawGraph(m_chara_graph[partner_id].s_graph_pos.x
			, m_chara_graph[partner_id].s_graph_pos.y
			, m_chara_graph[partner_id].s_graph_hdl, TRUE);
	}
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

