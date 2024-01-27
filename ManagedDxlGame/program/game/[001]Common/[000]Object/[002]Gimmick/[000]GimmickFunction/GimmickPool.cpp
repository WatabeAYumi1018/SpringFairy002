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
        // �񊈐����A�C�e����T��
        if (!gimmick->GetIsActive())
        {
            return gimmick;
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
