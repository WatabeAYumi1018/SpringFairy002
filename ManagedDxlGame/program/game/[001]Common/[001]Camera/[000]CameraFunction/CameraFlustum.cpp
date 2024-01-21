#include "../../[002]Mediator/Mediator.h"
#include "../GameCamera.h"
#include "CameraFlustum.h"


void CameraFlustum::IsIntersectFlustum(const float delta_time)
{
	tnl::Vector3 player_pos = m_mediator->GetPlayerPos();

	float player_radius = m_mediator->GetPlayerCollisionSize();

	// 上下左右のフラスタム面との当たり判定と補正処理
	InFlustumPlane(delta_time,player_pos, player_radius);
}

void CameraFlustum::InFlustumPlane(const float delta_time,tnl::Vector3& pos,float size)
{
	// meshpos,flustomvec,camerapos
	//tnl::Vector3 GetNearestPointPlane(const tnl::Vector3 & v, const tnl::Vector3 & pn, const tnl::Vector3 & pv)
	//{
	//	float d = tnl::Vector3::Dot(pn, pv);
	//	float t = tnl::Vector3::Dot(pn, v) - d;
	//	return v - (pn * t);
	//}

	// 6 : フラスタム面の数だけループ
	for (int i = 0; i < static_cast<int>(dxe::Camera::eFlustum::Max); ++i)
	{
		// フラスタム面の法線を取得
		tnl::Vector3 flustum_normal
			= m_mediator->GetFlustumNormal(static_cast<dxe::Camera::eFlustum>(i));

		float D = tnl::Vector3::Dot(flustum_normal, m_mediator->GetCameraPos());

		float distance = tnl::Vector3::Dot(flustum_normal, pos) - D;

		// プレイヤーがカメラ面の外側にいる場合

		// プレイヤーをフラスタム内に留めるための補正を行う
		pos -= (flustum_normal * (distance + size));
		

		// 近平面と遠平面との当たり判定と補正処理
		if (i == 4 || i == 5)
		{
			CorrectPlayer(delta_time, size, pos);
		}

		// 補正した位置をセット
		m_mediator->SetPlayerPos(pos);
	}
}

void CameraFlustum::CorrectPlayer(const float delta_time, float size,tnl::Vector3& pos)
{
	// カメラの位置を取得
	tnl::Vector3 camera_pos = m_mediator->GetCameraPos();

	// カメラからプレイヤーへの方向ベクトルを正規化
	tnl::Vector3 direction = pos - camera_pos;
	direction.normalize();

	float distance = (pos - camera_pos).length();

	// 近平面の補正
	if (distance < 300.0f + size)
	{
		// プレイヤーを近平面の内側に移動
		pos = camera_pos + direction * delta_time * (300 + size);
	}
	// 遠平面の補正
	else if (distance > 700.0f - size)
	{
		// プレイヤーを遠平面の内側に移動
		pos = camera_pos + direction * delta_time * (700 - size);
	}

	// 補正した位置をセット
	m_mediator->SetPlayerPos(pos);
}
