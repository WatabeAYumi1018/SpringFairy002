#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"


class TextLoad
{

public:

	TextLoad();

	~TextLoad();

private:

	// マップ情報の読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_text;
	// テキストデータを格納
	std::vector<Text::sTextInfo> m_texts;

	// 本当は、これもデバッグで読み取るべき（後ほど）
	std::vector<std::string> m_opning_text_ids;
	std::vector<std::string> m_event_text_ids;
	std::vector<std::string> m_ending_text_ids;


	// テキストデータを読み取る
	void LoadText();

	void LoadTextIDs();

public:

	// 識別番号に基づいてテキストデータを取得
	Text::sTextInfo GetStoryText(const std::string& id);

	const std::vector<std::string>& GetOpningTextIDs() const;

	const std::vector<std::string>& GetEventTextIDs() const;

	const std::vector<std::string>& GetEndingTextIDs() const;
};
