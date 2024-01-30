#include "../../[002]Mediator/Mediator.h"
#include "CinemaCamera.h"



CinemaCamera::CinemaCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT)
{
	// カメラに映る範囲の最近距離(ドアップのため限りなく0に近い数値で)
	near_ = 1;
}

void CinemaCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	target_ = m_mediator->GetPlayerPos();

	pos_.x = target_.x;
	pos_.y = target_.y;
	pos_.z = target_.z - m_offset.z * 2;

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT))
	{
		m_move_mouse = true;
	}

	if(m_move_mouse)
	{
		Control(delta_time);
	}

	//// 座標デバッグ用
	//DrawStringEx(1000, 100, -1, "CameraPos_x:%f", pos_.x);
	//DrawStringEx(1000, 120, -1, "CameraPos_y:%f", pos_.y);
	//DrawStringEx(1000, 140, -1, "CameraPos_z:%f", pos_.z);
}


//bool CinemaCamera::SeqTrigger(const float delta_time)
//{
//
//}
//
//bool CinemaCamera::SeqUp(const float delta_time)
//{
//
//}
//
//bool CinemaCamera::SeqSide(const float delta_time)
//{
//
//}
//
//bool CinemaCamera::SeqBack(const float delta_time)
//{
//
//}




// -----デバッグ用----- //

void CinemaCamera::Control(const float delta_time)
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

tnl::Vector3 CinemaCamera::RotateAroundPlayer(const tnl::Vector3& point
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

