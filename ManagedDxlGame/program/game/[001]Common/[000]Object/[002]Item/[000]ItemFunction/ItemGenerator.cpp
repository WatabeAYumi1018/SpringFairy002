#include "ItemGenerator.h"
#include "../../../[002]Mediator/Mediator.h"


void ItemGenerator::Initialize()
{
	// レーン情報を取得
    m_items = m_mediator->GetPoolItems();
}

void ItemGenerator::Update(const float delta_time)
{
    tnl_sequence_.update(delta_time);

    CheckItems(delta_time);
}

void ItemGenerator::CheckItems(const float delta_time)
{
    // アイテムプール内のすべてのアイテムを反復処理
    for (std::shared_ptr<Item>& item : m_items)
    {
		// アクティブアイテムかつ条件を満たせばリセット
        if (item->GetIsActive() 
            && item->GetPos().y < m_mediator->GetPlayerPos().y - 750)
        {
			item->Reset();
		}
	}
}

void ItemGenerator::GenerateItem(const float delta_time)
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
        std::shared_ptr<Item> active_item = m_mediator->GetNotActiveItemPool();

        if (active_item
            && m_item_lane.s_id == m_mediator->CurrentTargetItemLane().s_id)
        {
            tnl::Vector3 pos = CalcRandomPos();

            active_item->SetPos(pos);

            active_item->SetIsActive(true);
        }

        elapsed_time = 0.0f;
    }
 }

tnl::Vector3 ItemGenerator::CalcRandomPos()
{
    tnl::Vector3 player_pos = m_mediator->GetCameraTargetPlayerPos();

    float offset = 700.0f;

    tnl::Vector3 random_pos
        = tnl::Vector3(tnl::GetRandomDistributionFloat(player_pos.x - (offset * 2), player_pos.x - offset)
                       ,800
                       ,player_pos.z + offset);

    return random_pos;
}

bool ItemGenerator::SeqFlower(const float delta_time)
{
    // 足元idが1の場合移行
    if (m_item_lane.s_id == 1)
    {
        m_is_flower_active = false;

		tnl_sequence_.change(&ItemGenerator::SeqButterfly);
	}

    // 5秒に一度だけ足元判定して処理軽減（アイテム生成はアバウトでokかと）
    TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
    {
        m_is_flower_active = true;

        // ターゲットの座標に対応するレーンを取得
        m_item_lane = m_mediator->CurrentTargetItemLane();
    });

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() 
    {
		GenerateItem(delta_time);
    });

	TNL_SEQ_CO_END;
}

bool ItemGenerator::SeqButterfly(const float delta_time)
{
    // 足元idが1の場合移行
    if (m_item_lane.s_id == 0)
    {
        m_is_flower_active = true;

        tnl_sequence_.change(&ItemGenerator::SeqFlower);
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
    {
        GenerateItem(delta_time);
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