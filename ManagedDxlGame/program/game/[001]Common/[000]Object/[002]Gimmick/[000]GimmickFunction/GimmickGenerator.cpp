#include <random>
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "../../../[003]Phase/StagePhase.h"
#include "../../[000]Stage/[002]Floor/Floor.h"
#include "GimmickGenerator.h"


void GimmickGenerator::Initialize()
{
    // poolギミックアイテム取得
    //m_gimmicks = m_mediator->GetPoolGimmick();
}

void GimmickGenerator::Update(const float delta_time)
{

    if(m_mediator->GetPlayerLookSideRight() 
       || m_mediator->GetPlayerLookSideLeft())
    {
        m_is_ground_active = true;
    }

    //tnl_sequence_.update(delta_time);

    if (m_is_ground_active)
    {
        CreateGimmick(delta_time);
    }
}

void GimmickGenerator::CreateGimmick(const float delta_time)
{
    StagePhase::eStagePhase stage_phase 
                = m_mediator->GetNowStagePhaseState();

    if (stage_phase == StagePhase::eStagePhase::e_flower
        || stage_phase == StagePhase::eStagePhase::e_fancy)
    {
        CalcGroundPos(delta_time, Gimmick::eGimmickType::plant);
    }
    if (stage_phase == StagePhase::eStagePhase::e_wood)
    {
        CalcGroundPos(delta_time,Gimmick::eGimmickType::tree);
    }
 // if (stage_phase == StagePhase::eStagePhase::e_fancy)
 // {
 //  	CalcGroundPos(delta_time, Gimmick::eGimmickType::);
 // }
    
    
    //CalcSkyRandomPos();
}

void GimmickGenerator::CalcGroundPos(const float delta_time, Gimmick::eGimmickType type)
{
    std::vector<std::shared_ptr<Gimmick>>& gimmicks
                 = m_mediator->GetGimmickTypePools(type);

    // ギミックのベクターの中身をランダムに並び替え
    std::shuffle(gimmicks.begin(), gimmicks.end()
                 , std::mt19937(std::random_device()()));

    // プレイヤーのforward方向ベクトル
    tnl::Vector3 forward = m_mediator->PlayerForward();
    forward.normalize();

    // forward方向に垂直なベクトルを計算
    tnl::Vector3 perpendicular;

    if (forward.z > 0)
    {
        if (m_mediator->GetPlayerLookSideRight())
        {
            perpendicular 
                = tnl::Vector3::Cross(forward, tnl::Vector3(0, 1, 0));
        }
        else if (m_mediator->GetPlayerLookSideLeft())
        {
            perpendicular 
                = tnl::Vector3::Cross(forward, tnl::Vector3(0, -1, 0));
        }
    }
    else
    {
        if (m_mediator->GetPlayerLookSideRight())
        {
            perpendicular 
                = tnl::Vector3::Cross(forward, tnl::Vector3(0, -1, 0));
        }
        else if (m_mediator->GetPlayerLookSideLeft())
        {
            perpendicular 
                = tnl::Vector3::Cross(forward, tnl::Vector3(0, 1, 0));
        }
    }

    perpendicular.normalize();

    tnl::Vector3 start_offset = perpendicular * 500.0f;
    tnl::Vector3 target_pos = m_mediator->GetCameraTargetPlayerPos();
  
    target_pos += start_offset;

    // ギミックを配置
    for (int i = 0; i < gimmicks.size(); ++i)
    {
        std::shared_ptr<Gimmick>& gimmick = gimmicks[i];

        // 活性化してなければ配置
        if (!gimmick->GetIsActive())
        {
            // 線分上のこのポイントからforward方向にランダムに配置するための距離
            float forward_distance
                = tnl::GetRandomDistributionFloat(600.0f, 1000.0f);

            // ギミックの新しい位置を計算
            tnl::Vector3 pos
                = target_pos + perpendicular * forward_distance;

            // y座標を地面の高さに設定
            pos.y = Floor::DRAW_DISTANCE;

            // ギミックを配置
            gimmick->SetPos(pos);
            gimmick->SetIsActive(true);

            // 次のポイントを設定
            target_pos += forward * 300.0f;
        }
        else
        {
             CheckGimmicks(delta_time, type, gimmick);
        }
    }
}

