#include "../[002]Mediator/Mediator.h"
#include "CameraPhase.h"



void CameraPhase::Update(float delta_time)
{
	PhaseChange();

	tnl_sequence_.update(delta_time);
}

void CameraPhase::PhaseChange()
{
	// ターゲットが特定のレーンに入ったら遷移
	if (m_mediator->GetEventLane().s_id == 6
		|| m_mediator->GetEventLane().s_id == 9)
	{
		m_mediator->SetCinemaCameraIsActive(true);
		
		m_now_camera = eCameraPhase::e_cinema;
	}

	// シネマカメラが終わったら遷移
	if (!m_mediator->GetCinemaCameraIsActive())
	{
		m_now_camera = eCameraPhase::e_game;
	}
}

bool CameraPhase::SeqCinema(const float delta_time)
{
	if (m_now_camera == eCameraPhase::e_game)
	{
		tnl_sequence_.change(&CameraPhase::SeqGame);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}

bool CameraPhase::SeqGame(const float delta_time)
{
	if (m_now_camera == eCameraPhase::e_cinema)
	{
		tnl_sequence_.change(&CameraPhase::SeqCinema);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}
