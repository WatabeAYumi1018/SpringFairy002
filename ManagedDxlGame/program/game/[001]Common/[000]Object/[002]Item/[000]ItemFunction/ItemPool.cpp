#include <random>
#include <algorithm>
#include "ItemPool.h"


ItemPool::~ItemPool()
{
	m_items.clear();
}

void ItemPool::AddItem(std::shared_ptr<Item>& item)
{
    m_items.emplace_back(item);
}

std::shared_ptr<Item> ItemPool::GetNotActiveItem()
{
    for (std::shared_ptr<Item>& item : m_items)
    {
        // 非活性化アイテムを探す
        if (!item->GetIsActive())
        {
            return item;
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
