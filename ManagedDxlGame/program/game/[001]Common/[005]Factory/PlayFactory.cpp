#include "../../../wta_library/wta_Astar.h"
#include "../../../wta_library/wta_Collision.h"
#include "../[000]Object/[000]Stage/[000]Back/SkyBox.h"
#include "../[000]Object/[000]Stage/[000]Back/CinemaBack.h"
#include "../[000]Object/[000]Stage/[000]Back/[000]BackFunction/BackLoad.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneLoad.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneMove.h"
#include "../[000]Object/[000]Stage/[002]Floor/Floor.h"
#include "../[000]Object/[000]Stage/[003]Model/Model.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelLoad.h"
#include "../[000]Object/[001]Character/[000]Player/Player.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerLoad.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerMove.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerDraw.h"
#include "../[000]Object/[001]Character/[000]Player/[000]PlayerFunction/PlayerCollision.h"
#include "../[000]Object/[001]Character/[000]Player/CinemaPlayer.h"
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
#include "../[000]Object/[008]OtherGraph/ChangeGraph.h"
#include "../[000]Object/[008]OtherGraph/ChildChangeGraph.h"
#include "../[000]Object/[008]OtherGraph/[000]OtherFunction/OtherGraphLoad.h"
#include "../[001]Camera/GameCamera.h"
#include "../[001]Camera/CinemaCamera.h"
#include "../[001]Camera/[000]CameraFunction/CameraLoad.h"
#include "../[002]Mediator/Mediator.h"
#include "../[003]Phase/CameraPhase.h"
#include "../[003]Phase/StagePhase.h"
#include "../[004]ScreenShot/ScreenShot.h"
#include "PlayFactory.h"



PlayFactory::PlayFactory()
{
	CreateObject();

	SetObjectReference();

	SetMediatorReference();

	StorageObjectGameCamera();

	StorageObjectCinemaCamera();

	m_laneMove->GetAutoMove();
}

PlayFactory::~PlayFactory()
{
	m_objects_gameCamera.clear();
	m_objects_cinemaCamera.clear();
	m_gimmicks.clear();

	SharedExReset();
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

	m_cameraPhase = std::make_shared<CameraPhase>();
	m_stagePhase = std::make_shared<StagePhase>();

	m_skyBox = std::make_shared<SkyBox>();
	m_cinemaBack = std::make_shared<CinemaBack>();
	m_backLoad = std::make_shared<BackLoad>();

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
	m_playerCollision = std::make_shared<PlayerCollision>();
	m_cinemaPlayer = std::make_shared<CinemaPlayer>();

	m_partner = std::make_shared<Partner>();
	m_partnerLoad = std::make_shared<PartnerLoad>();
	m_partnerMove = std::make_shared<PartnerMove>();
	m_partnerDraw = std::make_shared<PartnerDraw>();

	m_gameCameraTarget = std::make_shared<GameCameraTarget>();
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

	m_changeGraph = std::make_shared<ChangeGraph>();
	m_childChangeGraph = std::make_shared<ChildChangeGraph>();
	m_otherGraphLoad = std::make_shared<OtherGraphLoad>();

	m_gameCamera = std::make_shared<GameCamera>();
	m_cameraLoad = std::make_shared<CameraLoad>();

	m_cinemaCamera = std::make_shared<CinemaCamera>();

	m_mediator = std::make_shared<Mediator>();

	m_screenShot = std::make_shared<ScreenShot>();
}

void PlayFactory::SetObjectReference()
{
	m_mediator->SetCameraPhase(m_cameraPhase);
	m_mediator->SetStagePhase(m_stagePhase);
	m_mediator->SetCinemaBack(m_cinemaBack);
	m_mediator->SetBackLoad(m_backLoad);
	m_mediator->SetLaneLoad(m_laneLoad);
	m_mediator->SetLaneMove(m_laneMove);
	m_mediator->SetModel(m_model);
	m_mediator->SetModelLoad(m_modelLoad);
	m_mediator->SetCharacter(m_character);
	m_mediator->SetPlayer(m_player);
	m_mediator->SetPlayerLoad(m_playerLoad);
	m_mediator->SetPlayerMove(m_playerMove);
	m_mediator->SetPlayerDraw(m_playerDraw);
	m_mediator->SetPlayerCollision(m_playerCollision);
	m_mediator->SetCinemaPlayer(m_cinemaPlayer);
	m_mediator->SetPartner(m_partner);
	m_mediator->SetPartnerLoad(m_partnerLoad);
	m_mediator->SetPartnerMove(m_partnerMove);
	m_mediator->SetPartnerDraw(m_partnerDraw);
	m_mediator->SetCameraTargetPlayer(m_gameCameraTarget);
	m_mediator->SetCinemaCameraTarget(m_cinemaCameraTarget);
	m_mediator->SetButterfly(m_butterfly);
	m_mediator->SetButterflyLoad(m_butterflyLoad);
	m_mediator->SetGimmickLoad(m_gimmickLoad);
	m_mediator->SetGimmickGenerator(m_gimmickGenerator);
	m_mediator->SetGimmickPool(m_gimmickPool);
	m_mediator->SetEffect(m_effect);
	m_mediator->SetEffectLoad(m_effectLoad);
	m_mediator->SetScore(m_score);
	m_mediator->SetText(m_text);
	m_mediator->SetTextLoad(m_textLoad);
	m_mediator->SetTextDraw(m_textDraw);
	m_mediator->SetCharaGraph(m_charaGraph);
	m_mediator->SetCharaGraphLoad(m_charaGraphLoad);
	m_mediator->SetChangeGraph(m_changeGraph);
	m_mediator->SetChildChangeGraph(m_childChangeGraph);
	m_mediator->SetOtherGraphLoad(m_otherGraphLoad);
	m_mediator->SetScreenShot(m_screenShot);
	m_mediator->SetGameCamera(m_gameCamera);
	m_mediator->SetCameraLoad(m_cameraLoad);
	m_mediator->SetCinemaCamera(m_cinemaCamera);
}

