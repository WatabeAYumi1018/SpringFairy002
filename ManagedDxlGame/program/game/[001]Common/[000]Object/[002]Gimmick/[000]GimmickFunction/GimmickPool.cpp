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
    case Gimmick::eGimmickType::ground_flower:
    
        m_gimmick_plants.emplace_back(gimmick);
        
        break;
    
    case Gimmick::eGimmickType::wood:
    
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
        // ”ñŠˆ«‰»ƒAƒCƒeƒ€‚ð’T‚·
        if (!gimmick->GetIsActive())
        {
            return gimmick;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Gimmick>>& GimmickPool::GetGimmickPools(Gimmick::eGimmickType type)
{
    switch (type)
    {
    case Gimmick::eGimmickType::ground_flower:
		
		return m_gimmick_plants;

        break;

    case Gimmick::eGimmickType::wood:

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
