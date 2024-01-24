#include "GimmickLoad.h"
#include "../../[000]Stage/[001]Lane/Lane.h"


GimmickLoad::GimmickLoad()
{
	LoadGimmickVector();

	LoadGimmickTypeInfo();
}

GimmickLoad::~GimmickLoad()
{
	m_gimmick_type.clear();
}

Gimmick::sGimmickType GimmickLoad::GetGimmickInfoById(int id)
{
	for (const Gimmick::sGimmickType& item : m_gimmick_type)
	{
		if (item.s_id == id)
		{
			return item;
		}
	}
	// IDが見つからなかった場合のデフォルト値
	return Gimmick::sGimmickType();
}

void GimmickLoad::LoadGimmickVector()
{
	// csvファイルの読み込み
	m_csv_gimmick_lane = tnl::LoadCsv<int>("csv/gimmick/gimmick_lane.csv");

	Gimmick::sGimmick gimmick_lane;

	// レーン配列の情報取得と格納
	for (int y = 0; y < m_lane_height; y++)
	{
		for (int x = 0; x < m_lane_width; x++)
		{
			// －1は除外
			if (m_csv_gimmick_lane[y][x] == -1)
			{
				continue;
			}

			gimmick_lane.s_id = m_csv_gimmick_lane[y][x];

			gimmick_lane.s_pos
				= tnl::Vector3(x * Lane::LANE_SIZE, 0, y * Lane::LANE_SIZE);

			m_gimmick_lanes.emplace_back(gimmick_lane);
		}
	}
}

void GimmickLoad::LoadGimmickTypeInfo()
{
	m_csv_gimmick_type_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/gimmick_model.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_gimmick_type_info.size();

	// idの数を取得（必要時に使うため）
	m_id_num = max_num -1;

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		Gimmick::sGimmickType gimmick_info;

		gimmick_info.s_id = m_csv_gimmick_type_info[y][0].getInt();

		gimmick_info.s_model_path = m_csv_gimmick_type_info[y][1].getString();

		gimmick_info.s_texture_path = m_csv_gimmick_type_info[y][2].getString();

		m_gimmick_type.emplace_back(gimmick_info);
	}
}

