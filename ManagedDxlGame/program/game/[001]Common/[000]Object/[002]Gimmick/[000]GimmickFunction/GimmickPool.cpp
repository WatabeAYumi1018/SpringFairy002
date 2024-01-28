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
        // �񊈐����A�C�e����T��
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
