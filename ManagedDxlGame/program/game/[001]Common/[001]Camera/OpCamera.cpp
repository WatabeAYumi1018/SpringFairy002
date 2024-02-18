#include "../[002]Mediator/Mediator.h"
#include "OpCamera.h"


OpCamera::OpCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT){}

void OpCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	tnl_sequence_.update(delta_time);

	// スペース押したら
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))
	{
		m_is_mouse = true;
	}

	if (m_is_mouse)
	{
		Control(delta_time);
	}
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
	pos_ = Lerp(pos_, target_pos, 0.3f);
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
		tnl::Vector3 offset = tnl::Vector3(0, 300, -500);

		ToOffset(delta_time, offset);
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
		tnl::Vector3 offset = tnl::Vector3(0, 300, -500);

		Fixed(offset);
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
		ToOffset(delta_time, m_new_offset);
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

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		tnl_sequence_.change(&OpCamera::SeqStageIn);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed(m_new_offset);
	});

	TNL_SEQ_CO_END;
}

bool OpCamera::SeqStageIn(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.1f, delta_time, [&]()
	{
		ToOffset(delta_time, m_stage_in_offset);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed(m_stage_in_offset);
	});

	TNL_SEQ_CO_END;
}

void OpCamera::Control(const float delta_time)
{
	// マウスの移動量を取得
	tnl::Vector3 mouse_velocity = tnl::Input::GetMouseVelocity();
	// マウス感度の調整
	float mouse_sensitivity = 0.1f;
	// カメラの回転
	float yaw = mouse_velocity.x * mouse_sensitivity;
	float pitch = mouse_velocity.y * mouse_sensitivity;
	// カメラの横回転（Y軸回転）
	pos_ = RotateAroundPlayer(pos_, target_, tnl::Vector3(0, 1, 0), yaw);
	// カメラの縦回転（X軸回転）
	pos_ = RotateAroundPlayer(pos_, target_, right(), pitch);
	// カメラの前後移動
	float scroll = tnl::Input::GetMouseWheel();
	// ズーム感度
	float zoom_sensitivity = 0.5f;

	pos_ += forward() * scroll * zoom_sensitivity;
	// カメラの向きを更新
	view_ = tnl::Matrix::LookAtLH(pos_, target_, up_);
}

tnl::Vector3 OpCamera::RotateAroundPlayer(const tnl::Vector3& point
	, const tnl::Vector3& pivot
	, const tnl::Vector3& axis
	, float angle)
{
	// 回転
	tnl::Quaternion rotation
		= tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(angle));
	// 回転行列を生成
	tnl::Matrix rotation_matrix = tnl::Matrix::RotationQuaternion(rotation);
	// 点を回転行列で変換
	tnl::Vector3 transformed_point
		= tnl::Vector3::Transform(point - pivot, rotation_matrix);
	// 変換した点にピボットを加算して最終的な位置を得る
	return transformed_point + pivot;
}
