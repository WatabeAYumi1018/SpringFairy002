#include <random>
#include <algorithm>
#include "GimmickPool.h"


GimmickPool::~GimmickPool()
{
	m_gimmiks.clear();
}

void GimmickPool::AddGimmick(std::shared_ptr<Gimmick>& gimmick)
{
    m_gimmiks.emplace_back(gimmick);
}

std::shared_ptr<Gimmick> GimmickPool::GetNotActiveGimmick()
{
    for (std::shared_ptr<Gimmick>& gimmick : m_gimmiks)
    {
        // 非活性化アイテムを探す
        if (!gimmick->GetIsActive())
        {
            return gimmick;
        }
    }
    return nullptr;
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