std::shared_ptr<Gimmick> GimmickGenerator::GetInactiveType(std::vector<std::shared_ptr<Gimmick>>& gimmicks)
{
    // GimmickPool から非アクティブな Gimmick を取得
    const std::shared_ptr<Gimmick> inactive_gimmick
        = m_mediator->GetNotActiveGimmickPool(gimmicks);

    if (inactive_gimmick)
    {
        return inactive_gimmick;
    }

    return nullptr;
}

void GimmickGenerator::GenerateGimmick(const float delta_time)
{
    //   // 1秒ごとに実行する
    //   static float elapsed_time = 0.0f;

    //   elapsed_time += delta_time;

    //   if (elapsed_time < 1.0f)
    //   {
       //	return;
       //}
    //   else
    //   {
    //       std::shared_ptr<Gimmick> active_item = m_mediator->GetNotActiveGimmickPool();

    //       //if (active_item
    //       //    && m_gimmick_lane.s_id == m_mediator->CurrentTargetGimmickLane().s_id)
    //       //{
    //       //    tnl::Vector3 pos = CalcRandomPos();

    //       //    active_item->SetPos(pos);

    //       //    active_item->SetIsActive(true);
    //       //}

    //       elapsed_time = 0.0f;
    //   }
}

//tnl::Vector3 GimmickGenerator::CalcRandomPos()
//{
//    tnl::Vector3 player_pos = m_mediator->GetCameraTargetPlayerPos();
//
//    float offset = 700.0f;
//
//    tnl::Vector3 random_pos
//        = tnl::Vector3(tnl::GetRandomDistributionFloat(player_pos.x - (offset * 2), player_pos.x - offset)
//            , 800
//            , player_pos.z + offset);
//
//    return random_pos;
//}

bool GimmickGenerator::SeqFlower(const float delta_time)
{
    //   // 足元idが1の場合移行
    //   if (m_gimmick_lane.s_id == 1)
    //   {
    //       m_is_flower_active = false;

       //	tnl_sequence_.change(&GimmickGenerator::SeqButterfly);
       //}

       // 5秒に一度だけ足元判定して処理軽減（アイテム生成はアバウトでokかと）
    TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
        {
            m_is_sky_flower_active = true;

            //// ターゲットの座標に対応するレーンを取得
            //m_gimmick_lane = m_mediator->CurrentTargetGimmickLane();
        });

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
        {
            GenerateGimmick(delta_time);
        });

    TNL_SEQ_CO_END;
}

bool GimmickGenerator::SeqButterfly(const float delta_time)
{
    // 足元idが1の場合移行
    //if (m_gimmick_lane.s_id == 0)
    //{
    //    m_is_flower_active = true;

    //    tnl_sequence_.change(&GimmickGenerator::SeqFlower);
    //}

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
        {
            GenerateGimmick(delta_time);
        });

    TNL_SEQ_CO_END;
}

void GimmickGenerator::CheckGimmicks(const float delta_time
                                     , Gimmick::eGimmickType type
                                     , std::shared_ptr<Gimmick> gimmick)
{
    // 活性化していて条件を満たしていればリセット
    if ((type == Gimmick::eGimmickType::plant
        && m_mediator->IsCameraFixed())
        || (type == Gimmick::eGimmickType::tree
            && m_mediator->IsCameraFixed())
        || (type == Gimmick::eGimmickType::sky_flower
            && gimmick->GetPos().y < m_mediator->GetPlayerPos().y - 750))
    {
        gimmick->Reset();

        m_is_ground_active = false;
    }
}


