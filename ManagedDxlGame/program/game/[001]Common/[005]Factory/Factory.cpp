#include "../../../wta_library/wta_Astar.h"
#include "../../../wta_library/wta_Collision.h"
#include "../[000]Object/[000]Stage/[000]SkyBox/SkyBox.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneLoad.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneMove.h"
#include "../[000]Object/[000]Stage/[002]Floor/Floor.h"
#include "../[000]Object/[001]Character/[000]Player/Player.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerLoad.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerMove.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerDraw.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerSkill.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerCollision.h"
#include "../[000]Object/[001]Character/[001]Partner/Partner.h"
#include "../[000]Object/[001]Character/[001]Partner/[000]PartnerFunction/PartnerMove.h"
#include "../[000]Object/[001]Character/[001]Partner/[000]PartnerFunction/PartnerDraw.h"
#include "../[000]Object/[001]Character/[002]CameraTargetPlayer/CameraTargetPlayer.h"
#include "../[000]Object/[000]Stage/[003]Model/Model.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelLoad.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelPool.h"
#include "../[000]Object/[002]Item/Item.h"
#include "../[000]Object/[002]Item/[000]ItemFunction/ItemLoad.h"
#include "../[000]Object/[002]Item/[000]ItemFunction/ItemPool.h"
#include "../[000]Object/[002]Item/[000]ItemFunction/ItemGenerator.h"
#include "../[000]Object/[003]Effect/Effect.h"
#include "../[000]Object/[003]Effect/[000]EffectFunction/EffectLoad.h"
#include "../[000]Object/[004]Score/Score.h"
#include "../[000]Object//[005]Message/[001]CharaGraph/CharaGraph.h"
#include "../[000]Object//[005]Message/[001]CharaGraph/[000]CharaGraphFunction/CharaGraphLoad.h"
#include "../[000]Object/[005]Message/[001]CharaGraph/[000]CharaGraphFunction/CharaGraphDraw.h"
#include "../[001]Camera/GameCamera.h"
#include "../[001]Camera/[000]CameraFunction/CameraLoad.h"
//#include "../[001]Camera/[000]CameraFunction/CameraFrustum.h"
#include "../[002]Mediator/Mediator.h"
#include "../[004]ScreenShot/ScreenShot.h"
#include "Factory.h"


Factory::Factory()
{
	CreateObject();

	SetObjectReference();

	//PoolModelObject();

	StorageObject();

	PoolItemObject();

	m_laneMove->GetAutoMove();
}

Factory::~Factory()
{
	m_objects.clear();
}

void Factory::CreateObject()
{
	m_astar = std::make_shared<wta::Astar<Lane::sLane>>();
	m_collision_player_item = std::make_shared<wta::Collision<Player,Item>>();
	m_collision_mesh_item = std::make_shared<wta::Collision<dxe::Mesh, Item>>();
	m_collision_player_partner = std::make_shared<wta::Collision<Player, Partner>>();
	//m_collision_camera = std::make_shared<wta::Collision<Player, GameCamera>>();

	m_stagePhase = std::make_shared<StagePhase>();

	m_skyBox = std::make_shared<SkyBox>();

	m_laneLoad = std::make_shared<LaneLoad>();
	m_laneMove = std::make_shared<LaneMove>();

	m_floor = std::make_shared<Floor>();

	m_model = std::make_shared<Model>();
	m_modelLoad = std::make_shared<ModelLoad>();

	m_character = std::make_shared<Character>();

	m_player = std::make_shared<Player>();
	m_playerLoad = std::make_shared<PlayerLoad>();
	m_playerMove = std::make_shared<PlayerMove>();
	m_playerDraw = std::make_shared<PlayerDraw>();
	m_playerSkill = std::make_shared<PlayerSkill>();
	m_playerCollision = std::make_shared<PlayerCollision>();

	m_partner = std::make_shared<Partner>();
	m_partnerMove = std::make_shared<PartnerMove>();
	m_partnerDraw = std::make_shared<PartnerDraw>();

	m_cameraTargetPlayer = std::make_shared<CameraTargetPlayer>();

	//m_modelPool = std::make_shared<ModelPool>();

	m_itemLoad = std::make_shared<ItemLoad>();
	m_itemGenerator = std::make_shared<ItemGenerator>();
	m_itemPool = std::make_shared<ItemPool>();

	m_effect = std::make_shared<Effect>();
	m_effectLoad = std::make_shared<EffectLoad>();

	m_score = std::make_shared<Score>();

	m_charaGraph = std::make_shared<CharaGraph>();
	m_charaGraphLoad = std::make_shared<CharaGraphLoad>();
	m_charaGraphDraw = std::make_shared<CharaGraphDraw>();

	m_gameCamera = std::make_shared<GameCamera>();
	m_cameraLoad = std::make_shared<CameraLoad>();
	//m_cameraFrustum = std::make_shared<CameraFrustum>();

	m_mediator = std::make_shared<Mediator>();

	m_screenShot = std::make_shared<ScreenShot>();
}

