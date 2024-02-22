#include <random>
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "../../../[003]Phase/StagePhase.h"
#include "../../[000]Stage/[002]Floor/Floor.h"
#include "GimmickGenerator.h"


void GimmickGenerator::Update(const float delta_time)
{
 //   tnl_sequence_.update(delta_time);

    if(m_mediator->GetPlayerLookSideRight() 
       || m_mediator->GetPlayerLookSideLeft())
    {
        m_is_ground_active = true;
    }

    if (m_is_ground_active)
    {
        CreateGimmick(delta_time);
    }
}

void GimmickGenerator::CreateGimmick(const float delta_time)
{
    StagePhase::eStagePhase stage_phase 
                = m_mediator->GetNowStagePhaseState();

    if (stage_phase == StagePhase::eStagePhase::e_wood)
    {
        CalcGroundPos(delta_time, Gimmick::eGimmickType::e_wood);
    }
    else
    {
        CalcGroundPos(delta_time, Gimmick::eGimmickType::e_ground_flower);
    }
}

void GimmickGenerator::CalcGroundPos(const float delta_time, Gimmick::eGimmickType type)
{
    // 生成ギミックの取得
    std::vector<std::shared_ptr<Gimmick>>& gimmicks
                   = m_mediator->GetGimmickTypePools(type);

    // ギミックのベクターの中身をランダムに並び替え
    std::shuffle(gimmicks.begin(), gimmicks.end()
                , std::mt19937(std::random_device()()));

    // プレイヤーのforward単位ベクトルを生成
    tnl::Vector3 forward = m_mediator->PlayerForward();
    forward.normalize();

    // forwardとへ移行なベクトルを計算
    tnl::Vector3 perpendicular = DirectionCalcPos(forward);
    // 300 : 疑似プレイヤーとギミックとの最低距離
    tnl::Vector3 start_offset = perpendicular * 300.0f;

    tnl::Vector3 target_pos 
        = m_mediator->GetGameCameraTargetPos() + start_offset;

    for (std::shared_ptr<Gimmick>& gimmick : gimmicks)
    {
        // 活性化してなければ配置
        if (!gimmick->GetIsActive())
        {
            // 座標決定
            SetPlacePos(gimmick, target_pos, forward, perpendicular);

            // 2 : 木のモデルが大きいためギミック間の距離を広げる
            if (m_mediator->GetNowStagePhaseState() 
                == StagePhase::eStagePhase::e_wood)
            {
                target_pos += forward * 400.0f * 2;
			}
            else
            {
                // ギミック同士の距離を設定
                target_pos += forward * 400.0f;
            }
        }
        else
        {
            // 活性化していて条件を満たしていればリセット
            CheckGimmicks(delta_time, type, gimmick);
        }
    }
}

tnl::Vector3 GimmickGenerator::DirectionCalcPos(const tnl::Vector3& forward)
{
    // 経路からforward方向に水平なベクトルを計算
    tnl::Vector3 perpendicular;

    if (forward.z > 0)
    {
        if (m_mediator->GetPlayerLookSideRight())
        {
            perpendicular = tnl::Vector3::Cross(forward, tnl::Vector3(0, 1, 0));
        }
        else if (m_mediator->GetPlayerLookSideLeft())
        {
            perpendicular = tnl::Vector3::Cross(forward, tnl::Vector3(0, -1, 0));
        }
    }
    else
    {
        if (m_mediator->GetPlayerLookSideRight())
        {
            perpendicular = tnl::Vector3::Cross(forward, tnl::Vector3(0, -1, 0));
        }
        else if (m_mediator->GetPlayerLookSideLeft())
        {
            perpendicular = tnl::Vector3::Cross(forward, tnl::Vector3(0, 1, 0));
        }
    }

    perpendicular.normalize();
    
    return perpendicular;
}

void GimmickGenerator::SetPlacePos(std::shared_ptr<Gimmick>& gimmick
                                    , const tnl::Vector3& target_pos
                                    , const tnl::Vector3& forward
                                    , const tnl::Vector3& perpendicular)
{
    // 自動経路の線分上からforward方向へのベクトルをランダム生成
    float forward_distance 
        = tnl::GetRandomDistributionFloat(600.0f, 1500.0f);

    // ギミックの新しい位置を計算
    tnl::Vector3 pos = target_pos + perpendicular * forward_distance;
    
    pos.y = Floor::DRAW_OFFSET;

    // 2 : エリアwoodの時は木にぶつからないようにフロアの描画位置を下げる
    if (m_mediator->GetNowStagePhaseState() 
        == StagePhase::eStagePhase::e_wood)
    {
        pos.y *= 2;
    }

    // ギミックの座標とフラグ設定
    gimmick->SetPos(pos);
    gimmick->SetIsActive(true);
}


void GimmickGenerator::CalcSkyFlowerPos(const float delta_time,Gimmick::eGimmickType type)
{
    // 1秒ごとに実行する
    static float elapsed_time = 0.0f;

    elapsed_time += delta_time;

    if (elapsed_time < 1.0f)
    {
        return;
    }
    // 生成ギミックの取得
    std::vector<std::shared_ptr<Gimmick>>& gimmicks
                   = m_mediator->GetGimmickTypePools(Gimmick::eGimmickType::e_sky_flower);

    for (std::shared_ptr<Gimmick>& gimmick : gimmicks)
    {
        if (m_mediator->CurrentTargetCameraLane().s_id == 0)
        {
            tnl::Vector3 pos = CalcRandomPos();

            gimmick->SetPos(pos);

            gimmick->SetIsActive(true);
        }
    }
    elapsed_time = 0.0f;
}

tnl::Vector3 GimmickGenerator::CalcRandomPos()
{
    tnl::Vector3 player_pos = m_mediator->GetGameCameraTargetPos();

    float offset = 700.0f;

    tnl::Vector3 random_pos
        = tnl::Vector3(tnl::GetRandomDistributionFloat(player_pos.x - (offset * 2), player_pos.x - offset)
                        , 800
                        , player_pos.z + offset);

    return random_pos;
}

bool GimmickGenerator::SeqFlower(const float delta_time)
{
    //// 足元idが1の場合移行
    //if (m_gimmick_lane.s_id == 1)
    //{
    //    m_is_flower_active = false;

    //	tnl_sequence_.change(&GimmickGenerator::SeqButterfly);
    //}

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
    {
        CalcSkyFlowerPos(delta_time,Gimmick::eGimmickType::e_sky_flower);
    });

    TNL_SEQ_CO_END;
}

void GimmickGenerator::CheckGimmicks(const float delta_time
                                     , Gimmick::eGimmickType type
                                     , std::shared_ptr<Gimmick> gimmick)
{
    // 活性化していて条件を満たしていればリセット
    if (m_mediator->IsCameraFixed())
    {
        gimmick->Reset();

        m_is_ground_active = false;
    }
}
