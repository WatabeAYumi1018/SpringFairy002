#pragma once
#include "../Character.h"


class Butterfly : public Character
{
	
public:

	Butterfly();

	~Butterfly();

private:

	int m_model_hdl = 0;
	int m_texture_hdl = 0;
	int m_anim_bone_move_hdl = 0;

	// ‰~‚Ì‘¬“x
	float m_speed = 10;
	// ‰~‚Ì”¼Œa
	float m_circle_radius = 100.0f;
	// ‰~‚ÌŒ»İ‚ÌŠp“xiÃ“I•Ï”j
	float m_circle_angle = 10.0f;

	float m_elapsed_time = 0.0f;

	float m_time_count= 0.0f;

	float m_anim_speed = 0.0f;

	void SetAnim();

	void AnimMove(const float delta_time);

	void AnimDraw(const float delta_time);

	void MoveRound(const float delta_time);

	void MoveStraight(const float delta_time);

public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

};