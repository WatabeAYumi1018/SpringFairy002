#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Effect.h"


class EffectLoad
{

public:

	EffectLoad();

	~EffectLoad();

private:

	// �G�t�F�N�g�̎�ޓǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_effect_type_info;
	// �G�t�F�N�g�̎�ޏ��i�[�p
	std::vector<Effect::sEffectType> m_effect_type;

	// �G�t�F�N�g�p�X�̏��ǂݍ���
	void LoadEffectTypeInfo();

public:

	const std::vector<Effect::sEffectType>& GetEffectType() const
	{
		return m_effect_type; 
	}
};