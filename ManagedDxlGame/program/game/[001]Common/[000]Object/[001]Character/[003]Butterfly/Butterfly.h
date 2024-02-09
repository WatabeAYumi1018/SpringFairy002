#pragma once
#include "../Character.h"


class Mediator;


class Butterfly : public Character
{
	
public:

	Butterfly();

	~Butterfly();

private:

	float m_speed = 100.0f;
	float m_elapsed_time_circle = 0.0f;
	float m_total_time = 2.0f;
	float m_radius = 100.0f;
	
	// move�A�j���[�V�����o�ߎ���
	float m_elapsed_time = 0.0f;
	// move�A�j���[�V�����̃��[�v����
	float m_time_count= 0.0f;
	// move�A�j���[�V�����̑��x
	float m_anim_speed = 100.0f;
	// move�A�j���[�V�����̃C���f�b�N�X
	int m_anim_index = 0;

	// �I�[�v�j���O�`��t���O
	bool m_is_op_active = false;
	// �~�^���t���O
	bool m_is_circle = false;
	// ���Ńt���O
	bool m_is_clear = false;
	// �V�l�}�`��t���O
	bool m_is_cinema_active = false;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Butterfly, &Butterfly::SeqMove);

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;


	void AnimMove(const float delta_time);

	void MoveRound(const float delta_time);

	void MoveStraightHeight(const float delta_time);

	void MoveStraightWidth(const float delta_time);

	bool SeqMove(const float delta_time);
	bool SeqRound(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetIsOpActive(bool is_op_active) { m_is_op_active = is_op_active; }

	bool GetIsClear() const { return m_is_clear; }

	void SetIsCinemaActive(bool is_cinema_active)
	{
		m_is_cinema_active = is_cinema_active; 
	}

	bool GetIsCinemaActive() const { return m_is_cinema_active; }

	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}
};