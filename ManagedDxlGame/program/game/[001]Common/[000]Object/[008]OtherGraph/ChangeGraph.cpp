#include "../../[002]Mediator/Mediator.h"
#include "ChangeGraph.h"


ChangeGraph::ChangeGraph()
{
}

ChangeGraph::~ChangeGraph()
{
	m_graph_info.clear();
}

void ChangeGraph::Initialize()
{
	m_graph_info = m_mediator->GetChangeGraphInfo();
}

void ChangeGraph::Update(const float delta_time)
{
	if (m_is_active_tulip)
	{
		UpdateChangeGraph(delta_time, 0, 4);
	}
	else if(m_is_active_white)
	{
		UpdateWhite(delta_time);
	}
	else if (m_is_active_blossom)
	{
		UpdateChangeGraph(delta_time, 6, 11);
	}
	else if (m_is_active_butterfly)
	{
		UpdateChangeGraph(delta_time,12 ,14);
	}
}

void ChangeGraph::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_is_active_tulip)
	{
		DrawChangeGraph(0, 4);
	}
	else if (m_is_active_white)
	{
		DrawWhite();
	}
	else if (m_is_active_blossom)
	{
		DrawChangeGraph(6, 11);
	}
	else if (m_is_active_butterfly)
	{
		DrawChangeGraph(12, 14);
	}
}

void ChangeGraph::UpdateChangeGraph(const float delta_time, int start, int end)
{
	for (int i = start; i <= end; ++i)
	{
		if (m_is_active_tulip)
		{
			m_graph_info[i].s_pos.x -= delta_time * m_graph_info[i].s_speed;
		}
		else if(m_is_active_blossom)
		{
			m_graph_info[i].s_pos.x -= delta_time * m_graph_info[i].s_speed;
			m_graph_info[i].s_pos.y += delta_time * m_graph_info[i].s_speed; 
		}
		else if (m_is_active_butterfly)
		{
			m_graph_info[i].s_pos.y -= delta_time * m_graph_info[i].s_speed;
		}
	}
}

void ChangeGraph::DrawChangeGraph(int start, int end)
{
	for (int i = start; i <= end; ++i)
	{
		DrawGraph(m_graph_info[i].s_pos.x, m_graph_info[i].s_pos.y
				, m_graph_info[i].s_graph_hdl, TRUE);
	}
}

void ChangeGraph::UpdateWhite(const float delta_time)
{
	m_white_alpha += delta_time * m_graph_info[5].s_speed;

	// 255 : 完全不透明
	if (m_white_alpha > 255)
	{
		m_white_alpha = 255;
	}
}

void ChangeGraph::DrawWhite()
{
	// アルファブレンドを設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_white_alpha);

	// alphaが0より大きい場合のみ白画面描画
	if (m_white_alpha > 0)
	{
		DrawExtendGraph(0, 0,DXE_WINDOW_WIDTH ,DXE_WINDOW_HEIGHT
						, m_graph_info[5].s_graph_hdl,TRUE);
	}

	// アルファブレンドを解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
