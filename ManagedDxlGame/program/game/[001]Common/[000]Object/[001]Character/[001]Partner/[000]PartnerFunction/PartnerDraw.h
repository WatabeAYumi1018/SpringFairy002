#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../Character.h"
#include "../Partner.h"


class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// パートナーの描画処理に関するクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class PartnerDraw
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	PartnerDraw() {}
	~PartnerDraw();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// ※現在moveは使用していませんが、今後の拡張を見越して残しています

	// モデル
	int m_model_hdl = 0;
	// moveボーン
	int m_anim_bone_move_hdl = 0;
	// idleボーン
	int m_anim_bone_idle_hdl = 0;

	// アニメーションインデックス番号
	int m_anim_move_index = 0;
	int m_anim_idle_index = 0;

	// 経過時間
	float m_elapsed_time_move = 0;
	float m_elapsed_time_idle = 0;

	// ループ再生
	float m_time_count_move = 0;
	float m_time_count_idle = 0;

	// アニメーションの速度
	float m_anim_speed = 10;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(PartnerDraw, &PartnerDraw::SeqIdle);

	// プレイヤーメディエータのスマートポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// 単発再生の時間設定をする
	// arg ... delta_time(前フレームからの経過時間)
	void AnimMove(const float delta_time);

	// ループ再生の時間設定をする　
	// arg ... delta_time(前フレームからの経過時間)
	void AnimIdle(const float delta_time);

	// 移動状態
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqMove(const float delta_time);

	// アイドル状態
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqIdle(const float delta_time);

public:

	void Initialize();
	
	void Update(const float delta_time);
	
	void Draw();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// メディエータのポインタ設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};