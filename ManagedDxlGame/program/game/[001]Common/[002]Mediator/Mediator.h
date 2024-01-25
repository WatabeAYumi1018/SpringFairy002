#pragma once
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"
#include "../[000]Object/[000]Stage/[003]Model/Model.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelLoad.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelPool.h"
#include "../[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickLoad.h"
#include "../[000]Object/[003]Effect/Effect.h"
#include "../[000]Object/[005]Event/[001]Text/Text.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/CharaGraph.h"
#include "../[001]Camera/GameCamera.h"
#include "../[003]Phase/StagePhase.h"



class LaneLoad;
class LaneMove;

class Character;

class Player;
class PlayerLoad;
class PlayerMove;	
class PlayerDraw;
class PlayerSkill;
class PlayerCollision;

class Partner;
class PartnerMove;
class PartnerDraw;

class CameraTargetPlayer;

class Gimmick;
class GimmickLoad;
class GimmickGenerator;
class GimmickPool;

class EffectLoad;

class TextLoad;
class TextDraw;

class CharaGraphLoad;
class CharaGraphDraw;

class GameCamera;
class CameraLoad;

class Mediator
{

private:

	//--------------------�|�C���^--------------------//

	std::shared_ptr<StagePhase> m_stagePhase = nullptr;

	std::shared_ptr<Lane> m_lane = nullptr;
	std::shared_ptr<LaneLoad> m_laneLoad = nullptr;
	std::shared_ptr<LaneMove> m_laneMove = nullptr;

	std::shared_ptr<Character> m_character = nullptr;

	std::shared_ptr<Player> m_player = nullptr;
	std::shared_ptr<PlayerLoad> m_playerLoad = nullptr;
	std::shared_ptr<PlayerMove> m_playerMove = nullptr;
	std::shared_ptr<PlayerDraw> m_playerDraw = nullptr;
	std::shared_ptr<PlayerSkill> m_playerSkill = nullptr;
	std::shared_ptr<PlayerCollision> m_playerCollision = nullptr;

	std::shared_ptr<Partner> m_partner = nullptr;
	std::shared_ptr<PartnerMove> m_partnerMove = nullptr;
	std::shared_ptr<PartnerDraw> m_partnerDraw = nullptr;

	std::shared_ptr<CameraTargetPlayer> m_cameraTargetPlayer = nullptr;

	std::shared_ptr<Model> m_model = nullptr;
	std::shared_ptr<ModelLoad> m_modelLoad = nullptr;
	std::shared_ptr<ModelPool> m_modelPool = nullptr;

	std::shared_ptr<Gimmick> m_gimmick = nullptr;
	std::shared_ptr<GimmickLoad> m_gimmickLoad = nullptr;
	std::shared_ptr<GimmickGenerator> m_gimmickGenerator = nullptr;
	std::shared_ptr<GimmickPool> m_gimmickPool = nullptr;

	std::shared_ptr<EffectLoad> m_effectLoad = nullptr;

	std::shared_ptr<Text> m_text = nullptr;
	std::shared_ptr<TextLoad> m_textLoad = nullptr;
	std::shared_ptr<TextDraw> m_textDraw = nullptr;

	std::shared_ptr<CharaGraphLoad> m_charaGraphLoad = nullptr;
	std::shared_ptr<CharaGraphDraw> m_charaGraphDraw = nullptr;

	std::shared_ptr<GameCamera> m_gameCamera = nullptr;
	std::shared_ptr<CameraLoad> m_cameraLoad = nullptr;

	//------------------------------------------------//

public:

	//-------------------�����o�֐�-------------------//

	//---------StagePhase---------//

	// stagePhase

	// �X�e�[�W�t�F�[�Y�擾
	// �Q�ƌ� ... StagePhase::m_stage_phase
	// �Q�Ɛ� ... �t�F�[�Y��Ԃ̎擾���K�v�ȑS�N���X�i�t�F�[�Y�J�ڂ̉e�������N���X�j
	StagePhase::eStagePhase GetNowStagePhaseState() const;

	//---------------------------//


	//-----------Stage-----------//

	// LaneLoad

	// ���[���z��̕��擾
	// �Q�ƌ� ... LaneLoad::m_lane_width
	// �Q�Ɛ� ... ���[���z��̏�񂪕K�v�ȑS�N���X
	int GetStageLaneWidth() const;

	// ���[���z��̍����擾
	// �Q�ƌ� ... LaneLoad::m_lane_height
	// �Q�Ɛ� ... ���[���z��̏�񂪕K�v�ȑS�N���X
	int GetStageLaneHeight() const;

	// ���[���z��̏��擾
	// �Q�ƌ� ... LaneLoad::m_lanes
	// �Q�Ɛ� ... ���[���z��̏�񂪕K�v�ȑS�N���X
	const std::vector<Lane::sLane>& GetStageLane() const;

