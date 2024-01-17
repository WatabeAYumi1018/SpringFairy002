#include "../../../[002]Item/Item.h"
#include "PlayerCollision.h"
#include "../Player.h"


PlayerCollision::~PlayerCollision()
{
	m_items.clear();
}

void PlayerCollision::CollisionRegister()
{
	std::string key
		= typeid(Player).name() + std::string(typeid(Item).name());

	m_collision->registerIntersect( key
									, [this](std::shared_ptr<Player> player
									, std::shared_ptr<Item> item)
	{
		if(m_collision->IsIntersectSphere(player,player->GetCollisionSize()
										  , item, item->GetCollisionSize()))
		{
			// “–‚½‚è”»’è”­¶‡}
			item->SetIsHit(true);
			// •`‰æØ‚è‘Ö‚¦‡}
			item->SetIsDrawChange(true);
		}
	});
}

void PlayerCollision::CollisionCheck()
{
	for (std::shared_ptr<Item>& item : m_items)
	{
		m_collision->Intersect(m_player, item);
	}
}
