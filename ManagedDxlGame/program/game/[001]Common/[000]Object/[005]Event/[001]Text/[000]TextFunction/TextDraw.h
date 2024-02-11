#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"

class Mediator;


class TextDraw
{
private:

	// 文字のインデックス
	int m_index_char_first = 0;
	int m_index_char_second = 0;
	// 行の表示間隔のカウント
	// 最後の文字を表示してからのカウント
	float m_elapsed_time_last_char = 0;
	// 文字の表示間隔のデフォルト
	float m_char_interval = 0.1f;

	// 比較のためのインデックス番号
	int m_now_text_lane_num = 0;
	// 現在のテキストインデックス番号
	int m_now_text_id = 0;
	// 経過時間
	float m_elasped_time = 0.0f;

	// IDごとの待機フラグ
	bool m_is_interval = false;
	// テキスト表示終了フラグ
	bool m_is_end = true;

	std::vector<Text::sTextData> m_lane_text_data;


	std::shared_ptr<Mediator> m_mediator = nullptr;

	TNL_CO_SEQUENCE(TextDraw, &TextDraw::SeqStop);

	// 一行一文字ずつ表示する処理
	void DrawTextData(const float delta_time
						, std::string text_line_first
						, std::string text_line_second);

	// レーンに該当するテキストIDの表示が終了したら次のIDを表示
	void SetNextText(const float delta_time);
	// 表示テキストIDの設定
	void UpdateTexts();


	// テキストの描画を停止
	bool SeqStop(const float delta_time);
	// テキストの描画を開始
	bool SeqDrawTextData(const float delta_time);
	// 次のテキストの設定
	bool SeqSetNextText(const float delta_time);

public:


	void Update(const float delta_time);

	void Draw();

	bool GetIsEnd() const { return m_is_end; }

	int GetNowTextID() const { return m_now_text_id; }
	
	const std::vector<Text::sTextData>& GetLaneTextData() const 
	{
		return m_lane_text_data; 
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};

