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
	float m_speed = 10.0f;
	// 円の半径
	float m_radius = 100.0f;
	// 円運動一回分の総時間
	float m_total_time = 7.0f;
	// 円運動の経過時間
	float m_elapsed_time_circle = 0.0f;

	bool m_is_idle = true;
	bool m_is_move = false;
	bool m_is_dance = false;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CinemaPlayer, &CinemaPlayer::SeqTrigger);

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 横移動
	void MoveRound(const float delta_time);

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