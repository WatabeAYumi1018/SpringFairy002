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
#include "../[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickLoad.h"
//#include "../[000]Object/[002]Item/[000]ItemFunction/ItemDraw.h"
#include "../[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickGenerator.h"
#include "../[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickPool.h"
#include "../[000]Object/[003]Effect/[000]EffectFunction/EffectLoad.h"
#include "../[000]Object/[005]Event/[001]Text/[000]TextFunction/TextLoad.h"
#include "../[000]Object/[005]Event/[001]Text/[000]TextFunction/TextDraw.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/[000]CharaGraphFunction/CharaGraphLoad.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/[000]CharaGraphFunction/CharaGraphDraw.h"
#include "../[001]Camera/[000]CameraFunction/CameraLoad.h"
#include "../[001]Camera/[000]CameraFunction/CameraFlustum.h"


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

const std::vector<Lane::sLaneEvent>& Mediator::GetStageLaneEvent() const
{
	return m_laneLoad->GetLaneEvent();
}

const std::vector<Lane::sLane>& Mediator::GetStageLane()const
{
	return m_laneLoad->GetLane();
}

// LaneMove

void Mediator::MoveAstarCharaMatrix(const float delta_time
								, tnl::Vector3& pos
								, tnl::Quaternion& rot)
{
	m_laneMove->MoveAstarChara(delta_time,pos,rot);
}

void Mediator::MoveAstarTargetPos(const float delta_time, tnl::Vector3& pos)
{
	m_laneMove->MoveAstarTarget(delta_time,pos);
}

void Mediator::SetPlayerLookSide(bool look_side)
{
	m_laneMove->SetLookSide(look_side);
}

//void Mediator::SetPlayerLookSideLeft(bool look_side)
//{
//	m_laneMove->SetLookSideLeft(look_side);
//}

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

const std::vector<std::shared_ptr<dxe::Mesh>>& Mediator::PlayerGetMeshs() const
{
	return m_player->GetMeshs();
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
	m_playerCollision->CollisionRegisterPlayerToItem();
	m_playerCollision->CollisionRegisterMeshToItem();
	m_playerCollision->CollisionRegisterPlayerToPartner();
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

void Mediator::SetPartnerScale(tnl::Vector3& scale)
{
	m_partner->SetScale(scale);
}


const float Mediator::GetPartnerCollisionSize() const
{
	return m_partner->GetCollisionSize();
}


// PartnerMove

void Mediator::UpdatePartnerMoveMatrix(const float delta_time)
{
	m_partnerMove->Update(delta_time);
}

void Mediator::SetIsPartnerPushed(bool is_pushed)
{
	m_partnerMove->SetIsPushed(is_pushed);
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

const GameCamera::sCameraInfo& Mediator::GetTargetCameraInfo() const
{
	return m_cameraTargetPlayer->GetCameraInfo();
}

Gimmick::sGimmick Mediator::CurrentTargetGimmickLane()
{
	return m_cameraTargetPlayer->CurrentGimmickLane();
}

const Lane::sLaneEvent& Mediator::GetEventLane() const
{
	return m_cameraTargetPlayer->GetEvent();
}


//--------------------------//


//----------Model-----------//

// model

//const tnl::Vector3& Mediator::GetModelPos() const
//{
//	return m_model->GetPos();
//}
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


//-----------Gimmick-----------//

// Gimmick

void Mediator::SetGimmickIsActive(bool is_active)
{
	m_gimmick->SetIsActive(is_active);
}

bool Mediator::GetGimmickIsHit() const
{
	return m_gimmick->GetIsHit();
}

// GimmickLoad

int Mediator::GetGimmickIdNum() const
{
	return m_gimmickLoad->GetIdNum();
}

const std::vector<Gimmick::sGimmick>& Mediator::GetGimmickLoadLane() const
{
	return m_gimmickLoad->GetGimmickLane();
}

const std::vector<Gimmick::sGimmickType>& Mediator::GetGimmickTypeInfo() const
{
	return m_gimmickLoad->GetGimmickTypeInfo();
}
	
Gimmick::sGimmickType Mediator::GetGimmickLoadInfoById(int id)
{
	return m_gimmickLoad->GetGimmickInfoById(id);
}

// GimmickPool

std::shared_ptr<Gimmick> Mediator::GetNotActiveGimmickPool()
{
	return m_gimmickPool->GetNotActiveGimmick();
}

const std::vector<std::shared_ptr<Gimmick>>& Mediator::GetPoolGimmick() const
{
	return m_gimmickPool->GetGimmicks();
}


// GimmickGenerator

bool Mediator::GetIsGimmickFlowerActive() const
{
	return m_gimmickGenerator->GetIsFlowerActive();
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

// TextLoad

//const std::vector<std::string>& Mediator::GetTextsLoadLane()
//{
//	return m_textLoad->GetTextsLane();
//}

//const std::vector<Text::sTextData>& Mediator::GetTextsLoadLane()
//{
//	return m_textLoad->GetTextsLane();
//}

void Mediator::GetTextsLoadLane()
{
	m_textLoad->GetTextsLane();
}


const std::vector<Text::sTextData>& Mediator::GetTextsLoadForLane() const
{
	return m_textLoad->GetTextsForLane();
}

//const std::vector<std::string>& Mediator::GetTextsLoadMessageForLane() const
//{
//	return m_textLoad->GetTextsMessageForLane();
//}


// TextDraw

void Mediator::UpdateText(const float delta_time)
{
	m_textDraw->Update(delta_time);
}

void Mediator::DrawTextMessage()
{
	m_textDraw->Draw();
}

void Mediator::SetIsTextDrawEnd(bool is_end)
{
	m_textDraw->SetIsEnd(is_end);
}


//void Mediator::SetTextDrawLine(const std::vector<std::string>& text_lines)
//{
//	m_textDraw->ResetText(text_lines);
//}

//bool Mediator::IsTextDrawEnd()
//{
//	return m_textDraw->IsTextEnd();
//}

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

void Mediator::DrawCharacterGraph(int graph_id)
{
	m_charaGraphDraw->DrawCharaGraph(graph_id);
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

//const tnl::Vector3& Mediator::GetCameraLeft() const
//{
//	return m_gameCamera->left();
//}
//
//const tnl::Vector3& Mediator::GetCameraBack() const
//{
//	return m_gameCamera->back();
//}

//const tnl::Matrix& Mediator::GetCameraView() const
//{
//	return m_gameCamera->GetView();
//}
//
//const tnl::Matrix& Mediator::GetCameraProj() const
//{
//	return m_gameCamera->GetProj();
//}

//GameCamera::sCameraInfo Mediator::CurrentGameCameraType()
//{
//	return m_gameCamera->CurrentCameraType();
//}

tnl::Vector3 Mediator::GetFlustumNormal(dxe::Camera::eFlustum flusum)
{
	return m_gameCamera->getFlustumNormal(flusum);
}

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

// CameraFlustum

void Mediator::IsIntersectCameraFlustum(const float delta_time)
{
	m_cameraFlustum->IsIntersectFlustum(delta_time);
}


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