void PlayFactory::SetMediatorReference()
{
	m_cameraPhase->SetMediator(m_mediator);
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
	m_gameCameraTarget->SetMediator(m_mediator);
	m_butterfly->SetMediator(m_mediator);
	m_gimmickGenerator->SetMediator(m_mediator);
	m_effect->SetMediator(m_mediator);
	m_score->SetMediator(m_mediator);
	m_text->SetMediator(m_mediator);
	m_textDraw->SetMediator(m_mediator);
	m_charaGraph->SetMediator(m_mediator);
	m_changeGraph->SetMediator(m_mediator);
	m_childChangeGraph->SetMediator(m_mediator);
	m_screenShot->SetMediator(m_mediator);
	m_gameCamera->SetMediator(m_mediator);
	m_cameraLoad->SetMediator(m_mediator);
	m_cinemaCamera->SetMediator(m_mediator);
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

			if (type_info.s_type == Gimmick::eGimmickType::e_wood)
			{
				gimmick->SetCollisionSize(500);
			}
			else
			{
				gimmick->SetCollisionSize(300);
			}

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
	m_objects_gameCamera.emplace_back(m_gameCameraTarget);

	// 各ギミックタイプごとに処理
	PoolGimmickType(m_gimmickLoad->GetGimmicksType(Gimmick::eGimmickType::e_ground_flower));
	PoolGimmickType(m_gimmickLoad->GetGimmicksType(Gimmick::eGimmickType::e_wood));
	PoolGimmickType(m_gimmickLoad->GetGimmicksType(Gimmick::eGimmickType::e_sky_flower));

	m_playerCollision->SetGimmicks(m_gimmicks);

	m_objects_gameCamera.emplace_back(m_partner);
	m_objects_gameCamera.emplace_back(m_player);
	m_objects_gameCamera.emplace_back(m_effect);
	m_objects_gameCamera.emplace_back(m_score);
	m_objects_gameCamera.emplace_back(m_charaGraph);
	m_objects_gameCamera.emplace_back(m_text);
	m_objects_gameCamera.emplace_back(m_childChangeGraph);
}

void PlayFactory::StorageObjectCinemaCamera()
{
	// シネマ用カメラターゲット
	m_objects_cinemaCamera.emplace_back(m_cinemaCameraTarget);
	// シネマ用背景
	m_objects_cinemaCamera.emplace_back(m_cinemaBack);
	// シネマ用プレイヤー
	m_objects_cinemaCamera.emplace_back(m_cinemaPlayer);
	// シネマ用蝶
	m_objects_cinemaCamera.emplace_back(m_butterfly);
	// シネマ用エフェクト
	m_objects_cinemaCamera.emplace_back(m_effect);
	// sceneチェンジ用画像
	m_objects_cinemaCamera.emplace_back(m_changeGraph);
}

// 明示的なリセットは本来必要ないが、メモリリークが発生しているため一時的な対処として実装
void PlayFactory::SharedExReset()
{
	m_astar.reset();
	m_collision_player_item.reset();
	m_collision_mesh_item.reset();
	m_collision_player_partner.reset();
	m_cameraPhase.reset();
	m_stagePhase.reset();
	m_skyBox.reset();
	m_cinemaBack.reset();
	m_backLoad.reset();
	m_laneLoad.reset();
	m_laneMove.reset();
	m_floor.reset();
	m_model.reset();
	m_modelLoad.reset();
	m_character.reset();
	m_player.reset();
	m_playerLoad.reset();
	m_playerMove.reset();
	m_playerDraw.reset();
	m_playerCollision.reset();
	m_cinemaPlayer.reset();
	m_partner.reset();
	m_partnerLoad.reset();
	m_partnerMove.reset();
	m_partnerDraw.reset();
	m_gameCameraTarget.reset();
	m_cinemaCameraTarget.reset();
	m_butterfly.reset();
	m_butterflyLoad.reset();
	m_gimmickLoad.reset();
	m_gimmickGenerator.reset();
	m_gimmickPool.reset();
	m_effect.reset();
	m_effectLoad.reset();
	m_score.reset();
	m_text.reset();
	m_textLoad.reset();
	m_textDraw.reset();
	m_charaGraph.reset();
	m_charaGraphLoad.reset();
	m_changeGraph.reset();
	m_childChangeGraph.reset();
	m_otherGraphLoad.reset();
	m_gameCamera.reset();
	m_cameraLoad.reset();
	m_cinemaCamera.reset();
	m_mediator.reset();
	m_screenShot.reset();
}
