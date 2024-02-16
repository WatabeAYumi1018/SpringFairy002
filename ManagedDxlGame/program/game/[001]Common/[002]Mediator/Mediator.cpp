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
#include "../[000]Object/[005]Event/[001]Text/Text.h"
#include "../[000]Object/[005]Event/[001]Text/[000]TextFunction/TextLoad.h"
#include "../[000]Object/[005]Event/[001]Text/[000]TextFunction/TextDraw.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/[000]CharaGraphFunction/CharaGraphLoad.h"
#include "../[000]Object/[006]Title/Title.h"
#include "../[000]Object/[007]Gate/[000]GateFunction/GateLoad.h"
#include "../[000]Object/[008]OtherGraph/EnterGraph.h"
#include "../[000]Object/[008]OtherGraph/ChangeGraph.h"
#include "../[000]Object/[008]OtherGraph/ChildChangeGraph.h"
#include "../[001]Camera/[000]CameraFunction/CameraLoad.h"
#include "../[004]ScreenShot/ScreenShot.h"


//--------CameraPhase--------//

// CameraPhase

const CameraPhase::eCameraPhase& Mediator::GetNowCameraPhaseState() const
{
	// std::weak_ptr‚©‚çstd::shared_ptr‚Ö•ÏŠ·
	std::shared_ptr<CameraPhase> shared_cameraPhase = m_cameraPhase.lock(); 
	
	if (shared_cameraPhase)
	{
		return shared_cameraPhase->GetNowCameraPhase();
	}
	else
	{
		// —áŠO‚ð“Š‚°‚é
		throw std::runtime_error("CameraPhase shared pointer is expired");
	}
}

//----------------------------//


//---------StagePhase---------//

const StagePhase::eStagePhase& Mediator::GetNowStagePhaseState() const
{
	std::shared_ptr<StagePhase> shared_stagePhase = m_stagePhase.lock();

	if (shared_stagePhase)
	{
		return shared_stagePhase->GetNowStagePhase();
	}
	else
	{
		throw std::runtime_error("StagePhase shared pointer is expired");
	}
}

//---------------------------//


//---------CinemaBack---------//

// CinemaBack

void Mediator::SetIsCinemaBackFog(bool is_fog)
{
	std::shared_ptr<CinemaBack> shared_cinemaBack = m_cinemaBack.lock();

	if (shared_cinemaBack)
	{
		shared_cinemaBack->SetIsFog(is_fog);
	}
	else
	{
		throw std::runtime_error("CinemaBack shared pointer is expired");
	}
}

void Mediator::SetIsCinemaBackBubble(bool is_bubble)
{
	std::shared_ptr<CinemaBack> shared_cinemaBack = m_cinemaBack.lock();

	if (shared_cinemaBack)
	{
		shared_cinemaBack->SetIsBubble(is_bubble);
	}
	else
	{
		throw std::runtime_error("CinemaBack shared pointer is expired");
	}
}

//----------------------------//


//-----------SkyBox-----------//

// SkyBox

void Mediator::SetSkyIsOp(bool is_op)
{
	std::shared_ptr<SkyBox> shared_skyBox = m_skyBox.lock();

	if (shared_skyBox)
	{
		shared_skyBox->SetIsOp(is_op);
	}
	else
	{
		throw std::runtime_error("SkyBox shared pointer is expired");
	}
}

//---------------------------//


//-----------Stage-----------//

// LaneLoad

int Mediator::GetStageLaneWidth() const
{
	std::shared_ptr<LaneLoad> shared_laneLoad = m_laneLoad.lock();

	if (shared_laneLoad)
	{
		return shared_laneLoad->GetLaneWidth();
	}
	else
	{
		throw std::runtime_error("LaneLoad shared pointer is expired");
	}
}

int Mediator::GetStageLaneHeight() const
{
	std::shared_ptr<LaneLoad> shared_laneLoad = m_laneLoad.lock();

	if (shared_laneLoad)
	{
		return shared_laneLoad->GetLaneHeight();
	}
	else
	{
		throw std::runtime_error("LaneLoad shared pointer is expired");
	}
}

const std::vector<Lane::sLaneEvent>& Mediator::GetStageLaneEvent() const
{
	std::shared_ptr<LaneLoad> shared_laneLoad = m_laneLoad.lock();

	if (shared_laneLoad)
	{
		return shared_laneLoad->GetLaneEvent();
	}
	else
	{
		throw std::runtime_error("LaneLoad shared pointer is expired");
	}
}

const std::vector<Lane::sLane>& Mediator::GetStageLane()const
{
	std::shared_ptr<LaneLoad> shared_laneLoad = m_laneLoad.lock();

	if (shared_laneLoad)
	{
		return shared_laneLoad->GetLane();
	}
	else
	{
		throw std::runtime_error("LaneLoad shared pointer is expired");
	}
}

// LaneMove

void Mediator::MoveAstarCharaUpdatePos(const float delta_time
										, tnl::Vector3& pos)
{
	std::shared_ptr<LaneMove> shared_laneMove = m_laneMove.lock();

	if (shared_laneMove)
	{
		shared_laneMove->MoveAstarCharaPos(delta_time, pos);
	}
	else
	{
		throw std::runtime_error("LaneMove shared pointer is expired");
	}
}

