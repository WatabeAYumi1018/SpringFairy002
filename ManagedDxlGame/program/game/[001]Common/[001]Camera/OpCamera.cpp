#include "../[002]Mediator/Mediator.h"
#include "OpCamera.h"


OpCamera::OpCamera()
{
	near_ = { 100 };
}

void OpCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	tnl_sequence_.update(delta_time);
}

bool OpCamera::SeqNormal(const float delta_time)
{
	// 蝶が２回転したら
	if (m_mediator->GetButterflyIsCircle())
	{
		tnl_sequence_.change(&OpCamera::SeqNormalToUp);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		target_ = m_mediator->GetButterflyPos();

		pos_.x = target_.x;
		pos_.y = target_.y;
		pos_.z = target_.z - m_offset.z;
	});

	TNL_SEQ_CO_END;
}

bool OpCamera::SeqNormalToUp(const float delta_time)
{
	// ドアップへの滑らかな遷移
	// ターゲットとの距離が110になるまで
	if (pos_.z - target_.z <= 110)
	{


		tnl_sequence_.change(&OpCamera::SeqUp);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		target_ = m_mediator->GetButterflyPos();

		pos_.x = target_.x;
		pos_.y = target_.y;
		pos_.z = target_.z - m_offset.z;
	});

	TNL_SEQ_CO_END;
}

bool OpCamera::SeqUp(const float delta_time)
{
	// タイトルロゴの表示が終わるまで
	if (m_mediator->GetTitleIsDraw())
	{
		tnl_sequence_.change(&OpCamera::SeqUpToBack);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
			// オフセット110のまま固定
		target_ = m_mediator->GetButterflyPos();

		pos_.x = target_.x;
		pos_.y = target_.y;
		pos_.z = target_.z - m_offset.z;
	});

	TNL_SEQ_CO_END;
}

bool OpCamera::SeqUpToBack(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.5f, delta_time, [&]()
	{
		target_ = m_mediator->GetButterflyPos();

		pos_.x = target_.x;
		pos_.y = target_.y;
		pos_.z = target_.z - m_offset.z;
	});

	tnl_sequence_.change(&OpCamera::SeqBack);

	TNL_SEQ_CO_END;
}

bool OpCamera::SeqBack(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(-1, delta_time, [&]()
	{
		target_ = m_mediator->GetButterflyPos();

		pos_.x = target_.x;
		pos_.y = target_.y;
		pos_.z = target_.z - m_offset.z;
	});

	TNL_SEQ_CO_END;
}