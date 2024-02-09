#include "Mediator.h"
#include "../[000]Object/[000]Stage/[000]SkyBox/CinemaBack.h"
#include "../[000]Object/[000]Stage/[000]SkyBox/SkyBox.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneLoad.h"
#include "../[000]Object/[000]Stage/[001]Lane/[000]LaneFunction/LaneMove.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelLoad.h"
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
#include "../[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickGenerator.h"
#include "../[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickPool.h"
#include "../[000]Object/[003]Effect/[000]EffectFunction/EffectLoad.h"
#include "../[000]Object/[004]Score/Score.h"
#include "../[000]Object/[005]Event/[001]Text/[000]TextFunction/TextLoad.h"
#include "../[000]Object/[005]Event/[001]Text/[000]TextFunction/TextDraw.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/[000]CharaGraphFunction/CharaGraphLoad.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/[000]CharaGraphFunction/CharaGraphDraw.h"
#include "../[000]Object/[006]Title/Title.h"
#include "../[000]Object/[007]Gate/[000]GateFunction/GateLoad.h"
#include "../[001]Camera/[000]CameraFunction/CameraLoad.h"


//--------CameraPhase--------//

// CameraPhase

void Mediator::SetNowCameraPhaseState(CameraPhase::eCameraPhase& camera_phase)
{
	m_cameraPhase->SetNowCameraPhase(camera_phase);
}

const CameraPhase::eCameraPhase& Mediator::GetNowCameraPhaseState() const
{
	return m_cameraPhase->GetNowCameraPhase();
}

//----------------------------//

//---------StagePhase---------//

const StagePhase::eStagePhase& Mediator::GetNowStagePhaseState() const
{
	return m_stagePhase->GetNowStagePhase();
}

//---------------------------//


//---------CinemaBack---------//

// CinemaBack

void Mediator::SetCinemaBackIsFirst(bool is_first)
{
	m_cinemaBack->SetIsFirst(is_first);
}

void Mediator::SetCinemaBackIsSecond(bool is_second)
{
	m_cinemaBack->SetIsSecond(is_second);
}

bool Mediator::GetCinemaBackIsSecond() const
{
	return m_cinemaBack->GetIsSecond();
}

void Mediator::SetCinemaBackIsThird(bool is_third)
{
	m_cinemaBack->SetIsThird(is_third);
}

bool Mediator::GetCinemaBackIsThird() const
{
	return m_cinemaBack->GetIsThird();
}


void Mediator::SetIsCinemaBackFog(bool is_fog)
{
	m_cinemaBack->SetIsFog(is_fog);
}

void Mediator::SetIsCinemaBackBubble(bool is_bubble)
{
	m_cinemaBack->SetIsBubble(is_bubble);
}

//----------------------------//


//-----------SkyBox-----------//

// SkyBox

void Mediator::SetSkyIsOp(bool is_op)
{
	m_skyBox->SetIsOp(is_op);
}

//---------------------------//


//-----------Stage-----------//

// LaneLoad

int Mediator::GetStageLaneWidth() const
{
	return m_laneLoad->GetLaneWidth();
}

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

void Mediator::MoveAstarCharaUpdatePos(const float delta_time
										, tnl::Vector3& pos)
{
	m_laneMove->MoveAstarCharaPos(delta_time,pos);
}

void Mediator::MoveAstarCharaUpdateRot(const float delta_time
										, tnl::Vector3& pos
										, tnl::Quaternion& rot)
{
	m_laneMove->MoveAstarCharaRot(delta_time, pos,rot);
}

void Mediator::MoveAstarTargetPos(const float delta_time, tnl::Vector3& pos)
{
	m_laneMove->MoveAstarTarget(delta_time,pos);
}

void Mediator::SetPlayerLookSideRight(bool look_side)
{
	m_laneMove->SetLookSideRight(look_side);
}

bool Mediator::GetPlayerLookSideRight() const
{
	return m_laneMove->GetLookSideRight();
}

void Mediator::SetPlayerLookSideLeft(bool look_side)
{
	m_laneMove->SetLookSideLeft(look_side);
}

bool Mediator::GetPlayerLookSideLeft() const
{
	return m_laneMove->GetLookSideLeft();
}

//---------------------------//


//----------Model-----------//

// modelLoad

const std::vector<Model::sModelInfo>& Mediator::GetStageModelInfo() const
{
	return m_modelLoad ->GetModelInfo();
}

//--------------------------//


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

tnl::Vector3 Mediator::PlayerForward()
{
	return m_player->Forward();
}

