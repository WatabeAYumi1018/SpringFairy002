#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"

class Mediator;

class TextLoad
{

public:

	TextLoad();

	~TextLoad();

private:

	// マップ情報の読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_text;
	// 全テキストデータを格納
	std::vector<Text::sTextData> m_texts_all;
	// レーンIDに該当するテキストデータを格納
	std::vector<Text::sTextData> m_texts_for_lane;

	std::shared_ptr<Mediator> m_mediator = nullptr;


	// テキストデータを読み取る
	void LoadText();


public:

	// レーンIDに該当するテキストを一括取得
	void GetTextsLane();


	const std::vector<Text::sTextData>& GetTextsForLane() const
	{
		return m_texts_for_lane;
	}

	//const std::vector<std::string>& GetTextsMessageForLane() const
	//{
	//	return m_texts_message_for_lanes;
	//}


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
