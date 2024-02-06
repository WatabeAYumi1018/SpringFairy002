#pragma once
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"
#include "../[000]Object/[000]Stage/[003]Model/Model.h"
#include "../[000]Object/[002]Gimmick/Gimmick.h"
#include "../[000]Object/[003]Effect/Effect.h"
#include "../[000]Object/[005]Event/[001]Text/Text.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/CharaGraph.h"
#include "../[000]Object/[007]Gate/Gate.h"
#include "../[001]Camera/GameCamera.h"
#include "../[001]Camera/CinemaCamera.h"
#include "../[003]Phase/StagePhase.h"


class CinemaBack;
class SkyBox;

class LaneLoad;
class LaneMove;

class ModelLoad;

class Character;

class Player;
class PlayerLoad;
class PlayerMove;	
class PlayerDraw;
class PlayerSkill;
class PlayerCollision;
class CinemaPlayer;

class Partner;
class PartnerLoad;
class PartnerMove;
class PartnerDraw;

class CameraTargetPlayer;
class CinemaCameraTarget;

class Butterfly;
class ButterflyLoad;
		
class Gimmick;
class GimmickLoad;
class GimmickGenerator;
class GimmickPool;

class EffectLoad;

class Score;

class TextLoad;
class TextDraw;

class CharaGraphLoad;
class CharaGraphDraw;

class Title;

class GateLoad;

class CameraLoad;

class Mediator
{

private:

	//CinemaCamera::eCameraSplitType active_cinema_type;


	//--------------------�|�C���^--------------------//

	std::shared_ptr<StagePhase> m_stagePhase = nullptr;

	std::shared_ptr<CinemaBack> m_cinemaBack = nullptr;
	std::shared_ptr<SkyBox> m_skyBox = nullptr;

	std::shared_ptr<Lane> m_lane = nullptr;
	std::shared_ptr<LaneLoad> m_laneLoad = nullptr;
	std::shared_ptr<LaneMove> m_laneMove = nullptr;

	std::shared_ptr<Model> m_model = nullptr;
	std::shared_ptr<ModelLoad> m_modelLoad = nullptr;

	std::shared_ptr<Character> m_character = nullptr;

	std::shared_ptr<Player> m_player = nullptr;
	std::shared_ptr<PlayerLoad> m_playerLoad = nullptr;
	std::shared_ptr<PlayerMove> m_playerMove = nullptr;
	std::shared_ptr<PlayerDraw> m_playerDraw = nullptr;
	std::shared_ptr<PlayerSkill> m_playerSkill = nullptr;
	std::shared_ptr<PlayerCollision> m_playerCollision = nullptr;
	std::shared_ptr<CinemaPlayer> m_cinemaPlayer = nullptr;

	std::shared_ptr<Partner> m_partner = nullptr;
	std::shared_ptr<PartnerLoad> m_partnerLoad = nullptr;
	std::shared_ptr<PartnerMove> m_partnerMove = nullptr;
	std::shared_ptr<PartnerDraw> m_partnerDraw = nullptr;

	std::shared_ptr<CameraTargetPlayer> m_cameraTargetPlayer = nullptr;
	std::shared_ptr<CinemaCameraTarget> m_cinemaCameraTarget = nullptr;

	std::shared_ptr<Butterfly> m_butterfly = nullptr;
	std::shared_ptr<ButterflyLoad> m_butterflyLoad = nullptr;

	std::shared_ptr<Gimmick> m_gimmick = nullptr;
	std::shared_ptr<GimmickLoad> m_gimmickLoad = nullptr;
	std::shared_ptr<GimmickGenerator> m_gimmickGenerator = nullptr;
	std::shared_ptr<GimmickPool> m_gimmickPool = nullptr;

	std::shared_ptr<EffectLoad> m_effectLoad = nullptr;

	std::shared_ptr<Score> m_score = nullptr;

	std::shared_ptr<Text> m_text = nullptr;
	std::shared_ptr<TextLoad> m_textLoad = nullptr;
	std::shared_ptr<TextDraw> m_textDraw = nullptr;

