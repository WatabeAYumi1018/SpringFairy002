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

	// ���f��
	int m_model_hdl = 0;
	// idle�{�[��
	int m_anim_bone_idle_hdl = 0;
	// move�{�[��
	int m_anim_bone_move_hdl = 0;
	// bloom�{�[��
	int m_anim_bone_bloom_hdl = 0;
	// dance�{�[��
	int m_anim_bone_dance_hdl = 0;

	// �e�N�X�`��
	int m_texture_hdl = 0;

	// �A�j���[�V�����C���f�b�N�X�ԍ�
	int m_anim_idle_index = 0;
	int m_anim_move_index = 0;
	int m_anim_bloom_index = 0;
	int m_anim_dance_index = 0;

	// �o�ߎ���
	float m_elapsed_time_idle = 0;
	float m_elapsed_time_move = 0;
	float m_elapsed_time_bloom = 0;
	float m_elapsed_time_dance = 0;

	// ���[�v�Đ�
	float m_time_count_idle = 0;
	float m_time_count_move = 0;
	float m_time_count_bloom = 0;
	float m_time_count_dance = 0;

	// �A�j���[�V�����̑��x
	float m_anim_speed = 10;
	// walk�A�j���[�V�����̃I�t�Z�b�g
	float m_anim_move_offset = 200;
	// bllom�A�j���[�V�����̃I�t�Z�b�g
	float m_anim_bloom_offset = 40;
	// dance�A�j���[�V�����̃I�t�Z�b�g
	float m_anim_dance_offset = 80;

	bool m_is_attack = false;

	eDirection m_direction = eDirection::none;

	StagePhase::eStagePhase m_stage_phase = StagePhase::eStagePhase::e_fly;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(PlayerDraw, &PlayerDraw::SeqIdle);

	// �v���C���[���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	// ���C�g�̐ݒ�
	void SetLight();

	// move ���[�v�Đ��̎��Ԑݒ�
	void AnimMove(float delta_time);
	// idle ���[�v�Đ��̎��Ԑݒ�@
	void AnimIdle(float delta_time);
	// bloom �P���Đ��̎��Ԑݒ�
	void AnimBloom(float delta_time);
	// dance �P���Đ��̎��Ԑݒ�
	void AnimDance(float delta_time);

	// �ړ����
	bool SeqMove(const float delta_time);
	// �A�C�h�����
	bool SeqIdle(const float delta_time);
	// �u���[�����
	bool SeqBloom(const float delta_time);
	// �_���X���
	bool SeqDance(const float delta_time);


public:

	// �A�j���[�V�����̍X�V����
	void Update(float delta_time);
	// PlayerHuman�N���X��Draw�֐��ɂĖ��t���[���Ăяo��
	void Draw();


	int GetModelHdl() const { return m_model_hdl; }

	bool GetIsAttack() const { return m_is_attack; }


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};