	// �C�x���g�z��̏��擾
	// �Q�ƌ� ... LaneLoad::m_lane_events
	// �Q�Ɛ� ... �C�x���g�z��̏�񂪕K�v�ȑS�N���X
	const std::vector<Lane::sLaneEvent>& GetStageLaneEvent() const;

	// LaneMove

	// �����ړ��ɂ����W�Ɖ�]�X�V
	// �Q�ƌ� ... LoadMove::MoveAstar(float delta_time)
	// �Q�Ɛ� ... �����o�H�ɂ��X�V���K�v�ȑS�N���X
	void MoveAstarCharaMatrix(const float delta_time
							 ,tnl::Vector3& pos
							 ,tnl::Quaternion& rot);

	// �����ړ��ɂ����W�X�V
	// �Q�ƌ� ... LoadMove::MoveAstarPos(float delta_time)
	// �Q�Ɛ� ... �����o�H�ɂ��X�V���K�v�ȑS�N���X
	void MoveAstarTargetPos(const float delta_time, tnl::Vector3& pos);

	// �L�����̉�]�E�t���O�ݒ�
	// �Q�ƌ� ... Player::m_look_side_right
	// �Q�Ɛ� ... GameCamera::ConditionType()
	void SetPlayerLookSide(bool look_side);

	//// �L�����̉�]���t���O�擾
	//// �Q�ƌ� ... Player::m_look_side_left
	//// �Q�Ɛ� ... GameCamera::ConditionType()
	//void SetPlayerLookSideLeft(bool look_side);

	//// �����ړ��ɂ�鎟�̃��[�����B����
	//// �Q�ƌ� ... LoadMove::NextLane()
	//// �Q�Ɛ� ... Item::Update(float delta_time)
	//bool NextLaneMove();

	//// �����ړ��ɂ��ړ��O���W�ݒ�
	//// �Q�ƌ� ... LoadMove::m_now_pos
	//// �Q�Ɛ� ... �����o�H�ɂ��X�V���K�v�ȑS�N���X
	//void SetMoveNowPos(tnl::Vector3 pos);

	//// �����ړ��ɂ��ړ�����W�擾
	//// �Q�ƌ� ... LoadMove::m_new_pos
	//// �Q�Ɛ� ... �����o�H�ɂ��X�V���K�v�ȑS�N���X
	//tnl::Vector3 GetMoveNewPos() const;

	//// �����ړ��ɂ��ړ��O��]�ݒ�
	//// �Q�ƌ� ... LoadMove::m_now_rot
	//// �Q�Ɛ� ... �����o�H�ɂ��X�V���K�v�ȑS�N���X
	//void SetMoveNowRot(tnl::Quaternion rot);

	//// �����ړ��ɂ��ړ����]�擾
	//// �Q�ƌ� ... LoadMove::m_new_rot
	//// �Q�Ɛ� ... �����o�H�ɂ��X�V���K�v�ȑS�N���X
	//tnl::Quaternion GetMoveNewRot() const;

	//---------------------------//


	//----------Player----------//
	
	// player 

	// �v���C���[�̍��W�ݒ�
	// �Q�ƌ� ... Player::m_pos
	// �Q�Ɛ� ... Player�̍��W���K�v�ȑS�N���X
	void SetPlayerPos(tnl::Vector3& pos);

	// �v���C���[�̉�]�擾
	// �Q�ƌ� ... Player::m_rot
	// �Q�Ɛ� ... Player�̉�]���K�v�ȑS�N���X
	void SetPlayerRot(tnl::Quaternion& rot);

	// �v���C���[�̍��W�擾
	// �Q�ƌ� ... Player::m_pos
	// �Q�Ɛ� ... Player�̍��W���K�v�ȑS�N���X
	const tnl::Vector3& GetPlayerPos() const;

	// �v���C���[�̉�]�擾
	// �Q�ƌ� ... Player::m_rot
	// �Q�Ɛ� ... Player�̉�]���K�v�ȑS�N���X
	const tnl::Quaternion& GetPlayerRot() const;

	// �v���C���[�̓����蔻��T�C�Y�擾
	// �Q�ƌ� ... Player::m_collision_size
	// �Q�Ɛ� ... Player�̓����蔻��T�C�Y���K�v�ȑS�N���X
	float GetPlayerCollisionSize() const;

	// �v���C���[�̑O�����̎擾
	// �Q�ƌ� ... Player::tnl::Vector3 Forward();
	// �Q�Ɛ� ... 
	tnl::Vector3 PlayerForward();

	// �v���C���[�̑������[�����擾
	// �Q�ƌ� ... Player::CurrentLane
	// �Q�Ɛ� ... ItemGenerator::GenerateItem()
	Lane::sLane CurrentPlayerLane();

