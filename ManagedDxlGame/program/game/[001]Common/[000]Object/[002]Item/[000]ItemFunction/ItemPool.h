#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Item.h"


class ItemPool
{

public:

	ItemPool() {}

	~ItemPool();

private:

	// 作成する各モデルの数
	int m_item_create_num = 20;

	// モデルのベクター
	std::vector<std::shared_ptr<Item>> m_items;

public:

	// モデルの格納
	void AddItem(std::shared_ptr<Item>& item);

	// 非活性化アイテムの取得
	std::shared_ptr<Item> GetNotActiveItem();


	int GetItemCreateNum() const
	{
		return m_item_create_num;
	}

	const std::vector<std::shared_ptr<Item>>& GetItems() const
	{
		return m_items;
	}
};