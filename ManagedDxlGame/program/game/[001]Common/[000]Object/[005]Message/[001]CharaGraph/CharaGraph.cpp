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
}

void CharaGraph::Initialize()
{
	m_mediator->LoadCharacterGraph();
}


void CharaGraph::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

void CharaGraph::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	if (m_window_active)
	{
		DrawGraph(500, 400, m_window_hdl, TRUE);
	}

	m_mediator->DrawCharacterGraph(0);
	m_mediator->DrawCharacterGraph(5);
}

bool CharaGraph::SeqSlideIn(const float delta_time)
{
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		DrawStringEx(0, 0, 1, "ground");
	});

	TNL_SEQ_CO_END;
}

bool CharaGraph::SeqDraw(const float delta_time)
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
		DrawStringEx(0, 0, 1, "ground");
	});

	TNL_SEQ_CO_END;
}

bool CharaGraph::SeqSlideOut(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_window_active = false;
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		DrawStringEx(0, 0, 1, "ground");
	});

	TNL_SEQ_CO_END;
}