	// �v���C���[�̒��������蔻��p���b�V�����擾
	// �Q�ƌ� ... Player::m_meshs
	// �Q�Ɛ� ... PlayerCollision::CollisionCheck()
	const std::vector<std::shared_ptr<dxe::Mesh>>& PlayerGetMeshs() const;


	// playerLoad

	// �v���C���[�̈ړ����x�擾
	// �Q�ƌ� ... PlayerLoad::m_move_speed
	// �Q�Ɛ� ... PlayerMove
	float GetPlayerMoveSpeed() const;

	// �v���C���[�̈ړ���]�擾
	// �Q�ƌ� ... PlayerLoad::m_rotate_speed
	// �Q�Ɛ� ... PlayerMove
	float GetPlayerMoveRot() const;

	// �v���C���[�̒��Ԃ葍���Ԏ擾
	// �Q�ƌ� ... PlayerLoad::m_salto_total_time
	// �Q�Ɛ� ... PlayerMove
	float GetPlayerSaltoTotalTime() const;

	// �v���C���[�̒��Ԃ蔼�a�擾
	// �Q�ƌ� ... PlayerLoad::m_salto_radius
	// �Q�Ɛ� ... PlayerMove
	float GetPlayerSaltoRadius() const;

	// �v���C���[�̒��Ԃ�ړ����x�擾
	// �Q�ƌ� ... PlayerLoad::m_salto_move_speed
	// �Q�Ɛ� ... PlayerMove
	float GetPlayerSaltoMoveSpeed() const;


	// playerMove

	//// �v���C���[�̌��݂̃��[��ID�擾
	//// �Q�ƌ� ... PlayerMove::m_current_step
	//// �Q�Ɛ� ... OriginalCamera::RotateBackToPlayer(float delta_time)
	//int GetMoveCurrentStep() const;

	// Player�ړ��ɂ����W�Ɖ�]�̍X�V����
	// �Q�ƌ� ... PlayerMove::Update(float delta_time)
	// �Q�Ɛ� ... Player::Update(float delta_time)
	void UpdatePlayerMoveMatrix(const float delta_time);
	
	//// �����ړ��Ɋւ��鏈��
	//// �Q�ƌ� ... PlayerMove::GetAutoMove()
	//// �Q�Ɛ� ... Player::Initialize()
	//void GetPlayerMoveAutoMove();

	// �v���C���[����̃t���O�擾
	// �Q�ƌ� ... PlayerMove::PushButton()
	// �Q�Ɛ� ... OriginalCamera::RotateBackToPlayer(float delta_time)
	bool GetPushButton();

	//// �����^�]�ɂ��v���C���[�̐V�������W�擾
	//// �Q�ƌ� ... PlayerMove::m_new_player_pos
	//// �Q�Ɛ� ... OriginalCamera::RotateBackToPlayer(float delta_time)
	//tnl::Vector3 GetNewPlayerMovePos();

	//// �����^�]�ɂ��v���C���[�̐V������]�擾
	//// �Q�ƌ� ... PlayerMove::m_new_player_rot
	//// �Q�Ɛ� ... OriginalCamera::RotateBackToPlayer(float delta_time)
	//tnl::Quaternion GetNewPlayerMoveRot();


	//std::vector<std::pair<int, int>> GetMoveGoalProcess();


	// playerDraw

	// Player���f���̃A�j���[�V�����X�V����
	// �Q�ƌ� ... PlayerDraw::Update(float delta_time)
	// �Q�Ɛ� ... Player::Update(float delta_time)
	void UpdatePlayerAnim(const float delta_time);

	// Player���f���̕`�揈��
	// �Q�ƌ� ... PlayerDraw::Draw()
	// �Q�Ɛ� ... Player::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawPlayerModel();

	// �v���C���[�̃��f���n���h���擾
	// �Q�ƌ� ... PlayerDraw::m_model_hdl
	// �Q�Ɛ� ... Player::Player()
	int GetPlayerModelHdl() const ;

	// �U���t���O�擾
	// �Q�ƌ� ... PlayerDraw::m_is_attack
	// �Q�Ɛ� ... Player::Update(float delta_time)
	bool GetIsPlayerAttack() const;

	// playerSkill

	// �v���C���[�X�L���̍X�V����
	// �Q�ƌ� ... PlayerSkill::Update(float delta_time)
	// �Q�Ɛ� ... Player::Update(float delta_time)
	void UpdatePlayerSkill(const float delta_time);

	// playerCollision

	// �v���C���[�̓����蔻��̓o�^
	// �Q�ƌ� ... PlayerCollision::CollisionRegister()
	// �Q�Ɛ� ... Player::Initialize()
	void InitCollisionRegister();