void Mediator::MoveAstarCharaUpdateRot(const float delta_time
										, tnl::Vector3& pos
										, tnl::Quaternion& rot)
{
	std::shared_ptr<LaneMove> shared_laneMove = m_laneMove.lock();

	if (shared_laneMove)
	{
		shared_laneMove->MoveAstarCharaRot(delta_time, pos, rot);
	}
	else
	{
		throw std::runtime_error("LaneMove shared pointer is expired");
	}
}

void Mediator::MoveAstarTargetPos(const float delta_time, tnl::Vector3& pos)
{
	std::shared_ptr<LaneMove> shared_laneMove = m_laneMove.lock();

	if (shared_laneMove)
	{
		shared_laneMove->MoveAstarTarget(delta_time, pos);
	}
	else
	{
		throw std::runtime_error("LaneMove shared pointer is expired");
	}

}

void Mediator::SetPlayerLookSideRight(bool look_side)
{
	std::shared_ptr<LaneMove> shared_laneMove = m_laneMove.lock();

	if (shared_laneMove)
	{
		shared_laneMove->SetLookSideRight(look_side);
	}
	else
	{
		throw std::runtime_error("LaneMove shared pointer is expired");
	}
}

bool Mediator::GetPlayerLookSideRight() const
{
	std::shared_ptr<LaneMove> shared_laneMove = m_laneMove.lock();

	if (shared_laneMove)
	{
		return shared_laneMove->GetLookSideRight();
	}
	else
	{
		throw std::runtime_error("LaneMove shared pointer is expired");
	}
}

void Mediator::SetPlayerLookSideLeft(bool look_side)
{
	std::shared_ptr<LaneMove> shared_laneMove = m_laneMove.lock();

	if (shared_laneMove)
	{
		shared_laneMove->SetLookSideLeft(look_side);
	}
	else
	{
		throw std::runtime_error("LaneMove shared pointer is expired");
	}
}

bool Mediator::GetPlayerLookSideLeft() const
{
	std::shared_ptr<LaneMove> shared_laneMove = m_laneMove.lock();

	if (shared_laneMove)
	{
		return shared_laneMove->GetLookSideLeft();
	}
	else
	{
		throw std::runtime_error("LaneMove shared pointer is expired");
	}
}

//---------------------------//


//----------Model-----------//

// modelLoad

const std::vector<Model::sModelInfo>& Mediator::GetStageModelInfo() const
{
	std::shared_ptr<ModelLoad> shared_modelLoad = m_modelLoad.lock();

	if (shared_modelLoad)
	{
		return shared_modelLoad->GetModelInfo();
	}
	else
	{
		throw std::runtime_error("ModelLoad shared pointer is expired");
	}
}

const std::vector<Model::sTreeInfo>& Mediator::GetStageTreeInfo() const
{
	std::shared_ptr<ModelLoad> shared_modelLoad = m_modelLoad.lock();

	if (shared_modelLoad)
	{
		return shared_modelLoad->GetTreeInfo();
	}
	else
	{
		throw std::runtime_error("ModelLoad shared pointer is expired");
	}
}

//--------------------------//


//----------Player----------//

// player

void Mediator::SetPlayerPos(tnl::Vector3& pos)
{
	std::shared_ptr<Player> shared_player = m_player.lock();

	if (shared_player)
	{
		shared_player->SetPos(pos);
	}
	else
	{
		throw std::runtime_error("Player shared pointer is expired");
	}
}

void Mediator::SetPlayerRot(tnl::Quaternion& rot)
{
	std::shared_ptr<Player> shared_player = m_player.lock();

	if (shared_player)
	{
		shared_player->SetRot(rot);
	}
	else
	{
		throw std::runtime_error("Player shared pointer is expired");
	}
}

const tnl::Vector3& Mediator::GetPlayerPos() const
{
	std::shared_ptr<Player> shared_player = m_player.lock();

	if (shared_player)
	{
		return shared_player->GetPos();
	}
	else
	{
		throw std::runtime_error("Player shared pointer is expired");
	}
}

const tnl::Quaternion& Mediator::GetPlayerRot() const
{
	std::shared_ptr<Player> shared_player = m_player.lock();

	if (shared_player)
	{
		return shared_player->GetRot();
	}
	else
	{
		throw std::runtime_error("Player shared pointer is expired");
	}
}

float Mediator::GetPlayerCollisionSize() const
{
	std::shared_ptr<Player> shared_player = m_player.lock();

	if (shared_player)
	{
		return shared_player->GetCollisionSize();
	}
	else
	{
		throw std::runtime_error("Player shared pointer is expired");
	}
}

tnl::Vector3 Mediator::PlayerForward()
{
	std::shared_ptr<Player> shared_player = m_player.lock();

	if (shared_player)
	{
		return shared_player->Forward();
	}
	else
	{
		throw std::runtime_error("Player shared pointer is expired");
	}
}

// playerLoad

int Mediator::GetPlayerModelGameHdl() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetModelGameHdl();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

int Mediator::GetPlayerModelCinemaHdl() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetModelCinemaHdl();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

int Mediator::GetPlayerAnimBoneIdleCinemaHdl() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetAnimBoneIdleCinemaHdl();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

