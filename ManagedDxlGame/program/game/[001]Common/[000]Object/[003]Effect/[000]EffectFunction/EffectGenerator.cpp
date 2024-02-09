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
	// シネマカメラの時
	if (m_camera_phase == CameraPhase::eCameraPhase::e_cinema)
	{
		// シネマカメラの時
		if (m_stage_phase == StagePhase::eStagePhase::e_flower)
		{
			// お花エリアのエフェクト
		}
		else if (m_stage_phase == StagePhase::eStagePhase::e_wood)
		{
			// 森林エリアのエフェクト
		}
		else if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
		{
			// 花の世界のエフェクト
		}
	}
	else
	{

	}
}