	// �v���C���[�̓����蔻��̍X�V
	// �Q�ƌ� ... PlayerCollision::CollisionCheck()
	// �Q�Ɛ� ... Player::Update(float delta_time)
	void UpdateCollisionCheck();

	//--------------------------//


	//---------Partner---------//

	// Partner

	// �p�[�g�i�[�̍��W�ݒ�
	// �Q�ƌ� ... Partner::m_pos
	// �Q�Ɛ� ... Partner�̍��W���K�v�ȑS�N���X
	void SetPartnerPos(tnl::Vector3& pos);

	// �p�[�g�i�[�̍��W�擾
	// �Q�ƌ� ... Partner::m_pos
	// �Q�Ɛ� ... Partner�̍��W���K�v�ȑS�N���X
	const tnl::Vector3& GetPartnerPos() const;

	// �p�[�g�i�[�̉�]�ݒ�
	// �Q�ƌ� ... Partner::m_rot
	// �Q�Ɛ� ... Partner�̉�]���K�v�ȑS�N���X
	void SetPartnerRot(tnl::Quaternion& rot);

	// �p�[�g�i�[�̃X�P�[���ݒ�
	// �Q�ƌ� ... Partner::m_scale
	// �Q�Ɛ� ... Partner�̃X�P�[�����K�v�ȑS�N���X
	void SetPartnerScale(tnl::Vector3& scale);

	// �p�[�g�i�[�̓����蔻��T�C�Y�擾
	// �Q�ƌ� ... Partner::m_collision_size
	// �Q�Ɛ� ... PartnerMove::Update(float delta_time)
	const float GetPartnerCollisionSize() const;

	// �p�[�g�i�[�̉�]�擾
	// �Q�ƌ� ... Partner::m_rot
	// �Q�Ɛ� ... Partner�̉�]���K�v�ȑS�N���X
	const tnl::Quaternion& GetPartnerRot() const;

	// PartnerMove

	// Partner�ړ��ɂ����W�Ɖ�]�̍X�V����
	// �Q�ƌ� ... PartnerMove::Update(float delta_time)
	// �Q�Ɛ� ... Partner::Update(float delta_time)
	void UpdatePartnerMoveMatrix(const float delta_time);

	// �p�[�g�i�[�̏Փ˃t���O�̐ݒ�
	// �Q�ƌ� ... PartnerMove::m_is_pushed
	// �Q�Ɛ� ... Partner::Update(float delta_time)
	void SetIsPartnerPushed(bool is_pushed);

	// PartnerDraw

	// Partner���f���̃A�j���[�V�����X�V����
	// �Q�ƌ� ... PartnerDraw::Update(float delta_time)
	// �Q�Ɛ� ... Partner::Update(float delta_time)
	void UpdatePartnerAnim(const float delta_time);

	// Partner���f���̕`�揈��
	// �Q�ƌ� ... PartnerDraw::Draw()
	// �Q�Ɛ� ... Partner::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawPartnerModel();

	// Partner�̃��f���n���h���擾
	// �Q�ƌ� ... PartnerDraw::m_model_hdl
	// �Q�Ɛ� ... Partner::Initialize()
	int GetPartnerModelHdl() const;

	//--------------------------//


	//----CameraTargetPlayer----//

	// CameraTargetPlayer

	// �J�����̃^�[�Q�b�g���W�擾
	// �Q�ƌ� ... CameraTargetPlayer::GetPos()
	// �Q�Ɛ� ... OriginalCamera::target_
	const tnl::Vector3& GetCameraTargetPlayerPos() const;

	// ���݂̃J�����^�C�v�擾
	// �Q�ƌ� ... CameraTargetPlayer::m_camera_info
	// �Q�Ɛ� ... 
	const GameCamera::sCameraInfo& GetTargetCameraInfo() const;

	//// �L�����N�^�[�̑����A�C�e�����[�����擾
	//// �Q�ƌ� ... Character::Item::sItem CurrentItemLane()
	//// �Q�Ɛ� ... ItemGenerator::GenerateItem()
	//Gimmick::sGimmick CurrentTargetGimmickLane();

	// �L�����N�^�[�̑����C�x���g���[�����擾
	// �Q�ƌ� ... Character::m_event
	// �Q�Ɛ� ... �C�x���g���[�����K�v�ȑS�N���X
	const Lane::sLaneEvent& GetEventLane() const;


	//--------------------------//


	//----------Model-----------//

	// model

	//// ���f���̍��W�ݒ�
	//// �Q�ƌ� ... Model::m_pos
	//// �Q�Ɛ� ... PlayerSkill::SeqBloom(float delta_time)
	//const tnl::Vector3& GetModelPos() const;

