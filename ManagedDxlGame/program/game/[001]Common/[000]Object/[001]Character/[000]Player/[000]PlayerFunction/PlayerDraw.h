#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../Character.h"

class Mediator;

/////////////////////////////////////////////////////////////////////////////////////////
// 
// プレイヤーのアニメーション描画を管理するクラス(ゲーム、シネマ両方)
//
/////////////////////////////////////////////////////////////////////////////////////////


class PlayerDraw
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	PlayerDraw() {}

	~PlayerDraw();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// モデルハンドル
	// ハンドルをそれぞれ分けないと挙動エラーになる

	//-----Player用変数-----//

	int m_model_game_hdl = 0;
	// moveボーン
	int m_anim_bone_move_game_hdl = 0;
	// bloomボーン
	int m_anim_bone_bloom_game_hdl = 0;
	// danceボーン
	int m_anim_bone_dance_game_hdl = 0;

	//----------------------//

	//--CinemaPlayer用変数--//

	int m_model_cinema_hdl = 0;
	// idleボーン
	int m_anim_bone_idle_cinema_hdl = 0;
	int m_anim_bone_dance_cinema_hdl = 0;

	//----------------------//


	//-------共用変数-------//

	// 各種アニメーションのインデックス番号
	int m_anim_idle_index = 0;
	int m_anim_move_index = 0;
	int m_anim_bloom_index = 0;
	int m_anim_dance_index = 0;

	// 各種経過時間
	float m_elapsed_time_idle = 0;
	float m_elapsed_time_move = 0;
	float m_elapsed_time_bloom = 0;
	float m_elapsed_time_dance = 0;

	// 各種再生時間のカウント
	float m_time_count_idle = 0;
	float m_time_count_move = 0;
	float m_time_count_bloom = 0;
	float m_time_count_dance = 0;

	// アニメーションの速度
	float m_anim_speed = 10;
	// ブレンド時間
	float m_blend_timer = 0;
	// ブレンド総時間
	float m_blend_total_time = 1.0f;
	
	// ブルーム攻撃フラグ
	bool m_is_bloom = false;
	// ダンス攻撃フラグ
	bool m_is_dance = false;

	//----------------------//


	//--CinemaPlayer用変数--//

	// ボーンのデタッチ設定フラグ(シネマプレイヤー用)
	bool m_is_touch_idle = false;
	bool m_is_touch_dance = false;

	//----------------------//

	// キャラクターの向き
	Character::eDirection m_direction
		= Character::eDirection::e_none;
	
	// ステージのフェーズ
	StagePhase::eStagePhase m_stage_phase 
		= StagePhase::eStagePhase::e_flower;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(PlayerDraw, &PlayerDraw::SeqMove);

	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// アニメーションのブレンド処理
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... モデルハンドル
	// arg3 ... 現在のアニメーションのインデックス番号
	// arg4 ... 次のアニメーションのインデックス番号
	// tips ... アニメーションのブレンド処理を行う
	//			DxlibのMV1SetAttachAnimBlendRate関数引数に準ずる
	void AnimBlend(const float delta_time,int model_hdl
					, int current_anim_index, int next_anim_index);

	// アニメーションのアタッチ処理
	// arg1 ... モデルハンドル
	// arg2 ... アニメーションのインデックス番号
	// arg3 ... アニメーションをアタッチするボーンのハンドル
	// arg4 ... アニメーションの再生時間カウント
	// Dxlib,MV1AttachAnim, MV1GetAttachAnimTotalTime関数引数に準ずる
	// ※anim_index、time_countのみ参照渡し
	void AnimAttach(int model_hdl, int& anim_index
					, int anim_bone_hdl, float& time_count);

	// move ループ再生の時間設定
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... モデルハンドル
	void AnimMove(const float delta_time, int model_hdl);

	// bloom 単発再生の時間設定
	// arg ... delta_time(前フレームからの経過時間)
	void AnimBloom(const float delta_time);

	// dance 単発再生の時間設定
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... モデルハンドル
	void AnimDance(const float delta_time, int model_hdl);

	// idle ループ再生の時間設定　
	// arg ... delta_time(前フレームからの経過時間)
	void AnimIdle(const float delta_time);

	// 移動状態
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqMove(const float delta_time);
	
	// ブルーム状態
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqBloom(const float delta_time);
	
	// moveアニメーションへの遷移
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqBloomToMove(const float delta_time);
	
	// ダンス状態
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqDance(const float delta_time);

	// danceアニメーションへの遷移
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqDanceToMove(const float delta_time);

public:

	void Initialize();
	
	void Update(const float delta_time);
	
	void Draw();
	

	//--CinemaPlayer用関数--//

	// シネマカメラ用のidleアニメーション
	// arg ... delta_time(前フレームからの経過時間)
	void CinemaAnimIdle(const float delta_time);

	// シネマカメラ用のdanceアニメーション
	// arg ... delta_time(前フレームからの経過時間)
	void CinemaAnimDance(const float delta_time);

	//----------------------//

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ダンスによる経過時間の設定（デフォルト0のため、引数は基本空で使用）
	// arg ... 経過時間
	// tips ...ダンス時間のリセットのために使用
	// ※セッターなのに引数がデフォルト値を持つのは好ましいのか難儀中
	void SetElapsedTimeDance(float elapsed_time_dance = 0) 
	{ 
		m_elapsed_time_dance = elapsed_time_dance; 
	}

	// bloomフラグを取得
	bool GetIsBloom() const { return m_is_bloom; }
	
	// danceフラグを取得
	bool GetIsDance() const { return m_is_dance; }

	// メディエータのポインタ設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};