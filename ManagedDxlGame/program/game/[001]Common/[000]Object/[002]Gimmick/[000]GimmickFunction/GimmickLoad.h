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

	GimmickLoad();

	~GimmickLoad();

private:
	
	// �@草花のギミックモデル(静的)
	std::vector<std::vector<tnl::CsvCell>> m_csv_ground_flowers;
	std::vector<Gimmick::sGimmickTypeInfo> m_ground_flowers;
	// �A樹木のギミックモデル(静的)
	std::vector<std::vector<tnl::CsvCell>> m_csv_woods;
	std::vector<Gimmick::sGimmickTypeInfo> m_woods;
	// �B舞う花のギミックモデル(動的)
	std::vector<std::vector<tnl::CsvCell>> m_csv_sky_flowers;
	std::vector<Gimmick::sGimmickTypeInfo> m_sky_flowers;
	// �C蝶のギミックモデル(動的)
	std::vector<std::vector<tnl::CsvCell>> m_csv_butterflys;
	std::vector<Gimmick::sGimmickTypeInfo> m_butterflys;


	// モデルの情報読み込み
	void LoadGimmickTypeInfo(std::vector<std::vector<tnl::CsvCell>>& csv_gimmick
							 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmicks);

public:

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmicksType(Gimmick::eGimmickType type) const;
};