	////���f���̐��E�����擾
	//// �Q�ƌ� ... Model::m_world_type
	//// �Q�Ɛ� ... PlayerSkill::SeqBloom(float delta_time)
	//Model::eWorldType GetWorldModelType() const;

	//// ���f���̌ʃA�N�e�B�u�t���O�ݒ�
	//// �Q�ƌ� ... Model::m_is_alive_active
	//// �Q�Ɛ� ... PlayerSkill::SeqBloom(float delta_time)
	//void SetIsModelAliveActive(bool is_active);

	//// ���f���̌ʃA�N�e�B�u�t���O�擾
	//// �Q�ƌ� ... Model::m_is_alive_active
	//// �Q�Ɛ� ... PlayerSkill::SeqBloom(float delta_time)
	//int GetIsModelAliveActive() const;

	//// �A�N�e�B�u���؂�ւ�
	//// �Q�ƌ� ... Model::ToggleActive(bool is_world_active)
	//// �Q�Ɛ� ... PlayerSkill::SeqBloom(float delta_time)
	//void ToggleModelActive(bool is_world_active);

	// modelLoad

	// �X�e�[�W���f���̑����擾
	// �Q�ƌ� ... ModelLoad::m_model_total_num
	// �Q�Ɛ� ... ModelPool::�֘A����֐�
	int GetStageModelTotalNum() const;

	//// �X�e�[�W���f���̃x�N�^�[�����擾
	//// �Q�ƌ� ... ModelLoad::m_model_vec_height
	//// �Q�Ɛ� ... Model::Initialize()
	//int GetStageModelVecHeight() const ;

	//// �X�e�[�W���f���̃x�N�^�[���擾
	//// �Q�ƌ� ... ModelLoad::m_model_vec_width
	//// �Q�Ɛ� ... Model::Initialize()
	//int GetStageModelVecWidth() const ;

	//// �X�e�[�W���f���̃x�N�^�[�擾
	//// �Q�ƌ� ... ModelLoad::m_stage_tree
	//// �Q�Ɛ� ... Model::�֘A����֐�
	//const std::vector<Model::sStageModel>& GetStageTreeVector() const;

	//// �X�e�[�W���f���̃x�N�^�[�擾
	//// �Q�ƌ� ... ModelLoad::m_stage_grass
	//// �Q�Ɛ� ... Model::�֘A����֐�
	//const std::vector<Model::sStageModel>& GetStageGrassVector() const;

	// �X�e�[�W���f���̏��擾
	// �Q�ƌ� ... ModelLoad::m_model_info
	// �Q�Ɛ� ... ModelPool::�֘A����֐�
	const std::vector<Model::sMeshModelType>& GetStageModelTypeInfo() const;

	//// �X�e�[�W���f����id�擾
	//// �Q�ƌ� ... ModelLoad::GetModelInfoById(int id)
	//// �Q�Ɛ� ... ModelPool::�֘A����֐�
	//Model::sStageModelType GetStageModelInfoById(int id);

	// modelPool

	//// ���E�ύX�ɂ�郂�f���̈�ăA�N�e�B�u��
	//// �Q�ƌ� ... ModelPool::DeactivateAllModels(Model::eWorldType world_type)
	//// �Q�Ɛ� ... StagePhase::�V�[�P���X�֐�
	//void IsActivatePoolAllModels(Model::eWorldType world_type);

	// �������E�̃x�N�^�[�擾
	// �Q�ƌ� ... ModelPool::GetModels()
	// �Q�Ɛ� ... StagePhase::�V�[�P���X�֐�
	std::vector<std::shared_ptr<Model>>& GetPoolModels() const;

	//// �����_���ȃ��f���̃|�C���^���擾
	//// �Q�ƌ� ... ModelPool::GetRandomModel(Model::eWorldType world_type)
	//// �Q�Ɛ� ... PlayerSkill::SeqBloom(float delta_time)
	//std::shared_ptr<Model> GetPoolRandomModel(Model::eWorldType world_type);


	//--------------------------//


	//-----------Gimmick-----------//

	// Gimmick

	// �A�C�e���̃A�N�e�B�u���ݒ�
	// �Q�ƌ� ... Gimmick::m_is_active
	// �Q�Ɛ� ... GimmickGenerator::Update(const float delta_time)
	void SetGimmickIsActive(bool is_active);

	// �A�C�e���̓����蔻���Ԏ擾
	// �Q�ƌ� ... Gimmick::m_is_hit
	// �Q�Ɛ� ... �����蔻�肪�K�v�ȑS�N���X
	bool GetGimmickIsHit() const;

	// GimmickLoad

	//// �A�C�e�����f���̑����擾
	//// �Q�ƌ� ... GimmickLoad::m_id_num
	//// �Q�Ɛ� ... Gimmick::Initialize()
	//int GetGimmickIdNum() const;

