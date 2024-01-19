#include "../../../../[002]Mediator/Mediator.h"
#include "../../../../[001]Camera/GameCamera.h"
#include "PartnerMove.h"


void PartnerMove::Update(float delta_time)
{
	m_pos = m_mediator->GetPartnerPos();
	m_rot = m_mediator->GetPartnerRot();

	// 自動経路による移動と回転の更新
	m_mediator->MoveAstarCharaMatrix(delta_time, m_pos,m_rot);
	
	UpdatePos(delta_time);

   // UpdateRot(delta_time);

	// パートナーの位置と回転を更新
	m_mediator->SetPartnerPos(m_pos);
	m_mediator->SetPartnerRot(m_rot);
}

void PartnerMove::UpdatePos(float delta_time)
{
    m_move_time += delta_time;

    // 周期的またはランダムに周波数を変更(3秒ごとに変更)
    if (m_move_time - m_last_move_time > 3.0f)
    {
        // 0.1～0.4の範囲でランダム
        m_orbit_frequency 
            = 0.1f + static_cast<float>(rand()) / RAND_MAX * 0.5f;
       
        m_last_move_time = m_move_time;
    }

    // プレイヤーの位置を取得
    tnl::Vector3 player_pos = m_mediator->GetPlayerPos();

    // 独自の動き（プレイヤーの周りを回る動き）を追加
    float orbit_radius = 1.0f;
    
    m_offset.x = orbit_radius * cosf(m_move_time * m_orbit_frequency);
    m_offset.z = orbit_radius * sinf(m_move_time * m_orbit_frequency);

    // 自動移動による位置にオーバーレイ
    m_pos += m_offset;
}

void PartnerMove::UpdateRot(float delta_time)
{
    m_rotation_time += delta_time;

    // 一定間隔でランダムな回転を設定
    if (m_rotation_time - m_last_rotation_time > 5.0f)
    {
        float random_angle 
            = static_cast<float>(rand()) / RAND_MAX * DirectX::XM_PI * 2;
    
        tnl::Vector3 random_axis(rand() % 2, rand() % 2, rand() % 2);
        
        m_target_rot 
            = tnl::Quaternion::RotationAxis(random_axis, random_angle);
        
        m_last_rotation_time = m_rotation_time;
    }

    // 現在の回転と目標の回転の間で滑らかに遷移    
    m_rot.slerp(m_target_rot, delta_time * 0.5f);
}


//bool PartnerMove::SeqTargetCalc(const float delta_time)
//{
//	if (m_random <= 5)
//	{
//		tnl_sequence_.change(&PartnerMove::SeqFall);
//	}
//
//	if (6 <= m_random && m_random <= 10)
//	{
//		tnl_sequence_.change(&PartnerMove::SeqInverse);
//	}
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
//	{
//		m_is_moved = false;
//
//		CalcRandomPos(m_mediator->GetPlayerPos());
//
//		m_random = rand() % 100;
//	});
//
//	tnl_sequence_.change(&PartnerMove::SeqMove);
//
//	TNL_SEQ_CO_END;
//}
//
//bool PartnerMove::SeqMove(const float delta_time)
//{
//	if (m_is_moved)
//	{
//		tnl_sequence_.change(&PartnerMove::SeqTargetCalc);
//	}
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		UpdateMatrix(delta_time);
//	});
//
//	TNL_SEQ_CO_END;
//}
//
//bool PartnerMove::SeqFall(const float delta_time)
//{
//	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
//	{
//		// 下に落下
//		m_target_pos = m_mediator->GetPlayerPos() 
//						- tnl::Vector3(0, rand() % 5, 0);
//	});
//
//	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
//	{
//		// 戻る
//		m_target_pos = m_mediator->GetPlayerPos()
//			+ tnl::Vector3(0, rand() % 5, 0);
//	});
//
//	tnl_sequence_.change(&PartnerMove::SeqTargetCalc);
//
//	TNL_SEQ_CO_END;
//}
//
//bool PartnerMove::SeqInverse(const float delta_time)
//{
//	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
//	{
//		// 適当な方向に移動
//		m_target_pos = m_mediator->GetPlayerPos() 
//						- tnl::Vector3(rand() % 10, 0, rand() % 10);
//	});
//
//	tnl_sequence_.change(&PartnerMove::SeqTargetCalc);
//
//	TNL_SEQ_CO_END;
//}