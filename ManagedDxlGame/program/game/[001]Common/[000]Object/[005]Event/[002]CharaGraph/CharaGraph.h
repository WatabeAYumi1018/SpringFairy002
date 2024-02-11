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
		// 描画位置
		int s_graph_side;
		// 描画ハンドル
		int s_graph_hdl;
		// 描画座標
		tnl::Vector3 s_graph_pos;
	};

	CharaGraph();

	~CharaGraph();

private:


	float m_elapsed_time = 0.0f;

	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CharaGraph, &CharaGraph::SeqSlideIn);

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//// キャラ画像のスライド処理
	//void UpdateCharaSlideGraph(const float delta_time, int graph_id);	

	// キャラ画像の更新
	void UpdateCharaGraph();
	
	void DrawCharaGraph();


	// スライドイン
	bool SeqSlideIn(const float delta_time);
	// 描画中
	bool SeqDrawChange(const float delta_time);
	// スライドアウト
	bool SeqSlideOut(const float delta_time);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};