int Mediator::GetPlayerAnimBoneMoveGameHdl() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetAnimBoneMoveGameHdl();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

int Mediator::GetPlayerAnimBoneMoveCinemaHdl() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetAnimBoneMoveCinemaHdl();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

int Mediator::GetPlayerAnimBoneBloomGameHdl() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetAnimBoneBloomGameHdl();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

int Mediator::GetPlayerAnimBoneDanceGameHdl() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetAnimBoneDanceGameHdl();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

int Mediator::GetPlayerAnimBoneDanceCinemaHdl() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetAnimBoneDanceCinemaHdl();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

float Mediator::GetPlayerMoveSpeed() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetMoveSpeed();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

float Mediator::GetPlayerMoveRot() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetMoveRot();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

float Mediator::GetPlayerSaltoTotalTime() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetSaltoTotalTime();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

float Mediator::GetPlayerSaltoRadius() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetSaltoRadius();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

float Mediator::GetPlayerSaltoMoveSpeed() const
{
	std::shared_ptr<PlayerLoad> shared_playerLoad = m_playerLoad.lock();

	if (shared_playerLoad)
	{
		return shared_playerLoad->GetSaltoMoveSpeed();
	}
	else
	{
		throw std::runtime_error("PlayerLoad shared pointer is expired");
	}
}

// playerMove

void Mediator::UpdatePlayerMoveMatrix(float delta_time)
{
	std::shared_ptr<PlayerMove> shared_playerMove = m_playerMove.lock();

	if (shared_playerMove)
	{
		shared_playerMove->Update(delta_time);
	}
	else
	{
		throw std::runtime_error("PlayerMove shared pointer is expired");
	}
}

// playerDraw

void Mediator::InitializePlayerDraw()
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		shared_playerDraw->Initialize();
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

void Mediator::UpdatePlayerAnim(const float delta_time)
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		shared_playerDraw->Update(delta_time);
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

void Mediator::DrawPlayerModel()
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		shared_playerDraw->Draw();
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

bool Mediator::GetIsPlayerBloom() const
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		return shared_playerDraw->GetIsBloom();
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

bool Mediator::GetIsPlayerDance() const
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		return shared_playerDraw->GetIsDance();
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

void Mediator::SetAnimElapsedTimeDance(float elapsed_time_dance)
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		shared_playerDraw->SetElapsedTimeDance(elapsed_time_dance);
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

void Mediator::SetIsPlayerEventDance(bool is_dance)
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		shared_playerDraw->SetIsEventDance(is_dance);
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

bool Mediator::GetIsPlayerEventDance() const
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		return shared_playerDraw->GetIsEventDance();
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

void Mediator::CinemaPlayerAnimIdle(const float delta_time)
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		shared_playerDraw->CinemaAnimIdle(delta_time);
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

void Mediator::CinemaPlayerAnimMove(const float delta_time)
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		shared_playerDraw->CinemaAnimMove(delta_time);
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

void Mediator::CinemaPlayerAnimDance(const float delta_time)
{
	std::shared_ptr<PlayerDraw> shared_playerDraw = m_playerDraw.lock();

	if (shared_playerDraw)
	{
		shared_playerDraw->CinemaAnimDance(delta_time);
	}
	else
	{
		throw std::runtime_error("PlayerDraw shared pointer is expired");
	}
}

// playerCollision

void Mediator::InitCollisionRegister()
{
	std::shared_ptr<PlayerCollision> shared_playerCollision = m_playerCollision.lock();

	if (shared_playerCollision)
	{
		shared_playerCollision->CollisionRegisterPlayerToGimmick();
		shared_playerCollision->CollisionRegisterMeshToGimmick();
		shared_playerCollision->CollisionRegisterPlayerToPartner();
	}
	else
	{
		throw std::runtime_error("PlayerCollision shared pointer is expired");
	}
}

void Mediator::UpdateCollisionCheck()
{
	std::shared_ptr<PlayerCollision> shared_playerCollision = m_playerCollision.lock();

	if (shared_playerCollision)
	{
		shared_playerCollision->CollisionCheck();
	}
	else
	{
		throw std::runtime_error("PlayerCollision shared pointer is expired");
	}
}

// CinemaPlayer

const tnl::Vector3& Mediator::GetCinemaPlayerPos() const
{
	std::shared_ptr<CinemaPlayer> shared_cinemaPlayer = m_cinemaPlayer.lock();

	if (shared_cinemaPlayer)
	{
		return shared_cinemaPlayer->GetPos();
	}
	else
	{
		throw std::runtime_error("CinemaPlayer shared pointer is expired");
	}
}

bool Mediator::GetCinemaPlayerIsDance() const
{
	std::shared_ptr<CinemaPlayer> shared_cinemaPlayer = m_cinemaPlayer.lock();

	if (shared_cinemaPlayer)
	{
		return shared_cinemaPlayer->GetIsDance();
	}
	else
	{
		throw std::runtime_error("CinemaPlayer shared pointer is expired");
	}
}

//--------------------------//


//---------Partner---------//

// Partner

void Mediator::SetPartnerPos(tnl::Vector3& pos)
{
	std::shared_ptr<Partner> shared_partner = m_partner.lock();

	if (shared_partner)
	{
		shared_partner->SetPos(pos);
	}
	else
	{
		throw std::runtime_error("Partner shared pointer is expired");
	}
}

