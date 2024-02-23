#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../../../[000]Stage/[001]Lane/Lane.h"
#include "../../Character.h"

class Mediator;

/////////////////////////////////////////////////////////////////////////////////////////
// 
// �v���C���[�̈ړ������̃N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class PlayerMove
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	PlayerMove() {}
	~PlayerMove() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �㉺�ɂ��ړ����x
	float m_move_high_and_low_speed = 10.0f;
	// �X����p�x
	float m_rot_angle = 0.05f;
	// �T�C�h���̌X���
	float m_side_rot_rate = 10.0f;

	// ���Ԃ�̌o�ߎ���
	float m_salto_elapsed_time = 0;

	// ���[���̉�]���x
	float m_rolling_rotation = 10;
	// ���̎��̉�]���x
	float m_figure_eight_rotation = 10;

	// ���f���̍��W�iPlayer�N���X��m_pos�Ɠ����j
	tnl::Vector3 m_pos;

	// �^�[�Q�b�g�v�Z�ňꎞ�I�Ɏg�p
	tnl::Quaternion m_target_rot;
	//���f���̉�]�iPlayer�N���X��m_rot�Ɠ����j
	tnl::Quaternion m_rot;

	// �v���C���[�̕���
	Character::eDirection m_direction 
		= Character::eDirection::e_none;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(PlayerMove, &PlayerMove::SeqNormal);

	// A*�̃|�C���^
	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �ړ��ɂ�郂�f���̍s��ϊ�
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void MoveMatrix(const float delta_time);

	// ����ɂ�郂�f����]��`
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void ControlMoveMatrix(const float delta_time);

	// ���Ԃ�A�N�V�����ł̃��f����]��`
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void SaltoActionMatrix(const float delta_time);

	// �ʏ�̈ړ�����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqNormal(const float delta_time);
	
	// ��~����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqStop(const float delta_time);
	
	// �㏸����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	// ������̊g���Ŏg�p����\�������邽�ߎc���Ă��܂��B�����͊����ς݁B
	bool SeqUpMove(const float delta_time);
	
	// ���~����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqDownMove(const float delta_time);

	// ���Ԃ�A�N�V����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqSaltoAction(const float delta_time);

public:

	// �{�^�������`�ƃt���O�֐�
	bool PushButton();

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// A*�̃|�C���^��ݒ�
	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>>& astar)
	{
		m_astar = astar;
	}

	// ���f�B�G�[�^�̃|�C���^��ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};