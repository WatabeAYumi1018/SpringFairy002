#pragma once
#include "../../Object.h"

class Mediator;
class GameCamera;


class Text : public Object
{

public:

	// テキストデータを格納する構造体
	struct sTextInfo
	{
		// csvで定義した識別番号
		std::string s_id;
		// テキスト描画終了フラグ
		bool s_text_end;
		// テキストの行を格納
		std::vector<std::string> s_text_lines;

	};

	Text();

	~Text();

private:

	// ウィンドウ画像のハンドル
	int m_window_hdl = 0;
	// 現在のテキストインデックス番号
	int m_now_text_index = 0;

	float m_elasped_time = 0.0f;

	bool m_window_active = true;

	//// コルーチンシーケンス
	//TNL_CO_SEQUENCE(Text, &Text::SeqOpning);

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

//
//	// 単発イベントテキストの設定と表示
//	void SetEventTextID();
//	// 複数のテキストIDベクターを設定
//	void SetTextIDs(std::vector<std::string> ids);
//	// テキストID表示毎の待機時間を設定
//	void SetNextText(float delta_time, std::vector<std::string> id);
//
//	// オープニング
//	bool SeqOpning(const float delta_time);
//	// ルール説明
//	bool SeqRule(const float delta_time);
//	// イベント
//	bool SeqEvent(const float delta_time);
//	//// エンディング
//	//bool SeqEnd(const float delta_time);
//
//public:
//
//	void Update(float delta_time) override;
//
//	void Draw(std::shared_ptr<GameCamera> gameCamera) override;

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
