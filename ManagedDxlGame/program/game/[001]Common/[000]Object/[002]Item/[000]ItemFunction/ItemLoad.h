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
	// レーン配列の高さ
	int m_lane_height = 0;
	// レーン配列の幅
	int m_lane_width = 0;

	// レーン配列読み取り専用（csvファイル）
	std::vector<std::vector<int>> m_csv_item_lane;
	// レーン配列情報格納用
	std::vector<Item::sItem> m_item_lanes;
	// アイテムモデルの情報読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_item_type_info;
	// アイテムモデルの情報格納用
	std::vector<Item::sItemType> m_item_type;


	// レーン配列の読み込み
	void LoadItemVector();

	// アイテムモデルの情報読み込み
	void LoadItemTypeInfo();

public:

	// アイテムモデルのid取得
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
