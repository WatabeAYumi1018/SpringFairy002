#include "GimmickLoad.h"
#include "../../[000]Stage/[001]Lane/Lane.h"


GimmickLoad::GimmickLoad()
{
	m_csv_gimmick_plants
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/plant.csv");

	m_csv_gimmick_trees
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/tree.csv");

	m_csv_gimmick_sky_flowers
		= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/sky_flower.csv");

	//m_csv_gimmick_butterfly
	//	= tnl::LoadCsv<tnl::CsvCell>("csv/gimmick/butterfly.csv");

	LoadGimmickTypeInfo(m_csv_gimmick_plants
						, m_gimmick_plants
						,Gimmick::eGimmickType::plant);
	
	LoadGimmickTypeInfo(m_csv_gimmick_trees
						, m_gimmick_trees
						,Gimmick::eGimmickType::tree);
	
	LoadGimmickTypeInfo(m_csv_gimmick_sky_flowers
						, m_gimmick_sky_flowers
						, Gimmick::eGimmickType::sky_flower);
}

GimmickLoad::~GimmickLoad()
{
	m_gimmick_plants.clear();
	m_gimmick_trees.clear();
	m_gimmick_sky_flowers.clear();
}

Gimmick::sGimmickTypeInfo GimmickLoad::GetGimmickInfoById(int id)
{
	//for (const Gimmick::sGimmickTypeInfo& item : m_gimmick_type)
	//{
	//	if (item.s_id == id)
	//	{
	//		return item;
	//	}
	//}
	// IDが見つからなかった場合のデフォルト値
	return Gimmick::sGimmickTypeInfo();
}

void GimmickLoad::LoadGimmickTypeInfo(std::vector<std::vector<tnl::CsvCell>>& csv_gimmick
									 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmicks
									 ,Gimmick::eGimmickType type)
{
	// マップタイルの総数を取得
	int max_num = csv_gimmick.size();

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		Gimmick::sGimmickTypeInfo gimmick_info;

		gimmick_info.s_id = csv_gimmick[y][0].getInt();

		gimmick_info.s_model_path = csv_gimmick[y][1].getString();

		gimmick_info.s_texture_path = csv_gimmick[y][2].getString();

		gimmick_info.s_type = type;

		gimmicks.emplace_back(gimmick_info);
	}
}
//
//void GimmickGenerator::ActivateTreeGimmicks()
//{
//	// プレイヤーの前方座標を取得
//	tnl::Vector3 playerForwardPos = m_mediator->GetPlayerPos() + m_mediator->GetPlayerForward() * 1500; // 1500は前方への距離オフセット
//
//	// カメラレーンIDが4またはカメラの状態がside_backの場合のみ処理
//	if (m_camera_lane.s_id == 4 || m_camera_lane.state == CameraState::side_back)
//	{
//		// 木のモデルを10個アクティブにする
//		for (int i = 0; i < 10; ++i)
//		{
//			// アクティブでない木のギミックを取得
//			auto treeGimmick = GetInactiveGimmick(m_gimmick_trees);
//			if (treeGimmick)
//			{
//				// プレイヤーの前方にランダムな位置を計算
//				tnl::Vector3 randomPos = CalcRandomPosAround(playerForwardPos);
//
//				// ギミックの位置を設定し、アクティブ化
//				treeGimmick->SetPosition(randomPos);
//				treeGimmick->SetActive(true);
//			}
//		}
//	}
//}
//
//tnl::Vector3 GimmickGenerator::CalcRandomPosAround(const tnl::Vector3& centerPos)
//{
//	// 中心位置からのランダムなオフセットを計算
//	float range = 500.0f; // ランダム配置の範囲
//	float offsetX = tnl::GetRandomDistributionFloat(-range, range);
//	float offsetZ = tnl::GetRandomDistributionFloat(-range, range);
//
//	return tnl::Vector3(centerPos.x + offsetX, centerPos.y, centerPos.z + offsetZ);
//}
//
//std::shared_ptr<Gimmick> GimmickGenerator::GetInactiveGimmick(const std::vector<Gimmick::sGimmickTypeInfo>& gimmickList)
//{
//	for (const auto& gimmickInfo : gimmickList)
//	{
//		auto gimmick = std::make_shared<Gimmick>(gimmickInfo);
//		if (!gimmick->GetIsActive())
//		{
//			return gimmick;
//		}
//	}
//	return nullptr; // アクティブでないギミックが見つからなかった場合
//}

//void GimmickLoad::LoadGimmickVector()
//{
//	// csvファイルの読み込み
//	m_csv_gimmick_lane = tnl::LoadCsv<int>("csv/gimmick/gimmick_lane.csv");
//
//	Gimmick::sGimmick gimmick_lane;
//
//	// レーン配列の情報取得と格納
//	for (int y = 0; y < m_lane_height; y++)
//	{
//		for (int x = 0; x < m_lane_width; x++)
//		{
//			// －1は除外
//			if (m_csv_gimmick_lane[y][x] == -1)
//			{
//				continue;
//			}
//
//			gimmick_lane.s_id = m_csv_gimmick_lane[y][x];
//
//			gimmick_lane.s_pos
//				= tnl::Vector3(x * Lane::LANE_SIZE, 0, y * Lane::LANE_SIZE);
//
//			m_gimmick_lanes.emplace_back(gimmick_lane);
//		}
//	}
//}

