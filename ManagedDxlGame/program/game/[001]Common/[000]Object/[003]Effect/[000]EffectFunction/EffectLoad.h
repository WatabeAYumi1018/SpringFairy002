#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Effect.h"


class EffectLoad
{

public:

	EffectLoad();

	~EffectLoad();

private:

	// エフェクトの種類読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_effect_type_info;
	// エフェクトの種類情報格納用
	std::vector<Effect::sEffectType> m_effect_type;

	// エフェクトパスの情報読み込み
	void LoadEffectTypeInfo();

public:

	const std::vector<Effect::sEffectType>& GetEffectType() const
	{
		return m_effect_type; 
	}
};