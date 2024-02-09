#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../[003]Phase/CameraPhase.h"
#include "../../../[003]Phase/StagePhase.h"
#include "EffectLoad.h"


class Mediator;

class EffectGenerator 
{

public:

	EffectGenerator();

	~EffectGenerator();

private:

	CameraPhase::eCameraPhase m_camera_phase 
			= CameraPhase::eCameraPhase::e_cinema;
	
	StagePhase::eStagePhase m_stage_phase 
			= StagePhase::eStagePhase::e_flower;

	std::vector<Effect::sEffectType> m_effect_type;


	// エフェクトの条件分け
	void EffectTrans();
};
