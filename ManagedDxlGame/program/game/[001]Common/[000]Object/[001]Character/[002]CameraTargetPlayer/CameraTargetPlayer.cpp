#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "../../../[003]Phase/CameraPhase.h"
#include "CameraTargetPlayer.h"


void GameCameraTarget::Initialize()
{
	m_collision_size = 50;

	StartPos();
}

void GameCameraTarget::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);

	if (m_event.s_id == 3)
	{
		m_mediator->SetChangeGraphIsFlower(false);
		m_mediator->SetChildGraphIsFlower(false);
	}
	else if (m_event.s_id == 9)
	{
		m_mediator->SetChangeGraphIsWood(false);
		m_mediator->SetChildGraphIsWood(false);
	}
}

void GameCameraTarget::MoveMatrix(const float delta_time)
{
	// 自動経路による移動の更新
	m_mediator->MoveAstarTargetPos(delta_time, m_pos);

	// カメラレーンの取得
	m_camera_info = CurrentCameraType();

	m_event = CurrentEventLane();
}

bool GameCameraTarget::SeqNormal(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_speed_up = false;
	}

	if (m_event.s_id == 6)
	{
		tnl_sequence_.change(&GameCameraTarget::SeqStop);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool GameCameraTarget::SeqStop(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
		// 5秒間座標更新を停止
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]()
	{
		// 10秒間座標更新速度を上げる
		m_is_speed_up = true;

		MoveMatrix(delta_time);
	});

	tnl_sequence_.change(&GameCameraTarget::SeqNormal);

	TNL_SEQ_CO_END;
}