	std::shared_ptr<CharaGraphLoad> m_charaGraphLoad = nullptr;
	std::shared_ptr<CharaGraphDraw> m_charaGraphDraw = nullptr;

	std::shared_ptr<Title> m_title = nullptr;

	std::shared_ptr<GateLoad> m_gateLoad = nullptr;

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


	//---------CinemaBack---------//

	// CinemaBack

	// �V�l�}�o�b�N��ԃt���O�ݒ�
	// �Q�ƌ� ... CinemaBack::m_is_first
	// �Q�Ɛ� ... CinemaCamera::Update(float delta_time)
	void SetCinemaBackIsFirst(bool is_first);

	// �V�l�}�o�b�N��ԃt���O�ݒ�
	// �Q�ƌ� ... CinemaBack::m_is_second
	// �Q�Ɛ� ... CinemaCamera::Update(float delta_time)
	void SetCinemaBackIsSecond(bool is_second);

	// �V�l�}�o�b�N�O�ԃt���O�ݒ�
	// �Q�ƌ� ... CinemaBack::m_is_third
	// �Q�Ɛ� ... CinemaCamera::Update(float delta_time)
	void SetCinemaBackIsThird(bool is_third);

	// �V�l�}�o�b�N�̃t�H�O�t���O�ݒ�
	// �Q�ƌ� ... CinemaBack::m_is_fog
	// �Q�Ɛ� ... CinemaPlayer::Update(float delta_time)
	void SetIsCinemaBackFog(bool is_fog);

	// �V�l�}�o�b�N�̃o�u���t���O�ݒ�
	// �Q�ƌ� ... CinemaBack::m_is_bubble
	// �Q�Ɛ� ... CinemaPlayer::Update(float delta_time)
	void SetIsCinemaBackBubble(bool is_bubble);


	//----------------------------//
	
	
	//-----------SkyBox-----------//

	// SkyBox

	// SkyBox��OP�t���O�ݒ�
	// �Q�ƌ� ... SkyBox::m_is_op
	// �Q�Ɛ� ... OpCamera::Update(float delta_time)
	void SetSkyIsOp(bool is_op);

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
	void MoveAstarCharaUpdatePos(const float delta_time
								 ,tnl::Vector3& pos);

	// �����ړ��ɂ���]�X�V
	// �Q�ƌ� ... LoadMove::MoveAstarRot(float delta_time)
	// �Q�Ɛ� ... �����o�H�ɂ��X�V���K�v�ȑS�N���X
	void MoveAstarCharaUpdateRot(const float delta_time
								 , tnl::Vector3& pos
								 , tnl::Quaternion& rot);

	// �����ړ��ɂ����W�X�V
	// �Q�ƌ� ... LoadMove::MoveAstarPos(float delta_time)
	// �Q�Ɛ� ... �����o�H�ɂ��X�V���K�v�ȑS�N���X
	void MoveAstarTargetPos(const float delta_time, tnl::Vector3& pos);

	// �L�����̉�]�t���O�ݒ�
	// �Q�ƌ� ... laneMove::m_look_side_right
	// �Q�Ɛ� ... GameCamera::ConditionType()
	void SetPlayerLookSideRight(bool look_side);

	// �L�����̉�]�t���O�擾
	// �Q�ƌ� ... laneMove::m_look_side_right
	// �Q�Ɛ� ... GimmickGenerator::CreateGimmick()
	bool GetPlayerLookSideRight() const;

	// �L�����̉�]���t���O�擾
	// �Q�ƌ� ... Player::m_look_side_left
	// �Q�Ɛ� ... GameCamera::ConditionType()
	void SetPlayerLookSideLeft(bool look_side);

	// �L�����̉�]���t���O�擾
	// �Q�ƌ� ... Player::m_look_side_left
	// �Q�Ɛ� ... GimmickGenerator::CreateGimmick()
	bool GetPlayerLookSideLeft() const;

	//---------------------------//


	//----------Model-----------//

	// modelLoad