// playerLoad

int Mediator::GetPlayerModelGameHdl() const
{
	return m_playerLoad->GetModelGameHdl();
}

int Mediator::GetPlayerModelCinemaHdl() const
{
	return m_playerLoad->GetModelCinemaHdl();
}

int Mediator::GetPlayerAnimBoneIdleCinemaHdl() const
{
	return m_playerLoad->GetAnimBoneIdleCinemaHdl();
}

int Mediator::GetPlayerAnimBoneMoveGameHdl() const
{
	return m_playerLoad->GetAnimBoneMoveGameHdl();
}

int Mediator::GetPlayerAnimBoneMoveCinemaHdl() const
{
	return m_playerLoad->GetAnimBoneMoveCinemaHdl();
}

int Mediator::GetPlayerAnimBoneBloomGameHdl() const
{
	return m_playerLoad->GetAnimBoneBloomGameHdl();
}

int Mediator::GetPlayerAnimBoneDanceGameHdl() const
{
	return m_playerLoad->GetAnimBoneDanceGameHdl();
}

int Mediator::GetPlayerAnimBoneDanceCinemaHdl() const
{
	return m_playerLoad->GetAnimBoneDanceCinemaHdl();
}

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

void Mediator::UpdatePlayerMoveMatrix(float delta_time)
{
	m_playerMove->Update(delta_time);
}

// playerDraw

void Mediator::InitializePlayerDraw()
{
	m_playerDraw->Initialize();
}

void Mediator::UpdatePlayerAnim(const float delta_time)
{
	m_playerDraw->Update(delta_time);
}

void Mediator::DrawPlayerModel()
{
	m_playerDraw->Draw();
}

bool Mediator::GetIsPlayerBloom() const
{
	return m_playerDraw->GetIsBloom();
}

void Mediator::SetAnimElapsedTimeDance(float elapsed_time_dance)
{
	m_playerDraw->SetElapsedTimeDance(elapsed_time_dance);
}

void Mediator::SetIsPlayerEventDance(bool is_dance)
{
	m_playerDraw->SetIsEventDance(is_dance);
}

bool Mediator::GetIsPlayerEventDance() const
{
	return m_playerDraw->GetIsEventDance();
}

void Mediator::CinemaPlayerAnimIdle(const float delta_time)
{
	m_playerDraw->CinemaAnimIdle(delta_time);
}

void Mediator::CinemaPlayerAnimMove(const float delta_time)
{
	m_playerDraw->CinemaAnimMove(delta_time);
}

void Mediator::CinemaPlayerAnimDance(const float delta_time)
{
	m_playerDraw->CinemaAnimDance(delta_time);
}

// playerSkill

void Mediator::UpdatePlayerSkill(const float delta_time)
{
	m_playerSkill->Update(delta_time);
}

// playerCollision

void Mediator::InitCollisionRegister()
{
	m_playerCollision->CollisionRegisterPlayerToGimmick();
	m_playerCollision->CollisionRegisterMeshToGimmick();
	m_playerCollision->CollisionRegisterPlayerToPartner();
}

void Mediator::UpdateCollisionCheck()
{
	m_playerCollision->CollisionCheck();
}

// CinemaPlayer

