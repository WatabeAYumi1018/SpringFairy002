#include "../[002]Mediator/Mediator.h"
#include "OpCamera.h"


OpCamera::OpCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT){}

void OpCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	tnl_sequence_.update(delta_time);
}

tnl::Vector3 OpCamera::Lerp(const tnl::Vector3& start
							, const tnl::Vector3& end, float t)
{
	return start + (end - start) * t;
}

void OpCamera::Fixed(tnl::Vector3& offset)
{
	target_ = m_mediator->GetButterflyPos();

	pos_.x = target_.x + offset.x;
	pos_.y = target_.y + offset.y;
	pos_.z = target_.z + offset.z;
}

void OpCamera::ToOffset(const float delta_time, tnl::Vector3& offset)
{
	// 目的の位置を計算
	tnl::Vector3 target_pos = m_mediator->GetButterflyPos() + offset;

	// 補間を使用してカメラ位置を更新
	pos_ = Lerp(pos_, target_pos, m_slide_speed);
}

bool OpCamera::SeqNormal(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_mediator->SetButterflyIsOpActive(true);

		m_mediator->SetSkyIsOp(true);
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
	{
		Fixed(m_offset);
	});

	tnl_sequence_.change(&OpCamera::SeqNormalToUp);

	TNL_SEQ_CO_END;
}

bool OpCamera::SeqNormalToUp(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.2f, delta_time, [&]()
	{
		ToOffset(delta_time, m_title_offset);
	});

	tnl_sequence_.change(&OpCamera::SeqUp);

	TNL_SEQ_CO_END;
}

bool OpCamera::SeqUp(const float delta_time)
{
	// タイトルロゴの表示終了フラグ取得
	if (m_mediator->GetTitleIsDisappear())
	{
		tnl_sequence_.change(&OpCamera::SeqUpToBack);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
	{
		m_mediator->SetTitleIsDraw(true);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed(m_title_offset);
	});

	TNL_SEQ_CO_END;
}

bool OpCamera::SeqUpToBack(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_mediator->SetTitleIsDraw(false);

		m_offset.y = 0;
	}

	TNL_SEQ_CO_TIM_YIELD_RETURN(0.2f, delta_time, [&]()
	{
		ToOffset(delta_time, m_gate_offset);
	});

	tnl_sequence_.change(&OpCamera::SeqBack);

	TNL_SEQ_CO_END;
}

bool OpCamera::SeqBack(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_mediator->SetButterflyIsOpActive(false);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed(m_gate_offset);
	});

	TNL_SEQ_CO_END;
}