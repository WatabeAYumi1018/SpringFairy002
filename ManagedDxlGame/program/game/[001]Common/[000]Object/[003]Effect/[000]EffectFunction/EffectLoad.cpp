#include "EffectLoad.h"



EffectLoad::EffectLoad()
{
	LoadEffectTypeInfo();
}

EffectLoad::~EffectLoad()
{
	m_csv_effect_type_info.clear();
	m_effect_type.clear();
}

void EffectLoad::LoadEffectTypeInfo()
{
	m_csv_effect_type_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/effect/effect.csv");

	// 0çsñ⁄ÇÕê‡ñæï∂Ç»ÇÃÇ≈ì«Ç›îÚÇŒÇ∑
	for (int y = 1; y < m_csv_effect_type_info.size(); ++y)
	{
		Effect::sEffectType effect_info;

		effect_info.s_id = m_csv_effect_type_info[y][0].getInt();

		effect_info.s_effect_path = m_csv_effect_type_info[y][1].getString().c_str();

		m_effect_type.emplace_back(effect_info);
	}
}