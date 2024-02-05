#include "../../../wta_library/wta_Astar.h"
#include "../../../wta_library/wta_Collision.h"
#include "../[000]Object/[000]Stage/[000]SkyBox/SkyBox.h"
#include "../[000]Object/[000]Stage/[000]SkyBox/CinemaBack.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneLoad.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneMove.h"
#include "../[000]Object/[000]Stage/[002]Floor/Floor.h"
#include "../[000]Object/[000]Stage/[003]Model/Model.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelLoad.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelPool.h"
#include "../[000]Object/[001]Character/[000]Player/Player.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerLoad.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerMove.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerDraw.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerSkill.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerCollision.h"
#include "../[000]Object/[001]Character/[000]Player/[001]CinemaPlayer/CinemaPlayer.h"
#include "../[000]Object/[001]Character/[001]Partner/Partner.h"
#include "../[000]Object/[001]Character/[001]Partner/[000]PartnerFunction/PartnerLoad.h"
#include "../[000]Object/[001]Character/[001]Partner/[000]PartnerFunction/PartnerMove.h"
#include "../[000]Object/[001]Character/[001]Partner/[000]PartnerFunction/PartnerDraw.h"
#include "../[000]Object/[001]Character/[002]CameraTargetPlayer/CameraTargetPlayer.h"
#include "../[000]Object/[001]Character/[002]CameraTargetPlayer/CinemaCameraTarget.h"
#include "../[000]Object/[001]Character/[003]Butterfly/Butterfly.h"
#include "../[000]Object/[001]Character/[003]Butterfly/[000]ButterflyFunction/ButterflyLoad.h"
#include "../[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickLoad.h"
#include "../[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickPool.h"
#include "../[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickGenerator.h"
#include "../[000]Object/[003]Effect/Effect.h"
#include "../[000]Object/[003]Effect/[000]EffectFunction/EffectLoad.h"
#include "../[000]Object/[004]Score/Score.h"
#include "../[000]Object/[005]Event/[001]Text/Text.h"
#include "../[000]Object/[005]Event/[001]Text/[000]TextFunction/TextLoad.h"
#include "../[000]Object/[005]Event/[001]Text/[000]TextFunction/TextDraw.h"
#include "../[000]Object//[005]Event/[002]CharaGraph/CharaGraph.h"
#include "../[000]Object//[005]Event/[002]CharaGraph/[000]CharaGraphFunction/CharaGraphLoad.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/[000]CharaGraphFunction/CharaGraphDraw.h"
#include "../[001]Camera/GameCamera.h"
#include "../[001]Camera/CinemaCamera.h"
#include "../[001]Camera/[000]CameraFunction/CameraLoad.h"
#include "../[002]Mediator/Mediator.h"
#include "../[004]ScreenShot/ScreenShot.h"
#include "PlayFactory.h"


PlayFactory::PlayFactory()
{
	CreateObject();

	SetObjectReference();

	StorageObjectGameCamera();

	StorageObjectCinemaCamera();

	//PoolGimmickObject();

	m_laneMove->GetAutoMove();
}

PlayFactory::~PlayFactory()
{
	m_objects_gameCamera.clear();
}

