#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"

class Mediator;


// �t�F�[�Y�Ǘ��N���X
// �Q�[���̐i�s�󋵂��Ǘ�����

class StagePhase
{

public:

	enum class eStagePhase
	{
		e_flower,
		e_wood,
		e_fancy
	};

private:

	eStagePhase m_now_stage_phase = eStagePhase::e_flower;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(StagePhase, &StagePhase::SeqFlower);

	// ���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	// ���ԃG���A
	bool SeqFlower(const float delta_time);
	// �X�уG���A
	bool SeqWood(const float delta_time);
	// �Ԃ̐��E
	bool SeqFancy(const float delta_time);

public:

	void Update(float delta_time);

	eStagePhase GetNowStagePhase() { return m_now_stage_phase; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};