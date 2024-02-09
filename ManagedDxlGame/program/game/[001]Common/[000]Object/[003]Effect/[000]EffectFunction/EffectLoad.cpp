#include "EffectLoad.h"



EffectLoad::EffectLoad()
{
	LoadEffectTypeInfo();
}

EffectLoad::~EffectLoad()
{

}

void EffectLoad::LoadEffectTypeInfo()
{
	m_csv_effect_type_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/effect/effect.csv");

	// �}�b�v�^�C���̑������擾
	int max_num = m_csv_effect_type_info.size();

	// id�̐����擾�i�K�v���Ɏg�����߁j
	m_id_num = max_num - 1;

	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	for (int y = 1; y < max_num; ++y)
	{
		Effect::sEffectType effect_info;

		effect_info.s_id = m_csv_effect_type_info[y][0].getInt();

		effect_info.e_group 
			= static_cast<Effect::eEffectGroup>(m_csv_effect_type_info[y][1].getInt());

		effect_info.s_effect_path = m_csv_effect_type_info[y][2].getString();

		m_effect_type.emplace_back(effect_info);
	}
}