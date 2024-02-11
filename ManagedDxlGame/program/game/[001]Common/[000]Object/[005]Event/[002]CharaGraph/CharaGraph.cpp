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

	// �e�L�X�g�f�[�^����̏ꍇ�͏������I��
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

		// ������X���C�h
		if (m_chara_graph[0].s_graph_side == 0)
		{
			start_x = -200;
		}
		// �E����X���C�h
		else
		{
			start_x = DXE_WINDOW_WIDTH + 200;
		}

		// ���݂̃X���C�h�ʒu���v�Z
		float current_x = start_x + (end_x - start_x) * delta_time * 5;

		// �O���t�B�b�N�̈ʒu���X�V
		m_chara_graph[0].s_graph_pos.x = current_x;
	});

	TNL_SEQ_CO_END;
}

bool CharaGraph::SeqDrawChange(const float delta_time)
{
	// �e�L�X�g�I���t���O���o������
	//if ()
	//{
	//	tnl_sequence_.change(&Graph::SeqSlideOut);
	//}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		
		// ���W�ύX�Ȃ�
	});

	TNL_SEQ_CO_END;
}

bool CharaGraph::SeqSlideOut(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		float start_x = m_chara_graph[0].s_graph_pos.x;
		float end_x = 0;

		// ������X���C�h
		if (m_chara_graph[0].s_graph_side == 0)
		{
			end_x = -200;
		}
		// �E����X���C�h
		else
		{
			end_x = DXE_WINDOW_WIDTH + 200;
		}

		// ���݂̃X���C�h�ʒu���v�Z
		float current_x = start_x + (end_x - start_x) * delta_time * 5;

		// �O���t�B�b�N�̈ʒu���X�V
		m_chara_graph[0].s_graph_pos.x = current_x;
	});

	TNL_SEQ_CO_END;
}

