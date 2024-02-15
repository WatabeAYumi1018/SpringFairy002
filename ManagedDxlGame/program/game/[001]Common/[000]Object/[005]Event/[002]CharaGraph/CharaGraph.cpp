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
	// テキストが終了していない場合
	if (!m_mediator->GetIsTextDrawEnd())
	{
		std::vector <Text::sTextData> texts_data
			= m_mediator->GetLaneTextDrawData();

		// テキストデータが空の場合は処理を終了
		if (texts_data.empty())
		{
			return;
		}

		m_now_id = m_mediator->GetNowTextDrawID();

		m_player_id
			= texts_data[m_now_id].s_player_graph_id;

		m_partner_id
			= texts_data[m_now_id].s_partner_graph_id;

		//　-1でなく、スライドインフラグがtrueの時
		UpdateSlideIn(delta_time);
	}
	else
	{
		// ウィンドウの透明度が100未満になったらスライドアウト
		if (m_mediator->GetTextWindowAlpha() < 200)
		{
			// -1でなく、スライドアウトフラグがtrueの時
			UpdateSlideOut(delta_time);
		}
	}
}

void CharaGraph::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_mediator->GetTextWindowAlpha() > 0)
	{
		DrawCharaGraph();
	}

	if (!m_mediator->GetIsScreenShot()
		&& (m_mediator->GetCurrentEventLane().s_id == 13
			|| tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)))
	{
		DrawScreenShot();
	}
}

void CharaGraph::UpdateSlideIn(const float delta_time)
{
	// -1でなく、かつスライドフラグ
	if (m_player_id != -1 && m_is_slide_in_player)
	{
		m_chara_graph[m_player_id].s_current_pos_x
			+= delta_time * m_chara_graph[m_player_id].s_slide_speed;

		if (m_chara_graph[m_player_id].s_current_pos_x 
			>= m_chara_graph[m_player_id].s_end_pos_x)
		{
			// プレイヤー画像のID全てに対して処理を行う
			for (int i = 0; i <= 3; ++i)
			{
				m_chara_graph[i].s_current_pos_x 
					= m_chara_graph[i].s_end_pos_x;
			}
			m_is_slide_in_player = false;
		}
	}

	if (m_partner_id != -1 && m_is_slide_in_partner)
	{
		m_chara_graph[m_partner_id].s_current_pos_x
			-= delta_time * m_chara_graph[m_partner_id].s_slide_speed;

		if (m_chara_graph[m_partner_id].s_current_pos_x
			<= m_chara_graph[m_partner_id].s_end_pos_x)
		{
			// パートナー画像のID全てに対して処理を行う
			for (int i = 4; i <= 7; ++i)
			{
				m_chara_graph[i].s_current_pos_x
					= m_chara_graph[i].s_end_pos_x;
			}
			m_is_slide_in_partner = false;
		}
	}
}

void CharaGraph::UpdateSlideOut(const float delta_time)
{
	if (m_player_id != -1 && m_is_slide_out_player)
	{
		m_chara_graph[m_player_id].s_current_pos_x
			-= delta_time * m_chara_graph[m_player_id].s_slide_speed;

		if (m_chara_graph[m_player_id].s_current_pos_x
			<= m_chara_graph[m_player_id].s_start_pos_x)
		{
			// プレイヤー画像のID全てに対して処理を行う
			for (int i = 0; i <= 3 ; ++i)
			{
				m_chara_graph[i].s_current_pos_x
					= m_chara_graph[i].s_start_pos_x;
			}

			// フラグリセット
			m_is_slide_in_player = true;
			m_is_slide_out_player = false;
		}
		
	}

	if (m_partner_id != -1 && m_is_slide_out_partner)
	{
		m_chara_graph[m_partner_id].s_current_pos_x
			+= delta_time * m_chara_graph[m_partner_id].s_slide_speed;

		if (m_chara_graph[m_partner_id].s_current_pos_x
			>= m_chara_graph[m_partner_id].s_start_pos_x)
		{
			// パートナー画像のID全てに対して処理を行う
			for (int i = 4; i <= 7; ++i)
			{
				m_chara_graph[i].s_current_pos_x
					= m_chara_graph[i].s_start_pos_x;
			}
			// フラグリセット
			m_is_slide_in_partner = true;
			m_is_slide_out_partner = false;
		}
	}
}

void CharaGraph::DrawCharaGraph()
{
	if (m_player_id != -1)
	{
		DrawGraph(m_chara_graph[m_player_id].s_current_pos_x
				, m_chara_graph[m_player_id].s_pos_y
				, m_chara_graph[m_player_id].s_graph_hdl, TRUE);
	}

	if (m_partner_id != -1)
	{
		DrawGraph(m_chara_graph[m_partner_id].s_current_pos_x
				, m_chara_graph[m_partner_id].s_pos_y
				, m_chara_graph[m_partner_id].s_graph_hdl, TRUE);
	}
}

void CharaGraph::DrawScreenShot()
{
	// 特定の画像を描画
	DrawGraph(m_chara_graph[1].s_end_pos_x
			, m_chara_graph[1].s_pos_y
			, m_chara_graph[1].s_graph_hdl, TRUE);

	DrawGraph(m_chara_graph[5].s_end_pos_x
			, m_chara_graph[5].s_pos_y
			, m_chara_graph[5].s_graph_hdl, TRUE);
}
