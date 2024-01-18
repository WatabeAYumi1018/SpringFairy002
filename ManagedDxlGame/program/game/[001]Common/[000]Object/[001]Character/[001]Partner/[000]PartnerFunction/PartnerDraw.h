#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../[000]GameEngine/[000]Engine/Engine.h"
#include "../Partner.h"

class Mediator;


class PartnerDraw
{

public:

	PartnerDraw();

	~PartnerDraw();

private:

	// ���f��
	int m_model_hdl = 0;
	// move�{�[��
	int m_anim_bone_move_hdl = 0;
	// idle�{�[��
	int m_anim_bone_idle_hdl = 0;

	// �e�N�X�`��
	int m_texture_green_hdl = 0;
	int m_texture_black_hdl = 0;
	int m_texture_pink_hdl = 0;

	// �A�j���[�V�����C���f�b�N�X�ԍ�
	int m_anim_move_index = 0;
	int m_anim_idle_index = 0;

	// �o�ߎ���
	float m_elapsed_time_move = 0;
	float m_elapsed_time_idle = 0;

	// ���[�v�Đ�
	float m_time_count_move = 0;
	float m_time_count_idle = 0;

	// �A�j���[�V�����̑��x
	float m_anim_speed = 10;
	// walk�A�j���[�V�����̃I�t�Z�b�g
	float m_anim_move_offset = 80;

	// �G�l�~�[�̎�ށi�e�N�X�`���j
	Partner::ePartnerType m_enemy_type = Partner::ePartnerType::green;

	eDirection m_direction = eDirection::none;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(PartnerDraw, &PartnerDraw::SeqIdle);

	// �v���C���[���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ���f���̃��[�h�Ə�����
	void LoadAndInitModels();
	// �e�N�X�`���̐ݒ�
	void SetTexture(int texture_hdl);
	// ���C�g�̐ݒ�
	void SetLight();

	// �P���Đ��̎��Ԑݒ������
	void AnimMove(float delta_time);
	// ���[�v�Đ��̎��Ԑݒ������@
	void AnimIdle(float delta_time);

	// �ړ����
	bool SeqMove(const float delta_time);
	// �A�C�h�����
	bool SeqIdle(const float delta_time);


public:

	// �A�j���[�V�����̍X�V����
	void Update(float delta_time);
	// PlayerHuman�N���X��Draw�֐��ɂĖ��t���[���Ăяo��
	void Draw();


	int GetModelHdl() const
	{
		return m_model_hdl;
	}

	void SetMediator(std::shared_ptr<Mediator> mediator)
	{
		m_mediator = mediator;
	}
};