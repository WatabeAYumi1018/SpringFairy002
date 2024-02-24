#include <random>
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "../../../[003]Phase/StagePhase.h"
#include "../../[000]Stage/[002]Floor/Floor.h"
#include "GimmickGenerator.h"


void GimmickGenerator::Update(const float delta_time)
{
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
    float distance = 300.0f;

    tnl::Vector3 start_offset = perpendicular * distance;

    tnl::Vector3 target_pos 
        = m_mediator->GetGameCameraTargetPos() + start_offset;

    // 400 : ギミック同士の距離
    float offset = 400.0f;
    float area_offset = 800.0f;

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
                // 2 : エリアwoodの時は木にぶつからないように間隔を広げる
                target_pos += forward * area_offset;
			}
            else
            {
                // ギミック同士の距離を設定
                target_pos += forward * offset;
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
            // 外積計算
            // 1 : プレイヤーの向きによって外積の向きを変える
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
    // 800 : ギミックの生成位置の最小値（デバッグでの制御を推奨。後日修正をします。）
    // 1000 : ギミックの生成位置の最大値（同様）
    float forward_distance 
        = tnl::GetRandomDistributionFloat(800.0f, 1000.0f);

    // ギミックの新しい位置を計算
    tnl::Vector3 pos = target_pos + perpendicular * forward_distance;
    
    pos.y = Floor::DRAW_OFFSET;

    // 2 : エリアwoodの時は木にぶつからないようにフロアの描画位置を下げる
    // 元モデルの大きさにも起因するため、変更はほぼなし。固定値とする。
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
                        , offset
                        , player_pos.z + offset);

    return random_pos;
}

bool GimmickGenerator::SeqFlower(const float delta_time)
{
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
    if (m_mediator->GetIsCameraFixed())
    {
        gimmick->Reset();

        m_is_ground_active = false;
    }
}