	//// �A�C�e�����[���z����擾
	//// �Q�ƌ� ... GimmickLoad::m_gimmick_lane
	//// �Q�Ɛ� ... Gimmick::�֘A����֐�
	//const std::vector<Gimmick::sGimmick>& GetGimmickLoadLane() const;

	//// �A�C�e�����z����擾
	//// �Q�ƌ� ... GimmickLoad::m_gimmick_info
	//// �Q�Ɛ� ... Gimmick::�֘A����֐�
	//const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeInfo() const;

	// �A�C�e�����f����id�擾
	// �Q�ƌ� ... GimmickLoad::GetGimmickInfoById()
	// �Q�Ɛ� ... Gimmick::
	Gimmick::sGimmickTypeInfo GetGimmickLoadInfoById(int id);

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeLoadPlants() const;

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeLoadTrees() const;

	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmickTypeLoadSkyFlowers() const;


	// GimmickPool

	// �A�C�e���v�[���̃A�N�e�B�u��Ԏ擾
	// �Q�ƌ� ... GimmickPool::GetNotActiveGimmick()
	// �Q�Ɛ� ... GimmickGenerator::
	std::shared_ptr<Gimmick> GetNotActiveGimmickPool();

	// �A�C�e���v�[���̃x�N�^�[�擾
	// �Q�ƌ� ... GimmickPool::GetGimmicks()
	// �Q�Ɛ� ... GimmickGenerator::SeqDelete(float delta_time)
	const std::vector<std::shared_ptr<Gimmick>>& GetPoolGimmick() const;

	// GimmickGenerator

	// �A�C�e���t�����[�̃A�N�e�B�u��Ԏ擾
	// �Q�ƌ� ... GimmickGenerator::m_is_flower_active
	// �Q�Ɛ� ... 
	bool GetIsGimmickFlowerActive() const ; 


	//// �A�C�e���̐����t���O�ݒ�
	//// �Q�ƌ� ... GimmickGenerator::m_is_create
	//// �Q�Ɛ� ... LaneMove::MoveAstar( ... );
	//void SetItemIsCreate(bool is_create);

	//// �A�C�e���̍폜�t���O�ݒ�
	//// �Q�ƌ� ... ItemGenerator::m_is_delete
	//// �Q�Ɛ� ... LaneMove::MoveAstar( ... );
	//void SetItemIsDelete(bool is_delete);

	//--------------------------//


	//----------Effect----------//

	// EffectLoad

	// �G�t�F�N�g���̎擾
	// �Q�ƌ� ... EffectLoad::m_effect_info
	// �Q�Ɛ� ... Effect::�֘A����֐�
	const std::vector<Effect::sEffectType>& GetEffectLoadInfo() const;

	//--------------------------//

	//------------Text-----------//

	// TextLoad

	// ���[��ID�ɊY������e�L�X�g�����̎擾
	// �Q�ƌ� ... TextLoad::GetTextsLane()
	// �Q�Ɛ� ... Text::�֘A����֐�
	void GetTextsLoadLane();
	//const std::vector<std::string>& GetTextsLoadLane();
	//const std::vector<Text::sTextData>& GetTextsLoadLane();
	
	// ���[��ID�ɊY�����S�Ă̍\���̃f�[�^�̎擾
	// �Q�ƌ� ... TextLoad::m_texts_for_lane
	// �Q�Ɛ� ... Text::�֘A����֐�
	const std::vector<Text::sTextData>& GetTextsLoadForLane() const;

	//// ���[��ID�ɊY������S�Ẵe�L�X�g�����̎擾
	//// �Q�ƌ� ... TextLoad::m_texts_message_for_lane
	//// �Q�Ɛ� ... Text::�֘A����֐�
	//const std::vector<std::string>& GetTextsLoadMessageForLane() const;

	 
	 
	// TextDraw

	// �e�L�X�g�̏���
	// �Q�ƌ� ... TextDraw::Update(const float delta_time)
	// �Q�Ɛ� ... Text::Update(float delta_time)
	void UpdateText(const float delta_time);

	// �e�L�X�g�̕`��
	// �Q�ƌ� ... TextDraw::Draw()
	// �Q�Ɛ� ... Text::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawTextMessage();

	// �e�L�X�g�̕`��I���t���O�̎擾
	// �Q�ƌ� ... TextDraw::m_is_end
	// �Q�Ɛ� ... TextLoad
	void SetIsTextDrawEnd(bool is_end);

	//// �`��e�L�X�g��ID�ݒ�
	//// �Q�ƌ� ... TextDraw::SetTextDrawLine(const std::vector<std::string>& text_lines)
	//// �Q�Ɛ� ... Text::Update(float delta_time)
	//void SetTextDrawLine(const std::vector<std::string>& text_lines);

