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

	bool m_is_end = false;

	std::vector<Text::sTextData> m_lane_text_data;


	std::shared_ptr<Mediator> m_mediator = nullptr;

	TNL_CO_SEQUENCE(TextDraw, &TextDraw::SeqStop);

	// 一行一文字ずつ表示する処理
	void DrawTextData(const float delta_time, std::string text_line);
	// レーンに該当するテキストIDの表示が終了したら次のIDを表示
	void SetNextText(const float delta_time);

	bool SeqStop(const float delta_time);
	bool SeqDrawTextData(const float delta_time);
	bool SeqSetNextText(const float delta_time);

public:


	void Update(const float delta_time);

	// 表示する文字のみの描画
	void Draw();

	//// レーンIDに該当する全ての表示終了
	//bool IsTextEnd();

	void SetIsEnd(bool is_end) { m_is_end = is_end; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};


// プレイヤー名
//std::string m_player_request_name;

