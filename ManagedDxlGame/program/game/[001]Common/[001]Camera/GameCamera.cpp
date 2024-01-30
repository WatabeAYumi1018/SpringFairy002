#include "../../../wta_library/wta_Convert.h"
#include "GameCamera.h"
#include "../[002]Mediator/Mediator.h"
#include "../[000]Object/[001]Character/[000]Player/Player.h"


GameCamera::GameCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT){}

void GameCamera::update(const float delta_time)
{
	//if (!m_mediator->GetIsCinemaCameraActive())
	//{
	//
	//// カメラの姿勢を更新
	//target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rot);
	//// カメラのアッパーベクトルを更新
	//up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_rot);

	dxe::Camera::update(delta_time);

	tnl_sequence_.update(delta_time);
//	IsInFlustum();

	//
	//// 座標デバッグ用
	//DrawStringEx(0, 100, -1, "CameraPos_x:%f", pos_.x);
	//DrawStringEx(0, 120, -1, "CameraPos_y:%f", pos_.y);
	//DrawStringEx(0, 140, -1, "CameraPos_z:%f", pos_.z);

	//}
}

void GameCamera::IsInFlustum()
{
	int max = static_cast<int>(eFlustum::Max);

	for (int i = 0; i < max; ++i)
	{
		tnl::Vector3 player_pos = m_mediator->GetPlayerPos();
				
		float size = m_mediator->GetPlayerCollisionSize();

		tnl::Vector3 v 
			= getFlustumNormal(static_cast<dxe::Camera::eFlustum>(i));

		
		tnl::Vector3 np 
			= tnl::GetNearestPointPlane(player_pos, v, pos_);
		
		float length = (np - player_pos).length();

		if (length < size)
		{
			tnl::Vector3 pos = np + (v * size );
			
			m_mediator->SetPlayerPos(pos);
		}
	}
}

tnl::Vector3 GameCamera::Lerp(const tnl::Vector3& start
						  , const tnl::Vector3& end, float t)
{
	return start + (end - start) * t;
}

void GameCamera::ConditionType()
{
	switch (m_mediator->GetTargetCameraInfo().s_type)
	{
		case eCameraType::e_right_side:
		{
			tnl_sequence_.change(&GameCamera::SeqRightSide);
		
			break;
		}
		case eCameraType::e_left_side:
		{
			tnl_sequence_.change(&GameCamera::SeqLeftSide);

			break;
		}
		case eCameraType::e_right_side_back:
		{
			m_mediator->SetPlayerLookSideRight(true);

			tnl_sequence_.change(&GameCamera::SeqRightSide);

			break;
		}
		case eCameraType::e_left_side_back:
		{
			m_mediator->SetPlayerLookSideLeft(true);

			tnl_sequence_.change(&GameCamera::SeqLeftSide);

			break;
		}
		case eCameraType::e_bottom:
		{
			tnl_sequence_.change(&GameCamera::SeqBottom);
		
			break;
		}
		case eCameraType::e_rotate:
		{
			tnl_sequence_.change(&GameCamera::SeqRotate);
		
			break;
		}
		case eCameraType::e_front:
		{
			tnl_sequence_.change(&GameCamera::SeqFront);
		
			break;
		}
	}
}

void GameCamera::Fixed()
{
	target_ = m_mediator->GetCameraTargetPlayerPos();

	pos_.x = target_.x;
	pos_.y = target_.y;
	pos_.z = target_.z + m_offset.z;
}

void GameCamera::Side(float offset)
{
	target_ = m_mediator->GetCameraTargetPlayerPos();

	pos_.x = target_.x + offset;
	pos_.y = target_.y;
	pos_.z = target_.z;
}

void GameCamera::ToSide(const float delta_time, float offset)
{
	// 目的の位置を計算
	tnl::Vector3 target_pos
		= tnl::Vector3(target_.x + offset, target_.y, target_.z);

	// 補間を使用してカメラ位置を更新
	pos_ = Lerp(pos_, target_pos, delta_time * 5);
}

void GameCamera::ToFix(const float delta_time)
{
	// 目的の位置を計算
	tnl::Vector3 target_pos
		= m_mediator->GetCameraTargetPlayerPos() + m_offset;

	// 補間を使用してカメラ位置を更新
	pos_ = Lerp(pos_, target_pos, delta_time * 2);
}

void GameCamera::Front()
{
	target_ = m_mediator->GetCameraTargetPlayerPos();

	pos_.x = target_.x;
	pos_.y = target_.y;
	pos_.z = target_.z - m_offset.z * 2;
}

void GameCamera::rotate(const float delta_time)
{
	// 軌道半径
	float orbit_radius = 300.0f;
	// 軌道高さ
	float orbit_height = 400.0f;

	target_ = m_mediator->GetPlayerPos();

	// 回転角度の更新
	m_rot_angle += delta_time;

	// カメラ位置の計算（プレイヤーの周りを円軌道で回転）
	pos_.x = target_.x + cos(m_rot_angle) * orbit_radius;
	pos_.y = target_.y + 400;
	pos_.z = target_.z + sin(m_rot_angle) * orbit_radius;
}



