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
		flower,
		wood,
		fancy
	};

private:

	eStagePhase m_now_stage_phase = eStagePhase::flower;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(StagePhase, &StagePhase::SeqFlower);


	// ���ԃG���A
	bool SeqFlower(const float delta_time);
	// �X�уG���A
	bool SeqWood(const float delta_time);
	// �Ԃ̐��E
	bool SeqFancy(const float delta_time);

public:

	void Update(float delta_time);

	eStagePhase GetNowStagePhase() { return m_now_stage_phase; }
};