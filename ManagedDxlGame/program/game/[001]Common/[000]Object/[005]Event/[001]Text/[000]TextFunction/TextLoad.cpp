#include "../../../../[002]Mediator/Mediator.h"
#include "../../../[000]Stage/[001]Lane/Lane.h"
#include "TextLoad.h"


TextLoad::TextLoad()
{
	LoadText();
}

TextLoad::~TextLoad()
{
	m_csv_text.clear();
}

void TextLoad::GetTextsLane()
{
	Lane::sLaneEvent lane_event = m_mediator->GetEventLane();

	if (lane_event.s_id == -1) 
	{
		return;
	}
	else
	{
		// -1以外であればテキスト描画を開始
		m_mediator->SetIsTextDrawEnd(false);

		int lane_id = lane_event.s_id;

		m_texts_for_lane.clear();

		// レーン番号に基づいてテキストデータを一括格納
		for (const Text::sTextData& story_text : m_texts_all)
		{
			if (story_text.s_lane_id == lane_id)
			{
				m_texts_for_lane.emplace_back(story_text);
			}
		}
	}
	//// テキストデータをID順にソート
	//std::sort(m_texts_for_lane.begin(), m_texts_for_lane.end(),
	//	[](const Text::sTextData& a, const Text::sTextData& b)
	//	{
	//		return a.s_text_id < b.s_text_id;
	//	});
}

// テキストデータを読み取る
void TextLoad::LoadText()
{
	m_csv_text
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/text/text.csv");

	// csvの最初の行は題目なのでスキップ
	for (int i = 1; i < m_csv_text.size();++i)
	{
		std::vector<tnl::CsvCell>& text = m_csv_text[i];
		
		Text::sTextData story_text;

		// 対応するレーンIDを設定
		story_text.s_lane_id = text[0].getInt();

		// グループ内でのIDを設定
		story_text.s_text_id = text[1].getInt();

		// プレイヤーグラフィックのIDを設定
		story_text.s_player_graph_id = text[2].getInt();

		// パートナーグラフィックのIDを設定
		story_text.s_partner_graph_id = text[3].getInt();

		// テキストの行を格納
		story_text.s_text_line_first = text[4].getString();

		story_text.s_text_line_second = text[5].getString();

		// テキストデータを格納
		m_texts_all.emplace_back(story_text);
	}
}

