#include "ItemLoad.h"
#include "../../[000]Stage/[001]Lane/Lane.h"


ItemLoad::ItemLoad()
{
	LoadItemVector();

	LoadItemTypeInfo();
}

ItemLoad::~ItemLoad()
{
	m_item_type.clear();
}

Item::sItemType ItemLoad::GetItemInfoById(int id)
{
	for (const Item::sItemType& item : m_item_type)
	{
		if (item.s_id == id)
		{
			return item;
		}
	}
	// IDが見つからなかった場合のデフォルト値
	return Item::sItemType();
}

void ItemLoad::LoadItemVector()
{
	// csvファイルの読み込み
	m_csv_item_lane = tnl::LoadCsv<int>("csv/item/item_lane.csv");

	Item::sItem lane_item;

	// レーン配列の情報取得と格納
	for (int y = 0; y < m_lane_height; y++)
	{
		for (int x = 0; x < m_lane_width; x++)
		{
			// －1は除外
			if (m_csv_item_lane[y][x] == -1)
			{
				continue;
			}

			lane_item.s_id = m_csv_item_lane[y][x];

			lane_item.s_pos
				= tnl::Vector3(x * Lane::LANE_SIZE, 0, y * Lane::LANE_SIZE);

			m_item_lanes.emplace_back(lane_item);
		}
	}
}

void ItemLoad::LoadItemTypeInfo()
{
	m_csv_item_type_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/item/item_model.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_item_type_info.size();

	// idの数を取得（必要時に使うため）
	m_id_num = max_num -1;

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		Item::sItemType item_info;

		item_info.s_id = m_csv_item_type_info[y][0].getInt();

		item_info.s_model_path = m_csv_item_type_info[y][1].getString();

		item_info.s_texture_path = m_csv_item_type_info[y][2].getString();

		m_item_type.emplace_back(item_info);
	}
}

