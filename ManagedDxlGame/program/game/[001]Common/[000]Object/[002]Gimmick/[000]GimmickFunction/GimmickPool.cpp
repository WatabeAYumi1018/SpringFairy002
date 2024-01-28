#include <random>
#include <algorithm>
#include "GimmickPool.h"


GimmickPool::~GimmickPool()
{
	m_gimmick_plants.clear();
    m_gimmick_trees.clear();
    m_gimmick_sky_flowers.clear();
    m_gimmick_butterflys.clear();
}

void GimmickPool::AddGimmick(std::shared_ptr<Gimmick>& gimmick
                             , Gimmick::eGimmickType type)
{
    switch (type)
    {
    case Gimmick::eGimmickType::plant:
    
        m_gimmick_plants.emplace_back(gimmick);
        
        break;
    
    case Gimmick::eGimmickType::tree:
    
        m_gimmick_trees.emplace_back(gimmick);
        
        break;
    
    case Gimmick::eGimmickType::sky_flower:

        m_gimmick_sky_flowers.emplace_back(gimmick);

        break;

    case Gimmick::eGimmickType::butterfly:

        m_gimmick_butterflys.emplace_back(gimmick);

		break;

    default:

		break;
    }
}

std::shared_ptr<Gimmick> GimmickPool::GetNotActiveGimmick(std::vector<std::shared_ptr<Gimmick>>& gimmicks)
{
    for (std::shared_ptr<Gimmick>& gimmick : gimmicks)
    {
        // 非活性化アイテムを探す
        if (!gimmick->GetIsActive())
        {
            return gimmick;
        }
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Gimmick>>& GimmickPool::GetGimmickPools(Gimmick::eGimmickType type) const
{
    switch (type)
    {
    case Gimmick::eGimmickType::plant:
		
		return m_gimmick_plants;

        break;

    case Gimmick::eGimmickType::tree:

        return m_gimmick_trees;

		break;

    case Gimmick::eGimmickType::sky_flower:

		return m_gimmick_sky_flowers;

        break;

    case Gimmick::eGimmickType::butterfly:

        return m_gimmick_butterflys;

        break;

    default:

		break;
    }
}


//// 活性化アイテムの取得
//std::shared_ptr<Item> ItemPool::GetActiveItem()
//{
//	std::vector<std::shared_ptr<Item>>::iterator active_items;
//
//    // 活性化していないアイテムを探す
//	active_items = std::find_if(m_items.begin(), m_items.end(),
//        		[](std::shared_ptr<Item> item) { return !item->GetIsActive(); });
//
//	// 活性化していないアイテムが見つからなかった場合
//	if (active_items == m_items.end())
//	{
//		return nullptr;
//	}
//
//	// 活性化していないアイテムを活性化する
//	(*active_items)->SetIsActive(true);
//
//	return (*active_items);
//}
