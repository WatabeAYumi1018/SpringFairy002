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
        // �񊈐����A�C�e����T��
        if (!item->GetIsActive())
        {
            return item;
        }
    }
    return nullptr;
}

//// �������A�C�e���̎擾
//std::shared_ptr<Item> ItemPool::GetActiveItem()
//{
//	std::vector<std::shared_ptr<Item>>::iterator active_items;
//
//    // ���������Ă��Ȃ��A�C�e����T��
//	active_items = std::find_if(m_items.begin(), m_items.end(),
//        		[](std::shared_ptr<Item> item) { return !item->GetIsActive(); });
//
//	// ���������Ă��Ȃ��A�C�e����������Ȃ������ꍇ
//	if (active_items == m_items.end())
//	{
//		return nullptr;
//	}
//
//	// ���������Ă��Ȃ��A�C�e��������������
//	(*active_items)->SetIsActive(true);
//
//	return (*active_items);
//}
