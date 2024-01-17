#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Item.h"


class ItemLoad
{

public:

	ItemLoad();

	~ItemLoad();

private:

	int m_id_num = 0;
	// ���[���z��̍���
	int m_lane_height = 0;
	// ���[���z��̕�
	int m_lane_width = 0;

	// ���[���z��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<int>> m_csv_item_lane;
	// ���[���z����i�[�p
	std::vector<Item::sItem> m_item_lanes;
	// �A�C�e�����f���̏��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_item_type_info;
	// �A�C�e�����f���̏��i�[�p
	std::vector<Item::sItemType> m_item_type;


	// ���[���z��̓ǂݍ���
	void LoadItemVector();

	// �A�C�e�����f���̏��ǂݍ���
	void LoadItemTypeInfo();

public:

	// �A�C�e�����f����id�擾
	Item::sItemType GetItemInfoById(int id);


	int GetIdNum() const{ return m_id_num; }

	const std::vector<Item::sItem>& GetItemLane() const
	{
		return m_item_lanes;
	}

	const std::vector<Item::sItemType>& GetItemTypeInfo() const
	{
		return m_item_type;
	}
};
