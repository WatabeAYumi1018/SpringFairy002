#include "Text.h"
#include "../../../[002]Mediator/Mediator.h"



Text::Text()
{
	m_window_hdl = LoadGraph("graphics/Opning/text_window.png");

	//SetFontSize(30);
}

Text::~Text()
{
	DeleteGraph(m_window_hdl);
}



void Text::Update(float delta_time)
{
	//m_mediator->GetTextsLoadForLane();

	//tnl_sequence_.update(delta_time);

	m_mediator->UpdateTextMessage(delta_time);
}

void Text::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	m_mediator->DrawTextMessage();
}

//
//void Text::SetEventTextID()
//{
//	// スコアポイントによって表示するテキストを変更
//	std::string story_id;
//
//	if (tile_id == 2)
//	{
//		m_window_active = true;
//		story_id = "meg_event_luck";
//	}
//	// 該当するテキストデータを取得
//	Text::sText textData
//		= m_mediator->GetStoryTextData(story_id);
//
//	// 表示処理
//	m_mediator->SetDrawTextID(textData.s_text_lines, story_id);
//}

//void Text::SetTextIDs(std::vector<std::string> id)
//{
//	Text::sTextData textInfo
//		= m_mediator->GetTextLoadInfo(id[m_now_text_index]);
//
//	m_mediator->SetTextDrawLine(textInfo.s_text_lines);
//}
//
//void Text::SetNextText(float delta_time, std::vector<std::string> id)
//{
//	float wait_time = 2.0f;
//
//	m_elasped_time += delta_time;
//
//	if (m_elasped_time >= wait_time)
//	{
//		m_now_text_index++;
//
//		m_elasped_time = 0.0f;
//
//		if (m_now_text_index < id.size())
//		{
//			// 次のテキストIDの準備
//			SetTextIDs(id);
//		}
//	}
//}

//// オープニング
//bool Text::SeqOpning(const float delta_time)
//{
//	if (tnl_sequence_.isStart())
//	{
//		SetTextIDs();
//	}
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		// オープニングテキストの表示(無限ループ)
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

//// ルール説明
//bool Text::SeqMessage(const float delta_time)
//{
//	if (tnl_sequence_.isStart())
//	{
//		// 初期化処理
//		m_now_text_index = 0;
//
//		m_mediator->GetTextsLoadForLane();
//	}
//
//	// 表示が終了したら処理終了
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

//// ★イベント(おそらく最初の一回しかなぜか実行されていない)
//bool Text::SeqEvent(const float delta_time)
//{
//	// 移動後のIDを取得するため、2フレームでの実行に設定
//	TNL_SEQ_CO_FRM_YIELD_RETURN(2, delta_time, [&]()
//	{
//		tnl::DebugTrace("set_current_ids");
//
//		SetEventTextID();
//	});
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		// テキストの表示が終了するまで待機
//		if (!m_mediator->GetIsTextEnd())
//		{
//			tnl::DebugTrace("text_moving");
//
//			// 表示中のテキスト更新
//			m_mediator->UpdateStoryText(delta_time);
//		}
//		else
//		{
//			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
//			{
//				if (m_phaseManager->GetGamePhase() == m_game_player)
//				{
//					// エネミーフェーズへ移行
//					m_phaseManager->
//						SetGamePhase(PhaseManager::eGamePhase::e_enemy);
//				}
//				else
//				{
//					// プレイヤーフェーズへ移行
//					m_phaseManager->
//						SetGamePhase(PhaseManager::eGamePhase::e_player);
//				}
//
//				// 次のフェーズへ移行
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



//// 名前の入力
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
//			// 名前入力の処理の完了フラグ
//			if (m_mediator->GetIsCompleteNameText())
//			{
//				TNL_SEQ_CO_BREAK;
//			}
//		});
//
//	// 入力後の待機時間
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
//// エンディング
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

