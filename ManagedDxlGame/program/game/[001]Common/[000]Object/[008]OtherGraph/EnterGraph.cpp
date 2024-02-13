#include "EnterGraph.h"


EnterGraph::EnterGraph()
{
	m_enter_hdl 
        = LoadGraph("graphics/other/enterGraph/press_enter.png");
}

EnterGraph::~EnterGraph()
{
	DeleteGraph(m_enter_hdl);
}

void EnterGraph::Update(const float delta_time)
{
    if (m_is_active)
    {
        // ゲートが開いたら画像の点滅表示
        m_elasped_time += delta_time;

        if (m_elasped_time > 1)
        {
            m_is_flash = !m_is_flash;

            m_elasped_time = 0;
        }
    }
}

void EnterGraph::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_is_flash)
	{
		DrawGraph(470, 550, m_enter_hdl, TRUE);
	}
}

void EnterGraph::Draw()
{
    if (m_is_flash)
    {
        DrawGraph(470, 550, m_enter_hdl, TRUE);
    }
}