const tnl::Vector3& Mediator::GetPartnerPos() const
{
	std::shared_ptr<Partner> shared_partner = m_partner.lock();

	if (shared_partner)
	{
		return shared_partner->GetPos();
	}
	else
	{
		throw std::runtime_error("Partner shared pointer is expired");
	}
}

void Mediator::SetPartnerRot(tnl::Quaternion& rot)
{
	std::shared_ptr<Partner> shared_partner = m_partner.lock();

	if (shared_partner)
	{
		shared_partner->SetRot(rot);
	}
	else
	{
		throw std::runtime_error("Partner shared pointer is expired");
	}
}

const tnl::Quaternion& Mediator::GetPartnerRot() const
{
	std::shared_ptr<Partner> shared_partner = m_partner.lock();

	if (shared_partner)
	{
		return shared_partner->GetRot();
	}
	else
	{
		throw std::runtime_error("Partner shared pointer is expired");
	}
}

const float Mediator::GetPartnerCollisionSize() const
{
	std::shared_ptr<Partner> shared_partner = m_partner.lock();

	if (shared_partner)
	{
		return shared_partner->GetCollisionSize();
	}
	else
	{
		throw std::runtime_error("Partner shared pointer is expired");
	}
}

GameCamera::sCamera Mediator::CurrentCameraLane()
{
	std::shared_ptr<Partner> shared_partner = m_partner.lock();

	if (shared_partner)
	{
		return shared_partner->CurrentCamera();
	}
	else
	{
		throw std::runtime_error("Partner shared pointer is expired");
	}
}

// PartnerLoad

int Mediator::GetPartnerModelHdl() const
{
	std::shared_ptr<PartnerLoad> shared_partnerLoad = m_partnerLoad.lock();

	if (shared_partnerLoad)
	{
		return shared_partnerLoad->GetModelGameHdl();
	}
	else
	{
		throw std::runtime_error("PartnerLoad shared pointer is expired");
	}
}

int Mediator::GetPartnerAnimBoneIdleHdl() const
{
	std::shared_ptr<PartnerLoad> shared_partnerLoad = m_partnerLoad.lock();

	if (shared_partnerLoad)
	{
		return shared_partnerLoad->GetAnimBoneIdleHdl();
	}
	else
	{
		throw std::runtime_error("PartnerLoad shared pointer is expired");
	}
}

int Mediator::GetPartnerAnimBoneMoveHdl() const
{
std::shared_ptr<PartnerLoad> shared_partnerLoad = m_partnerLoad.lock();

	if (shared_partnerLoad)
	{
		return shared_partnerLoad->GetAnimBoneMoveGameHdl();
	}
	else
	{
		throw std::runtime_error("PartnerLoad shared pointer is expired");
	}
}

// PartnerMove

void Mediator::UpdatePartnerMoveMatrix(const float delta_time)
{
	std::shared_ptr<PartnerMove> shared_partnerMove = m_partnerMove.lock();

	if (shared_partnerMove)
	{
		shared_partnerMove->Update(delta_time);
	}
	else
	{
		throw std::runtime_error("PartnerMove shared pointer is expired");
	}
}

void Mediator::SetIsPartnerPushed(bool is_pushed)
{
	std::shared_ptr<PartnerMove> shared_partnerMove = m_partnerMove.lock();

	if (shared_partnerMove)
	{
		shared_partnerMove->SetIsPushed(is_pushed);
	}
	else
	{
		throw std::runtime_error("PartnerMove shared pointer is expired");
	}
}

// PartnerDraw

void Mediator::InitializePartnerDraw()
{
	std::shared_ptr<PartnerDraw> shared_partnerDraw = m_partnerDraw.lock();

	if (shared_partnerDraw)
	{
		shared_partnerDraw->Initialize();
	}
	else
	{
		throw std::runtime_error("PartnerDraw shared pointer is expired");
	}
}

void Mediator::UpdatePartnerAnim(const float delta_time)
{
	std::shared_ptr<PartnerDraw> shared_partnerDraw = m_partnerDraw.lock();

	if (shared_partnerDraw)
	{
		shared_partnerDraw->Update(delta_time);
	}
	else
	{
		throw std::runtime_error("PartnerDraw shared pointer is expired");
	}
}

void Mediator::DrawPartnerModel()
{
	std::shared_ptr<PartnerDraw> shared_partnerDraw = m_partnerDraw.lock();

	if (shared_partnerDraw)
	{
		shared_partnerDraw->Draw();
	}
	else
	{
		throw std::runtime_error("PartnerDraw shared pointer is expired");
	}
}

//--------------------------//


//----CameraTargetPlayer----//

// CameraTargetPlayer

const tnl::Vector3& Mediator::GetCameraTargetPlayerPos() const
{
	std::shared_ptr<CameraTargetPlayer> shared_cameraTargetPlayer = m_cameraTargetPlayer.lock();

	if (shared_cameraTargetPlayer)
	{
		return shared_cameraTargetPlayer->GetPos();
	}
	else
	{
		throw std::runtime_error("CameraTargetPlayer shared pointer is expired");
	}
}