void Factory::SetObjectReference()
{
	m_mediator->SetStagePhase(m_stagePhase);
	m_mediator->SetLaneLoad(m_laneLoad);
	m_mediator->SetLaneMove(m_laneMove);
	m_mediator->SetCharacter(m_character);
	m_mediator->SetPlayer(m_player);
	m_mediator->SetPlayerLoad(m_playerLoad);
	m_mediator->SetPlayerMove(m_playerMove);
	m_mediator->SetPlayerDraw(m_playerDraw);
	m_mediator->SetPlayerSkill(m_playerSkill);
	m_mediator->SetPlayerCollision(m_playerCollision);
	m_mediator->SetPartner(m_partner);
	m_mediator->SetPartnerMove(m_partnerMove);
	m_mediator->SetPartnerDraw(m_partnerDraw);
	m_mediator->SetCameraTargetPlayer(m_cameraTargetPlayer);
	m_mediator->SetModel(m_model);
	m_mediator->SetModelLoad(m_modelLoad);
	m_mediator->SetModelPool(m_modelPool);
	m_mediator->SetItemLoad(m_itemLoad);
	m_mediator->SetItemGenerator(m_itemGenerator);
	m_mediator->SetItemPool(m_itemPool);
	m_mediator->SetEffectLoad(m_effectLoad);
	m_mediator->SetCharaGraphLoad(m_charaGraphLoad);
	m_mediator->SetCharaGraphDraw(m_charaGraphDraw);
	m_mediator->SetGameCamera(m_gameCamera);
	m_mediator->SetCameraLoad(m_cameraLoad);
	//m_mediator->SetCameraFrustum(m_cameraFrustum);

	m_laneMove->SetAstar(m_astar);
	m_laneMove->SetMediator(m_mediator);
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
	m_partner->SetMediator(m_mediator);
	m_partnerMove->SetMediator(m_mediator);
	m_partnerDraw->SetMediator(m_mediator);
	m_cameraTargetPlayer->SetMediator(m_mediator);
	m_itemGenerator->SetMediator(m_mediator);
	m_effect->SetMediator(m_mediator);
	m_charaGraph->SetMediator(m_mediator);
	m_charaGraphDraw->SetMediator(m_mediator);
	m_gameCamera->SetMediator(m_mediator);
	m_cameraLoad->SetMediator(m_mediator);
	m_screenShot->SetMediator(m_mediator);
	//m_cameraFrustum->SetCollision(m_collision_camera);
	//m_cameraFrustum->SetMediator(m_mediator);
	//m_cameraFrustum->SetPlayer(m_player);
	//m_cameraFrustum->SetGameCamera(m_gameCamera);
}

void Factory::PoolItemObject()
{
	int create_num = m_itemPool->GetItemCreateNum();

	// アイテムを最初に20個生成して格納
	for (int i = 0; i < create_num; ++i)
	{
		std::shared_ptr<Item> item = std::make_shared<Item>();
		// メディエーターの設定
		item->SetMediator(m_mediator);
		// アイテムの設定
		m_itemGenerator->SetItem(item);
		// アイテムプールに格納
		m_itemPool->AddItem(item);
		// オブジェクト型リストに追加（ポリモフィズムのため）
		m_objects.emplace_back(item);
	}

	std::vector<std::shared_ptr<Item>> items = m_itemPool->GetItems();

	m_playerCollision->SetItems(items);
}

void Factory::StorageObject()
{
	//m_objects.emplace_back(m_skyBox);
	m_objects.emplace_back(m_floor);
	//m_objects.emplace_back(m_model);
	m_objects.emplace_back(m_cameraTargetPlayer);
	m_objects.emplace_back(m_partner);
	m_objects.emplace_back(m_player);
	//m_objects.emplace_back(m_effect);
	m_objects.emplace_back(m_score);
	m_objects.emplace_back(m_charaGraph);
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