	// �X�e�[�W���f���̏��擾
	// �Q�ƌ� ... ModelLoad::m_model_info
	// �Q�Ɛ� ... ModelPool::�֘A����֐�
	const std::vector<Model::sModelInfo>& GetStageModelInfo() const;

	//--------------------------//


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

	// playerLoad

	// �v���C���[���f���n���h���̎擾
	// �Q�ƌ� ... PlayerLoad::m_model_game_hdl
	// �Q�Ɛ� ... Player�֘A�N���X
	int GetPlayerModelGameHdl() const; 

	// �v���C���[�V�l�}���f���n���h���̎擾
	// �Q�ƌ� ... PlayerLoad::m_model_cinema_hdl
	// �Q�Ɛ� ... Player�֘A�N���X
	int GetPlayerModelCinemaHdl() const;

	// �v���C���[�̃A�C�h���{�[���n���h���擾
	// �Q�ƌ� ... PlayerLoad::m_anim_bone_idle_hdl
	// �Q�Ɛ� ... Player�֘A�N���X
	int GetPlayerAnimBoneIdleCinemaHdl() const;

	// �v���C���[�̈ړ��{�[���n���h���擾
	// �Q�ƌ� ... PlayerLoad::m_anim_bone_move_game_hdl
	// �Q�Ɛ� ... Player�֘A�N���X
	int GetPlayerAnimBoneMoveGameHdl() const;

	// �v���C���[�̃V�l�}�ړ��{�[���n���h���擾
	// �Q�ƌ� ... PlayerLoad::m_anim_bone_move_cinema_hdl
	// �Q�Ɛ� ... Player�֘A�N���X
	int GetPlayerAnimBoneMoveCinemaHdl() const;

	// �v���C���[�̃u���[���{�[���n���h���擾
	// �Q�ƌ� ... PlayerLoad::m_anim_bone_bloom_game_hdl
	// �Q�Ɛ� ... Player�֘A�N���X
	int GetPlayerAnimBoneBloomGameHdl() const;

	// �v���C���[�̃_���X�{�[���n���h���擾
	// �Q�ƌ� ... PlayerLoad::m_anim_bone_dance_game_hdl
	// �Q�Ɛ� ... Player�֘A�N���X
	int GetPlayerAnimBoneDanceGameHdl() const;

	// �v���C���[�̃_���X�V�l�}�{�[���n���h���擾
	// �Q�ƌ� ... PlayerLoad::m_anim_bone_dance_cinema_hdl
	// �Q�Ɛ� ... Player�֘A�N���X
	int GetPlayerAnimBoneDanceCinemaHdl() const;

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

	// Player�ړ��ɂ����W�Ɖ�]�̍X�V����
	// �Q�ƌ� ... PlayerMove::Update(float delta_time)
	// �Q�Ɛ� ... Player::Update(float delta_time)
	void UpdatePlayerMoveMatrix(const float delta_time);

	// playerDraw

	// Player���f���`��̏���������
	// �Q�ƌ� ... PlayerDraw::Initialize()
	// �Q�Ɛ� ... Player::Initialize()
	void InitializePlayerDraw();

	// Player���f���̃A�j���[�V�����X�V����
	// �Q�ƌ� ... PlayerDraw::Update(float delta_time)
	// �Q�Ɛ� ... Player::Update(float delta_time)
	void UpdatePlayerAnim(const float delta_time);

	// Player���f���̕`�揈��
	// �Q�ƌ� ... PlayerDraw::Draw()
	// �Q�Ɛ� ... Player::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawPlayerModel();

	// �C�x���g�ɂ��_���X�A�j���[�V�����t���O�ݒ�
	// �Q�ƌ� ... PlayerDraw::m_is_event_dance
	// �Q�Ɛ� ... CameraTargetPlayer::Update(float delta_time)
	void SetIsPlayerEventDance(bool is_dance);

	// �u���[���t���O�擾
	// �Q�ƌ� ... PlayerDraw::m_is_bloom
	// �Q�Ɛ� ... �u���[���t���O���K�v�ȑS�N���X
	bool GetIsPlayerBloom() const;

