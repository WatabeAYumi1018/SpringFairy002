#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


class GimmickLoad
{

public:

	GimmickLoad();

	~GimmickLoad();

private:
	
	// ①草花のギミックモデル(静的)
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_plants;
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_plants;
	// ②樹木のギミックモデル(静的)
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_trees;
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_trees;
	// ③舞う花のギミックモデル(動的)
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_sky_flowers;
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_sky_flowers;
	// ④蝶のギミックモデル(動的)
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_butterfly;
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_butterfly;


	// アイテムモデルの情報読み込み
	void LoadGimmickTypeInfo(std::vector<std::vector<tnl::CsvCell>>& csv_gimmick
							 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmicks
							 ,Gimmick::eGimmickType type);

public:

	// アイテムモデルのid取得
	Gimmick::sGimmickTypeInfo GetGimmickInfoById(int id);

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypePlants() const
	{
		return m_gimmick_plants;
	}

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeTrees() const
	{
		return m_gimmick_trees;
	}

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeSkyFlowers() const
	{
		return m_gimmick_sky_flowers;
	}

};

//int m_id_num = 0;

//// レーン配列の高さ
//int m_lane_height = 0;
//// レーン配列の幅
//int m_lane_width = 0;

// ギミックはレーン配列でなく、カメラ状態で操作する方が合理的かも。（処理負荷軽減）

//// レーン配列読み取り専用（csvファイル）
//std::vector<std::vector<int>> m_csv_gimmick_lane;
//// レーン配列情報格納用
//std::vector<Gimmick::sGimmick> m_gimmick_lanes;

//// モデルの情報読み取り専用（csvファイル）
//std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_type_info;
//// アイテムモデルの情報格納用
//std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_type;


//// レーン配列の読み込み
//void LoadGimmickVector();

//int GetIdNum() const { return m_id_num; }

//const std::vector<Gimmick::sGimmick>& GetGimmickLane() const
//{
//	return m_gimmick_lanes;
//}

//const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeInfo() const
//{
//	return m_gimmick_type;
//}
