#pragma once
#include "../Object.h"

class Mediator;


class ChangeGraph : public Object
{

public:

	enum eMoveType
	{
		streight,
		right,
		left
	};

	struct sChangeGraphInfo
	{
		int s_id;
		int s_graph_hdl;
		tnl::Vector3 s_pos;
		float s_speed;
	};

	ChangeGraph();
	~ChangeGraph();

private:

	float m_white_alpha = 0.0f;

	// 描画フラグ
	bool m_is_active_tulip = false;
	bool m_is_active_white = false;
	bool m_is_active_blossom = false;
	bool m_is_active_butterfly = false;

	// グラフィック画像の情報格納
	std::vector<sChangeGraphInfo> m_graph_info;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 座標更新
	void UpdateChangeGraph(const float delta_time,int start,int end);
	// 描画処理
	void DrawChangeGraph(int start,int end);
	// 白画面フェードイン更新
	void UpdateWhite(const float delta_time);
	// 白画面描画
	void DrawWhite();
	

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr < dxe::Camera> camera) override;

	void SetIsActiveTulip(bool is_active)
	{
		m_is_active_tulip = is_active;
	}

	void SetIsActiveWhite(bool is_active)
	{
		m_is_active_white = is_active;
	}

	void SetIsActiveBlossom(bool is_active)
	{
		m_is_active_blossom = is_active;
	}

	void SetIsActiveButterfly(bool is_active)
	{
		m_is_active_butterfly = is_active;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};