const GameCamera::sCameraInfo& Mediator::GetTargetCameraInfo() const
{
	std::shared_ptr<CameraTargetPlayer> shared_cameraTargetPlayer = m_cameraTargetPlayer.lock();

	if (shared_cameraTargetPlayer)
	{
		return shared_cameraTargetPlayer->GetCameraInfo();
	}
	else
	{
		throw std::runtime_error("CameraTargetPlayer shared pointer is expired");
	}
}

const Lane::sLaneEvent& Mediator::GetCurrentEventLane() const
{
	std::shared_ptr<CameraTargetPlayer> shared_cameraTargetPlayer = m_cameraTargetPlayer.lock();

	if (shared_cameraTargetPlayer)
	{
		return shared_cameraTargetPlayer->GetCurrentEvent();
	}
	else
	{
		throw std::runtime_error("CameraTargetPlayer shared pointer is expired");
	}
}

bool Mediator::GetIsTargetSpeedUp() const
{
	std::shared_ptr<CameraTargetPlayer> shared_cameraTargetPlayer = m_cameraTargetPlayer.lock();

	if (shared_cameraTargetPlayer)
	{
		return shared_cameraTargetPlayer->GetIsSpeedUp();
	}
	else
	{
		throw std::runtime_error("CameraTargetPlayer shared pointer is expired");
	}
}

//-------------------------------//


//------CinemaCameraTarget------//

// CinemaCameraTarget

const tnl::Vector3& Mediator::GetCinemaCameraTargetPos() const
{
	std::shared_ptr<CinemaCameraTarget> shared_cinemaCameraTarget = m_cinemaCameraTarget.lock();

	if (shared_cinemaCameraTarget)
	{
		return shared_cinemaCameraTarget->GetPos();
	}
	else
	{
		throw std::runtime_error("CinemaCameraTarget shared pointer is expired");
	}
}

//-----------------------------//


//----------Butterfly----------//

// Butterfly

const tnl::Vector3& Mediator::GetButterflyPos() const
{
	std::shared_ptr<Butterfly> shared_butterfly = m_butterfly.lock();

	if (shared_butterfly)
	{
		return shared_butterfly->GetPos();
	}
	else
	{
		throw std::runtime_error("Butterfly shared pointer is expired");
	}
}

void Mediator::SetButterflyIsOpActive(bool is_op_active)
{
	std::shared_ptr<Butterfly> shared_butterfly = m_butterfly.lock();

	if (shared_butterfly)
	{
		shared_butterfly->SetIsOpActive(is_op_active);
	}
	else
	{
		throw std::runtime_error("Butterfly shared pointer is expired");
	}
}

void Mediator::SetButterflyIsCinemaActive(bool is_cinema_active)
{
	std::shared_ptr<Butterfly> shared_butterfly = m_butterfly.lock();

	if (shared_butterfly)
	{
		shared_butterfly->SetIsCinemaActive(is_cinema_active);
	}
	else
	{
		throw std::runtime_error("Butterfly shared pointer is expired");
	}
}

bool Mediator::GetButterflyIsClear() const
{
	std::shared_ptr<Butterfly> shared_butterfly = m_butterfly.lock();

	if (shared_butterfly)
	{
		return shared_butterfly->GetIsClear();
	}
	else
	{
		throw std::runtime_error("Butterfly shared pointer is expired");
	}
}

const tnl::Vector3& Mediator::GetButterflyNextDirection() const
{
	std::shared_ptr<Butterfly> shared_butterfly = m_butterfly.lock();

	if (shared_butterfly)
	{
		return shared_butterfly->GetNextDirection();
	}
	else
	{
		throw std::runtime_error("Butterfly shared pointer is expired");
	}
}


bool Mediator::GetButterflyIsCinemaActive() const
{
	std::shared_ptr<Butterfly> shared_butterfly = m_butterfly.lock();

	if (shared_butterfly)
	{
		return shared_butterfly->GetIsCinemaActive();
	}
	else
	{
		throw std::runtime_error("Butterfly shared pointer is expired");
	}
}

// ButterflyLoad

int Mediator::GetButterflyModelHdl() const
{
	std::shared_ptr<ButterflyLoad> shared_butterflyLoad = m_butterflyLoad.lock();

	if (shared_butterflyLoad)
	{
		return shared_butterflyLoad->GetModelHdl();
	}
	else
	{
		throw std::runtime_error("ButterflyLoad shared pointer is expired");
	}
}

//-----------------------------//


//-----------Gimmick-----------//

// Gimmick

const tnl::Vector3& Mediator::GetGimmickPos() const
{
	std::shared_ptr<Gimmick> shared_gimmick = m_gimmick.lock();

	if (shared_gimmick)
	{
		return shared_gimmick->GetPos();
	}
	else
	{
		throw std::runtime_error("Gimmick shared pointer is expired");
	}
}

bool Mediator::GetGimmickIsCollision() const
{
	std::shared_ptr<Gimmick> shared_gimmick = m_gimmick.lock();

	if (shared_gimmick)
	{
		return shared_gimmick->GetIsCollision();
	}
	else
	{
		throw std::runtime_error("Gimmick shared pointer is expired");
	}
}

// GimmickPool