//void GimmickGenerator::ActiveGimmick()
//{
//	// プレイヤーの前方座標を取得
//	tnl::Vector3 player_forward_pos 
//        = m_mediator->GetPlayerPos() + m_mediator->PlayerForward() * 1500;
//
//	// カメラレーンIDが4またはカメラの状態がside_backの場合のみ処理
//	if (m_camera_lane.s_id == 4 || m_camera_lane.state == CameraState::side_back)
//	{
//		// 木のモデルを10個アクティブにする
//		for (int i = 0; i < 10; ++i)
//		{
//			// アクティブでない木のギミックを取得
//			auto treeGimmick = GetInactiveGimmick(m_gimmick_trees);
//			if (treeGimmick)
//			{
//				// プレイヤーの前方にランダムな位置を計算
//				tnl::Vector3 randomPos = CalcRandomPosAround(player_forward_pos);
//
//				// ギミックの位置を設定し、アクティブ化
//				treeGimmick->SetPosition(randomPos);
//				treeGimmick->SetActive(true);
//			}
//		}
//	}
//}
//
//tnl::Vector3 GimmickGenerator::CalcRandomPos(const tnl::Vector3& center_pos)
//{
//	// 中心位置からのランダムなオフセットを計算
//	float range = 500.0f; // ランダム配置の範囲
//	float offsetX = tnl::GetRandomDistributionFloat(-range, range);
//	float offsetZ = tnl::GetRandomDistributionFloat(-range, range);
//
//	return tnl::Vector3(center_pos.x + offsetX, center_pos.y, center_pos.z + offsetZ);
//}
//
//std::shared_ptr<Gimmick> GimmickGenerator::GetInactiveGimmick(const std::vector<Gimmick::sGimmickTypeInfo>& gimmickList)
//{
//	for (const auto& gimmickInfo : gimmickList)
//	{
//		auto gimmick = std::make_shared<Gimmick>(gimmickInfo);
//		if (!gimmick->GetIsActive())
//		{
//			return gimmick;
//		}
//	}
//	return nullptr; // アクティブでないギミックが見つからなかった場合
//}


//bool ItemGenerator::SeqCreate(const float delta_time)
//{
//    if (tnl_sequence_.isStart() && m_mediator->NextLaneMove())
//    {
//		GenerateItem();
//	}
//
//    if (m_mediator->NextLaneMove())
//    {
//		tnl_sequence_.change(&ItemGenerator::SeqDelete);
//	}
//
//    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});
//
//	TNL_SEQ_CO_END;
//}
//
//bool ItemGenerator::SeqDelete(const float delta_time)
//{
//    // アイテムプール内のすべてのアイテムを反復処理
//    for (std::shared_ptr<Item>& item : m_mediator->GetPoolItems())
//    {
//        // アイテムがアクティブな場合、リセットする
//        if (item->GetIsActive())
//        {
//            item->Reset();
//        }
//    }
//
//    tnl_sequence_.change(&ItemGenerator::SeqCreate);
//
//    TNL_SEQ_CO_END;
//}


//tnl::Vector3 ItemGenerator::CalcRandom()
//{
//    // ゲームのプレイエリアのサイズを設定
//    const int area_width = 1000;
//    const int area_height = 600;
//
//    // 乱数生成器の設定（静的に宣言）
//    static std::random_device rnd;
//    static std::mt19937 gen(rnd());
//
//    // 乱数の範囲を指定
//    std::uniform_real_distribution<float> dist_x(0.0f, static_cast<float>(area_width));
//    std::uniform_real_distribution<float> dist_y(0.0f, static_cast<float>(area_height));
//    std::uniform_real_distribution<float> dist_z(0.0f, 1.0f); // Z座標用
//
//    // ランダムな座標を生成
//    float random_x = dist_x(gen);
//    float random_y = dist_y(gen);
//    float random_z = dist_z(gen);
//
//    // シンプレックスノイズを使用して、最終的な座標を決定
//    float noise_value_x = wta::SimplexNoise3D({ random_x, 0, 0 });
//    float noise_value_y = wta::SimplexNoise3D({ 0, random_y, 0 });
//    float noise_value_z = wta::SimplexNoise3D({ 0, 0, random_z });
//
//    // プレイエリア内の範囲にノイズ値をスケーリング
//    float x = (noise_value_x + 1.0f) / 2.0f * area_width;
//    float y = (noise_value_y + 1.0f) / 2.0f * area_height;
//    float z = (noise_value_z + 1.0f) / 2.0f;
//
//    // 生成した座標を返す
//    return tnl::Vector3(x, y, z);
//}