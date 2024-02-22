#include "GimmickLoad.h"
#include "../../[000]Stage/[001]Lane/Lane.h"


GimmickLoad::GimmickLoad()
{
	m_csv_ground_flowers
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/ground_flower.csv");

	m_csv_woods
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/wood.csv");

	m_csv_sky_flowers
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/sky_flower.csv");

	LoadGimmickTypeInfo(m_csv_ground_flowers, m_ground_flowers);
	
	LoadGimmickTypeInfo(m_csv_woods, m_woods);
	
	LoadGimmickTypeInfo(m_csv_sky_flowers, m_sky_flowers);
}

GimmickLoad::~GimmickLoad()
{
	m_csv_ground_flowers.clear();
	m_csv_woods.clear();
	m_csv_sky_flowers.clear();
	m_ground_flowers.clear();
	m_woods.clear();
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
	case Gimmick::eGimmickType::e_ground_flower:

		return m_ground_flowers;

		break;

	case Gimmick::eGimmickType::e_wood:

		return m_woods;

		break;

	case Gimmick::eGimmickType::e_sky_flower:

		return m_sky_flowers;

		break;

	default:

		break;
	}
}

