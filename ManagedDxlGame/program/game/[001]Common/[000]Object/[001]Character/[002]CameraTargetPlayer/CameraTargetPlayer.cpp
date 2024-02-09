#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "../../../[003]Phase/CameraPhase.h"
#include "CameraTargetPlayer.h"


void CameraTargetPlayer::Initialize()
{
	m_collision_size = 50;

	StartPos();
}

void CameraTargetPlayer::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);

}

void CameraTargetPlayer::MoveMatrix(const float delta_time)
{
	// 自動経路による移動の更新
	m_mediator->MoveAstarTargetPos(delta_time, m_game_pos);

	// カメラレーンの取得
	m_camera_info = CurrentCameraType();

	m_event = CurrentEventLane();
}

bool CameraTargetPlayer::SeqNormal(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_speed_up = false;
		m_is_move_up = false;
		m_is_move_down = false;
	}

	if (m_event.s_id == 5)
	{
		tnl_sequence_.change(&CameraTargetPlayer::SeqStop);
	}

	//if (m_event.s_id == 7)
	//{
	//	tnl_sequence_.change(&CameraTargetPlayer::SeqDownMove);
	//}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool CameraTargetPlayer::SeqStop(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
	{
		// 数秒間座標更新を停止
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]()
	{
		m_is_speed_up = true;

		MoveMatrix(delta_time);
	});

	tnl_sequence_.change(&CameraTargetPlayer::SeqNormal);

	TNL_SEQ_CO_END;
}

bool CameraTargetPlayer::SeqUpMove(const float delta_time)
{
	if(m_game_pos.y > 500)
	{
		tnl_sequence_.change(&CameraTargetPlayer::SeqNormal);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
	{
		// 1フレームでフラグ実行
		m_is_speed_up = true;

		m_is_move_up = true;
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
		// y座標を上昇
		m_game_pos.y += delta_time * 50;
	});

	TNL_SEQ_CO_END;
}

bool CameraTargetPlayer::SeqDownMove(const float delta_time)
{
	if( m_game_pos.y == 0 )
	{
		tnl_sequence_.change(&CameraTargetPlayer::SeqNormal);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
	{
		// 1フレームでフラグ実行
		//m_is_speed_up = true;

		m_is_move_down = true;
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveMatrix(delta_time);
		// y座標を下降
		m_game_pos.y -= delta_time * 100;

	});

	TNL_SEQ_CO_END;
}