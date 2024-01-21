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
		// 描画座標
		tnl::Vector3 s_graph_pos;
		// 描画ハンドル
		int s_graph_hdl;
		// 画像ファイルパス
		std::string s_graph_path;
	};

	CharaGraph();

	~CharaGraph();

private:

	int m_window_hdl = 0;

	float m_elapsed_time = 0.0f;

	bool m_window_active = true;


	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CharaGraph, &CharaGraph::SeqSlideIn);

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// キャラ画像の読み取り
	void LoadCharaGraph();
	//// キャラ画像のスライド処理
	//void UpdateCharaSlideGraph(const float delta_time, int graph_id);
	// キャラ画像の描画
	void DrawCharaGraph(int graph_id);

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