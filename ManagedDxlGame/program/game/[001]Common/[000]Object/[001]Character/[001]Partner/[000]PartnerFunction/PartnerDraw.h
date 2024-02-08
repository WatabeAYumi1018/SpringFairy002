#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../[000]GameEngine/[000]Engine/Engine.h"
#include "../Partner.h"

class Mediator;


class PartnerDraw
{

public:

	PartnerDraw() {}

	~PartnerDraw() {}

private:

	// モデル
	int m_model_hdl = 0;
	// moveボーン
	int m_anim_bone_move_game_hdl = 0;
	// idleボーン
	int m_anim_bone_idle_cinema_hdl = 0;

	// テクスチャ
	int m_texture_game_hdl = 0;

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
	// walkアニメーションのオフセット
	float m_anim_move_offset = 0;

	// エネミーの種類（テクスチャ）
	Partner::ePartnerType m_enemy_type = Partner::ePartnerType::green;

	eDirection m_direction = eDirection::e_none;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(PartnerDraw, &PartnerDraw::SeqIdle);

	// プレイヤーメディエータのスマートポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 単発再生の時間設定をする
	void AnimMove(float delta_time);
	// ループ再生の時間設定をする　
	void AnimIdle(float delta_time);

	// 移動状態
	bool SeqMove(const float delta_time);
	// アイドル状態
	bool SeqIdle(const float delta_time);


public:

	void Initialize();
	// アニメーションの更新処理
	void Update(float delta_time);
	// PlayerHumanクラスのDraw関数にて毎フレーム呼び出す
	void Draw();

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};