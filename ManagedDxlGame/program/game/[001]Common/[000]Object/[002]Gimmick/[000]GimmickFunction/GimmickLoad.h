#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


///////////////////////////////////////////////////////////////////////////
//
// ギミックのcsvファイルの読み込みクラス
//
///////////////////////////////////////////////////////////////////////////


class GimmickLoad
{

public:

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	GimmickLoad();
	~GimmickLoad();

	//---------------------------------------------------------------------------------//

private:
	
	//-----------------------------------メンバ変数------------------------------------//

	// ①草花のギミックモデル(静的)
	// csvファイルの情報
	std::vector<std::vector<tnl::CsvCell>> m_csv_ground_flowers;
	// 地上の草花のギミックモデル
	std::vector<Gimmick::sGimmickTypeInfo> m_ground_flowers;
	
	// ②樹木のギミックモデル(静的)
	// csvファイルの情報
	std::vector<std::vector<tnl::CsvCell>> m_csv_woods;
	// 樹木のギミックモデル
	std::vector<Gimmick::sGimmickTypeInfo> m_woods;
	
	// ③舞う花のギミックモデル(動的)
	// csvファイルの情報
	std::vector<std::vector<tnl::CsvCell>> m_csv_sky_flowers;
	// 舞う花のギミックモデル
	std::vector<Gimmick::sGimmickTypeInfo> m_sky_flowers;
	
	// ④蝶のギミックモデル(動的)
	// csvファイルの情報
	std::vector<std::vector<tnl::CsvCell>> m_csv_butterflys;
	// 蝶のギミックモデル
	std::vector<Gimmick::sGimmickTypeInfo> m_butterflys;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// モデルの情報読み込み
	// arg1 ... csvファイルのベクター
	// arg2 ... ギミックの情報
	void LoadGimmickTypeInfo(std::vector<std::vector<tnl::CsvCell>>& csv_gimmick
							 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmicks);

	//---------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// ギミックタイプの取得
	// arg ... ギミックの種類
	// ※ギミックタイプによって返すベクターが異なる処理のため、cppにて実装
	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmicksType(Gimmick::eGimmickType type) const;

	//---------------------------------------------------------------------------------//
};
