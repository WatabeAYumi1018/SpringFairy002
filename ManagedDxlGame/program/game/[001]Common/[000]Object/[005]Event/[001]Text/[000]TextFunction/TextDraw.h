#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"

class Mediator;


class TextDraw
{
private:

	// 行のインデックス
	int m_index_line = 0;
	// 文字のインデックス
	int m_index_char = 0;

	// 行の表示間隔のカウント
	// 最後の文字を表示してからのカウント
	float m_elapsed_time_last_char = 0;
	// 文字の表示間隔のデフォルト
	float m_char_interval = 0.2f;

	std::vector<std::string> m_text_line;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 全ての文字描画を終了
	void ResetText();

public:

	void Update(float delta_time);

	void Draw();

	// レーンIDに該当する全ての表示終了
	bool IsTextEnd();

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};


// プレイヤー名
//std::string m_player_request_name;

