#include "GimmickLoad.h"
#include "../../[000]Stage/[001]Lane/Lane.h"


GimmickLoad::GimmickLoad()
{
	m_csv_plants
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/plant.csv");

	m_csv_trees
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/tree.csv");

	m_csv_sky_flowers
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/sky_flower.csv");

	//m_csv_gimmick_butterfly
	//	= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/butterfly.csv");

	LoadGimmickTypeInfo(m_csv_plants, m_plants);
	
	//LoadGimmickTypeInfo(m_csv_trees, m_trees);
	
	//LoadGimmickTypeInfo(m_csv_sky_flowers, m_sky_flowers);
}

GimmickLoad::~GimmickLoad()
{
	m_plants.clear();
	m_trees.clear();
	m_sky_flowers.clear();
}

void GimmickLoad::LoadGimmickTypeInfo(std::vector<std::vector<tnl::CsvCell>>& csv_gimmick
									 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmicks)
{
	// マップタイルの総数を取得
	int max_num = csv_gimmick.size();

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		Gimmick::sGimmickTypeInfo gimmick_info;

		gimmick_info.s_id = csv_gimmick[y][0].getInt();

		gimmick_info.s_model_path = csv_gimmick[y][1].getString();

		gimmick_info.s_texture_a_path = csv_gimmick[y][2].getString();

		gimmick_info.s_texture_b_path = csv_gimmick[y][3].getString();

		gimmick_info.s_type = static_cast<Gimmick::eGimmickType>(csv_gimmick[y][4].getInt());

		gimmicks.emplace_back(gimmick_info);
	}
}

const std::vector<Gimmick::sGimmickTypeInfo>& GimmickLoad::GetGimmicksType(Gimmick::eGimmickType type) const
{
	switch (type)
	{
	case Gimmick::eGimmickType::plant:

		return m_plants;

		break;

	case Gimmick::eGimmickType::tree:

		return m_trees;

		break;

	case Gimmick::eGimmickType::sky_flower:

		return m_sky_flowers;

		break;

	//case Gimmick::eGimmickType::butterfly:
	//
	//	return m_butterflys;
	//
	//	break;

	default:

		break;
	}
}



//Gimmick::sGimmickTypeInfo GimmickLoad::GetGimmickInfoById(int id)
//{
//	for (const Gimmick::sGimmickTypeInfo& gimmick : gimmick_type)
//	{
//		if (gimmick.s_id == id)
//		{
//			return gimmick;
//		}
//	}
//	// IDが見つからなかった場合のデフォルト値
//	return Gimmick::sGimmickTypeInfo();
//}

//void GimmickLoad::LoadGimmickVector()
//{
//	// csvファイルの読み込み
//	m_csv_gimmick_lane = tnl::LoadCsv<int>("csv/gimmick/gimmick_lane.csv");
//
//	Gimmick::sGimmick gimmick_lane;
//
//	// レーン配列の情報取得と格納
//	for (int y = 0; y < m_lane_height; y++)
//	{
//		for (int x = 0; x < m_lane_width; x++)
//		{
//			// －1は除外
//			if (m_csv_gimmick_lane[y][x] == -1)
//			{
//				continue;
//			}
//
//			gimmick_lane.s_id = m_csv_gimmick_lane[y][x];
//
//			gimmick_lane.s_pos
//				= tnl::Vector3(x * Lane::LANE_SIZE, 0, y * Lane::LANE_SIZE);
//
//			m_gimmick_lanes.emplace_back(gimmick_lane);
//		}
//	}
//}

