#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Item.h"


class ItemPool
{

public:

	ItemPool() {}

	~ItemPool();

private:

	// �쐬����e���f���̐�
	int m_item_create_num = 20;

	// ���f���̃x�N�^�[
	std::vector<std::shared_ptr<Item>> m_items;

public:

	// ���f���̊i�[
	void AddItem(std::shared_ptr<Item>& item);

	// �񊈐����A�C�e���̎擾
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