	// �C�x���g�ɂ��_���X�A�j���[�V�����t���O�擾
	// �Q�ƌ� ... PlayerDraw::m_is_event_dance
	// �Q�Ɛ� ... PhaseManager::Update(float delta_time)
	bool GetIsPlayerEventDance() const;

	// �C�x���g�ɂ��idle�A�j���[�V��������
	// �Q�ƌ� ... PlayerDraw::CinemaAnimIdle(float delta_time)
	// �Q�Ɛ� ... CinemaPlayer::Update(float delta_time)
	void CinemaPlayerAnimIdle(const float delta_time);

	// �C�x���g�ɂ��move�A�j���[�V��������
	// �Q�ƌ� ... PlayerDraw::CinemaAnimMove(float delta_time)
	// �Q�Ɛ� ... CinemaPlayer::Update(float delta_time)
	void CinemaPlayerAnimMove(const float delta_time);
	
	// �C�x���g�ɂ��dance�A�j���[�V��������
	// �Q�ƌ� ... PlayerDraw::CinemaAnimDance(float delta_time)
	// �Q�Ɛ� ... CinemaPlayer::Update(float delta_time)
	void CinemaPlayerAnimDance(const float delta_time);

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

	// CinemaPlayer

	// �V�l�}�v���C���[�̍��W�擾
	// �Q�ƌ� ... Player::m_pos
	// �Q�Ɛ� ... Player�̍��W���K�v�ȑS�N���X
	const tnl::Vector3& GetCinemaPlayerPos() const;

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

	// �p�[�g�i�[�̓����蔻��T�C�Y�擾
	// �Q�ƌ� ... Partner::m_collision_size
	// �Q�Ɛ� ... PartnerMove::Update(float delta_time)
	const float GetPartnerCollisionSize() const;

	// �p�[�g�i�[�̉�]�擾
	// �Q�ƌ� ... Partner::m_rot
	// �Q�Ɛ� ... Partner�̉�]���K�v�ȑS�N���X
	const tnl::Quaternion& GetPartnerRot() const;

	// ���݂̑����J�����擾
	// �Q�ƌ� ... Partner::CurrentCamera()
	// �Q�Ɛ� ... GimmickGenerator::CalcGimmickRandomPos()
	GameCamera::sCamera CurrentCameraLane();

	// PartnerLoad

	// �p�[�g�i�[���f���n���h���̎擾
	// �Q�ƌ� ... PartnerLoad::m_model_hdl
	// �Q�Ɛ� ... Partner�֘A�N���X
	int GetPartnerModelHdl() const;

	// �p�[�g�i�[�̃A�C�h���{�[���n���h���擾
	// �Q�ƌ� ... PartnerLoad::m_anim_bone_idle_hdl
	// �Q�Ɛ� ... Partner�֘A�N���X
	int GetPartnerAnimBoneIdleHdl() const;

	// �p�[�g�i�[�̈ړ��{�[���n���h���擾
	// �Q�ƌ� ... PartnerLoad::m_anim_bone_move_hdl
	// �Q�Ɛ� ... Partner�֘A�N���X
	int GetPartnerAnimBoneMoveHdl() const;

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

	// Partner���f���`��̏���������
	// �Q�ƌ� ... PartnerDraw::Initialize()
	// �Q�Ɛ� ... Partner::Initialize()
	void InitializePartnerDraw();

	// Partner���f���̃A�j���[�V�����X�V����
	// �Q�ƌ� ... PartnerDraw::Update(float delta_time)
	// �Q�Ɛ� ... Partner::Update(float delta_time)
	void UpdatePartnerAnim(const float delta_time);

	// Partner���f���̕`�揈��
	// �Q�ƌ� ... PartnerDraw::Draw()
	// �Q�Ɛ� ... Partner::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawPartnerModel();

	//------------------------------//


	//------CameraTargetPlayer------//

	// CameraTargetPlayer

	// �J�����̃^�[�Q�b�g���W�擾
	// �Q�ƌ� ... CameraTargetPlayer::GetPos()
	// �Q�Ɛ� ... OriginalCamera::target_
	const tnl::Vector3& GetCameraTargetPlayerPos() const;

