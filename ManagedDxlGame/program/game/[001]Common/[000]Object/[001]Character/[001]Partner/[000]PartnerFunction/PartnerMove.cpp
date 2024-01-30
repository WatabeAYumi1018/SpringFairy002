#include "../../../../[002]Mediator/Mediator.h"
#include "../../../../[001]Camera/GameCamera.h"
#include "PartnerMove.h"


void PartnerMove::Update(float delta_time)
{
	m_pos = m_mediator->GetPartnerPos();
	m_rot = m_mediator->GetPartnerRot();

	// 自動経路による移動と回転の更新
	m_mediator->MoveAstarCharaUpdatePos(delta_time, m_pos);
	m_mediator->MoveAstarCharaUpdateRot(delta_time, m_pos,m_rot);

	UpdatePos(delta_time);

    //if (m_is_pushed)
    //{
    //    CorrectPos(delta_time);
    //}

    //UpdateRot(delta_time);

	// パートナーの位置と回転を更新
	m_mediator->SetPartnerPos(m_pos);
	m_mediator->SetPartnerRot(m_rot);
}

void PartnerMove::UpdatePos(const float delta_time)
{
    m_move_time += delta_time;

    // 周期的またはランダムに周波数を変更(3秒ごとに変更)
    if (m_move_time - m_last_move_time > 3.0f)
    {
        // 0.1～0.2の範囲でランダム
        m_orbit_frequency
            = tnl::GetRandomDistributionFloat(0.1f, 0.2f);
       
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

//void PartnerMove::UpdateRot(const float delta_time)
//{
//    m_rotation_time += delta_time;
//
//    // 一定間隔でランダムな回転を設定
//    if (m_rotation_time - m_last_rotation_time > 5.0f)
//    {
//        float random_angle 
//            = static_cast<float>(rand()) / RAND_MAX * DirectX::XM_PI * 2;
//    
//        tnl::Vector3 random_axis(rand() % 2, rand() % 2, rand() % 2);
//        
//        m_target_rot 
//            = tnl::Quaternion::RotationAxis(random_axis, random_angle);
//        
//        m_last_rotation_time = m_rotation_time;
//    }
//
//    // 現在の回転と目標の回転の間で滑らかに遷移    
//    m_rot.slerp(m_target_rot, delta_time * 0.5f);
//}

// 円同士の補正処理(Object2が弾かれる)
void PartnerMove::CorrectPos(const float delta_time)
{
    tnl::Vector3 player_pos = m_mediator->GetPlayerPos();
    tnl::Vector3 partner_pos = m_mediator->GetPartnerPos();

    // 2つのオブジェクト間の距離ベクトルを計算
    tnl::Vector3 distance_vec = partner_pos - player_pos;
    // 単位ベクトル取得
    distance_vec.normalize();
    // 2つのオブジェクト間の距離を算出
    float distance = distance_vec.length();

    // 2つのオブジェクトの半径の合計
    float total_radius 
        = m_mediator->GetPlayerCollisionSize()
        + m_mediator->GetPartnerCollisionSize();

    // 衝突が発生している場合、位置を補正する
    if (distance < total_radius)
    {
        // 重なりの量を計算
        float overlap = total_radius - distance;
        // 補正するための移動ベクトルを計算
        tnl::Vector3 correct_vec = distance_vec * overlap;
        //// 補正にかかる時間
        //float lerp_time = 0.5f;
        //tnl::Vector3 lerp_vec = tnl::Vector3(partner_pos + (correct_vec * lerp_time * delta_time));
        player_pos -= correct_vec * 5 * delta_time;
        partner_pos += correct_vec * 5 * delta_time;

        // オブジェクトの位置を補正
        m_mediator->SetPlayerPos(player_pos);
        m_mediator->SetPartnerPos(partner_pos);
    }

    m_is_pushed = false;
}

//void PartnerMove::ApplyForce()
//{
//    // 二つのオブジェクト間の距離ベクトル
//    tnl::Vector3 distanceVec 
//        = m_mediator->GetPlayerPos() - m_mediator->GetPartnerPos();
//
//    // 距離ベクトルを正規化して方向を得る
//    tnl::Vector3 direction = tnl::Vector3::Normalize(distanceVec);
//
//    // 力の大きさを決定
//    // 近いほど大きな力が加わる
//    float distance = distanceVec.length();
//
//    float forceMagnitude = std::max(0.0f, forceStrength * (object1_radius + object2_radius - distance));
//
//    // 力を加える
//    tnl::Vector3 force = direction * forceMagnitude;
//    object2->ApplyForce(force); // 仮想的な ApplyForce 関数
//}

//bool PartnerMove::SeqPartnerIn(const float delta_time)
//{
//	// 二つのオブジェクトの中心座標を求める
//	m_center = (m_mediator->GetPlayerPos() + m_mediator->GetPartnerPos()) / 2.0f;
//
//	// 中心座標からの単位ベクトルを求める
//	m_reverse = tnl::Vector3::Normalize(m_mediator->GetPlayerPos() - m_mediator->GetPartnerPos());
//
//	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
//	{
//
//	tnl::Vector3 rev = m_center - (m_reverse * m_mediator->GetPartnerCollisionSize());
//
//	m_mediator->SetPartnerPos(rev);
//
//
//		//// 沈み込む動作
//		//float sink = SINK_VALUE * (m_elapsed_time / SINK_DURATION);
//
//		//float sink_size = m_mediator->GetPartnerCollisionSize() / 2;
//
//		//tnl::Vector3 reverse = m_reverse * sink_size; //- sink);
//
//		//tnl::Vector3 sink_vec = tnl::Vector3(m_center - reverse);
//
//		//m_mediator->SetPartnerPos(sink_vec);
//	});
//
//	//tnl_sequence_.change(&PartnerMove::SeqPartnerOut);
//
//	TNL_SEQ_CO_END;
//}
//
//bool PartnerMove::SeqPartnerOut(const float delta_time)
//{
//	TNL_SEQ_CO_TIM_YIELD_RETURN(PUSH_DURATION, delta_time, [&]()
//	{
//		float push = PUSH_VALUE * ((m_elapsed_time - SINK_DURATION) / PUSH_DURATION);
//
//		tnl::Vector3 push_size 
//			= m_reverse * (m_mediator->GetPartnerCollisionSize() + push);
//
//		tnl::Vector3 push_vec = tnl::Vector3(m_center - push_size);
//
//		m_mediator->SetPartnerPos(push_vec);
//	});
//
//	m_is_pushed = false;
//
//	m_elapsed_time = 0;
//
//	tnl_sequence_.change(&PartnerMove::SeqPartnerIn);
//
//	TNL_SEQ_CO_END;
//}

//
//bool PartnerMove::SeqPartnerStay(const float delta_time)
//{
//	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
//		{
//			tnl::Vector3 scaele = tnl::Vector3(0.95f);
//
//			//パートナーのサイズを若干小さくする
//			m_mediator->SetPartnerScale(scaele);
//		});
//
//	tnl::Vector3 scaele = tnl::Vector3(1);
//
//	m_mediator->SetPartnerScale(scaele);
//
//	tnl_sequence_.change(&PartnerMove::SeqPartnerOut);
//
//	TNL_SEQ_CO_END;
//}

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