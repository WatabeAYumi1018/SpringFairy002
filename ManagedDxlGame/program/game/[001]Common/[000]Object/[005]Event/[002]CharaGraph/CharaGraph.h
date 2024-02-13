#pragma once
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../../Object.h"

class Mediator;


class CharaGraph : public Object
{

public:

	// 画像データを格納する構造体
	struct sGraphInfo
	{
		// csvで定義した識別番号
		int s_id;
		// 描画ハンドル
		int s_graph_hdl;
		// スライド速度
		float s_slide_speed;
		// 開始描画座標
		float s_start_pos_x;
		// 現在の描画座標
		float s_current_pos_x;
		// 最終描画座標
		float s_end_pos_x;
		// Y座標
		float s_pos_y;
	};

	CharaGraph();

	~CharaGraph();

private:

	int m_now_id = 0;
	int m_player_id = 0;
	int m_partner_id = 0;

	float m_elapsed_time = 0;

	bool m_is_slide_in_player = true;
	bool m_is_slide_in_partner = true;

	bool m_is_slide_out_player = false;
	bool m_is_slide_out_partner = false;

	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// キャラ画像の座標更新
	void UpdateSlideIn(const float delta_time);
	void UpdateSlideOut(const float delta_time);
	// キャラ画像の描画
	void DrawCharaGraph();
	// スクリーンショット時の描画
	void DrawScreenShot();

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetIsSlidOutPlayer(bool is_slide_out_player)
	{
		m_is_slide_out_player = is_slide_out_player;
	}

	void SetIsSlidOutPartner(bool is_slide_out_partner)
	{
		m_is_slide_out_partner = is_slide_out_partner;
	}

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};