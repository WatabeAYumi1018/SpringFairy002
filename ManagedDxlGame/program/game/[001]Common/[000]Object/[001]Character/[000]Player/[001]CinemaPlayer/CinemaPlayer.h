#pragma once
#include "../../Character.h"


class Mediator;
// update�ɂăC�x���g�������̂ݏ���������悤�ɂ���

class CinemaPlayer : public Character
{

public:

	CinemaPlayer();

	~CinemaPlayer();

private:

	// �~�̑��x
	float m_speed = 15.0f;
	// �~�̔��a
	float m_radius = 10.0f;
	// �~�^����񕪂̑�����
	float m_total_time = 4.0f;
	// �~�^���̌o�ߎ���
	float m_elapsed_time_circle = 0.0f;

	bool m_is_idle = false;
	bool m_is_move = false;
	bool m_is_dance = false;
	
	// �v���C���[�̎��Ȕ���
	DxLib::COLOR_F m_emissive = { 0.5f,0.5f,0.5f,1 };

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CinemaPlayer, &CinemaPlayer::SeqTrigger);

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ���`��Ԋ֐�
	float Lerp(float start, float end, float t);

	// ���ړ�
	void MoveRound(const float delta_time);
	// �����ړ�
	void MoveDown(const float delta_time);
	// �o�b�N�֐����悭�ړ�
	void MoveBackCenter(const float delta_time);


	// �ҋ@
	bool SeqTrigger(const float delta_time);
	// �Љ�
	bool SeqFirst(const float delta_time);
	// �G���A�Q�ւ̈ڍs
	bool SeqSecond(const float delta_time);
	// �G���A�R�ւ̈ڍs
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