void PlayFactory::CreateObject()
{
	m_astar = std::make_shared<wta::Astar<Lane::sLane>>();
	m_collision_player_item 
		= std::make_shared<wta::Collision<Player,Gimmick>>();
	m_collision_mesh_item 
		= std::make_shared<wta::Collision<dxe::Mesh, Gimmick>>();
	m_collision_player_partner 
		= std::make_shared<wta::Collision<Player, Partner>>();

	m_stagePhase = std::make_shared<StagePhase>();

	m_skyBox = std::make_shared<SkyBox>();
	m_cinemaBack = std::make_shared<CinemaBack>();

	m_laneLoad = std::make_shared<LaneLoad>();
	m_laneMove = std::make_shared<LaneMove>();

	m_floor = std::make_shared<Floor>();

	m_model = std::make_shared<Model>();
	m_modelLoad = std::make_shared<ModelLoad>();
	m_modelPool = std::make_shared<ModelPool>();

	m_character = std::make_shared<Character>();

	m_player = std::make_shared<Player>();
	m_playerLoad = std::make_shared<PlayerLoad>();
	m_playerMove = std::make_shared<PlayerMove>();
	m_playerDraw = std::make_shared<PlayerDraw>();
	m_playerSkill = std::make_shared<PlayerSkill>();
	m_playerCollision = std::make_shared<PlayerCollision>();
	m_cinemaPlayer = std::make_shared<CinemaPlayer>();

	m_partner = std::make_shared<Partner>();
	m_partnerLoad = std::make_shared<PartnerLoad>();
	m_partnerMove = std::make_shared<PartnerMove>();
	m_partnerDraw = std::make_shared<PartnerDraw>();

	m_cameraTargetPlayer = std::make_shared<CameraTargetPlayer>();
	m_cinemaCameraTarget = std::make_shared<CinemaCameraTarget>();

	m_butterfly = std::make_shared<Butterfly>();
	m_butterflyLoad = std::make_shared<ButterflyLoad>();

	m_gimmickLoad = std::make_shared<GimmickLoad>();
	m_gimmickGenerator = std::make_shared<GimmickGenerator>();
	m_gimmickPool = std::make_shared<GimmickPool>();

	m_effect = std::make_shared<Effect>();
	m_effectLoad = std::make_shared<EffectLoad>();

	m_score = std::make_shared<Score>();

	m_text = std::make_shared<Text>();
	m_textLoad = std::make_shared<TextLoad>();
	m_textDraw = std::make_shared<TextDraw>();

	m_charaGraph = std::make_shared<CharaGraph>();
	m_charaGraphLoad = std::make_shared<CharaGraphLoad>();
	m_charaGraphDraw = std::make_shared<CharaGraphDraw>();

	m_gameCamera = std::make_shared<GameCamera>();
	m_cameraLoad = std::make_shared<CameraLoad>();


	//m_cinemaCamera_half_right 
	//	= std::make_shared<CinemaCamera>(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT
	//									, CinemaCamera::eCameraSplitType::e_half_right);
	//m_cinemaCamera_third_left
	//	= std::make_shared<CinemaCamera>(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT
	//									, CinemaCamera::eCameraSplitType::e_third_left);
	//m_cinemaCamera_third_right 
	//	= std::make_shared<CinemaCamera>(DXE_WINDOW_WIDTH / 3, DXE_WINDOW_HEIGHT
	//									, CinemaCamera::eCameraSplitType::e_third_right);
	m_cinemaCamera = std::make_shared<CinemaCamera>();

	m_mediator = std::make_shared<Mediator>();

	m_screenShot = std::make_shared<ScreenShot>();
}

