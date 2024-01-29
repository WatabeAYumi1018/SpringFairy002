#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../[000]GameEngine/[000]Engine/Engine.h"

class Mediator;

class PlayerDraw
{

public:

	PlayerDraw();

	~PlayerDraw();

private:

	// モデル
	int m_model_hdl = 0;
	// idleボーン
	int m_anim_bone_idle_hdl = 0;
	// moveボーン
	int m_anim_bone_move_hdl = 0;
	// bloomボーン
	int m_anim_bone_bloom_hdl = 0;
	// danceボーン
	int m_anim_bone_dance_hdl = 0;

	// テクスチャ
	int m_texture_hdl = 0;

	// アニメーションインデックス番号
	int m_anim_idle_index = 0;
	int m_anim_move_index = 0;
	int m_anim_bloom_index = 0;
	int m_anim_dance_index = 0;

	// 経過時間
	float m_elapsed_time_idle = 0;
	float m_elapsed_time_move = 0;
	float m_elapsed_time_bloom = 0;
	float m_elapsed_time_dance = 0;

	// ループ再生
	float m_time_count_idle = 0;
	float m_time_count_move = 0;
	float m_time_count_bloom = 0;
	float m_time_count_dance = 0;

	// アニメーションの速度
	float m_anim_speed = 10;

	float m_blend_timer = 0;

	bool m_is_attack = false;


	eDirection m_direction = eDirection::e_none;

	StagePhase::eStagePhase m_stage_phase = StagePhase::eStagePhase::e_flower;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(PlayerDraw, &PlayerDraw::SeqMove);

	// プレイヤーメディエータのスマートポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;


	// ライトの設定
	void SetLight();
	
	// アニメーションのブレンド処理
	void AnimBlend(const float delta_time, int current_anim_index, int next_anim_index);

	void AnimAttach(int& anim_index, int anim_bone_hdl, float& time_count);


	// move ループ再生の時間設定
	void AnimMove(const float delta_time);
	// bloom 単発再生の時間設定
	void AnimBloom(const float delta_time);
	// dance 単発再生の時間設定
	void AnimDance(const float delta_time);

	// idle ループ再生の時間設定　
	void AnimIdle(const float delta_time);

	// 移動状態
	bool SeqMove(const float delta_time);
	// ブルーム状態
	bool SeqBloom(const float delta_time);
	// moveアニメーションへの遷移
	bool SeqBloomToMove(const float delta_time);
	// ダンス状態
	bool SeqDance(const float delta_time);
	// danceアニメーションへの遷移
	bool SeqDanceToMove(const float delta_time);

	// アイドル状態
	bool SeqIdle(const float delta_time);


public:

	// アニメーションの更新処理
	void Update(float delta_time);
	// PlayerHumanクラスのDraw関数にて毎フレーム呼び出す
	void Draw();


	int GetModelHdl() const { return m_model_hdl; }

	bool GetIsAttack() const { return m_is_attack; }


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};