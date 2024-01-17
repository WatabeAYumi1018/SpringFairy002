#include "../dxlib_ext/dxlib_ext.h"
#include "StagePhase.h"
#include "../[002]Mediator/Mediator.h"


void StagePhase::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

// �X�g�[���[���
bool StagePhase::SeqFly(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_stage_phase = eStagePhase::e_fly;
	}

	// �G���^�[�Ő؂�ւ�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		tnl_sequence_.change(&StagePhase::SeqGround);
	}

	// �Đ����I������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		DrawStringEx(0,0,1,"fly");
	});

	TNL_SEQ_CO_END;
}

// �v���C���
bool StagePhase::SeqGround(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_stage_phase = eStagePhase::e_ground;
	}

	// �G���^�[�Ő؂�ւ�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		tnl_sequence_.change(&StagePhase::SeqFly);
	}

	// �����܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		DrawStringEx(0, 0, 1, "ground");
	});

	TNL_SEQ_CO_END;
}