void PlayFactory::SetObjectReference()
{
	m_mediator->SetStagePhase(m_stagePhase);
	m_mediator->SetCinemaBack(m_cinemaBack);
	m_mediator->SetLaneLoad(m_laneLoad);
	m_mediator->SetLaneMove(m_laneMove);
	m_mediator->SetModel(m_model);
	m_mediator->SetModelLoad(m_modelLoad);
	m_mediator->SetCharacter(m_character);
	m_mediator->SetPlayer(m_player);
	m_mediator->SetPlayerLoad(m_playerLoad);
	m_mediator->SetPlayerMove(m_playerMove);
	m_mediator->SetPlayerDraw(m_playerDraw);
	m_mediator->SetPlayerSkill(m_playerSkill);
	m_mediator->SetPlayerCollision(m_playerCollision);
	m_mediator->SetCinemaPlayer(m_cinemaPlayer);
	m_mediator->SetPartner(m_partner);
	m_mediator->SetPartnerLoad(m_partnerLoad);
	m_mediator->SetPartnerMove(m_partnerMove);
	m_mediator->SetPartnerDraw(m_partnerDraw);
	m_mediator->SetCameraTargetPlayer(m_cameraTargetPlayer);
	m_mediator->SetCinemaCameraTarget(m_cinemaCameraTarget);
	m_mediator->SetButterfly(m_butterfly);
	m_mediator->SetButterflyLoad(m_butterflyLoad);
	m_mediator->SetGimmickLoad(m_gimmickLoad);
	m_mediator->SetGimmickGenerator(m_gimmickGenerator);
	m_mediator->SetGimmickPool(m_gimmickPool);
	m_mediator->SetEffectLoad(m_effectLoad);
	m_mediator->SetScore(m_score);
	m_mediator->SetText(m_text);
	m_mediator->SetTextLoad(m_textLoad);
	m_mediator->SetTextDraw(m_textDraw);
	m_mediator->SetCharaGraphLoad(m_charaGraphLoad);
	m_mediator->SetCharaGraphDraw(m_charaGraphDraw);
	m_mediator->SetGameCamera(m_gameCamera);
	m_mediator->SetCameraLoad(m_cameraLoad);
	//m_mediator->SetCinemaCamera(m_cinemaCamera);
	//m_mediator->SetCinemaCameraHalfRight(m_cinemaCamera_half_right);
	//m_mediator->SetCinemaCameraThirdLeft(m_cinemaCamera_third_left);
	//m_mediator->SetCinemaCameraThirdRight(m_cinemaCamera_third_right);

	m_stagePhase->SetMediator(m_mediator);
	m_skyBox->SetMediator(m_mediator);
	m_cinemaBack->SetMediator(m_mediator);
	m_laneMove->SetAstar(m_astar);
	m_laneMove->SetMediator(m_mediator);
	m_floor->SetMediator(m_mediator);
	m_model->SetMediator(m_mediator);
	m_character->SetMediator(m_mediator);
	m_player->SetMediator(m_mediator);
	m_playerMove->SetMediator(m_mediator);
	m_playerDraw->SetMediator(m_mediator);
	m_playerSkill->SetMediator(m_mediator);
	m_playerCollision->SetCollision(m_collision_player_item);
	m_playerCollision->SetCollision(m_collision_mesh_item);
	m_playerCollision->SetCollision(m_collision_player_partner);
	m_playerCollision->SetPlayer(m_player);
	m_playerCollision->SetPartner(m_partner);
	m_playerCollision->SetMediator(m_mediator);
	m_cinemaPlayer->SetMediator(m_mediator);
	m_partner->SetMediator(m_mediator);
	m_partnerMove->SetMediator(m_mediator);
	m_partnerDraw->SetMediator(m_mediator);
	m_cameraTargetPlayer->SetMediator(m_mediator);
	//m_cinemaCameraTarget->SetMediator(m_mediator);
	m_butterfly->SetMediator(m_mediator);
	m_gimmickGenerator->SetMediator(m_mediator);
	m_effect->SetMediator(m_mediator);
	m_score->SetMediator(m_mediator);
	m_text->SetMediator(m_mediator);
	m_textLoad->SetMediator(m_mediator);
	m_textDraw->SetMediator(m_mediator);
	m_charaGraph->SetMediator(m_mediator);
	m_charaGraphDraw->SetMediator(m_mediator);
	m_gameCamera->SetMediator(m_mediator);
	m_cameraLoad->SetMediator(m_mediator);
	m_cinemaCamera->SetMediator(m_mediator);
	//m_cinemaCamera_half_right->SetMediator(m_mediator);
	//m_cinemaCamera_third_left->SetMediator(m_mediator);
	//m_cinemaCamera_third_right->SetMediator(m_mediator);
	m_screenShot->SetMediator(m_mediator);
}

void PlayFactory::PoolGimmickType(const std::vector<Gimmick::sGimmickTypeInfo>& gimmick_types)
{
	// 各タイプごとに生成するギミックの数
	int create_num_per_type = m_gimmickPool->GetGimmickCreateNum();

	for (const Gimmick::sGimmickTypeInfo& type_info : gimmick_types)
	{
		for (int i = 0; i < create_num_per_type; ++i)
		{
			std::shared_ptr<Gimmick> gimmick = std::make_shared<Gimmick>();

			gimmick->LoadGimmickData(type_info);

			gimmick->SetMediator(m_mediator);

			m_mediator->SetGimmick(gimmick);
						
			m_gimmickPool->AddGimmick(gimmick, type_info.s_type);
			
			m_gimmicks.emplace_back(gimmick);

			m_objects_gameCamera.emplace_back(gimmick);
		}	
	}
}

void PlayFactory::StorageObjectGameCamera()
{
	m_objects_gameCamera.emplace_back(m_skyBox);
	m_objects_gameCamera.emplace_back(m_floor);
	m_objects_gameCamera.emplace_back(m_model);
	m_objects_gameCamera.emplace_back(m_cameraTargetPlayer);

	// 各ギミックタイプごとに処理
	PoolGimmickType(m_gimmickLoad->GetGimmicksType(Gimmick::eGimmickType::plant));
	PoolGimmickType(m_gimmickLoad->GetGimmicksType(Gimmick::eGimmickType::tree));
	PoolGimmickType(m_gimmickLoad->GetGimmicksType(Gimmick::eGimmickType::sky_flower));

	m_playerCollision->SetGimmicks(m_gimmicks);

	m_objects_gameCamera.emplace_back(m_partner);
	m_objects_gameCamera.emplace_back(m_player);
	m_objects_gameCamera.emplace_back(m_effect);
	m_objects_gameCamera.emplace_back(m_score);
	//m_objects_gameCamera.emplace_back(m_charaGraph);
	//m_objects_gameCamera.emplace_back(m_text);
}

