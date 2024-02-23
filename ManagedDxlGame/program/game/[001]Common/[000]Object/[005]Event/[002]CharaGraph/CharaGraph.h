#pragma once
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../../Object.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// 会話時のキャラクターイラストの定義と更新描画を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class CharaGraph : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

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

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ---------------------------//

	CharaGraph();
	~CharaGraph();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// 現在の描画ID
	int m_now_id = 0;
	// プレイヤーID
	int m_player_id = 0;
	// パートナーID
	int m_partner_id = 0;

	// 経過時間
	float m_elapsed_time = 0;

	// プレイヤーのスライド開始フラグ
	bool m_is_slide_in_player = true;
	// パートナーのスライド開始フラグ
	bool m_is_slide_in_partner = true;
	// プレイヤーのスライド終了フラグ
	bool m_is_slide_out_player = false;
	// パートナーのスライド終了フラグ
	bool m_is_slide_out_partner = false;

	// キャラクター画像の情報
	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// キャラ画像のスライド開始処理
	// arg ... delta_time(前フレームからの経過時間)
	void UpdateSlideIn(const float delta_time);
	
	// キャラ画像のスライド終了処理
	// arg ... delta_time(前フレームからの経過時間)
	void UpdateSlideOut(const float delta_time);
	
	// キャラ画像の描画
	void DrawCharaGraph();
	
	// スクリーンショット時の描画
	void DrawScreenShot();

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// プレイヤーのスライド終了フラグを設定
	void SetIsSlidOutPlayer(bool is_slide_out_player)
	{
		m_is_slide_out_player = is_slide_out_player;
	}

	// パートナーのスライド終了フラグを設定
	void SetIsSlidOutPartner(bool is_slide_out_partner)
	{
		m_is_slide_out_partner = is_slide_out_partner;
	}

	// メディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};