#pragma once
#include "../../../library/tnl_sequence.h"

class Mediator;


// �t�F�[�Y�Ǘ��N���X
// �Q�[���̐i�s�󋵂��Ǘ�����

class StagePhase
{

public:

	enum class eStagePhase
	{
		e_fly,
		e_ground
	};

private:

	eStagePhase m_now_stage_phase = eStagePhase::e_fly;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(StagePhase, &StagePhase::SeqFly);


	// ��
	bool SeqFly(const float delta_time);
	// �n��
	bool SeqGround(const float delta_time);

public:

	void Update(float delta_time);

	eStagePhase GetNowStagePhase() { return m_now_stage_phase; }
};