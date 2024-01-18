#include "Mediator.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneLoad.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneMove.h"
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
#include "../[000]Object/[002]Item/[000]ItemFunction/ItemLoad.h"
//#include "../[000]Object/[002]Item/[000]ItemFunction/ItemDraw.h"
#include "../[000]Object/[002]Item/[000]ItemFunction/ItemGenerator.h"
#include "../[000]Object/[002]Item/[000]ItemFunction/ItemPool.h"
#include "../[000]Object/[003]Effect/[000]EffectFunction/EffectLoad.h"
#include "../[000]Object/[005]Message/[000]Text/Text.h"
#include "../[000]Object/[005]Message/[000]Text/[000]TextFunction/TextLoad.h"
#include "../[000]Object/[005]Message/[000]Text/[000]TextFunction/TextDraw.h"
#include "../[000]Object/[005]Message/[001]CharaGraph/[000]CharaGraphFunction/CharaGraphLoad.h"
#include "../[000]Object/[005]Message/[001]CharaGraph/[000]CharaGraphFunction/CharaGraphDraw.h"
#include "../[001]Camera/[000]CameraFunction/CameraLoad.h"
//#include "../[001]Camera/[000]CameraFunction/CameraFrustum.h"


//---------StagePhase---------//

StagePhase::eStagePhase Mediator::GetNowStagePhaseState() const
{
	return m_stagePhase->GetNowStagePhase();
}

//---------------------------//


//-----------Stage-----------//

// LaneLoad

// レーン配列の幅取得
int Mediator::GetStageLaneWidth() const
{
	return m_laneLoad->GetLaneWidth();
}

// レーン配列の高さ取得
int Mediator::GetStageLaneHeight() const
{
	return m_laneLoad->GetLaneHeight();
}

//const std::vector<Lane::sLane>& Mediator::GetStageLaneEvent() const
//{
//	return m_laneLoad->GetLaneEvent();
//}

const std::vector<Lane::sLane>& Mediator::GetStageLane()const
{
	return m_laneLoad->GetLane();
}

// LaneMove

void Mediator::MoveAstarMatrix(const float delta_time
								, tnl::Vector3& pos
								, tnl::Quaternion& rot)
{
	m_laneMove->MoveAstar(delta_time,pos,rot);
}

void Mediator::MoveAstarPosition(const float delta_time, tnl::Vector3& pos)
{
	m_laneMove->MoveAstarPos(delta_time,pos);
}

void Mediator::SetPlayerLookSideRight(bool look_side)
{
	m_laneMove->SetLookSideRight(look_side);
}

void Mediator::SetPlayerLookSideLeft(bool look_side)
{
	m_laneMove->SetLookSideLeft(look_side);
}

//bool Mediator::NextLaneMove()
//{
//	return m_laneMove->NextLane();
//}

//void Mediator::SetMoveNowPos(tnl::Vector3 pos)
//{
//	m_laneMove->SetNowPos(pos);
//}
//
//
//tnl::Vector3 Mediator::GetMoveNewPos() const
//{
//	return m_laneMove->GetNewPos();
//}
//
//void Mediator::SetMoveNowRot(tnl::Quaternion rot)
//{
//	m_laneMove->SetNowRot(rot);
//}
//
//tnl::Quaternion Mediator::GetMoveNewRot() const
//{
//	return m_laneMove->GetNewRot();
//}

//---------------------------//


//----------Player----------//

// player

void Mediator::SetPlayerPos(tnl::Vector3& pos)
{
	m_player->SetPos(pos);
}

void Mediator::SetPlayerRot(tnl::Quaternion& rot)
{
	m_player->SetRot(rot);
}

const tnl::Vector3& Mediator::GetPlayerPos() const
{
	return m_player->GetPos();
}

const tnl::Quaternion& Mediator::GetPlayerRot() const
{
	return m_player->GetRot();
}

float Mediator::GetPlayerCollisionSize() const
{
	return m_player->GetCollisionSize();
}

Lane::sLane Mediator::CurrentPlayerLane()
{
	return m_character->CurrentMoveLane();
}

tnl::Vector3 Mediator::PlayerForward()
{
	return m_player->Forward();
}

// playerLoad

float Mediator::GetPlayerMoveSpeed() const
{
	return m_playerLoad->GetMoveSpeed();
}

float Mediator::GetPlayerMoveRot() const
{
	return m_playerLoad->GetMoveRot();
}

float Mediator::GetPlayerSaltoTotalTime() const
{
	return m_playerLoad->GetSaltoTotalTime();
}

float Mediator::GetPlayerSaltoRadius() const
{
	return m_playerLoad->GetSaltoRadius();
}

float Mediator::GetPlayerSaltoMoveSpeed() const
{
	return m_playerLoad->GetSaltoMoveSpeed();
}

// playerMove

//int Mediator::GetMoveCurrentStep() const
//{
//	return m_playerMove->GetCurrentStep();
//}