	//// �Y��ID�̃e�L�X�g�̕\���I���t���O
	//// �Q�ƌ� ... TextDraw::IsTextEnd()
	//// �Q�Ɛ� ... Text::Update(float delta_time)
	//bool IsTextDrawEnd();

	//---------------------------//

	
	//--------CharaGraph---------//

	// CharaGraphLoad

	//// �O���t�B�b�N�̑����擾
	//// �Q�ƌ� ... CharaGraphLoad::m_graph_total_num
	//// �Q�Ɛ� ... CharaGraph
	//const int GetCharaGraphLoadTotalNum() const ;

	// �O���t�B�b�N�f�[�^�擾
	// �Q�ƌ� ... CharaGraphLoad::m_graph_info
	// �Q�Ɛ� ... CharaGraph
	const std::vector<CharaGraph::sGraphInfo>& GetCharaGraphLoadInfo() const;

	// CharaGraphDraw

	// �L�����N�^�[�O���t�B�b�N�̃��[�h
	// �Q�ƌ� ... CharaGraphDraw::LoadCharaGraph()
	// �Q�Ɛ� ... CharaGraph
	void LoadCharacterGraph();

	// �L�����N�^�[�O���t�B�b�N�̕`��
	// �Q�ƌ� ... CharaGraphDraw::DrawCharaGraph()
	// �Q�Ɛ� ... CharaGraph
	void DrawCharacterGraph(int graph_id);


	//---------------------------//


	//----------Camera---------//

	// GameCamera

	// �J�����̍��W�擾
	// �Q�ƌ� ... GameCamera::pos_
	// �Q�Ɛ� ... PlayerMove::Update(const float delta_time)
	const tnl::Vector3& GetCameraPos() const;

	// �J�����̑O�����擾
	// �Q�ƌ� ... dxe::GameCamera::forward()
	// �Q�Ɛ� ... PlayerMove::ControlMoveMatrix(float delta_time)
	const tnl::Vector3& GetCameraForward() const;

	// �J�����̉E�����擾
	// �Q�ƌ� ... dxe::GameCamera::right()
	// �Q�Ɛ� ... PlayerMove::ControlMoveMatrix(float delta_time)
	const tnl::Vector3& GetCameraRight() const;

	//// �J�����̏�����擾
	//// �Q�ƌ� ... dxe::GameCamera::left()
	//// �Q�Ɛ� ... PlayerMove::ControlMoveMatrix(float delta_time)
	//const tnl::Vector3& GetCameraLeft() const;

	//// �J�����̉������擾
	//// �Q�ƌ� ... dxe::GameCamera::back()
	//// �Q�Ɛ� ... PlayerMove::ControlMoveMatrix(float delta_time)
	//const tnl::Vector3& GetCameraBack() const;

	//// �J�����̃r���[�s��擾
	//// �Q�ƌ� ... dxe::Camera::view_
	//// �Q�Ɛ� ... CameraFrustum::Update()
	//const tnl::Matrix& GetCameraView() const;

	//// �J�����̎ˉe�s��擾
	//// �Q�ƌ� ... dxe::Camera::proj_
	//// �Q�Ɛ� ... CameraFrustum::Update()
	//const tnl::Matrix& GetCameraProj() const;

	// �t���X�^���̖@���x�N�g���擾
	// �Q�ƌ� ... dxe::Camera::getFlustumNormal(eFlustum flustum)
	// �Q�Ɛ� ... CameraFrustum
	tnl::Vector3 GetFlustumNormal(dxe::Camera::eFlustum flusum);


	// CameraLoad

	// �J�����z��̍����擾
	// �Q�ƌ� ... CameraLoad::m_lane_height
	// �Q�Ɛ� ... Camera::CurrentCamera()
	int GetCameraLaneHeight() const;

	// �J�����z��̕��擾
	// �Q�ƌ� ... CameraLoad::m_lane_width
	// �Q�Ɛ� ... Camera::CurrentCamera()
	int GetCameraLaneWidth() const;

	// �J�����z��̏��擾
	// �Q�ƌ� ... CameraLoad::m_cameras
	// �Q�Ɛ� ... Camera::�֘A����֐�
	const std::vector<GameCamera::sCamera>& GetCameraLaneVector() const;

	// �J�������̎擾
	// �Q�ƌ� ... CameraLoad::GetCameraInfoById(int id)
	// �Q�Ɛ� ... Camera::�֘A����֐�
	GameCamera::sCameraInfo GetCameraTypeInfoById(int id);

	// CameraFlustum

	//// �t���X�^���̍X�V
	//// �Q�ƌ� ... CameraFrustum::Update()
	//// �Q�Ɛ� ... Camera::Update(float delta_time)
	//void UpdateCameraFrustum();

