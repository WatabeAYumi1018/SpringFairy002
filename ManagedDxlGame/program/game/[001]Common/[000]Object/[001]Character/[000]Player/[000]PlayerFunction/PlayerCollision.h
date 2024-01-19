#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../wta_library/wta_Collision.h"

class Player;
class Partner;
class Item;


class PlayerCollision
{

public:

	PlayerCollision() {}

	~PlayerCollision();

private:

	std::vector<std::shared_ptr<Item>> m_items;

	std::shared_ptr<Player> m_player = nullptr;

	std::shared_ptr<Partner> m_partner = nullptr;

	std::shared_ptr<wta::Collision<Player, Item>> m_collision_item = nullptr;

	std::shared_ptr<wta::Collision<dxe::Mesh,Item>> m_collision_mesh = nullptr;

	std::shared_ptr<wta::Collision<Player, Partner>> m_collision_chara = nullptr;

public:

	// “–‚½‚è”»’èˆ—‚Ì“o˜^
	void CollisionRegisterPlayerToItem();

	void CollisionRegisterMeshToItem();

	void CollisionRegisterPlayerToPartner();

	// ƒAƒCƒeƒ€‚Æ‚Ì“–‚½‚è”»’è
	void CollisionCheck();


	void SetItems(std::vector<std::shared_ptr<Item>>& items)
	{
		m_items = items;
	}
	
	void SetPlayer(std::shared_ptr<Player>& player)
	{
		m_player = player;
	}

	void SetPartner(std::shared_ptr<Partner>& partner)
	{
		m_partner = partner;
	}

	void SetCollision(std::shared_ptr<wta::Collision<Player, Item>>& collision)
	{
		m_collision_item = collision;
	}

	void SetCollision(std::shared_ptr<wta::Collision<dxe::Mesh, Item>>& collision)
	{
		m_collision_mesh = collision;
	}

	void SetCollision(std::shared_ptr<wta::Collision<Player, Partner>>& collision)
	{
		m_collision_chara = collision;
	}
};