void Mediator::UpdatePlayerMoveMatrix(float delta_time)
{
	m_playerMove->Update(delta_time);
}


//void Mediator::GetPlayerMoveAutoMove()
//{
//	m_playerMove->GetAutoMove();
//}

bool Mediator::GetPushButton()
{
	return m_playerMove->PushButton();
}

//tnl::Vector3 Mediator::GetNewPlayerMovePos()
//{
//	return m_playerMove->GetNewPlayerPos();
//}
//
//tnl::Quaternion Mediator::GetNewPlayerMoveRot()
//{
//	return m_playerMove->GetNewPlayerRot();
//}


//std::vector<std::pair<int, int>> Mediator::GetMoveGoalProcess()
//{
//	return m_playerMove->GetGoalProcess();
//}


// playerDraw

void Mediator::UpdatePlayerAnim(const float delta_time)
{
	m_playerDraw->Update(delta_time);
}

void Mediator::DrawPlayerModel()
{
	m_playerDraw->Draw();
}

int Mediator::GetPlayerModelHdl() const
{
	return m_playerDraw->GetModelHdl();
}

bool Mediator::GetIsPlayerAttack() const
{
	return m_playerDraw->GetIsAttack();
}


// playerSkill

void Mediator::UpdatePlayerSkill(const float delta_time)
{
	m_playerSkill->Update(delta_time);
}

// playerCollision

void Mediator::InitCollisionRegister()
{
	m_playerCollision->CollisionRegister();
}

void Mediator::UpdateCollisionCheck()
{
	m_playerCollision->CollisionCheck();
}

//--------------------------//


//---------Partner---------//

// Partner

void Mediator::SetPartnerPos(tnl::Vector3& pos)
{
	m_partner->SetPos(pos);
}

const tnl::Vector3& Mediator::GetPartnerPos() const
{
	return m_partner->GetPos();
}

void Mediator::SetPartnerRot(tnl::Quaternion& rot)
{
	m_partner->SetRot(rot);
}

const tnl::Quaternion& Mediator::GetPartnerRot() const
{
	return m_partner->GetRot();
}

// PartnerMove

void Mediator::UpdatePartnerMoveMatrix(const float delta_time)
{
	m_partnerMove->Update(delta_time);
}

// PartnerDraw

void Mediator::UpdatePartnerAnim(const float delta_time)
{
	m_partnerDraw->Update(delta_time);
}

void Mediator::DrawPartnerModel()
{
	m_partnerDraw->Draw();
}

int Mediator::GetPartnerModelHdl() const
{
	return m_partnerDraw->GetModelHdl();
}

//--------------------------//

//----CameraTargetPlayer----//

// CameraTargetPlayer

const tnl::Vector3& Mediator::GetCameraTargetPlayerPos() const
{
	return m_cameraTargetPlayer->GetPos();
}

GameCamera::sCameraInfo Mediator::GetTargetCameraInfo() const
{
	return m_cameraTargetPlayer->GetCameraInfo();
}

Item::sItem Mediator::CurrentTargetItemLane()
{
	return m_partner->CurrentItemLane();
}

//--------------------------//


//----------Model-----------//

// model

const tnl::Vector3& Mediator::GetModelPos() const
{
	return m_model->GetPos();
}
//
//Model::eWorldType Mediator::GetWorldModelType() const
//{
//	return m_model->GetWorldType();
//}

//void Mediator::SetIsModelAliveActive(bool is_active)
//{
//	m_model->SetIsAliveActive(is_active);
//}

//int Mediator::GetIsModelAliveActive() const
//{
//	return m_model->GetIsAliveActive();
//}
//
//void Mediator::ToggleModelActive(bool is_world_active)
//{
//	m_model->ToggleActive(is_world_active);
//}


// modelLoad

int Mediator::GetStageModelTotalNum() const
{
	return m_modelLoad->GetModelTotalNum();
}

int Mediator::GetStageModelVecHeight() const
{
	return m_modelLoad->GetModelVecHeight();
}

int Mediator::GetStageModelVecWidth() const
{
	return m_modelLoad->GetModelVecWidth();
}


const std::vector<Model::sStageModel>& Mediator::GetStageTreeVector() const
{
	return m_modelLoad->GetTreeVector();
}

const std::vector<Model::sStageModel>& Mediator::GetStageGrassVector() const
{
	return m_modelLoad->GetGrassVector();
}

const std::vector<Model::sStageModelType>& Mediator::GetStageModelTypeInfo() const
{
	return m_modelLoad ->GetModelTypeInfo();
}

Model::sStageModelType Mediator::GetStageModelInfoById(int id)
{
	return m_modelLoad -> GetModelInfoById(id);
}

// modelPool

//void Mediator::IsActivatePoolAllModels(Model::eWorldType world_type)
//{
//	m_modelPool->IsActivateAllModels(world_type);
//}

