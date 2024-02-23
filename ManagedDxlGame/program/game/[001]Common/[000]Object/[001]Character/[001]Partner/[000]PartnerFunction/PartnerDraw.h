#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../Character.h"
#include "../Partner.h"


class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �p�[�g�i�[�̕`�揈���Ɋւ���N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class PartnerDraw
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	PartnerDraw() {}
	~PartnerDraw();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ������move�͎g�p���Ă��܂��񂪁A����̊g�������z���Ďc���Ă��܂�

	// ���f��
	int m_model_hdl = 0;
	// move�{�[��
	int m_anim_bone_move_hdl = 0;
	// idle�{�[��
	int m_anim_bone_idle_hdl = 0;

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

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(PartnerDraw, &PartnerDraw::SeqIdle);

	// �v���C���[���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �P���Đ��̎��Ԑݒ������
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void AnimMove(const float delta_time);

	// ���[�v�Đ��̎��Ԑݒ������@
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void AnimIdle(const float delta_time);

	// �ړ����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqMove(const float delta_time);

	// �A�C�h�����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqIdle(const float delta_time);

public:

	void Initialize();
	
	void Update(const float delta_time);
	
	void Draw();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ���f�B�G�[�^�̃|�C���^�ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};