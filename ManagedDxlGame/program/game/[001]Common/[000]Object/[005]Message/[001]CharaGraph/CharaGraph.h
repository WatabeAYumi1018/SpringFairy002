#pragma once
#include "../../Object.h"

class Mediator;
class GameCamera;


class CharaGraph : public Object
{

public:

	// 画像データを格納する構造体
	struct sGraphInfo
	{
		// csvで定義した識別番号
		std::string s_id;
		// 描画位置
		int s_graph_side;
		// 描画ハンドル
		int s_graph_hdl;
		// 画像ファイルパス
		std::string s_graph_path;
	};

	CharaGraph();

	~CharaGraph();

private:

	int m_window_hdl = 0;

	float m_elasped_time = 0.0f;

	bool m_window_active = true;

	tnl::Vector3 m_pos_player_graph = { 100,250,0 };
	tnl::Vector3 m_pos_partner_graph = { 900,400,0 };

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CharaGraph, &CharaGraph::SeqSlideIn);

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// スライドイン
	bool SeqSlideIn(const float delta_time);
	// 描画中
	bool SeqDraw(const float delta_time);
	// スライドアウト
	bool SeqSlideOut(const float delta_time);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<GameCamera> gameCamera) override;

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};