	// ���݂̃J�����^�C�v�擾
	// �Q�ƌ� ... CameraTargetPlayer::m_camera_info
	// �Q�Ɛ� ... 
	const GameCamera::sCameraInfo& GetTargetCameraInfo() const;

	// �L�����N�^�[�̑����C�x���g���[�����擾
	// �Q�ƌ� ... Character::m_event
	// �Q�Ɛ� ... �C�x���g���[�����K�v�ȑS�N���X
	const Lane::sLaneEvent& GetEventLane() const;

	// �^�[�Q�b�g�̃X�s�[�h�A�b�v�t���O
	// �Q�ƌ� ... Character::m_is_speed_up
	// �Q�Ɛ� ... LaneMove::�����ړ��Ɋ֘A����N���X
	bool GetIsTargetSpeedUp() const;

	//// �^�[�Q�b�g�̏㏸�ړ��t���O
	//// �Q�ƌ� ... Character::m_is_move_up
	//// �Q�Ɛ� ... LaneMove::�����ړ��Ɋ֘A����N���X
	//bool GetIsTargetMoveUp() const;

	// �^�[�Q�b�g�̉��~�ړ��t���O
	// �Q�ƌ� ... Character::m_is_move_down
	// �Q�Ɛ� ... LaneMove::�����ړ��Ɋ֘A����N���X
	bool GetIsTargetMoveDown() const;

	//-------------------------------//


	//------CinemaCameraTarget------//

	// CinemaCameraTarget

	// �V�l�}�J�����̃^�[�Q�b�g���W�擾
	// �Q�ƌ� ... CinemaCameraTarget::m_pos
	// �Q�Ɛ� ... OriginalCamera::target_
	const tnl::Vector3& GetCinemaCameraTargetPos() const;

	//-----------------------------//


	//----------Butterfly----------//

	// Butterfly

	// �o�^�t���C�̍��W�擾
	// �Q�ƌ� ... Butterfly::m_pos
	// �Q�Ɛ� ... Butterfly�̍��W���K�v�ȑS�N���X
	const tnl::Vector3& GetButterflyPos() const;

	// �o�^�t���C��OP�`��t���O�ݒ�
	// �Q�ƌ� ... Butterfly::m_is_op_active
	// �Q�Ɛ� ... OpCamera::Update(float delta_time)
	void SetButterflyIsOpActive(bool is_op_active);

	// �o�^�t���C�̗ؕ��t���O�擾
	// �Q�ƌ� ... Butterfly::m_is_powder
	// �Q�Ɛ� ... Op�Ɋ֘A����֐�
	bool GetButterflyIsPowder() const;

	// �o�^�t���C�̃V�l�}�t���O�ݒ�
	// �Q�ƌ� ... Butterfly::m_is_cinema_active
	// �Q�Ɛ� ... OpCamera::Update(float delta_time)
	void SetButterflyIsCinemaActive(bool is_cinema_active);

	// �o�^�t���C�̃V�l�}�t���O�擾
	// �Q�ƌ� ... Butterfly::m_is_cinema_active
	// �Q�Ɛ� ... CinemaCamera::Fixed(const tnl::Vector3& offset)
	bool GetButterflyIsCinemaActive() const;

	// ButterflyLoad

	// �o�^�t���C���f���n���h���̎擾
	// �Q�ƌ� ... ButterflyLoad::m_model_hdl
	// �Q�Ɛ� ... Butterfly�֘A�N���X
	int GetButterflyModelHdl() const;

	//-----------------------------//


	//-----------Gimmick-----------//

	// GimmickPool

	// �A�C�e���v�[���̃A�N�e�B�u��Ԏ擾
	// �Q�ƌ� ... GimmickPool::GetNotActiveGimmick(std::vector<std::shared_ptr<Gimmick>>& gimmicks)
	// �Q�Ɛ� ... GimmickGenerator::
	std::shared_ptr<Gimmick> GetNotActiveGimmickPool(std::vector<std::shared_ptr<Gimmick>>& gimmicks);

