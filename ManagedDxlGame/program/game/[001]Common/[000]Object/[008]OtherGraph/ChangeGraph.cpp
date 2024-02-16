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
	if (m_is_active_white)
	{
		UpdateWhite(delta_time);
	}

	if (m_is_flower)
	{
		UpdateChangeGraph(delta_time, 0, 0);
	}
	else if (m_is_wood)
	{
		UpdateChangeGraph(delta_time, 2, 2);
	}
}

void ChangeGraph::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_is_active_white)
	{
		DrawWhite();
	}

	if (m_is_flower)
	{
		DrawChangeGraph(0, 0);
	}
	else if (m_is_wood)
	{
		DrawChangeGraph(2, 2);
	}
}

void ChangeGraph::UpdateChangeGraph(const float delta_time, int start, int end)
{
	for (int i = start; i <= end; ++i)
	{
		if (m_is_flower)
		{
			m_graph_info[i].s_pos.x 
				-= delta_time * m_graph_info[i].s_speed;
		}
		else if(m_is_wood)
		{
			m_graph_info[i].s_pos.x
				-= delta_time * m_graph_info[i].s_speed;

			m_graph_info[i].s_pos.y 
				+= delta_time * m_graph_info[i].s_speed; 
		}
	}
}

void ChangeGraph::DrawChangeGraph(int start, int end)
{
	for (int i = start; i <= end; ++i)
	{
		DrawGraph(m_graph_info[i].s_pos.x, m_graph_info[i].s_pos.y
				 ,m_graph_info[i].s_graph_hdl, TRUE);
	}
}

void ChangeGraph::UpdateWhite(const float delta_time)
{
	// 255 : 完全不透明
	if (m_white_alpha > 255)
	{
		m_white_alpha = 255;
		m_is_not_active_white = true;
	}
	
	if (m_is_not_active_white)
	{
		m_white_alpha -= delta_time * m_graph_info[1].s_speed;

		// 0 : 完全透明
		if (m_white_alpha < 0)
		{
			m_white_alpha = 0;
			m_is_active_white = false;
			m_is_not_active_white = false;
		}
	}
	else
	{
		m_white_alpha += delta_time * m_graph_info[1].s_speed;
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
						, m_graph_info[1].s_graph_hdl,TRUE);
	}

	// アルファブレンドを解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
