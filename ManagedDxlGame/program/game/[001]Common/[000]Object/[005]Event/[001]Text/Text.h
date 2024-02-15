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
		// 同じグループ内での識別ID
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

	// ウィンドウハンドル
	int m_window_hdl = 0;
	// ウィンドウのアルファ値(最初は透明)
	// キャラクター画像でのフラグと関連付けるため-1で初期化
	int m_window_alpha = -1;
	// 現在のテキストインデックス番号
	int m_now_text_index = 0;

	// 経過時間
	float m_elasped_time = 0.0f;
	// 透明化の速度
	float m_alpha_speed = 200.0f;

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// テキストデータを格納
	void UpdateTexts();

	// ウィンドウ描画の更新
	void UpdateWindow(const float delta_time);
	// ウィンドウ描画
	void DrawWindow();

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	int GetWindowAlpha() const { return m_window_alpha; }

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
