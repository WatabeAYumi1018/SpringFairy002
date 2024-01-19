#include "../../../[002]Item/Item.h"
#include "PlayerCollision.h"
#include "../Player.h"
#include "../../[001]Partner/Partner.h"


PlayerCollision::~PlayerCollision()
{
	m_items.clear();
}

void PlayerCollision::CollisionRegisterPlayerToItem()
{
	// プレイヤーとアイテムの当たり判定
	std::string player_to_item_key
		= typeid(Player).name() + std::string(typeid(Item).name());

	m_collision_item->registerIntersect( player_to_item_key
										, [this](std::shared_ptr<Player> player
										, std::shared_ptr<Item> item)
	{
		if(m_collision_item->IsIntersectSphere(player,player->GetCollisionSize()
												, item, item->GetCollisionSize()))
		{
			// 当たり判定発生合図
			item->SetIsHit(true);
			// 描画切り替え合図
			item->SetIsDrawChange(true);
		}
	});
}

void PlayerCollision::CollisionRegisterMeshToItem()
{
	// メッシュとアイテムの当たり判定
	std::string mesh_to_item_key
		= typeid(dxe::Mesh).name() + std::string(typeid(Item).name());

	m_collision_mesh->registerIntersect(mesh_to_item_key
										, [this](std::shared_ptr<dxe::Mesh> mesh
										, std::shared_ptr<Item> item)
	{
		if (m_collision_mesh->IsIntersectSphere(mesh, m_player->GetMeshs().size()
												, item, item->GetCollisionSize()))
		{
			// 当たり判定発生合図
			item->SetIsHit(true);
			// 描画切り替え合図
			item->SetIsDrawChange(true);
		}
	});
}

void PlayerCollision::CollisionRegisterPlayerToPartner()
{
	// プレイヤーとパートナーの当たり判定
	std::string player_to_partner_key
		= typeid(Player).name() + std::string(typeid(Partner).name());

	m_collision_chara->registerIntersect(player_to_partner_key
										 , [this](std::shared_ptr<Player> player
										 , std::shared_ptr<Partner> partner)
	{
		if (m_collision_chara->IsIntersectSphere(player, player->GetCollisionSize()
												 , partner, partner->GetCollisionSize()))
		{
			// パートナーの座標補正
			m_collision_chara->CorrectSphere(player, player->GetCollisionSize()
											 , partner, partner->GetCollisionSize());
		}
	});
}

void PlayerCollision::CollisionCheck()
{
	// Player と Item の衝突判定
	for (std::shared_ptr<Item>& item : m_items)
	{
		m_collision_item->Intersect(m_player, item);
	}

	// PlayerのMesh と Item の衝突判定
	for (const std::shared_ptr<dxe::Mesh>& mesh : m_player->GetMeshs())
	{
		for (std::shared_ptr<Item>& item : m_items)
		{
			m_collision_mesh->Intersect(mesh, item);
		}
	}

	// Player と Partner の衝突判定
	m_collision_chara->Intersect(m_player, m_partner);
}