std::vector<std::shared_ptr<Gimmick>>& Mediator::GetGimmickTypePools(Gimmick::eGimmickType type)
{
	std::shared_ptr<GimmickPool> shared_gimmickPool = m_gimmickPool.lock();

	if (shared_gimmickPool)
	{
		return shared_gimmickPool->GetGimmickPools(type);
	}
	else
	{
		throw std::runtime_error("GimmickPool shared pointer is expired");
	}
}

// GimmickGenerator

bool Mediator::GetIsGimmickFlowerActive() const
{
	std::shared_ptr<GimmickGenerator> shared_gimmickGenerator = m_gimmickGenerator.lock();

	if (shared_gimmickGenerator)
	{
		return shared_gimmickGenerator->GetIsFlowerActive();
	}
	else
	{
		throw std::runtime_error("GimmickGenerator shared pointer is expired");
	}
}

bool Mediator::GetIsGimmickGroundActive() const
{
	std::shared_ptr<GimmickGenerator> shared_gimmickGenerator = m_gimmickGenerator.lock();

	if (shared_gimmickGenerator)
	{
		return shared_gimmickGenerator->GetIsGroundActive();
	}
	else
	{
		throw std::runtime_error("GimmickGenerator shared pointer is expired");
	}
}

//--------------------------//


//----------Effect----------//

// Effect

void Mediator::SetEffectIsScreen(bool is_screen)
{
	std::shared_ptr<Effect> shared_effect = m_effect.lock();

	if (shared_effect)
	{
		shared_effect->SetIsScreen(is_screen);
	}
	else
	{
		throw std::runtime_error("Effect shared pointer is expired");
	}

}

// EffectLoad

const std::vector<Effect::sEffectType>& Mediator::GetEffectLoadInfo() const
{
	std::shared_ptr<EffectLoad> shared_effectLoad = m_effectLoad.lock();

	if (shared_effectLoad)
	{
		return shared_effectLoad->GetEffectType();
	}
	else
	{
		throw std::runtime_error("EffectLoad shared pointer is expired");
	}
}

//--------------------------//


//----------Score-----------//

// Score

void Mediator::SetIsScoreAdd(bool is_add)
{
	std::shared_ptr<Score> shared_score = m_score.lock();

	if (shared_score)
	{
		shared_score->SetIsAdd(is_add);
	}
	else
	{
		throw std::runtime_error("Score shared pointer is expired");
	}
}

//--------------------------//


//------------Text-----------//

// Text

int Mediator::GetTextWindowAlpha() const
{
	std::shared_ptr<Text> shared_text = m_text.lock();

	if (shared_text)
	{
		return shared_text->GetWindowAlpha();
	}
	else
	{
		throw std::runtime_error("Text shared pointer is expired");
	}
}

// TextLoad

const std::vector<Text::sTextData>& Mediator::GetTextsLoadAll() const
{
	std::shared_ptr<TextLoad> shared_textLoad = m_textLoad.lock();

if (shared_textLoad)
	{
		return shared_textLoad->GetTextsAll();
	}
	else
	{
		throw std::runtime_error("TextLoad shared pointer is expired");
	}
}

// TextDraw

void Mediator::InitializeText()
{
	std::shared_ptr<TextDraw> shared_textDraw = m_textDraw.lock();

	if (shared_textDraw)
	{
		shared_textDraw->Initialize();
	}
	else
	{
		throw std::runtime_error("TextDraw shared pointer is expired");
	}
}

void Mediator::UpdateText(const float delta_time)
{
	std::shared_ptr<TextDraw> shared_textDraw = m_textDraw.lock();

	if (shared_textDraw)
	{
		shared_textDraw->Update(delta_time);
	}
	else
	{
		throw std::runtime_error("TextDraw shared pointer is expired");
	}
}

void Mediator::DrawTextMessage()
{
	std::shared_ptr<TextDraw> shared_textDraw = m_textDraw.lock();

	if (shared_textDraw)
	{
		shared_textDraw->Draw();
	}
	else
	{
		throw std::runtime_error("TextDraw shared pointer is expired");
	}
}

bool Mediator::GetIsTextDrawEnd()
{
	std::shared_ptr<TextDraw> shared_textDraw = m_textDraw.lock();

	if (shared_textDraw)
	{
		return shared_textDraw->GetIsEnd();
	}
	else
	{
		throw std::runtime_error("TextDraw shared pointer is expired");
	}
}

int Mediator::GetNowTextDrawID()const
{
	std::shared_ptr<TextDraw> shared_textDraw = m_textDraw.lock();

	if (shared_textDraw)
	{
		return shared_textDraw->GetNowTextID();
	}
	else
	{
		throw std::runtime_error("TextDraw shared pointer is expired");
	}
}

const std::vector<Text::sTextData>& Mediator::GetLaneTextDrawData() const
{
	std::shared_ptr<TextDraw> shared_textDraw = m_textDraw.lock();

	if (shared_textDraw)
	{
		return shared_textDraw->GetLaneTextData();
	}
	else
	{
		throw std::runtime_error("TextDraw shared pointer is expired");
	}
}

//---------------------------//


//-----------Graph----------//

// CharaGraph