std::vector<std::shared_ptr<Model>>& Mediator::GetPoolModels() const
{
	return m_modelPool->GetModels();
}

//std::shared_ptr<Model> Mediator::GetPoolRandomModel(Model::eWorldType world_type)
//{
//	return m_modelPool->GetRandomModel(world_type);
//}


//--------------------------//


//-----------ltem-----------//

// Item

void Mediator::SetItemIsActive(bool is_active)
{
	m_item->SetIsActive(is_active);
}

bool Mediator::GetItemIsHit() const
{
	return m_item->GetIsHit();
}

// ItemLoad

int Mediator::GetItemIdNum() const
{
	return m_itemLoad->GetIdNum();
}

const std::vector<Item::sItem>& Mediator::GetItemLoadLane() const
{
	return m_itemLoad->GetItemLane();
}

const std::vector<Item::sItemType>& Mediator::GetItemTypeInfo() const
{
	return m_itemLoad->GetItemTypeInfo();
}
	
Item::sItemType Mediator::GetItemLoadInfoById(int id)
{
	return m_itemLoad->GetItemInfoById(id);
}

// ItemPool

std::shared_ptr<Item> Mediator::GetNotActiveItemPool()
{
	return m_itemPool->GetNotActiveItem();
}

const std::vector<std::shared_ptr<Item>>& Mediator::GetPoolItems() const
{
	return m_itemPool->GetItems();
}


// ItemGenerator

bool Mediator::GetIsItemFlowerActive() const
{
	return m_itemGenerator->GetIsFlowerActive();
}


//void Mediator::SetItemIsCreate(bool is_create)
//{
//	m_itemGenerator->SetIsCreate(is_create);
//}
//
//void Mediator::SetItemIsDelete(bool is_delete)
//{
//	m_itemGenerator->SetIsDelete(is_delete);
//}

//--------------------------//


//----------Effect----------//

// EffectLoad

const std::vector<Effect::sEffectType>& Mediator::GetEffectLoadInfo() const
{
	return m_effectLoad->GetEffectType();
}

//--------------------------//




//------------Text-----------//

// TextDraw

void Mediator::UpdateTextMessage(const float delta_time)
{
	m_textDraw->Update(delta_time);
}

void Mediator::DrawTextMessage()
{
	m_textDraw->Draw();
}

//---------------------------//


//-----------Graph----------//

// GraphLoad

//const int Mediator::GetCharaGraphLoadTotalNum() const
//{
//	return m_charaGraphLoad->GetGraphTotalNum();
//}

const std::vector<CharaGraph::sGraphInfo>& Mediator::GetCharaGraphLoadInfo() const
{
	return m_charaGraphLoad->GetGraphInfo();
}

// CharaGraphDraw

void Mediator::LoadCharacterGraph()
{
	m_charaGraphDraw->LoadCharaGraph();
}

void Mediator::DrawCharacterGraph(tnl::Vector3 pos, int graph_id)
{
	m_charaGraphDraw->DrawCharaGraph(pos, graph_id);
}

//---------------------------//


//----------Camera---------//

// GameCamera

const tnl::Vector3& Mediator::GetCameraPos() const
{
	return m_gameCamera->GetPos();
}

const tnl::Vector3& Mediator::GetCameraForward() const
{
	return m_gameCamera->forward();
}

const tnl::Vector3& Mediator::GetCameraRight() const
{
	return m_gameCamera->right();
}

const tnl::Vector3& Mediator::GetCameraLeft() const
{
	return m_gameCamera->left();
}

const tnl::Vector3& Mediator::GetCameraBack() const
{
	return m_gameCamera->back();
}

const tnl::Matrix& Mediator::GetCameraView() const
{
	return m_gameCamera->GetView();
}

const tnl::Matrix& Mediator::GetCameraProj() const
{
	return m_gameCamera->GetProj();
}

//GameCamera::sCameraInfo Mediator::CurrentGameCameraType()
//{
//	return m_gameCamera->CurrentCameraType();
//}


// CameraLoad

int Mediator::GetCameraLaneHeight() const
{
	return m_cameraLoad->GetLaneHeight();
}

int Mediator::GetCameraLaneWidth() const
{
	return m_cameraLoad->GetLaneWidth();
}

const std::vector<GameCamera::sCamera>& Mediator::GetCameraLaneVector() const
{
	return m_cameraLoad->GetCameraLane();
}

GameCamera::sCameraInfo Mediator::GetCameraTypeInfoById(int id)
{
	return m_cameraLoad->GetCameraInfoById(id);
}

// CameraFrustum
//
//void Mediator::UpdateCameraFrustum()
//{
//	m_cameraFrustum->Update();
//}

//void Mediator::CollisionFrustumRegister()
//{
//	m_cameraFrustum->CollisionRegister();
//}
//
//void Mediator::CollisionFrustumCheck()
//{
//	m_cameraFrustum->CollisionCheck();
//}

//---------------------------//


