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
	// ID��������Ȃ������ꍇ�̃f�t�H���g�l
	return Item::sItemType();
}

void ItemLoad::LoadItemVector()
{
	// csv�t�@�C���̓ǂݍ���
	m_csv_item_lane = tnl::LoadCsv<int>("csv/item/item_lane.csv");

	Item::sItem lane_item;

	// ���[���z��̏��擾�Ɗi�[
	for (int y = 0; y < m_lane_height; y++)
	{
		for (int x = 0; x < m_lane_width; x++)
		{
			// �|1�͏��O
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

	// �}�b�v�^�C���̑������擾
	int max_num = m_csv_item_type_info.size();

	// id�̐����擾�i�K�v���Ɏg�����߁j
	m_id_num = max_num -1;

	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	for (int y = 1; y < max_num; ++y)
	{
		Item::sItemType item_info;

		item_info.s_id = m_csv_item_type_info[y][0].getInt();

		item_info.s_model_path = m_csv_item_type_info[y][1].getString();

		item_info.s_texture_path = m_csv_item_type_info[y][2].getString();

		m_item_type.emplace_back(item_info);
	}
}

