#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"

///////////////////////////////////////////////////////////////////////////
//
// �X�e�[�W�̃G���A�Ǘ����s���N���X
//
///////////////////////////////////////////////////////////////////////////

class Mediator;

class StagePhase
{

public:

	enum class eStagePhase
	{
		e_flower,
		e_wood,
		e_fancy,
		e_end
	};

private:

	eStagePhase m_now_stage = eStagePhase::e_flower;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(StagePhase, &StagePhase::SeqFlower);

	std::shared_ptr<Mediator> m_mediator = nullptr;

	void PhaseChange();

	// ���ԃG���A
	bool SeqFlower(const float delta_time);
	// �X�уG���A
	bool SeqWood(const float delta_time);
	// �Ԃ̐��E
	bool SeqFancy(const float delta_time);

public:

	void Update(float delta_time);

	const eStagePhase& GetNowStagePhase() const { return m_now_stage; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};