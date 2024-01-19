#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "CameraTargetPlayer.h"


void CameraTargetPlayer::Initialize()
{
	m_collision_size = 50;

	StartPos();
}

void CameraTargetPlayer::Update(float delta_time)
{
	// 自動経路による移動と回転の更新
	m_mediator->MoveAstarTargetPos(delta_time, m_pos);

	m_camera_info = CurrentCameraType();

	DrawStringEx(500,0,-1,"ID番号 : %d",m_camera_info.s_id);

	m_item = CurrentItemLane();

	if (m_item.s_id == 1)
	{
		Item::sItemType item_type 
			= m_mediator->GetItemLoadInfoById(m_item.s_id);
	}
}

void CameraTargetPlayer::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	//// 当たり判定デバッグ用
	VECTOR pos = wta::ConvertToVECTOR(m_pos);
	pos.y += m_collision_size;
	DrawSphere3D(pos, m_collision_size, 32, -1, -1, true);

	// 座標デバッグ用
	DrawStringEx(1000, 100, 1, "TargetPos_x:%f", m_pos.x);
	DrawStringEx(1000, 120, 1, "TargetPos_y:%f", m_pos.y);
	DrawStringEx(1000, 140, 1, "TargetPos_z:%f", m_pos.z);
}