void Mediator::SetGraphIsSlidOutPlayer(bool is_slide_out_player)
{
	std::shared_ptr<CharaGraph> shared_charaGraph = m_charaGraph.lock();

	if (shared_charaGraph)
	{
		shared_charaGraph->SetIsSlidOutPlayer(is_slide_out_player);
	}
	else
	{
		throw std::runtime_error("CharaGraph shared pointer is expired");
	}
}

void Mediator::SetGraphIsSlidOutPartner(bool is_slide_out_partner)
{
	std::shared_ptr<CharaGraph> shared_charaGraph = m_charaGraph.lock();

	if (shared_charaGraph)
	{
		shared_charaGraph->SetIsSlidOutPartner(is_slide_out_partner);
	}
	else
	{
		throw std::runtime_error("CharaGraph shared pointer is expired");
	}
}

// CharaGraphLoad

const std::vector<CharaGraph::sGraphInfo>& Mediator::GetCharaGraphLoadInfo() const
{
	std::shared_ptr<CharaGraphLoad> shared_charaGraphLoad = m_charaGraphLoad.lock();

	if (shared_charaGraphLoad)
	{
		return shared_charaGraphLoad->GetGraphInfo();
	}
	else
	{
		throw std::runtime_error("CharaGraphLoad shared pointer is expired");
	}
}

//---------------------------//


//------------Title-----------//

// Title

void Mediator::SetTitleIsDraw(bool is_draw)
{
	std::shared_ptr<Title> shared_title = m_title.lock();

	if (shared_title)
	{
		shared_title->SetIsDraw(is_draw);
	}
	else
	{
		throw std::runtime_error("Title shared pointer is expired");
	}
}

bool Mediator::GetTitleIsDisappear() const
{
	std::shared_ptr<Title> shared_title = m_title.lock();

	if (shared_title)
	{
		return shared_title->GetIsDisappear();
	}
	else
	{
		throw std::runtime_error("Title shared pointer is expired");
	}
}

//---------------------------//


//------------Gate-----------//

// GateLoad

const std::vector<Gate::sGateInfo>& Mediator::GetGatesInfo() const
{
	std::shared_ptr<GateLoad> shared_gateLoad = m_gateLoad.lock();

	if (shared_gateLoad)
	{
		return shared_gateLoad->GetGates();
	}
	else
	{
		throw std::runtime_error("GateLoad shared pointer is expired");
	}
}

//---------------------------//


//--------OtherGraph---------//

// EnterGraph

void Mediator::SetEnterGraphIsActive(bool is_active)
{
	std::shared_ptr<EnterGraph> shared_enterGraph = m_enterGraph.lock();

	if (shared_enterGraph)
	{
		return shared_enterGraph->SetIsActive(is_active);
	}
	else
	{
		throw std::runtime_error("EnterGraph shared pointer is expired");
	}
}

// ChangeGraph

void Mediator::SetChangeGraphIsFlower(bool is_active)
{
	std::shared_ptr<ChangeGraph> shared_changeGraph = m_changeGraph.lock();

	if (shared_changeGraph)
	{
		shared_changeGraph->SetIsFlower(is_active);
	}
	else
	{
		throw std::runtime_error("ChangeGraph shared pointer is expired");
	}
}

void Mediator::SetChangeGraphIsWood(bool is_active)
{
	std::shared_ptr<ChangeGraph> shared_changeGraph = m_changeGraph.lock();

	if (shared_changeGraph)
	{
		shared_changeGraph->SetIsWood(is_active);
	}
	else
	{
		throw std::runtime_error("ChangeGraph shared pointer is expired");
	}
}

void Mediator::SetChangeGraphIsFancy(bool is_active)
{
	std::shared_ptr<ChangeGraph> shared_changeGraph = m_changeGraph.lock();

	if (shared_changeGraph)
	{
		shared_changeGraph->SetIsFancy(is_active);
	}
	else
	{
		throw std::runtime_error("ChangeGraph shared pointer is expired");
	}
}

void Mediator::SetChangeGraphIsActiveWhite(bool is_active)
{
	std::shared_ptr<ChangeGraph> shared_changeGraph = m_changeGraph.lock();

	if (shared_changeGraph)
	{
		shared_changeGraph->SetIsActiveWhite(is_active);
	}
	else
	{
		throw std::runtime_error("ChangeGraph shared pointer is expired");
	}
}

// ChildChangeGraph

void Mediator::SetChildGraphIsFlower(bool is_active)
{
	std::shared_ptr<ChildChangeGraph> shared_childChangeGraph = m_childChangeGraph.lock();

	if (shared_childChangeGraph)
	{
		shared_childChangeGraph->SetIsFlower(is_active);
	}
	else
	{
		throw std::runtime_error("ChildChangeGraph shared pointer is expired");
	}
}

void Mediator::SetChildGraphIsWood(bool is_active)
{
	std::shared_ptr<ChildChangeGraph> shared_childChangeGraph = m_childChangeGraph.lock();

	if (shared_childChangeGraph)
	{
		shared_childChangeGraph->SetIsWood(is_active);
	}
	else
	{
		throw std::runtime_error("ChildChangeGraph shared pointer is expired");
	}
}

void Mediator::SetChildGraphIsFancy(bool is_active)
{
	std::shared_ptr<ChildChangeGraph> shared_childChangeGraph = m_childChangeGraph.lock();

	if (shared_childChangeGraph)
	{
		shared_childChangeGraph->SetIsFancy(is_active);
	}
	else
	{
		throw std::runtime_error("ChildChangeGraph shared pointer is expired");
	}
}

