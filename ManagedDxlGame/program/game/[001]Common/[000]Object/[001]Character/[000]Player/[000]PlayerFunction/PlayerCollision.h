#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../wta_library/wta_Collision.h"

class Player;
class Item;


class PlayerCollision
{

public:

	PlayerCollision() {}

	~PlayerCollision();

private:

	std::vector<std::shared_ptr<Item>> m_items;

	std::shared_ptr<Player> m_player = nullptr;

	std::shared_ptr<wta::Collision<Player, Item>> m_collision = nullptr;

public:

	// 当たり判定処理の登録
	void CollisionRegister();

	// アイテムとの当たり判定
	void CollisionCheck();


	void SetItems(std::vector<std::shared_ptr<Item>>& items)
	{
		m_items = items;
	}
	void SetPlayer(std::shared_ptr<Player>& player)
	{
		m_player = player;
	}

	void SetCollision(std::shared_ptr<wta::Collision<Player, Item>>& collision)
	{
		m_collision = collision;
	}
};
