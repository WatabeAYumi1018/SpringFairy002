#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


class GimmickLoad
{

public:

	GimmickLoad();

	~GimmickLoad();

private:

	int m_id_num = 0;
	// レーン配列の高さ
	int m_lane_height = 0;
	// レーン配列の幅
	int m_lane_width = 0;

	// レーン配列読み取り専用（csvファイル）
	std::vector<std::vector<int>> m_csv_gimmick_lane;
	// レーン配列情報格納用
	std::vector<Gimmick::sGimmick> m_gimmick_lanes;
	// アイテムモデルの情報読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_gimmick_type_info;
	// アイテムモデルの情報格納用
	std::vector<Gimmick::sGimmickType> m_gimmick_type;


	// レーン配列の読み込み
	void LoadGimmickVector();

	// アイテムモデルの情報読み込み
	void LoadGimmickTypeInfo();

public:

	// アイテムモデルのid取得
	Gimmick::sGimmickType GetGimmickInfoById(int id);


	int GetIdNum() const{ return m_id_num; }

	const std::vector<Gimmick::sGimmick>& GetGimmickLane() const
	{
		return m_gimmick_lanes;
	}

	const std::vector<Gimmick::sGimmickType>& GetGimmickTypeInfo() const
	{
		return m_gimmick_type;
	}
};
