#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class TextDraw
{
private:

	// 行のインデックス
	int m_index_line = 0;
	// 文字のインデックス
	int m_index_char = 0;

	// 行の表示間隔のカウント（最後の文字を表示してからのカウント）
	float m_elapsed_time_last_char = 0;
	// 文字の表示間隔のデフォルト
	float m_char_interval = 0.2f;

	// テキストデータの識別番号格納用
	std::vector<std::string> m_text_ids;


public:

	void Draw();

	void Update(float delta_time);

	// テキストIDの複数行テキストデータ（最大2行）の設定と表示
	void SetTextID(const std::vector<std::string>& text_lines);

	bool IsTextEnd() const;
};


// プレイヤー名
//std::string m_player_request_name;

