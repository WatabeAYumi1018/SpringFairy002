#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "GimmickGenerator.h"


void GimmickGenerator::Initialize()
{
	// poolギミックアイテム取得
    m_gimmicks = m_mediator->GetPoolGimmick();

    m_gimmick_plants = m_mediator->GetGimmickLoadTypePlants();

    m_gimmick_trees = m_mediator->GetGimmickLoadTypeTrees();

    m_gimmick_sky_flowers = m_mediator->GetGimmickLoadTypeSkyFlowers();

    // プールしたモデルを取得して、アクティブにする
    // ランダムな座標を算出
    // その位置に一気に描画する
    for (Gimmick::sGimmickTypeInfo gimmick_type : m_gimmick_plants)
    {
        // ランダムな座標を算出
        m_pos = CalcGroundRandomPos();

        
    }

}

void GimmickGenerator::Update(const float delta_time)
{
    // 現在のカメラレーンを取得
    m_camera_lane = m_mediator->CurrentCameraLane();

    tnl_sequence_.update(delta_time);

    CheckGimmicks(delta_time);
}

void GimmickGenerator::CreateGimmick()
{
    switch (m_camera_lane.s_id)
    {
    // サイドビューの時は限定
    case 3:
    case 4:

        break;

    // それ以外は恒常
    default:

    	break;

    }

}

tnl::Vector3 GimmickGenerator::CalcGroundRandomPos()
{
    //現在のカメラレーンをpairで取得
    std::pair<int, int> current_pos;

    current_pos.first = static_cast<int>(m_camera_lane.s_pos.x);
    current_pos.second = static_cast<int>(m_camera_lane.s_pos.z);

    // 現在のレーンのワールド座標を取得
    tnl::Vector3 current_grid_pos 
        = wta::ConvertGridIntToFloat(current_pos, Lane::LANE_SIZE);

    // レーンの中点を算出
    current_grid_pos.x += Lane::LANE_SIZE / 2;
    current_grid_pos.z += Lane::LANE_SIZE / 2;
;
    float offset = Lane::LANE_SIZE / 2;

    //　中点を基準にグリッドサイズの範囲でランダムな座標を算出
	tnl::Vector3 random_pos
        = {tnl::GetRandomDistributionFloat(current_grid_pos.x - offset , current_grid_pos.x + offset)
           , 0
           , tnl::GetRandomDistributionFloat(current_grid_pos.z - offset, current_grid_pos.z + offset)};

	return random_pos;
}

void GimmickGenerator::CheckGimmicks(const float delta_time)
{
    // アイテムプール内のすべてのアイテムを反復処理
    for (std::shared_ptr<Gimmick>& item : m_gimmicks)
    {
		// アクティブアイテムかつ条件を満たせばリセット
        if (item->GetIsActive() 
            && item->GetPos().y < m_mediator->GetPlayerPos().y - 750)
        {
			item->Reset();
		}
	}
}

void GimmickGenerator::GenerateGimmick(const float delta_time)
{
    // 1秒ごとに実行する
    static float elapsed_time = 0.0f;

    elapsed_time += delta_time;

    if (elapsed_time < 1.0f)
    {
		return;
	}

    else
    {
        std::shared_ptr<Gimmick> active_item = m_mediator->GetNotActiveGimmickPool();

        //if (active_item
        //    && m_gimmick_lane.s_id == m_mediator->CurrentTargetGimmickLane().s_id)
        //{
        //    tnl::Vector3 pos = CalcRandomPos();

        //    active_item->SetPos(pos);

        //    active_item->SetIsActive(true);
        //}

        elapsed_time = 0.0f;
    }
 }

tnl::Vector3 GimmickGenerator::CalcRandomPos()
{
    tnl::Vector3 player_pos = m_mediator->GetCameraTargetPlayerPos();

    float offset = 700.0f;

    tnl::Vector3 random_pos
        = tnl::Vector3(tnl::GetRandomDistributionFloat(player_pos.x - (offset * 2), player_pos.x - offset)
                       ,800
                       ,player_pos.z + offset);

    return random_pos;
}

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
        m_is_flower_active = true;

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


//tnl::Vector3 player_back_pos = m_mediator->PlayerBack();

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