void Mediator::SetChildGraphIsActiveWhite(bool is_active)
{
	std::shared_ptr<ChildChangeGraph> shared_childChangeGraph = m_childChangeGraph.lock();

	if (shared_childChangeGraph)
	{
		shared_childChangeGraph->SetIsActiveWhite(is_active);
	}
	else
	{
		throw std::runtime_error("ChildChangeGraph shared pointer is expired");
	}
}

// OtherGraphLoad

const std::vector<ChangeGraph::sChangeGraphInfo>& Mediator::GetChangeGraphInfo() const
{
	std::shared_ptr<OtherGraphLoad> shared_otherGraphLoad = m_otherGraphLoad.lock();

	if (shared_otherGraphLoad)
	{
		return shared_otherGraphLoad->GetGraphInfo();
	}
	else
	{
		throw std::runtime_error("OtherGraphLoad shared pointer is expired");
	}
}

//---------------------------//


//----------Camera---------//

// GameCamera

const tnl::Vector3& Mediator::GetGameCameraPos() const
{
	std::shared_ptr<GameCamera> shared_gameCamera = m_gameCamera.lock();

	if (shared_gameCamera)
	{
		return shared_gameCamera->GetPos();
	}
	else
	{
		throw std::runtime_error("GameCamera shared pointer is expired");
	}
}

const tnl::Vector3& Mediator::GetCameraForward() const
{
	std::shared_ptr<GameCamera> shared_gameCamera = m_gameCamera.lock();

	if (shared_gameCamera)
	{
		return shared_gameCamera->forward();
	}
	else
	{
		throw std::runtime_error("GameCamera shared pointer is expired");
	}
}

const tnl::Vector3& Mediator::GetCameraRight() const
{
	std::shared_ptr<GameCamera> shared_gameCamera = m_gameCamera.lock();

	if (shared_gameCamera)
	{
		return shared_gameCamera->right();
	}
	else
	{
		throw std::runtime_error("GameCamera shared pointer is expired");
	}
}

void Mediator::IsInCameraFlustum()
{
	std::shared_ptr<GameCamera> shared_gameCamera = m_gameCamera.lock();

	if (shared_gameCamera)
	{
		shared_gameCamera->IsInFlustum();
	}
	else
	{
		throw std::runtime_error("GameCamera shared pointer is expired");
	}
}

bool Mediator::IsCameraFixed() const
{
	std::shared_ptr<GameCamera> shared_gameCamera = m_gameCamera.lock();

	if (shared_gameCamera)
	{
		return shared_gameCamera->IsFixed();
	}
	else
	{
		throw std::runtime_error("GameCamera shared pointer is expired");
	}
}

// CameraLoad

const std::vector<GameCamera::sCamera>& Mediator::GetCameraLaneVector() const
{
	std::shared_ptr<CameraLoad> shared_cameraLoad = m_cameraLoad.lock();

	if (shared_cameraLoad)
	{
		return shared_cameraLoad->GetCameraLane();
	}
	else
	{
		throw std::runtime_error("CameraLoad shared pointer is expired");
	}
}

GameCamera::sCameraInfo Mediator::GetCameraTypeInfoById(int id)
{
	std::shared_ptr<CameraLoad> shared_cameraLoad = m_cameraLoad.lock();

	if (shared_cameraLoad)
	{
		return shared_cameraLoad->GetCameraInfoById(id);
	}
	else
	{
		throw std::runtime_error("CameraLoad shared pointer is expired");
	}
}

// CinemaCamera

const tnl::Vector3& Mediator::GetCinemaCameraPos() const
{
	std::shared_ptr<CinemaCamera> shared_cinemaCamera = m_cinemaCamera.lock();

	if (shared_cinemaCamera)
	{
		return shared_cinemaCamera->GetPos();
	}
	else
	{
		throw std::runtime_error("CinemaCamera shared pointer is expired");
	}
}

void Mediator::SetCinemaCameraIsActive(bool is_active)
{
	std::shared_ptr<CinemaCamera> shared_cinemaCamera = m_cinemaCamera.lock();

	if (shared_cinemaCamera)
	{
		shared_cinemaCamera->SetIsActive(is_active);
	}
	else
	{
		throw std::runtime_error("CinemaCamera shared pointer is expired");
	}
}

bool Mediator::GetCinemaCameraIsActive() const
{
	std::shared_ptr<CinemaCamera> shared_cinemaCamera = m_cinemaCamera.lock();

	if (shared_cinemaCamera)
	{
		return shared_cinemaCamera->GetIsActive();
	}
	else
	{
		throw std::runtime_error("CinemaCamera shared pointer is expired");
	}
}

//---------------------------//


//---------ScreenShot--------//

// ScreenShot

bool Mediator::GetIsScreenShot() const
{
	std::shared_ptr<ScreenShot> shared_screenShot = m_screenShot.lock();

	if (shared_screenShot)
	{
		return shared_screenShot->GetIsShot();
	}
	else
	{
		throw std::runtime_error("ScreenShot shared pointer is expired");
	}
}

//---------------------------//
