#pragma once
#include "../Object.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// カメラ遷移する際のイラストの定義と更新描画処理を行うクラス
// ※遷移を自然にするために、本クラスはシネマカメラのみで使用
//　
///////////////////////////////////////////////////////////////////////////


class ChangeGraph : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

	// グラフィック画像の情報
	struct sChangeGraphInfo
	{
		int s_id;
		int s_graph_hdl;
		tnl::Vector3 s_pos;
		float s_speed;
	};

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	ChangeGraph();
	~ChangeGraph();

	//---------------------------------------------------------------------------------//

protected:

	//-----------------------------------メンバ変数------------------------------------//

	// 白画面のアルファ値
	float m_white_alpha = 0.0f;

	// flowerステージシネマの描画フラグ
	bool m_is_flower = false;
	// woodステージシネマの描画フラグ
	bool m_is_wood = false;
	// 白画面活性化フラグ
	bool m_is_active_white = false;
	// 白画面非活性化フラグ
	bool m_is_not_active_white = false;

	// グラフィック画像の情報格納
	std::vector<sChangeGraphInfo> m_graph_info;

	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 座標更新
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... 開始インデックス
	// arg3 ... 終了インデックス
	void UpdateChangeGraph(const float delta_time, int start, int end);
	
	// 描画処理
	// arg1 ... 開始インデックス
	// arg2 ... 終了インデックス
	void DrawChangeGraph(int start, int end);
	
	// 白画面フェードイン更新
	// arg ... delta_time(前フレームからの経過時間)
	void UpdateWhite(const float delta_time);
	
	// 白画面描画
	void DrawWhite();

	//---------------------------------------------------------------------------------//

public:

	//-----------------------------------メンバ関数------------------------------------//

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr < dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//

	
	//----------------------------------Setter&Getter----------------------------------//

	// flowerステージシネマの描画フラグを設定
	void SetIsFlower(bool is_active) { m_is_flower = is_active; }

	// woodステージシネマの描画フラグを設定
	void SetIsWood(bool is_active) { m_is_wood = is_active; }

	// 白画面活性化フラグを設定
	void SetIsActiveWhite(bool is_active)
	{
		m_is_active_white = is_active;
	}

	// メディエータのポインタを設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};