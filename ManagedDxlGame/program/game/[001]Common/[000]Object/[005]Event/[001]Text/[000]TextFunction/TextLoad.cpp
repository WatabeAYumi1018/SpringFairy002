#include "TextLoad.h"


TextLoad::TextLoad()
{
	LoadText();
}

TextLoad::~TextLoad()
{
	m_csv_texts.clear();
}

// テキストデータを読み取る
void TextLoad::LoadText()
{
	m_csv_texts
		//= tnl::LoadCsv<tnl::CsvCell>("csv/ui/text/text.csv");
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/text/text0219.csv");

	// csvの最初の行は題目なのでスキップ
	for (int i = 1; i < m_csv_texts.size();++i)
	{
		std::vector<tnl::CsvCell>& text = m_csv_texts[i];
		
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

