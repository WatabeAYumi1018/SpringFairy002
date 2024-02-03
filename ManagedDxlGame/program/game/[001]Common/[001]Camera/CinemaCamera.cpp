#include "../[002]Mediator/Mediator.h"
#include "CinemaCamera.h"



CinemaCamera::CinemaCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT)
{
	// 使用する画面の作成
	CreateScreen();

	// カメラに映る範囲の最近距離(ドアップのため限りなく0に近い数値で)
	near_ = 10;
}

CinemaCamera::CinemaCamera(int screen_w, int screen_h)
	: dxe::Camera(screen_w, screen_h)
{
	// 使用する画面の作成
	CreateScreen();

	// カメラに映る範囲の最近距離(ドアップのため限りなく0に近い数値で)
	near_ = 10;
}

void CinemaCamera::update(const float delta_time)
{
	dxe::Camera::update(delta_time);

	target_ = m_mediator->GetCinemaPlayerPos();

	pos_ = target_ + m_offset;

	// 分割比率に基づいて各スクリーンの幅を計算します。
	m_split_width_left
		= static_cast<int>(DXE_WINDOW_WIDTH * (1.0f - split_rate) / 2);

	m_split_width_right = DXE_WINDOW_WIDTH - m_split_width_left;

	tnl_sequence_.update(delta_time);

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

void CinemaCamera::Render(int x1, int y1, int x2, int y2, int screen_hdl)
{
	if (m_mediator->GetEventLane().s_id == 1)
	{
		// 画面に描画
		SetDrawScreen(screen_hdl);
		ClearDrawScreen();

		// 描画対象を表画面に設定
		SetDrawScreen(DX_SCREEN_BACK);

		DrawExtendGraph(x1, y1, x2, y2, screen_hdl, FALSE);
	}
}

void CinemaCamera::CreateScreen()
{	
	m_all_hdl = MakeScreen(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, TRUE);

	m_half_right = MakeScreen(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT, TRUE);

	m_third_left = MakeScreen(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT, TRUE);

	m_third_right = MakeScreen(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT, TRUE);
}

void CinemaCamera::SplitAnimation(const float delta_time)
{
	// 分割比率の変更
	split_rate += delta_time * 10;

	// 分割比率が1を超えたら1にする
	if (split_rate > 1.0f)
	{
		split_rate = 1.0f;
	}
}

bool CinemaCamera::SeqTrigger(const float delta_time)
{
	// １番のイベントの場合（登場カメラ）
	if (m_mediator->GetEventLane().s_id == 1)
	{
		// アップで正面全体に映す
		
	}
	if (m_mediator->GetEventLane().s_id == 5)
	{
		// 画面を三分割にする
		//全てサブカメラにして、それぞれのカメラで描画アップ、サイド描画
	}
	if (m_mediator->GetEventLane().s_id == 9)
	{
		// 画面を二分割にする
		// 蝶とプレイヤーをサイドからそれぞれアップへ
		// プレイヤーをアップで全画面
	}
	
	TNL_SEQ_CO_END;
}

bool CinemaCamera::SeqUp(const float delta_time)
{
	// イベントが終了したらTriggerに戻る
	if(m_is_completed)
	{
		tnl_sequence_.change(&CinemaCamera::SeqTrigger);
	}

	TNL_SEQ_CO_END;

}

bool CinemaCamera::SeqSide(const float delta_time)
{
	// イベントが終了したらTriggerに戻る
	if (m_is_completed)
	{
		tnl_sequence_.change(&CinemaCamera::SeqTrigger);
	}

	TNL_SEQ_CO_END;


}

bool CinemaCamera::SeqBack(const float delta_time)
{
	// イベントが終了したらTriggerに戻る
	if (m_is_completed)
	{
		tnl_sequence_.change(&CinemaCamera::SeqTrigger);
	}

	TNL_SEQ_CO_END;


}




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

