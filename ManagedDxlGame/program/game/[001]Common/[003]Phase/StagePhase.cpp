#include "../dxlib_ext/dxlib_ext.h"
#include "StagePhase.h"
#include "../[002]Mediator/Mediator.h"


void StagePhase::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

// �X�g�[���[���
bool StagePhase::SeqFlower(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_stage_phase = eStagePhase::flower;
	}

	// �J�����̉�]����b���I��������
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		tnl_sequence_.change(&StagePhase::SeqWood);
	}

	// �Đ����I������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		DrawStringEx(0,0,1,"fly");
	});

	TNL_SEQ_CO_END;
}

bool StagePhase::SeqWood(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_stage_phase = eStagePhase::wood;
	}

	// �Ăщ�b���I��������
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		tnl_sequence_.change(&StagePhase::SeqFancy);
	}

	// �����܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		DrawStringEx(0, 0, 1, "wood");
	});

	TNL_SEQ_CO_END;
}

bool StagePhase::SeqFancy(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_stage_phase = eStagePhase::fancy;
	}

	// �Ăщ�b���I��������
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		//�G���f�B���O�t���Oon
	}

	// �����܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		DrawStringEx(0, 0, 1, "fancy");
	});

	TNL_SEQ_CO_END;
}