void PlayFactory::StorageObjectCinemaCamera()
{
	// シネマ用背景
	// シネマ用カメラターゲット
	m_objects_cinemaCamera.emplace_back(m_cinemaCameraTarget);
	//m_objects_cinemaCamera_half_right.emplace_back(m_cinemaCameraTarget);
	//m_objects_cinemaCamera_third_left.emplace_back(m_cinemaCameraTarget);
	//m_objects_cinemaCamera_third_right.emplace_back(m_cinemaCameraTarget);
	m_objects_cinemaCamera.emplace_back(m_cinemaBack);
	//m_objects_cinemaCamera_half_right.emplace_back(m_cinemaBack);
	//m_objects_cinemaCamera_third_left.emplace_back(m_cinemaBack);
	//m_objects_cinemaCamera_third_right.emplace_back(m_cinemaBack);
	// シネマ用プレイヤー
	m_objects_cinemaCamera.emplace_back(m_cinemaPlayer);
	//m_objects_cinemaCamera_half_right.emplace_back(m_cinemaPlayer);
	//m_objects_cinemaCamera_third_left.emplace_back(m_cinemaPlayer);
	//m_objects_cinemaCamera_third_right.emplace_back(m_cinemaPlayer);
	// シネマ用エフェクト
	m_objects_cinemaCamera.emplace_back(m_effect);
	//m_objects_cinemaCamera_half_right.emplace_back(m_effect);
	//m_objects_cinemaCamera_third_left.emplace_back(m_effect);
	//m_objects_cinemaCamera_third_right.emplace_back(m_effect);
	// シネマ用蝶
	//m_objects_cinemaCamera.emplace_back(m_butterfly);
}

//// 初期化
//m_itemGenerator->Initialize();
//// ランダム座標設定
//m_itemGenerator->GenerateItem();

//void Factory::PoolModelObject()
//{
//	int create_num = m_modelPool->GetModelCreateNum();
//
//	// 各IDに対してモデルを1個ずつ生成
//	for (int id = 0; id < m_modelLoad->GetModelTotalNum(); ++id)
//	{
//		std::shared_ptr<Model> stage_model 
//					= std::make_shared<Model>(id);
//			
//		stage_model->SetMediator(m_mediator);
//			
//		m_mediator->SetModel(stage_model);
//		
//		stage_model->LoadInitModel();
//		
//		m_modelPool->AddModel(stage_model);
//
//		m_objects.emplace_back(stage_model);
//
//		// 残りのモデルを複製
//		for (int i = 0; i < create_num ; ++i)
//		{
//			int new_model_hdl = MV1DuplicateModel(stage_model->GetModelHdl());
//			
//			std::shared_ptr<Model> model_copy 
//				= std::make_shared<Model>(new_model_hdl, id); 
//			
//			model_copy->CopyInitModel( stage_model->GetTextureAHdl()
//										, stage_model->GetTextureBHdl()
//										, stage_model->GetTextureCHdl()
//										, stage_model->GetMaterialCount()
//										, stage_model->GetMaterialAName()
//										, stage_model->GetMaterialBName()
//										, stage_model->GetMaterialCName());
//
//			// 複製をプールに追加
//			m_modelPool->AddModel(model_copy);
//			
//			m_objects.emplace_back(model_copy);
//		}
//	}
//}

//void Factory::PoolModelObject()
//{
//	int create_num = m_modelPool->GetModelCreateNum() >> 1;
//
//	for (int id = 0; id < m_modelLoad->GetModelTotalNum(); ++id)
//	{
//		// 各IDに対して現実のモデルを5個生成
//		for (int i = 0; i < create_num; ++i)
//		{
//			auto model_real
//				= std::make_shared<Model>(id, Model::eWorldType::e_real);
//
//			model_real->SetMediator(m_mediator);
//
//			m_mediator->SetModel(model_real);
//			// ロードと初期化
//			model_real->LoadAndInitModels();
//			// プール（モデル型ベクター）に追加（アクティブ可否の操作）
//			m_modelPool->AddModel(model_real);
//			// オブジェクト型リストに追加（ポリモフィズムのため）
//			m_objects.emplace_back(model_real);
//		}
//
//		// 各IDに対して夢のモデルを5個生成
//		for (int i = 0; i < create_num; ++i)
//		{
//			auto model_dream
//				= std::make_shared<Model>(id, Model::eWorldType::e_dream);
//
//			model_dream->SetMediator(m_mediator);
//
//			m_mediator->SetModel(model_dream);
//
//			model_dream->LoadAndInitModels();
//
//			m_modelPool->AddModel(model_dream);
//
//			m_objects.emplace_back(model_dream);
//		}
//	}
//}