	// �M�~�b�N�v�[���̃x�N�^�[�擾
	// �Q�ƌ� ... GimmickPool::GetGimmickPools()
	// �Q�Ɛ� ... GimmickGenerator::�֘A����֐�
	std::vector<std::shared_ptr<Gimmick>>& GetGimmickTypePools(Gimmick::eGimmickType type);

	// GimmickGenerator

	// �A�C�e���t�����[�̃A�N�e�B�u��Ԏ擾
	// �Q�ƌ� ... GimmickGenerator::m_is_flower_active
	// �Q�Ɛ� ... 
	bool GetIsGimmickFlowerActive() const ; 

	// �n�ʃM�~�b�N�̃A�N�e�B�u��Ԏ擾
	// �Q�ƌ� ... GimmickGenerator::m_is_ground_active
	// �Q�Ɛ� ... Model::Draw(std::shared_ptr<GameCamera> gameCamera)
	bool GetIsGimmickGroundActive() const;

	//--------------------------//


	//----------Effect----------//

	// EffectLoad

	// �G�t�F�N�g���̎擾
	// �Q�ƌ� ... EffectLoad::m_effect_info
	// �Q�Ɛ� ... Effect::�֘A����֐�
	const std::vector<Effect::sEffectType>& GetEffectLoadInfo() const;

	//--------------------------//


	//----------Score-----------//

	// Score
	
	// �X�R�A���Z����t���O�̐ݒ�
	// �Q�ƌ� ... Score::m_is_add
	// �Q�Ɛ� ... Gimmick::Update(float delta_time)
	void SetIsScoreAdd(bool is_add) ;

	//--------------------------//


	//------------Text-----------//

	// TextLoad

	// ���[��ID�ɊY������e�L�X�g�����̎擾
	// �Q�ƌ� ... TextLoad::GetTextsLane()
	// �Q�Ɛ� ... Text::�֘A����֐�
	void GetTextsLoadLane();
	
	// ���[��ID�ɊY�����S�Ă̍\���̃f�[�^�̎擾
	// �Q�ƌ� ... TextLoad::m_texts_for_lane
	// �Q�Ɛ� ... Text::�֘A����֐�
	const std::vector<Text::sTextData>& GetTextsLoadForLane() const;

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

	//---------------------------//

	
	//--------CharaGraph---------//

	// CharaGraphLoad

	// �O���t�B�b�N�f�[�^�擾
	// �Q�ƌ� ... CharaGraphLoad::m_graph_info
	// �Q�Ɛ� ... CharaGraph
	const std::vector<CharaGraph::sGraphInfo>& GetCharaGraphLoadInfo() const;

	// CharaGraphDraw

	//---------------------------//


	//------------Title-----------//

	// Title
	
	// �^�C�g���̕`��t���O�ݒ�
	// �Q�ƌ� ... Title::m_is_draw
	// �Q�Ɛ� ... OpCamera::Update(float delta_time)
	void SetTitleIsDraw(bool is_draw);

	// �^�C�g�����������t���O�擾
	// �Q�ƌ� ... Title::m_is_disappear
	// �Q�Ɛ� ... OpCamera::Update(float delta_time)
	bool GetTitleIsDisappear() const;

	//---------------------------//


	//------------Gate-----------//

	// GateLoad

	// �Q�[�g�̏��擾
	// �Q�ƌ� ... GateLoad::m_gates
	// �Q�Ɛ� ... Gate::���f����񂪕K�v�ȑS�֐�
	const std::vector<Gate::sGateInfo>& GetGatesInfo() const;

	//---------------------------//


	//-----------Camera----------//

	// GameCamera

	// �J�����̑O�����擾
	// �Q�ƌ� ... GameCamera::forward()
	// �Q�Ɛ� ... PlayerMove::ControlMoveMatrix(float delta_time)
	const tnl::Vector3& GetCameraForward() const;

	// �J�����̉E�����擾
	// �Q�ƌ� ... GameCamera::right()
	// �Q�Ɛ� ... PlayerMove::ControlMoveMatrix(float delta_time)
	const tnl::Vector3& GetCameraRight() const;

