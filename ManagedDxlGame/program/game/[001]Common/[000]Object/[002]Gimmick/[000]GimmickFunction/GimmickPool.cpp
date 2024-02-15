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
    case Gimmick::eGimmickType::e_ground_flower:
    
        m_gimmick_plants.emplace_back(gimmick);
        
        break;
    
    case Gimmick::eGimmickType::e_wood:
    
        m_gimmick_trees.emplace_back(gimmick);
        
        break;
    
    case Gimmick::eGimmickType::e_sky_flower:

        m_gimmick_sky_flowers.emplace_back(gimmick);

        break;

    case Gimmick::eGimmickType::e_butterfly:

        m_gimmick_butterflys.emplace_back(gimmick);

		break;

    default:

		break;
    }
}

std::vector<std::shared_ptr<Gimmick>>& GimmickPool::GetGimmickPools(Gimmick::eGimmickType type)
{
    switch (type)
    {
    case Gimmick::eGimmickType::e_ground_flower:
		
		return m_gimmick_plants;

        break;

    case Gimmick::eGimmickType::e_wood:

        return m_gimmick_trees;

		break;

    case Gimmick::eGimmickType::e_sky_flower:

		return m_gimmick_sky_flowers;

        break;

    case Gimmick::eGimmickType::e_butterfly:

        return m_gimmick_butterflys;

        break;

    default:

		break;
    }
}
