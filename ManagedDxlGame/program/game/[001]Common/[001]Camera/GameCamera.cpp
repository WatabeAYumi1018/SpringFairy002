#include "../../../wta_library/wta_Convert.h"
#include "GameCamera.h"
#include "../[002]Mediator/Mediator.h"
#include "../[000]Object/[001]Character/[000]Player/Player.h"


GameCamera::GameCamera()
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT){}

void GameCamera::update(const float delta_time)
{
	//// カメラの姿勢を更新
	//target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rot);
	//// カメラのアッパーベクトルを更新
	//up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_rot);

	dxe::Camera::update(delta_time);

	tnl_sequence_.update(delta_time);

	//for (int i = 0; i < 6; ++i)
	//{
	//	tnl::Vector3 player_pos = m_mediator->GetPlayerPos();
	//	float size = m_mediator->GetPlayerCollisionSize();

	//	tnl::Vector3 v = getFlustumNormal(static_cast<dxe::Camera::eFlustum>(i));
	//	tnl::Vector3 np = tnl::GetNearestPointPlane(player_pos, v, pos_);
	//	float length = (np - player_pos).length();
	//	if (length < size)
	//	{
	//		tnl::Vector3 pos = np + (v * size);
	//		m_mediator->SetPlayerPos(pos);
	//	}
	//}


	//m_mediator->IsIntersectCameraFlustum(delta_time);
	
	//m_mediator->UpdateCameraFrustum();
	//
	//// 座標デバッグ用
	//DrawStringEx(0, 100, -1, "CameraPos_x:%f", pos_.x);
	//DrawStringEx(0, 120, -1, "CameraPos_y:%f", pos_.y);
	//DrawStringEx(0, 140, -1, "CameraPos_z:%f", pos_.z);
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
		m_mediator->SetPlayerLookSideRight(false);
		m_mediator->SetPlayerLookSideLeft(false);
	}

	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT))
	{
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
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqRightSideToFix);
	}

	// サイドへカメラを移動
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		ToSide(delta_time,400);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Side(400);
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
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqLeftSideToFix);
	}

	// サイドへカメラを移動
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.3f, delta_time, [&]()
	{
		ToSide(delta_time, -400);
	});

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		Side(-400);
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
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqFrontToFix);
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
	if (m_mediator->GetTargetCameraInfo().s_type == eCameraType::e_fixed)
	{
		tnl_sequence_.change(&GameCamera::SeqRotateToFix);
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


//UpdateFrustumPlane();	

//// どの時カメラを切り替えるか、その時にどんな動きにするかを記述
//// 補間を使用してカメラ位置とターゲットを更新
//float lerpRate = delta_time * 0.5f;
//pos_ = Lerp(pos_, m_mediator->GetPlayerPos(), lerpRate);
//target_ = Lerp(target_, m_mediator->GetPlayerPos(), lerpRate);

//for (int i = 0; i < 6; i++) {
//	DrawFrustumPlane(m_frustum_param[i].s_normal, m_frustum_param[i].s_d);
//}

//void OriginalCamera::DrawFrustumPlane(const tnl::Vector3& normal, float d)
//{
//	// 平面の中心点を計算
//	tnl::Vector3 center = normal * d;
//
//	// 四角形の頂点を計算（簡単化のため、一定のサイズを仮定）
//	float size = 100.0f; // 四角形のサイズ
//	// 頂点の計算...
//
//	VECTOR center_vec = wta::ConvertToVECTOR(center);
//	
//	DrawSphere3D(center_vec, size, 32, -1, 1, true);
//}

//// フラスタムの各平面の法線ベクトルを計算し、
//// 定数項でその平面の位置を特定することにより、フラスタムの境界を定義
//void Camera::UpdateFrustumPlane()
//{
//	// ビュー行列と射影行列を合成
//	// オブジェクトの世界座標系から2D画面空間への直接的な変換
//	tnl::Matrix view_proj = view_ * proj_;
//
//	// ☆行列の乗算 : 座標変換（回転、拡大縮小、平行移動）
//	// ☆行列の加算 : 座標変換の合成（複数の座標変換を一度に行い、新しいベクトル生成）
//
//	// 左平面
//	// 左平面の法線ベクトル(平面に対する垂直ベクトル)を算出
//	// view_proj._11 ～ view_proj._31 : 合成行列の1行目（カメラ空間における右方向ベクトル）
//	// view_proj._12 ～ view_proj._32 : 合成行列の2行目（カメラ空間における上方向ベクトル）
//	// view_proj._13 ～ view_proj._33 : 合成行列の3行目（カメラ空間における前方向ベクトル）
//	// view_proj._14 ～ view_proj._34 : 合成行列の4行目（カメラ空間の原点からの変換ベクトル）
//	// 加算することで左平面の法線ベクトルを算出（フラスタムの左平面と他の部分との境界）
//	m_frustum_param[0].s_normal = tnl::Vector3(view_proj._14 + view_proj._11,
//												view_proj._24 + view_proj._21,
//												view_proj._34 + view_proj._31);
//
//	// フラスタム平面左平面の方程式における定数項を算出
//	// 方程式 : Ax+By+Cz+D=0 (A,B,C : 法線ベクトルの成分 ・　D : 定数項)
//	// 結果が 0 より大きい場合: 点は平面の一方の側（通常は「内側」）
//	// 結果が 0 より小さい場合: 点は平面の他方の側（通常は「外側」）
//	// 結果が 0 の場合: 点は平面上
//	// _44 : Z軸に沿った深度（奥行き）の情報をスケール
//	// _41 : X軸に沿った横幅の位置情報をスケール
//	// 加算することで左平面が3D空間内でどのように位置するかを特定（カメラから見てどれだけ左側か）
//	m_frustum_param[0].s_d = view_proj._44 + view_proj._41;
//
//	// 右平面
//	m_frustum_param[1].s_normal = tnl::Vector3(view_proj._14 - view_proj._11,
//												view_proj._24 - view_proj._21,
//												view_proj._34 - view_proj._31);
//	m_frustum_param[1].s_d = view_proj._44 - view_proj._41;
//
//	// 上平面
//	m_frustum_param[2].s_normal = tnl::Vector3(view_proj._14 - view_proj._12,
//												view_proj._24 - view_proj._22,
//												view_proj._34 - view_proj._32);
//	m_frustum_param[2].s_d = view_proj._44 - view_proj._42;
//
//	// 下平面
//	m_frustum_param[3].s_normal = tnl::Vector3(view_proj._14 + view_proj._12,
//												view_proj._24 + view_proj._22,
//												view_proj._34 + view_proj._32);
//	m_frustum_param[3].s_d = view_proj._44 + view_proj._42;
//
//	// 近平面
//	// 近平面はカメラの法線ベクトルは前方向ベクトルと平行
//	m_frustum_param[4].s_normal = tnl::Vector3(view_proj._13,
//												view_proj._23,
//												view_proj._33);
//	m_frustum_param[4].s_d = view_proj._43;
//
//	// 遠平面
//	m_frustum_param[5].s_normal = tnl::Vector3(view_proj._14 - view_proj._13,
//												view_proj._24 - view_proj._23,
//												view_proj._34 - view_proj._33);
//	m_frustum_param[5].s_d = view_proj._44 - view_proj._43;
//
//	// 各平面の法線ベクトルを正規化
//	// 法線ベクトルの長さが一定（通常は1）であることを保証することで、
//	// フラスタムの平面とオブジェクトとの距離計算が一貫したものになる
//	// 点と平面との距離は、点の位置ベクトルと法線ベクトルの内積
//	// そして定数項を加算するだけで算出できる
//	for (int i = 0; i < m_frustum_plane_num; i++)
//	{
//		m_frustum_param[i].s_normal.normalize();
//	}
//}
//
//bool Camera::IsInFrustum(const tnl::Vector3& pos)
//{
//	for (int i = 0; i < m_frustum_plane_num; i++)
//	{
//		// 内積を計算し、定数項を加算
//		// 点と平面との距離を算出
//		// 点と平面との距離が0より小さい場合、点は平面の外側にある
//		float dot = tnl::Vector3::Dot(m_frustum_param[i].s_normal, pos);
//
//		dot += m_frustum_param[i].s_d;
//
//		if (dot < 0)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//void Camera::ReturnPlayerPos(const tnl::Vector3& pos)
//{
//	// フラスタム境界外にプレイヤーの座標が移動した場合
//	if (!IsInFrustum(pos))
//	{
//		// フラスタムの各面とプレイヤーの距離を格納する配列
//		float distance[4];
//		// フラスタムの各面とプレイヤーの距離を計算
//		for (int i = 0; i < m_frustum_plane_num; i++)
//		{
//			distance[i] = tnl::Vector3::Dot(m_frustum_param[i].s_normal, pos)
//						+ m_frustum_param[i].s_d;
//		}
//		// 一番近いフラスタムの面にプレイヤーを戻す
//		  // フラスタムの境界に最も近い平面を見つける
//		int min_index 
//			= std::min_element(distance, distance + m_frustum_plane_num) - distance;
//		// プレイヤーの座標をフラスタムの面に戻す
//		tnl::Vector3 return_pos 
//			= pos - m_frustum_param[min_index].s_normal * distance[min_index];
//
//		m_mediator->SetPlayerPos(return_pos);
//	}
//}

//
//void OriginalCamera::DrawFrustumPlane()
//{
//	// 逆行列を生成
//	// 逆行列を生成することで、ビュー座標系からワールド座標系への変換を行う
//	tnl::Matrix inv_view_proj = tnl::Matrix::Inverse(view_ * proj_);
//	// フラスタムカリングのコーナー計算
//	std::vector<tnl::Vector3> frustum_corners = CalculateFrustumCorners(inv_view_proj);
//
//	// 近平面と遠平面のコーナーを結ぶ
//	for (int i = 0; i < 4; i++) 
//	{
//		// 近平面(0,1,2,3)
//		// 近平面の各コーナーを次のコーナーと接続
//		// % 4 : インデックスが3のときに次のコーナーが0に戻ることを保証
//		// 3 + 1 = 4 ,4 % 4 = 0
//		DrawLine3DEx(m_debug_camera, frustum_corners[i], frustum_corners[(i + 1) % 4], 1);
//		// 遠平面(4,5,6,7)
//		DrawLine3DEx(m_debug_camera, frustum_corners[i + 4], frustum_corners[((i + 1) % 4) + 4], 1);
//		// 近平面と遠平面を結ぶ
//		// 近平面(0,1,2,3)と遠平面(4,5,6,7)を結ぶ
//		// 各々対応するコーナーと接続
//		DrawLine3DEx(m_debug_camera, frustum_corners[i], frustum_corners[i + 4], 1);
//	}
//}
//
//std::vector<tnl::Vector3> OriginalCamera::CalculateFrustumCorners(const tnl::Matrix& inv_view_proj)
//{
//	// フラスタムカリングのコーナーを格納する配列を生成
//	std::vector<tnl::Vector3> corners(8);
//
//	// ビュー座標系の8つのコーナーを計算
//	// ビュー座標系のコーナーは、すべてのコーナーが原点を中心とした単位立方体にある
//	// 単位立方体 : すべての辺の長さが1の立方体
//
//	// 左上手前
//	corners[0] = tnl::Vector3(-1, 1, 0);
//	// 右上手前
//	corners[1] = tnl::Vector3(1, 1, 0);
//	// 右下手前
//	corners[2] = tnl::Vector3(1, -1, 0);
//	// 左下手前
//	corners[3] = tnl::Vector3(-1, -1, 0);
//	// 左上奥
//	corners[4] = tnl::Vector3(-1, 1, 1);
//	// 右上奥
//	corners[5] = tnl::Vector3(1, 1, 1);
//	// 右下奥
//	corners[6] = tnl::Vector3(1, -1, 1);
//	// 左下奥
//	corners[7] = tnl::Vector3(-1, -1, 1);
//
//	for (int i = 0; i < corners.size(); i++)
//	{
//		// ビュー座標系の8つのコーナーをワールド座標系に変換
//		corners[i] = tnl::Vector3::Transform(corners[i], inv_view_proj);
//	}
//
//	return corners;
//}