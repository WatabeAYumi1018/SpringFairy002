#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../wta_library/wta_Collision.h"

class Player;
class Partner;
class Gimmick;


class PlayerCollision
{

public:

	PlayerCollision() {}

	~PlayerCollision();

private:

	bool m_is_partner_in = false;

	std::vector<std::shared_ptr<Gimmick>> m_gimmicks;

	std::shared_ptr<Player> m_player = nullptr;

	std::shared_ptr<Partner> m_partner = nullptr;

	std::shared_ptr<wta::Collision<Player, Gimmick>> m_collision_gimmick = nullptr;

	std::shared_ptr<wta::Collision<dxe::Mesh,Gimmick>> m_collision_mesh = nullptr;

	std::shared_ptr<wta::Collision<Player, Partner>> m_collision_chara = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

public:

	// “–‚½‚è”»’èˆ—‚Ì“o˜^
	void CollisionRegisterPlayerToGimmick();

	void CollisionRegisterMeshToGimmick();

	void CollisionRegisterPlayerToPartner();

	// ƒAƒCƒeƒ€‚Æ‚Ì“–‚½‚è”»’è
	void CollisionCheck();


	void SetGimmicks(std::vector<std::shared_ptr<Gimmick>>& gimmicks)
	{
		m_gimmicks = gimmicks;
	}
	
	void SetPlayer(std::shared_ptr<Player>& player)
	{
		m_player = player;
	}

	void SetPartner(std::shared_ptr<Partner>& partner)
	{
		m_partner = partner;
	}

	void SetCollision(std::shared_ptr<wta::Collision<Player, Gimmick>>& collision)
	{
		m_collision_gimmick = collision;
	}

	void SetCollision(std::shared_ptr<wta::Collision<dxe::Mesh, Gimmick>>& collision)
	{
		m_collision_mesh = collision;
	}

	void SetCollision(std::shared_ptr<wta::Collision<Player, Partner>>& collision)
	{
		m_collision_chara = collision;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
