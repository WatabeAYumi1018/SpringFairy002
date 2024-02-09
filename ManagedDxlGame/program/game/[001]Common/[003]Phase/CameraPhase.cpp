#include "CameraPhase.h"


void CameraPhase::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
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