bool GameCamera::SeqFixed(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = true;

		m_mediator->SetPlayerLookSideRight(false);

		m_mediator->SetPlayerLookSideLeft(false);

		tnl::Vector3 pos = m_mediator->GetCameraTargetPlayerPos();

		m_mediator->SetPlayerPos(pos);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		m_is_fixed = false;

		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	ConditionType();

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Fixed();
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqRightSide(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = false;
	}

	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqRightSideToFix);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	// サイドへカメラを移動
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		ToSide(delta_time,400);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Side(400);

		//if (m_mediator->GetPlayerLookSide())
		//{
		//	m_mediator->SetIsGimmickGroundActive(true);
		//}
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqRightSideToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		Side(400);
	});

	// カメラを元の位置に戻す
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);
	
	TNL_SEQ_CO_END;
}

bool GameCamera::SeqLeftSide(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = false;
	}

	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqLeftSideToFix);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	// サイドへカメラを移動
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		ToSide(delta_time, -400);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Side(-400);

		//if (m_mediator->GetPlayerLookSide())
		//{
		//	m_mediator->SetIsGimmickGroundActive(true);
		//}
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqLeftSideToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
	{
		Side(-400);
	});

	// カメラを元の位置に戻す
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqFront(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = false;
	}

	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqFrontToFix);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	// 正面へカメラを移動
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.5f, delta_time, [&]()
	{
		// 目的の位置を計算
		tnl::Vector3 target_pos
			= tnl::Vector3(target_.x, target_.y, target_.z - m_offset.z);
		
		// 補間を使用してカメラ位置を更新
		pos_ = Lerp(pos_, target_pos, delta_time * 3);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Front();
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqFrontToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		Front();
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqRotate(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_fixed = false;
	}

	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqRotateToFix);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		rotate(delta_time);
	});

	TNL_SEQ_CO_END;
}

// プレイヤー周りの回転からfixへ移行
bool GameCamera::SeqRotateToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		rotate(delta_time);
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(0.6f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

	m_rot_angle = 0;

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}


//-----------//

void GameCamera::Bottom()
{
	target_ = m_mediator->GetCameraTargetPlayerPos();

	pos_.y = target_.y + 500;
	pos_.z = target_.z;

	//up_ = tnl::Vector3(0, 0, 1);
}

bool GameCamera::SeqBottom(const float delta_time)
{
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqBottomToFix);
	}

	// 上へカメラを移動
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		// 目的の位置を計算
		tnl::Vector3 target_pos
			= tnl::Vector3(target_.x, target_.y + 500, target_.z);

		// 補間を使用してカメラ位置を更新
		pos_ = Lerp(pos_, target_pos, delta_time * 5);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Bottom();
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqBottomToFix(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]()
	{
		Bottom();
	});

	TNL_SEQ_CO_TIM_YIELD_RETURN(0.4f, delta_time, [&]()
	{
		ToFix(delta_time);
	});

	tnl_sequence_.change(&GameCamera::SeqFixed);

	TNL_SEQ_CO_END;
}


// -----デバッグ用----- //

void GameCamera::Control(const float delta_time)
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

tnl::Vector3 GameCamera::RotateAroundPlayer(const tnl::Vector3& point
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

bool GameCamera::SeqFollow(const float delta_time)
{
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
	{
		tnl_sequence_.change(&GameCamera::SeqControl);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		target_ = m_mediator->GetPlayerPos();

		pos_ = target_ + m_offset;
	});

	TNL_SEQ_CO_END;
}

bool GameCamera::SeqControl(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		target_ = m_mediator->GetPlayerPos();
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
	{
		tnl_sequence_.change(&GameCamera::SeqFixed);
	}
	
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Control(delta_time);

		if(target_.y < 100)
		{
			target_.y = 100;
		}
	});
	
	TNL_SEQ_CO_END;
}

//bool GameCamera::SeqBottom(const float delta_time)
//{
//	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
//	{
//		up_ = tnl::Vector3(0, 1, 0);
//
//		tnl_sequence_.change(&GameCamera::SeqFixed);
//	}
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		target_ = m_mediator->GetPlayerPos();
//
//		pos_.y = target_.y - 500;
//		pos_.z = target_.z;
//
//		up_ = tnl::Vector3(0, 0, 1);
//	});
//
//	TNL_SEQ_CO_END;
//}

//bool GameCamera::SeqCinematic(const float delta_time)
//{
//	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
//	{
//		tnl_sequence_.change(&GameCamera::SeqFixed);
//	}
//
//	//TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	//{
//	//	MoveRotation(delta_time);
//	//});
//
//	TNL_SEQ_CO_END;
//
//}