	// �J�����̃t���X�^�������蔻��
	// �Q�ƌ� ... GameCamera::IsInFlustum()
	// �Q�Ɛ� ... PlayerMove::
	void IsInCameraFlustum();

	// �J�����̌Œ�t���O�擾
	// �Q�ƌ� ... GameCamera::m_is_fixed
	// �Q�Ɛ� ... GimmickGenerator::CheckGimmicks(const float delta_time,)
	bool IsCameraFixed() const;

	// �Q�[���J�����̃A�N�e�B�u��Ԑݒ�
	// �Q�ƌ� ... GameCamera::m_is_active_game
	// �Q�Ɛ� ... �J�����؂�ւ��Ɋ֘A����֐�
	void SetIsActiveGameCamera(bool is_active_game);

	// �Q�[���J�����̃A�N�e�B�u��Ԏ擾
	// �Q�ƌ� ... GameCamera::m_is_active_game
	// �Q�Ɛ� ... �Q�[���J�����ŕ`�悷��֐�
	bool GetIsActiveGameCamera() const;

	// CameraLoad

	// �J�����z��̏��擾
	// �Q�ƌ� ... CameraLoad::m_cameras
	// �Q�Ɛ� ... Camera::�֘A����֐�
	const std::vector<GameCamera::sCamera>& GetCameraLaneVector() const;

	// �J�������̎擾
	// �Q�ƌ� ... CameraLoad::GetCameraInfoById(int id)
	// �Q�Ɛ� ... Camera::�֘A����֐�
	GameCamera::sCameraInfo GetCameraTypeInfoById(int id);

	// CinemaCamera


	//---------------------------//


	//------------------------------------------------//


	//-----------------�|�C���^Setter-----------------//

	void SetStagePhase(std::shared_ptr<StagePhase>& stagePhase)
	{
		m_stagePhase = stagePhase;
	}

	void SetCinemaBack(std::shared_ptr<CinemaBack>& cinemaBack)
	{
		m_cinemaBack = cinemaBack;
	}

	void SetSkyBox(std::shared_ptr<SkyBox>& skyBox)
	{
		m_skyBox = skyBox;
	}

	void SetLaneLoad(std::shared_ptr<LaneLoad>& laneLoad)
	{
		m_laneLoad = laneLoad;
	}
	
	void SetLaneMove(std::shared_ptr<LaneMove>& laneMove)
	{
		m_laneMove = laneMove;
	}

	void SetModel(std::shared_ptr<Model>& model)
	{
		m_model = model;
	}

	void SetModelLoad(std::shared_ptr<ModelLoad>& modelLoad)
	{
		m_modelLoad = modelLoad;
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

	void SetCinemaPlayer(std::shared_ptr<CinemaPlayer>& cinemaPlayer)
	{
		m_cinemaPlayer = cinemaPlayer;
	}

	void SetPartner(std::shared_ptr<Partner>& partner)
	{
		m_partner = partner;
	}

	void SetPartnerLoad(std::shared_ptr<PartnerLoad>& partnerLoad)
	{
		m_partnerLoad = partnerLoad;
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

	void SetCinemaCameraTarget(std::shared_ptr<CinemaCameraTarget>& cinemaCameraTarget)
	{
		m_cinemaCameraTarget = cinemaCameraTarget;
	}

	void SetButterfly(std::shared_ptr<Butterfly>& butterfly)
	{
		m_butterfly = butterfly;
	}

	void SetButterflyLoad(std::shared_ptr<ButterflyLoad>& butterflyLoad)
	{
		m_butterflyLoad = butterflyLoad;
	}

	void SetGimmick(std::shared_ptr<Gimmick>& gimmick)
	{
		m_gimmick = gimmick;
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

	void SetScore(std::shared_ptr<Score>& score)
	{
		m_score = score;
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

	void SetTitle(std::shared_ptr<Title>& title)
	{
		m_title = title;
	}

	void SetGateLoad(std::shared_ptr<GateLoad>& gateLoad)
	{
		m_gateLoad = gateLoad;
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