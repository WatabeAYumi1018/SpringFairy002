#pragma once
#include "../[002]CharaGraph/CharaGraph.h"
#include "../../Object.h"

class Mediator;
class GameCamera;


class Text : public Object
{

public:

	// テキストデータを格納する構造体
	struct sTextData
	{
		// 対応するレーンID
		int s_lane_id;
		// 同じグループ内でのテキストID
		//　ここで読み取ったIDをキャラグラフに代入して関連付け
		int s_text_id;
		// プレイヤーの対応グラフィックID
		int s_player_graph_id;
		// パートナーの対応グラフィックID
		int s_partner_graph_id;
		// テキストの行を格納(1行)
		std::string s_text_line_first;
		// テキストの行を格納(2行)
		std::string s_text_line_second;
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
	//TNL_CO_SEQUENCE(Text, &Text::SeqMessage);

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;


	//// 単発イベントテキストの設定と表示
	//void SetEventTextID();
	//// 複数のテキストIDベクターを設定
	//void SetTextIDs(std::vector<std::string> ids);
	// テキストID表示毎の待機時間を設定
	void SetNextText(const float delta_time, std::vector<std::string> id);

	//// オープニング
	//bool SeqOpning(const float delta_time);
	//// 会話
	//bool SeqMessage(const float delta_time);
	//// イベント
	//bool SeqEvent(const float delta_time);
	///// エンディング
	//bool SeqEnd(const float delta_time);

public:

//	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
