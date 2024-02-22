#include "../[002]Mediator/Mediator.h"
#include "../[003]Phase/StagePhase.h"
#include "CinemaCamera.h"



CinemaCamera::CinemaCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT)
{
	// 使用する画面の作成
	m_screen_hdl = MakeScreen(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, TRUE);

	// カメラに映る範囲の最近距離
	// 10 : ドアップのため限りなく0に近い数値で
	near_ = 10;
}

void CinemaCamera::SetCanvas()
{
	// 画面に描画
	SetDrawScreen(m_screen_hdl);
	ClearDrawScreen();
}

void CinemaCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	tnl_sequence_.update(delta_time);
}

void CinemaCamera::Render()
{
	// 描画対象を表画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH
					, DXE_WINDOW_HEIGHT, m_screen_hdl, FALSE);
}

tnl::Vector3 CinemaCamera::Lerp(const tnl::Vector3& start
								, const tnl::Vector3& end, float t)
{
	return start + (end - start) * t;
}

void CinemaCamera::Fixed(const tnl::Vector3& offset)
{
	if (m_mediator->GetButterflyIsCinemaActive())
	{
		target_ = m_mediator->GetButterflyPos();
	}
	else
	{
		target_ = m_mediator->GetCinemaCameraTargetPos();
	}

	pos_.x = target_.x + offset.x;
	pos_.y = target_.y + offset.y;
	pos_.z = target_.z + offset.z;
}

void CinemaCamera::ToSlide(const float delta_time,const tnl::Vector3& offset,float speed)
{
	// 目的の位置を計算
	tnl::Vector3 target_pos
		= tnl::Vector3(target_.x + offset.x, target_.y + offset.y, target_.z + offset.z);

	// 補間を使用してカメラ位置を更新
	pos_ = Lerp(pos_, target_pos, delta_time * speed);
}

bool CinemaCamera::SeqTrigger(const float delta_time)
{
	StagePhase::eStagePhase stage_phase
			= m_mediator->GetNowStagePhaseState();

	if (stage_phase == StagePhase::eStagePhase::e_flower)
	{
		tnl_sequence_.change(&CinemaCamera::SeqFirst);
	}
	if (stage_phase == StagePhase::eStagePhase::e_wood)
	{
		tnl_sequence_.change(&CinemaCamera::SeqSecond);
	}
	if (stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		tnl_sequence_.change(&CinemaCamera::SeqThird);
	}

	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqFirst(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		Fixed({0,200,-500});
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		ToSlide(delta_time, {0,80,-100},10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2.4f, delta_time, [&]()
	{
		Fixed({ 0,80,-100 });
	});

	m_is_active = false;

	tnl_sequence_.change(&CinemaCamera::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqSecond(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		Fixed({ 0,0,-100 });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		ToSlide(delta_time, { 0,0,-2000 },2);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(9, delta_time, [&]()
	{
		Fixed({ 0,0,-2000 });
	});

	m_is_active = false;

	tnl_sequence_.change(&CinemaCamera::SeqTrigger);

	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqThird(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		Fixed({ 0,0,-700 });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		ToSlide(delta_time, { 700,0,-300 }, 10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		ToSlide(delta_time, { -700,0,-500 }, 10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		m_mediator->SetButterflyIsCinemaActive(true);

		target_ = m_mediator->GetButterflyPos();

		ToSlide(delta_time, { 0,100,-200 }, 10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(8, delta_time, [&]()
	{
		Fixed({ 0,100,-300 });
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
	{
		target_ = m_mediator->GetCinemaCameraTargetPos();

		ToSlide(delta_time, { 0,0,-300 }, 10);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(4.5f, delta_time, [&]()
	{
		Fixed({ 0,0,-300 });
	});

	m_is_active = false;

	tnl_sequence_.change(&CinemaCamera::SeqTrigger);

	TNL_SEQ_CO_END;
}