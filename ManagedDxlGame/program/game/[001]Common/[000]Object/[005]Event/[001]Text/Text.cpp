#include "Text.h"
#include "../../../[002]Mediator/Mediator.h"


Text::Text()
{
	SetFontSize(20);

	//�����t�H���g
	tnl::AddFontTTF("font/pen.ttf");

	m_window_hdl
		= LoadGraph("graphics/ui/message/window.png");
}

Text::~Text()
{
	DeleteGraph(m_window_hdl);
}

void Text::Update(float delta_time)
{
	UpdateWindow(delta_time);

	m_mediator->UpdateText(delta_time);
}

void Text::Draw(std::shared_ptr<dxe::Camera> camera)
{
	DrawWindow();

	m_mediator->DrawTextMessage();
}

void Text::UpdateWindow(const float delta_time)
{
	// �`��J�n
	if (!m_mediator->GetIsTextDrawEnd())
	{
		m_window_alpha += delta_time * m_alpha_speed;

		// 255 : ���S�s����
		if (m_window_alpha > 255)
		{
			m_window_alpha = 255;
		}
	}
	// �`��I��
	else
	{
		m_window_alpha -= delta_time * m_alpha_speed;

		// 0 : ���S����
		if (m_window_alpha < 0)
		{
			m_window_alpha = 0;
		}
	}
}

void Text::DrawWindow()
{
	int start_x = 480;
	int start_y = 500;

	// �A���t�@�u�����h��ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_window_alpha);

	// alpha��0���傫���ꍇ�̂݃E�B���h�E�`��
	if (m_window_alpha > 0)
	{
		DrawExtendGraph(start_x, start_y
						, start_x + 300, start_y + 200
						, m_window_hdl, TRUE);
	}

	// �A���t�@�u�����h������
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//void Text::SetEventTextID()
//{
//	// �X�R�A�|�C���g�ɂ���ĕ\������e�L�X�g��ύX
//	std::string story_id;
//
//	if (tile_id == 2)
//	{
//		m_window_active = true;
//		story_id = "meg_event_luck";
//	}
//	// �Y������e�L�X�g�f�[�^���擾
//	Text::sText textData
//		= m_mediator->GetStoryTextData(story_id);
//
//	// �\������
//	m_mediator->SetDrawTextID(textData.s_text_lines, story_id);
//}


//// �I�[�v�j���O
//bool Text::SeqOpning(const float delta_time)
//{
//	if (tnl_sequence_.isStart())
//	{
//		SetTextIDs();
//	}
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		// �I�[�v�j���O�e�L�X�g�̕\��(�������[�v)
//		if (m_now_text_index < m_opning_text_ids.size())
//		{
//			SetNextText(delta_time, m_opning_text_ids);
//		}
//		else
//		{
//			m_now_text_index = 0;
//
//			tnl_sequence_.change(&StoryText::SeqRule);
//
//			TNL_SEQ_CO_END;
//		}
//	});
//
//	TNL_SEQ_CO_END;
//}

//// ���[������
//bool Text::SeqMessage(const float delta_time)
//{
//	if (tnl_sequence_.isStart())
//	{
//		// ����������
//		m_now_text_index = 0;
//
//		m_mediator->GetTextsLoadForLane();
//	}
//
//	// �\�����I�������珈���I��
//	if (m_mediator->IsTextDrawEnd())
//	{
//		return false;
//	}
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		if (m_now_text_index < m_rule_text_ids.size())
//		{
//			SetNextText(delta_time, m_rule_text_ids);
//		}
//		else
//		{
//			m_now_text_index = 0;
//
//			TNL_SEQ_CO_END;
//		}
//	});
//
//	TNL_SEQ_CO_END;
//}

//// ���C�x���g(�����炭�ŏ��̈�񂵂��Ȃ������s����Ă��Ȃ�)
//bool Text::SeqEvent(const float delta_time)
//{
//	// �ړ����ID���擾���邽�߁A2�t���[���ł̎��s�ɐݒ�
//	TNL_SEQ_CO_FRM_YIELD_RETURN(2, delta_time, [&]()
//	{
//		tnl::DebugTrace("set_current_ids");
//
//		SetEventTextID();
//	});
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		// �e�L�X�g�̕\�����I������܂őҋ@
//		if (!m_mediator->GetIsTextEnd())
//		{
//			tnl::DebugTrace("text_moving");
//
//			// �\�����̃e�L�X�g�X�V
//			m_mediator->UpdateStoryText(delta_time);
//		}
//		else
//		{
//			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
//			{
//				if (m_phaseManager->GetGamePhase() == m_game_player)
//				{
//					// �G�l�~�[�t�F�[�Y�ֈڍs
//					m_phaseManager->
//						SetGamePhase(PhaseManager::eGamePhase::e_enemy);
//				}
//				else
//				{
//					// �v���C���[�t�F�[�Y�ֈڍs
//					m_phaseManager->
//						SetGamePhase(PhaseManager::eGamePhase::e_player);
//				}
//
//				// ���̃t�F�[�Y�ֈڍs
//				m_phaseManager->
//					SetActionPhase(PhaseManager::eActionPhase::e_dice);
//
//				TNL_SEQ_CO_END;
//			}
//		}
//	});
//
//	TNL_SEQ_CO_END;
//}



//// ���O�̓���
//bool StoryText::SeqName(const float delta_time)
//{
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//		{
//			if (TNL_SEQ_CO_YIELD_FRM_IS_START)
//			{
//				auto text_data
//					= m_mediator->GetStoryTextData("meg_name_001");
//
//				m_mediator->SetTextId(text_data.s_text_lines, "meg_name_001");
//
//				m_mediator->SetIsNameWindowDrawActive(true);
//			}
//
//			m_mediator->ProcessNameDrawInput();
//
//			// ���O���͂̏����̊����t���O
//			if (m_mediator->GetIsCompleteNameText())
//			{
//				TNL_SEQ_CO_BREAK;
//			}
//		});
//
//	// ���͌�̑ҋ@����
//	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]() {});
//
//	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
//		{
//			auto text_data
//				= m_mediator->GetStoryTextData("meg_name_002");
//
//			m_mediator->SetTextId(text_data.s_text_lines, "meg_name_002");
//		});
//
//	TNL_SEQ_CO_END;
//}

//
//// �G���f�B���O
//bool StoryText::SeqEnd(const float delta_time)
//{
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//
//
//	});
//
//	TNL_SEQ_CO_END;
//}

