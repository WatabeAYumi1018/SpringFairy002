#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Effect.h"


///////////////////////////////////////////////////////////////////////////
//
// エフェクトパーティクルのcsvファイルの読み込みクラス
//
///////////////////////////////////////////////////////////////////////////


class EffectLoad
{

public:

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	EffectLoad();
	~EffectLoad();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// エフェクトの種類読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_effect_type_info;
	// エフェクトの種類情報格納用
	std::vector<Effect::sEffectType> m_effect_type;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// エフェクトパスの情報読み込み
	// tips ... 初期化時に一度だけ呼び出す
	void LoadEffectTypeInfo();

	//---------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// エフェクトの全種類取得
	const std::vector<Effect::sEffectType>& GetEffectType() const
	{
		return m_effect_type; 
	}

	//---------------------------------------------------------------------------------//
};