	//// �t���X�^���̓����蔻��̓o�^
	//// �Q�ƌ� ... CameraFrustum::CollisionRegister()
	//// �Q�Ɛ� ... Camera::Initialize()
	//void CollisionFrustumRegister();

	//// �t���X�^���̓����蔻��̍X�V
	//// �Q�ƌ� ... CameraFrustum::CollisionCheck()
	//// �Q�Ɛ� ... Camera::Update(float delta_time)
	//void CollisionFrustumCheck();

	// �t���X�^���̓����蔻�菈��
	// �Q�ƌ� ... CameraFlustum::IsIntersectFlustum(const float delta_time)
	// �Q�Ɛ� ... Camera::Update(float delta_time)
	void IsIntersectCameraFlustum(const float delta_time);

	//---------------------------//


	//------------------------------------------------//


	//-----------------�|�C���^Setter-----------------//

	void SetStagePhase(std::shared_ptr<StagePhase>& stagePhase)
	{
		m_stagePhase = stagePhase;
	}

	void SetLaneLoad(std::shared_ptr<LaneLoad>& laneLoad)
	{
		m_laneLoad = laneLoad;
	}
	
	void SetLaneMove(std::shared_ptr<LaneMove>& laneMove)
	{
		m_laneMove = laneMove;
	}

	void SetCharacter(std::shared_ptr<Character>& character)
	{
		m_character = character;
	}

	void SetPlayer(std::shared_ptr<Player>& player)
	{
		m_player = player;
	}

void SetPlayerLoad(std::shared_ptr<PlayerLoad>& playerLoad)
	{
		m_playerLoad = playerLoad;
	}

	void SetPlayerMove(std::shared_ptr<PlayerMove>& playerMove)
	{
		m_playerMove = playerMove;
	}

	void SetPlayerDraw(std::shared_ptr<PlayerDraw>& playerDraw)
	{
		m_playerDraw = playerDraw;
	}

	void SetPlayerSkill(std::shared_ptr<PlayerSkill>& playerSkill)
	{
		m_playerSkill = playerSkill;
	}

	void SetPlayerCollision(std::shared_ptr<PlayerCollision>& playerCollision)
	{
		m_playerCollision = playerCollision;
	}

	void SetPartner(std::shared_ptr<Partner>& partner)
	{
		m_partner = partner;
	}

	void SetPartnerMove(std::shared_ptr<PartnerMove>& partnerMove)
	{
		m_partnerMove = partnerMove;
	}

	void SetPartnerDraw(std::shared_ptr<PartnerDraw>& partnerDraw)
	{
		m_partnerDraw = partnerDraw;
	}

	void SetCameraTargetPlayer(std::shared_ptr<CameraTargetPlayer>& cameraTargetPlayer)
	{
		m_cameraTargetPlayer = cameraTargetPlayer;
	}

	void SetModel(std::shared_ptr<Model>& model)
	{
		m_model = model;
	}

	void SetModelLoad(std::shared_ptr<ModelLoad>& modelLoad)
	{
		m_modelLoad = modelLoad;
	}

	void SetModelPool(std::shared_ptr<ModelPool>& modelPool)
	{
		m_modelPool = modelPool;
	}

	void SetGimmickLoad(std::shared_ptr<GimmickLoad>& gimmickLoad)
	{
		m_gimmickLoad = gimmickLoad;
	}

	void SetGimmickGenerator(std::shared_ptr<GimmickGenerator>& gimmickGenerator)
	{
		m_gimmickGenerator = gimmickGenerator;
	}

	void SetGimmickPool(std::shared_ptr<GimmickPool>& itemPool)
	{
		m_gimmickPool = itemPool;
	}

	void SetEffectLoad(std::shared_ptr<EffectLoad>& effectLoad)
	{
		m_effectLoad = effectLoad;
	}

	void SetText(std::shared_ptr<Text>& text)
	{
		m_text = text;
	}

	void SetTextLoad(std::shared_ptr<TextLoad>& textLoad)
	{
		m_textLoad = textLoad;
	}

	void SetTextDraw(std::shared_ptr<TextDraw>& textDraw)
	{
		m_textDraw = textDraw;
	}
	
	void SetCharaGraphLoad(std::shared_ptr<CharaGraphLoad>& charaGraphLoad)
	{
		m_charaGraphLoad = charaGraphLoad;
	}

	void SetCharaGraphDraw(std::shared_ptr<CharaGraphDraw>& charaGraphDraw)
	{
		m_charaGraphDraw = charaGraphDraw;
	}

	void SetGameCamera(std::shared_ptr<GameCamera>& gameCamera)
	{
		m_gameCamera = gameCamera;
	}

	void SetCameraLoad(std::shared_ptr<CameraLoad>& cameraLoad)
	{
		m_cameraLoad = cameraLoad;
	}

	//------------------------------------------------//
};