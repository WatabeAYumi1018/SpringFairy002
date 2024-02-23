#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../Character.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �p�[�g�i�[�̈ړ������Ɋւ���N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class PartnerMove
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	PartnerMove() {}
	~PartnerMove() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �o�ߎ���
	float m_elapsed_time = 0;
	// �ړ�����
	float m_move_time = 0.0f;
	// �O��̈ړ�����
	float m_last_move_time = 0.0f;

	// �������g��
	float m_orbit_frequency = 0.2f; 

	// �����o���t���O
	bool m_is_pushed = false;

	// ���ݍ��W
	tnl::Vector3 m_pos;
	// �ړ����W�I�t�Z�b�g
	tnl::Vector3 m_offset;

	// ���݉�]
	tnl::Quaternion m_rot;
	// �ڕW��]
	tnl::Quaternion m_target_rot;

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//

	
	//-----------------------------------�����o�֐�------------------------------------//

	// ���W�̃����_���X�V�����i�w�ǂ̓v���C���[���l�̎����ړ��{���ʂ̓Ǝ��̈ړ������j
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void UpdateRandomPos(const float delta_time);

	// �v���C���[�Ƃ̏Փ˂ɂ��␳����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void CorrectPos(const float delta_time);

public:

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ���W�␳�t���O�̐ݒ�
	void SetIsPushed(bool is_pushed) { m_is_pushed = is_pushed ; }

	// ���f�B�G�[�^�̃|�C���^�̐ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};