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

	// �~�̑��x
	float m_speed = 10.0f;
	// �~�̔��a
	float m_radius = 20.0f;
	// �~�^����񕪂̑�����
	float m_total_time = 5.0f;
	// �~�^���̌o�ߎ���
	float m_elapsed_time_circle = 0.0f;

	// move�A�j���[�V�����o�ߎ���
	float m_elapsed_time = 0.0f;
	// move�A�j���[�V�����̃��[�v����
	float m_time_count= 0.0f;
	// move�A�j���[�V�����̑��x
	float m_anim_speed = 100.0f;
	// move�A�j���[�V�����̃C���f�b�N�X
	int m_anim_index = 0;

	// �~�^���t���O
	bool m_is_circle = false;
	// �ؕ��t���O
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