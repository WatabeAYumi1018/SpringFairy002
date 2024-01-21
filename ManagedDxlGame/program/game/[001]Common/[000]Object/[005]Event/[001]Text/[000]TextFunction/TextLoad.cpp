#include "TextLoad.h"


TextLoad::TextLoad()
{
	m_csv_text
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/text/text.csv");

	LoadText();

	LoadTextIDs();
}

TextLoad::~TextLoad()
{
	m_csv_text.clear();
}

// 識別番号に基づいてテキストデータを取得
Text::sTextInfo TextLoad::GetStoryText(const std::string& id)
{
	// 識別番号に基づいてテキストデータを取得
	for (const Text::sTextInfo& story_text : m_texts)
	{
		if (story_text.s_id == id)
		{
			return story_text;
		}
	}

	// 見つからなければ空の構造体を返す
	// 空の場合、構造体名()で生成（デフォルトコンストラクタ）
	return Text::sTextInfo();
}

// テキストデータを読み取る
void TextLoad::LoadText()
{
	// csvの最初の行は題目なのでスキップ
	for (int i = 1; i < m_csv_text.size();++i)
	{
		std::vector<tnl::CsvCell>& text = m_csv_text[i];
		
		Text::sTextInfo story_text;

		// 識別番号を設定
		story_text.s_id = text[0].getString();

		// テキスト描画終了フラグを設定
		story_text.s_text_end = text[1].getInt();

		// テキストの行を格納
		for (int j = 2; j < text.size(); ++j)
		{
			// テキストが空白でなければ格納
			if (!text[j].getString().empty())
			{
				// 識別番号で、行ごとにテキストを格納
				story_text.s_text_lines.emplace_back(text[j].getString());
			}
		}
		// テキストデータを格納
		m_texts.emplace_back(story_text);
	}
}

void TextLoad::LoadTextIDs()
{
	// オープニングに該当する最初の2行のid名を取得
	for (const Text::sTextInfo& story_text : m_texts)
	{
		if (story_text.s_id[0] || story_text.s_id[1])
		{
			m_opning_text_ids.emplace_back(story_text.s_id);
		}
		/*else if (story_text.s_id[] || story_text.s_id[])
		{
			m_ending_text_ids.emplace_back(story_text.s_id);
		}
		else
		{
			m_event_text_ids.emplace_back(story_text.s_id);
		}*/
	}
	
}

