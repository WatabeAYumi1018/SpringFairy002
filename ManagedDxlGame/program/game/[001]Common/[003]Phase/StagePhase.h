#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// �X�e�[�W�̃G���A�Ǘ����s���N���X
//
///////////////////////////////////////////////////////////////////////////


class StagePhase
{

public:

	//-----------------------------------enum class------------------------------------//

	// �X�e�[�W�̃G���A�t�F�[�Y
	enum class eStagePhase
	{
		e_flower,
		e_wood,
		e_fancy,
		e_end
	};
	
	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	StagePhase() {}
	~StagePhase() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���݂̃X�e�[�W�t�F�[�Y
	eStagePhase m_now_stage = eStagePhase::e_flower;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(StagePhase, &StagePhase::SeqFlower);

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//

	
	//-----------------------------------�����o�֐�-----------------------------------//

	// �t�F�[�Y�J��
	void PhaseChange();

	// ���ԃG���A	
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFlower(const float delta_time);

	// �X�уG���A
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqWood(const float delta_time);

	// �Ԃ̐��E
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFancy(const float delta_time);

public:

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ���݂̃X�e�[�W�t�F�[�Y���擾
	const eStagePhase& GetNowStagePhase() const { return m_now_stage; }

	// ���f�B�G�[�^�̃|�C���^�ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};