const tnl::Vector3& Mediator::GetCinemaPlayerPos() const
{
	return m_cinemaPlayer->GetPos();
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

const float Mediator::GetPartnerCollisionSize() const
{
	return m_partner->GetCollisionSize();
}

GameCamera::sCamera Mediator::CurrentCameraLane()
{
	return m_partner->CurrentCamera();
}

// PartnerLoad

int Mediator::GetPartnerModelHdl() const
{
	return m_partnerLoad->GetModelGameHdl();
}

int Mediator::GetPartnerAnimBoneIdleHdl() const
{
	return m_partnerLoad->GetAnimBoneIdleHdl();
}

int Mediator::GetPartnerAnimBoneMoveHdl() const
{
	return m_partnerLoad->GetAnimBoneMoveGameHdl();
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

void Mediator::InitializePartnerDraw()
{
	m_partnerDraw->Initialize();
}

void Mediator::UpdatePartnerAnim(const float delta_time)
{
	m_partnerDraw->Update(delta_time);
}

void Mediator::DrawPartnerModel()
{
	m_partnerDraw->Draw();
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

const Lane::sLaneEvent& Mediator::GetEventLane() const
{
	return m_cameraTargetPlayer->GetEvent();
}

bool Mediator::GetIsTargetSpeedUp() const
{
	return m_cameraTargetPlayer->GetIsSpeedUp();
}

//bool Mediator::GetIsTargetMoveUp() const
//{
//	return m_cameraTargetPlayer->GetIsSpeedUp();
//}

bool Mediator::GetIsTargetMoveDown() const
{
	return m_cameraTargetPlayer->GetIsMoveDown();
}

//-------------------------------//


//------CinemaCameraTarget------//

// CinemaCameraTarget

const tnl::Vector3& Mediator::GetCinemaCameraTargetPos() const
{
	return m_cinemaCameraTarget->GetPos();
}

//-----------------------------//


//----------Butterfly----------//

// Butterfly

const tnl::Vector3& Mediator::GetButterflyPos() const
{
	return m_butterfly->GetPos();
}

void Mediator::SetButterflyIsOpActive(bool is_op_active)
{
	m_butterfly->SetIsOpActive(is_op_active);
}

bool Mediator::GetButterflyIsPowder() const
{
	return m_butterfly->GetIsPowder();
}

void Mediator::SetButterflyIsCinemaActive(bool is_cinema_active)
{
	m_butterfly->SetIsCinemaActive(is_cinema_active);
}

bool Mediator::GetButterflyIsCinemaActive() const
{
	return m_butterfly->GetIsCinemaActive();
}

// ButterflyLoad

int Mediator::GetButterflyModelHdl() const
{
	return m_butterflyLoad->GetModelHdl();
}


//-----------------------------//


//-----------Gimmick-----------//

// GimmickPool

std::shared_ptr<Gimmick> Mediator::GetNotActiveGimmickPool(std::vector<std::shared_ptr<Gimmick>>& gimmicks) 
{
	return m_gimmickPool->GetNotActiveGimmick(gimmicks);
}

std::vector<std::shared_ptr<Gimmick>>& Mediator::GetGimmickTypePools(Gimmick::eGimmickType type)
{
	return m_gimmickPool->GetGimmickPools(type);
}

// GimmickGenerator

bool Mediator::GetIsGimmickFlowerActive() const
{
	return m_gimmickGenerator->GetIsFlowerActive();
}

bool Mediator::GetIsGimmickGroundActive() const
{
	return m_gimmickGenerator->GetIsGroundActive();
}

//--------------------------//


//----------Effect----------//

// EffectLoad

const std::vector<Effect::sEffectType>& Mediator::GetEffectLoadInfo() const
{
	return m_effectLoad->GetEffectType();
}

//--------------------------//


//----------Score-----------//

// Score

void Mediator::SetIsScoreAdd(bool is_add)
{
	m_score->SetIsAdd(is_add);
}

//--------------------------//


//------------Text-----------//

// TextLoad

void Mediator::GetTextsLoadLane()
{
	m_textLoad->GetTextsLane();
}


const std::vector<Text::sTextData>& Mediator::GetTextsLoadForLane() const
{
	return m_textLoad->GetTextsForLane();
}

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

//---------------------------//


//-----------Graph----------//

// GraphLoad

const std::vector<CharaGraph::sGraphInfo>& Mediator::GetCharaGraphLoadInfo() const
{
	return m_charaGraphLoad->GetGraphInfo();
}

// CharaGraphDraw

//---------------------------//


//------------Title-----------//

// Title

void Mediator::SetTitleIsDraw(bool is_draw)
{
	m_title->SetIsDraw(is_draw);
}

bool Mediator::GetTitleIsDisappear() const
{
	return m_title->GetIsDisappear();
}

//---------------------------//


//------------Gate-----------//

// GateLoad

const std::vector<Gate::sGateInfo>& Mediator::GetGatesInfo() const
{
	return m_gateLoad->GetGates();
}

//---------------------------//


//----------Camera---------//

// GameCamera

const tnl::Vector3& Mediator::GetCameraForward() const
{
	return m_gameCamera->forward();
}

const tnl::Vector3& Mediator::GetCameraRight() const
{
	return m_gameCamera->right();
}

void Mediator::IsInCameraFlustum()
{
	m_gameCamera->IsInFlustum();
}

bool Mediator::IsCameraFixed() const
{
	return m_gameCamera->IsFixed();
}

// CameraLoad

const std::vector<GameCamera::sCamera>& Mediator::GetCameraLaneVector() const
{
	return m_cameraLoad->GetCameraLane();
}

GameCamera::sCameraInfo Mediator::GetCameraTypeInfoById(int id)
{
	return m_cameraLoad->GetCameraInfoById(id);
}

// CinemaCamera



//---------------------------//


