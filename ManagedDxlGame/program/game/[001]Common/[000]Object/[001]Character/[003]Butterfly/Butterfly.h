#pragma once
#include "../Character.h"


class Mediator;


class Butterfly : public Character
{
	
public:

	Butterfly();

	~Butterfly();

private:

	int m_texture_tip_hdl = 0;

	// 円の速度
	float m_speed = 10.0f;
	// 円の半径
	float m_radius = 20.0f;
	// 円運動一回分の総時間
	float m_total_time = 5.0f;
	// 円運動の経過時間
	float m_elapsed_time_circle = 0.0f;

	// moveアニメーション経過時間
	float m_elapsed_time = 0.0f;
	// moveアニメーションのループ時間
	float m_time_count= 0.0f;
	// moveアニメーションの速度
	float m_anim_speed = 100.0f;
	// moveアニメーションのインデックス
	int m_anim_index = 0;

	// 円運動フラグ
	bool m_is_circle = false;
	// 鱗粉フラグ
	bool m_is_powder = false;

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	void SetAnim();

	void AnimMove(const float delta_time);

	void AnimDraw(const float delta_time);

	void MoveRound(const float delta_time);

	void MoveStraight(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;


	bool GetIsCircle() const { return m_is_circle; }

	bool GetIsPowder() const { return m_is_powder; }

	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}
};