#pragma once
#include "../../Character.h"


class Mediator;
// updateにてイベント発生時のみ処理をするようにする

class CinemaPlayer : public Character
{

public:

	CinemaPlayer();

	~CinemaPlayer();

private:

	// 円の速度
	float m_speed = 15.0f;
	// 円の半径
	float m_radius = 10.0f;
	// 円運動一回分の総時間
	float m_total_time = 4.0f;
	// 円運動の経過時間
	float m_elapsed_time_circle = 0.0f;

	bool m_is_idle = false;
	bool m_is_move = false;
	bool m_is_dance = false;
	
	// プレイヤーの自己発光
	DxLib::COLOR_F m_emissive = { 0.5f,0.5f,0.5f,1 };

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CinemaPlayer, &CinemaPlayer::SeqTrigger);

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 線形補間関数
	float Lerp(float start, float end, float t);

	// 横移動
	void MoveRound(const float delta_time);
	// 落下移動
	void MoveDown(const float delta_time);
	// バックへ勢いよく移動
	void MoveBackCenter(const float delta_time);


	// 待機
	bool SeqTrigger(const float delta_time);
	// 紹介
	bool SeqFirst(const float delta_time);
	// エリア２への移行
	bool SeqSecond(const float delta_time);
	// エリア３への移行
	bool SeqThird(const float delta_time);


public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};