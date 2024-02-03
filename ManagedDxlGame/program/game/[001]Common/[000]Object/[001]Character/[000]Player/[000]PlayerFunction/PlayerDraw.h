#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../[000]GameEngine/[000]Engine/Engine.h"

class Mediator;

class PlayerDraw
{

public:

	PlayerDraw() {}

	~PlayerDraw() {}

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

	float m_blend_timer = 0;
	// �u���[���U���t���O
	bool m_is_bloom = false;
	// �_���X�U���t���O
	bool m_is_dance = false;
	// �C�x���g�ɂ��dance�̎��������t���O
	bool m_is_event_dance = false;
	// �{�[���̃f�^�b�`�ݒ�t���O(�V�l�}�v���C���[�p)
	bool m_is_touch_idle = false;
	bool m_is_touch_move = false;
	bool m_is_touch_dance = false;

	eDirection m_direction = eDirection::e_none;

	StagePhase::eStagePhase m_stage_phase = StagePhase::eStagePhase::e_flower;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(PlayerDraw, &PlayerDraw::SeqMove);

	// �v���C���[���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	
	// �A�j���[�V�����̃u�����h����
	void AnimBlend(const float delta_time, int current_anim_index, int next_anim_index);

	void AnimAttach(int& anim_index, int anim_bone_hdl, float& time_count);

	// move ���[�v�Đ��̎��Ԑݒ�
	void AnimMove(const float delta_time);
	// bloom �P���Đ��̎��Ԑݒ�
	void AnimBloom(const float delta_time);
	// dance �P���Đ��̎��Ԑݒ�
	void AnimDance(const float delta_time);
	// idle ���[�v�Đ��̎��Ԑݒ�@
	void AnimIdle(const float delta_time);

	// �ړ����
	bool SeqMove(const float delta_time);
	// �u���[�����
	bool SeqBloom(const float delta_time);
	// move�A�j���[�V�����ւ̑J��
	bool SeqBloomToMove(const float delta_time);
	// �_���X���
	bool SeqDance(const float delta_time);
	// dance�A�j���[�V�����ւ̑J��
	bool SeqDanceToMove(const float delta_time);

public:

	void Initialize();
	// �A�j���[�V�����̍X�V����
	void Update(float delta_time);
	// PlayerHuman�N���X��Draw�֐��ɂĖ��t���[���Ăяo��
	void Draw();
	

	//-----�V�l�}�J�����p�֐�-----//

	// �V�l�}�J�����p�̃A�j���[�V����
	void CinemaAnimIdle(const float delta_time);
	void CinemaAnimMove(const float delta_time);
	void CinemaAnimDance(const float delta_time);

	//---------------------------//

	bool GetIsBloom() const { return m_is_bloom; }

	void SetIsEventDance(bool is_event_dance) { m_is_event_dance = is_event_dance; }

	bool GetIsDance() const { return m_is_dance; }

	bool GetIsEventDance() const { return m_is_event_dance; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};