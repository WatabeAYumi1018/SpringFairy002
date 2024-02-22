#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"


///////////////////////////////////////////////////////////////////////////
//
// テキストcsvファイルの読み込みクラス
//
///////////////////////////////////////////////////////////////////////////


class TextLoad
{

public:

	TextLoad();

	~TextLoad();

private:

	// マップ情報の読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_texts;
	// 全テキストデータを格納
	std::vector<Text::sTextData> m_texts_all;

	// テキストデータを読み取る
	void LoadText();

public:

	const std::vector<Text::sTextData>& GetTextsAll() const
	{
		return m_texts_all;
	}

	//const std::vector<std::string>& GetTextsMessageForLane() const
	//{
	//	return m_texts_message_for_lanes;
	//}
};
