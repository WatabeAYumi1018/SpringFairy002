#include "../../../[002]Mediator/Mediator.h"
#include "EffectGenerator.h"



EffectGenerator::EffectGenerator()
{
	
}

EffectGenerator::~EffectGenerator()
{
}

void EffectGenerator::EffectTrans()
{
	// �V�l�}�J�����̎�
	if (m_camera_phase == CameraPhase::eCameraPhase::e_cinema)
	{
		// �V�l�}�J�����̎�
		if (m_stage_phase == StagePhase::eStagePhase::e_flower)
		{
			// ���ԃG���A�̃G�t�F�N�g
		}
		else if (m_stage_phase == StagePhase::eStagePhase::e_wood)
		{
			// �X�уG���A�̃G�t�F�N�g
		}
		else if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
		{
			// �Ԃ̐��E�̃G�t�F�N�g
		}
	}
	else
	{

	}
}