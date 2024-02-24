#include "../../../../[002]Mediator/Mediator.h"
#include "../../../../[001]Camera/GameCamera.h"
#include "PartnerMove.h"


void PartnerMove::Update(const float delta_time)
{
	m_pos = m_mediator->GetPartnerPos();
	m_rot = m_mediator->GetPartnerRot();

    if (m_mediator->GetCurrentEventLane().s_id != 6)
    {
        // 自動経路による移動と回転の更新
        m_mediator->MoveAstarCharaUpdatePos(delta_time, m_pos);
        m_mediator->MoveAstarCharaUpdateRot(delta_time, m_pos, m_rot);

        UpdateRandomPos(delta_time);
    }

    if (m_mediator->GetCurrentEventLane().s_id == 14)
    {
        // 物語終了後、エンドへ移行するための上昇速度
        float move_speed_y = 1000.0f;

        m_pos.y += delta_time * move_speed_y;
    }

	// パートナーの位置と回転を更新
	m_mediator->SetPartnerPos(m_pos);
	m_mediator->SetPartnerRot(m_rot);
}

void PartnerMove::UpdateRandomPos(const float delta_time)
{
    float change_move_time = 3.0f;

    m_move_time += delta_time;

    // 周期的またはランダムに周波数を変更(3秒ごとに変更)
    if (m_move_time - m_last_move_time > change_move_time)
    {
        // 0.1～0.2の範囲でランダム
        // わずかな数値で変化も殆どないため、固定値
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

// 円同士の補正処理(Object2が弾かれる)
void PartnerMove::CorrectPos(const float delta_time)
{
    // 弾かれる速度
    float push_speed = 5.0f;

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
        //tnl::Vector3 lerp_vec 
        // = tnl::Vector3(partner_pos + (correct_vec * lerp_time * delta_time));
        player_pos -= correct_vec * push_speed * delta_time;
        partner_pos += correct_vec * push_speed * delta_time;

        // オブジェクトの位置を補正
        m_mediator->SetPlayerPos(player_pos);
        m_mediator->SetPartnerPos(partner_pos);
    }

    m_is_pushed = false;
}