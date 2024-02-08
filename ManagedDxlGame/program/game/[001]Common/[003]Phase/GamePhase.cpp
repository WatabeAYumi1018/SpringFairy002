#include "../dxlib_ext/dxlib_ext.h"
#include "GamePhase.h"


void CameraPhase::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

bool CameraPhase::SeqGame(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_state = eCameraState::e_game;
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}

bool CameraPhase::SeqCinema(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_now_state = eCameraState::e_cinema;
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;

}