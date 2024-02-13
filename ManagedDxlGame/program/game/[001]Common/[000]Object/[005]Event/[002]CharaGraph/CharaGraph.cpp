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
	// �e�L�X�g���I�����Ă��Ȃ��ꍇ
	if (!m_mediator->GetIsTextDrawEnd())
	{
		std::vector <Text::sTextData> texts_data
			= m_mediator->GetLaneTextDrawData();

		// �e�L�X�g�f�[�^����̏ꍇ�͏������I��
		if (texts_data.empty())
		{
			return;
		}

		m_now_id = m_mediator->GetNowTextDrawID();

		m_player_id
			= texts_data[m_now_id].s_player_graph_id;

		m_partner_id
			= texts_data[m_now_id].s_partner_graph_id;

		//�@-1�łȂ��A�X���C�h�C���t���O��true�̎�
		UpdateSlideIn(delta_time);
	}
	else
	{
		// �E�B���h�E�̓����x��100�����ɂȂ�����X���C�h�A�E�g
		if (m_mediator->GetTextWindowAlpha() < 200)
		{
			// -1�łȂ��A�X���C�h�A�E�g�t���O��true�̎�
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
	// -1�łȂ��A���X���C�h�t���O
	if (m_player_id != -1 && m_is_slide_in_player)
	{
		m_chara_graph[m_player_id].s_current_pos_x
			+= delta_time * m_chara_graph[m_player_id].s_slide_speed;

		if (m_chara_graph[m_player_id].s_current_pos_x 
			>= m_chara_graph[m_player_id].s_end_pos_x)
		{
			// �v���C���[�摜��ID�S�Ăɑ΂��ď������s��
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
			// �p�[�g�i�[�摜��ID�S�Ăɑ΂��ď������s��
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
			// �v���C���[�摜��ID�S�Ăɑ΂��ď������s��
			for (int i = 0; i <= 3 ; ++i)
			{
				m_chara_graph[i].s_current_pos_x
					= m_chara_graph[i].s_start_pos_x;
			}

			// �t���O���Z�b�g
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
			// �p�[�g�i�[�摜��ID�S�Ăɑ΂��ď������s��
			for (int i = 4; i <= 7; ++i)
			{
				m_chara_graph[i].s_current_pos_x
					= m_chara_graph[i].s_start_pos_x;
			}
			// �t���O���Z�b�g
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
	// ����̉摜��`��
	DrawGraph(m_chara_graph[1].s_end_pos_x
			, m_chara_graph[1].s_pos_y
			, m_chara_graph[1].s_graph_hdl, TRUE);

	DrawGraph(m_chara_graph[5].s_end_pos_x
			, m_chara_graph[5].s_pos_y
			, m_chara_graph[5].s_graph_hdl, TRUE);
}
