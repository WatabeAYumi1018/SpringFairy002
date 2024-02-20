#pragma once
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"
#include "../[000]Object/[000]Stage/[003]Model/Model.h"
#include "../[000]Object/[002]Gimmick/Gimmick.h"
#include "../[000]Object/[003]Effect/Effect.h"
#include "../[000]Object/[005]Event/[001]Text/Text.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/CharaGraph.h"
#include "../[000]Object/[007]Gate/Gate.h"
#include "../[000]Object/[008]OtherGraph/[000]OtherFunction/OtherGraphLoad.h"
#include "../[001]Camera/GameCamera.h"
#include "../[001]Camera/CinemaCamera.h"
#include "../[003]Phase/CameraPhase.h"
#include "../[003]Phase/StagePhase.h"

///////////////////////////////////////////////////////////////////////////
//
// クラス間の情報のやり取りを行うクラス（weak参照）
//
///////////////////////////////////////////////////////////////////////////



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

class Text;
class TextLoad;
class TextDraw;

class CharaGraph;
class CharaGraphLoad;

class Title;

class GateLoad;

class EnterGraph;
class ChangeGraph;
class ChildChangeGraph;
class OtherGraphLoad;

class CameraLoad;
class CinemaCamera;

class ScreenShot;

class Mediator
{

private:

	//--------------------ポインタ--------------------//

	std::weak_ptr<CameraPhase> m_cameraPhase;
	std::weak_ptr<StagePhase> m_stagePhase;

	std::weak_ptr<CinemaBack> m_cinemaBack;
	std::weak_ptr<SkyBox> m_skyBox;

	std::weak_ptr<Lane> m_lane;
	std::weak_ptr<LaneLoad> m_laneLoad;
	std::weak_ptr<LaneMove> m_laneMove;

	std::weak_ptr<Model> m_model;
	std::weak_ptr<ModelLoad> m_modelLoad;

	std::weak_ptr<Character> m_character;

	std::weak_ptr<Player> m_player;
	std::weak_ptr<PlayerLoad> m_playerLoad;
	std::weak_ptr<PlayerMove> m_playerMove;
	std::weak_ptr<PlayerDraw> m_playerDraw;
	std::weak_ptr<PlayerCollision> m_playerCollision;
	std::weak_ptr<CinemaPlayer> m_cinemaPlayer;

	std::weak_ptr<Partner> m_partner;
	std::weak_ptr<PartnerLoad> m_partnerLoad;
	std::weak_ptr<PartnerMove> m_partnerMove;
	std::weak_ptr<PartnerDraw> m_partnerDraw;

	std::weak_ptr<CameraTargetPlayer> m_cameraTargetPlayer;
	std::weak_ptr<CinemaCameraTarget> m_cinemaCameraTarget;

	std::weak_ptr<Butterfly> m_butterfly;
	std::weak_ptr<ButterflyLoad> m_butterflyLoad;

	std::weak_ptr<Gimmick> m_gimmick;
	std::weak_ptr<GimmickLoad> m_gimmickLoad;
	std::weak_ptr<GimmickGenerator> m_gimmickGenerator;
	std::weak_ptr<GimmickPool> m_gimmickPool;

	std::weak_ptr<Effect> m_effect;
	std::weak_ptr<EffectLoad> m_effectLoad;

	std::weak_ptr<Score> m_score;

	std::weak_ptr<Text> m_text;
	std::weak_ptr<TextLoad> m_textLoad;
	std::weak_ptr<TextDraw> m_textDraw;

	std::weak_ptr<CharaGraph> m_charaGraph;
	std::weak_ptr<CharaGraphLoad> m_charaGraphLoad;

	std::weak_ptr<Title> m_title;

	std::weak_ptr<GateLoad> m_gateLoad;

	std::weak_ptr<EnterGraph> m_enterGraph;
	std::weak_ptr<ChangeGraph> m_changeGraph;	
	std::weak_ptr<ChildChangeGraph> m_childChangeGraph;
	std::weak_ptr<OtherGraphLoad> m_otherGraphLoad;

	std::weak_ptr<GameCamera> m_gameCamera;
	std::weak_ptr<CameraLoad> m_cameraLoad;
	std::weak_ptr<CinemaCamera> m_cinemaCamera;

	std::weak_ptr<ScreenShot> m_screenShot;

	//------------------------------------------------//

public:

	//-------------------メンバ関数-------------------//

	//--------CameraPhase--------//

	// CameraPhase

	// カメラフェーズ取得
	// 参照元 ... CameraPhase::m_now_camera
	// 参照先 ... フェーズ状態の取得が必要な全クラス（フェーズ遷移の影響を持つクラス）
	const CameraPhase::eCameraPhase& GetNowCameraPhaseState() const ;

	//----------------------------//


	//---------StagePhase---------//

	// StagePhase

	// ステージフェーズ取得
	// 参照元 ... StagePhase::m_stage_phase
	// 参照先 ... フェーズ状態の取得が必要な全クラス（フェーズ遷移の影響を持つクラス）
	const StagePhase::eStagePhase& GetNowStagePhaseState() const;

	//---------------------------//


	//---------CinemaBack---------//

	// CinemaBack

	// シネマバックのフォグフラグ設定
	// 参照元 ... CinemaBack::m_is_fog
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetIsCinemaBackFog(bool is_fog);

	// シネマバックのバブルフラグ設定
	// 参照元 ... CinemaBack::m_is_bubble
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetIsCinemaBackBubble(bool is_bubble);

	//----------------------------//
	
	
	//-----------SkyBox-----------//

	// SkyBox

	// SkyBoxのOPフラグ設定
	// 参照元 ... SkyBox::m_is_op
	// 参照先 ... OpCamera::Update(float delta_time)
	void SetSkyIsOp(bool is_op);

	//---------------------------//


	//-----------Stage-----------//

	// LaneLoad

	// レーン配列の幅取得
	// 参照元 ... LaneLoad::m_lane_width
	// 参照先 ... レーン配列の情報が必要な全クラス
	int GetStageLaneWidth() const;

	// レーン配列の高さ取得
	// 参照元 ... LaneLoad::m_lane_height
	// 参照先 ... レーン配列の情報が必要な全クラス
	int GetStageLaneHeight() const;

	// レーン配列の情報取得
	// 参照元 ... LaneLoad::m_lanes
	// 参照先 ... レーン配列の情報が必要な全クラス
	const std::vector<Lane::sLane>& GetStageLane() const;

	// イベント配列の情報取得
	// 参照元 ... LaneLoad::m_lane_events
	// 参照先 ... イベント配列の情報が必要な全クラス
	const std::vector<Lane::sLaneEvent>& GetStageLaneEvent() const;

	// LaneMove

	// 自動移動による座標と回転更新
	// 参照元 ... LoadMove::MoveAstar(float delta_time)
	// 参照先 ... 自動経路による更新が必要な全クラス
	void MoveAstarCharaUpdatePos(const float delta_time
								 ,tnl::Vector3& pos);

	// 自動移動による回転更新
	// 参照元 ... LoadMove::MoveAstarRot(float delta_time)
	// 参照先 ... 自動経路による更新が必要な全クラス
	void MoveAstarCharaUpdateRot(const float delta_time
								 , tnl::Vector3& pos
								 , tnl::Quaternion& rot);

	// 自動移動による座標更新
	// 参照元 ... LoadMove::MoveAstarPos(float delta_time)
	// 参照先 ... 自動経路による更新が必要な全クラス
	void MoveAstarTargetPos(const float delta_time, tnl::Vector3& pos);

	// キャラの回転フラグ設定
	// 参照元 ... laneMove::m_look_side_right
	// 参照先 ... GameCamera::ConditionType()
	void SetPlayerLookSideRight(bool look_side);

	// キャラの回転フラグ取得
	// 参照元 ... laneMove::m_look_side_right
	// 参照先 ... GimmickGenerator::CreateGimmick()
	bool GetPlayerLookSideRight() const;

	// キャラの回転左フラグ取得
	// 参照元 ... Player::m_look_side_left
	// 参照先 ... GameCamera::ConditionType()
	void SetPlayerLookSideLeft(bool look_side);

	// キャラの回転左フラグ取得
	// 参照元 ... Player::m_look_side_left
	// 参照先 ... GimmickGenerator::CreateGimmick()
	bool GetPlayerLookSideLeft() const;

	//---------------------------//


	//----------Model-----------//

	// model

	// モデルの向きフラグ設定
	// 参照元 ... Model::m_look_side_front
	// 参照先 ... GameCamera::ConditionType()
	void LookSideModelFront(bool is_front);

	// modelLoad

	// ステージモデルの情報取得
	// 参照元 ... ModelLoad::m_model_info
	// 参照先 ... ModelPool::関連する関数
	const std::vector<Model::sModelInfo>& GetStageModelInfo() const;

	// 樹木ステージモデルの情報取得
	// 参照元 ... ModelLoad::m_tree_info
	// 参照先 ... ModelPool::関連する関数
	const std::vector<Model::sTreeInfo>& GetStageTreeInfo() const;

	//--------------------------//


	//----------Player----------//
	
	// player 

	// プレイヤーの座標設定
	// 参照元 ... Player::m_pos
	// 参照先 ... Playerの座標が必要な全クラス
	void SetPlayerPos(tnl::Vector3& pos);

	// プレイヤーの回転取得
	// 参照元 ... Player::m_rot
	// 参照先 ... Playerの回転が必要な全クラス
	void SetPlayerRot(tnl::Quaternion& rot);

	// プレイヤーの座標取得
	// 参照元 ... Player::m_pos
	// 参照先 ... Playerの座標が必要な全クラス
	const tnl::Vector3& GetPlayerPos() const;

	// プレイヤーの回転取得
	// 参照元 ... Player::m_rot
	// 参照先 ... Playerの回転が必要な全クラス
	const tnl::Quaternion& GetPlayerRot() const;

	// プレイヤーの当たり判定サイズ取得
	// 参照元 ... Player::m_collision_size
	// 参照先 ... Playerの当たり判定サイズが必要な全クラス
	float GetPlayerCollisionSize() const;

	// プレイヤーの前方向の取得
	// 参照元 ... Player::tnl::Vector3 Forward();
	// 参照先 ... プレイヤーの前方向が必要な全クラス
	tnl::Vector3 PlayerForward();

	// playerLoad

	// プレイヤーモデルハンドルの取得
	// 参照元 ... PlayerLoad::m_model_game_hdl
	// 参照先 ... Player関連クラス
	int GetPlayerModelGameHdl() const; 

	// プレイヤーシネマモデルハンドルの取得
	// 参照元 ... PlayerLoad::m_model_cinema_hdl
	// 参照先 ... Player関連クラス
	int GetPlayerModelCinemaHdl() const;

	// プレイヤーのアイドルボーンハンドル取得
	// 参照元 ... PlayerLoad::m_anim_bone_idle_hdl
	// 参照先 ... Player関連クラス
	int GetPlayerAnimBoneIdleCinemaHdl() const;

	// プレイヤーの移動ボーンハンドル取得
	// 参照元 ... PlayerLoad::m_anim_bone_move_game_hdl
	// 参照先 ... Player関連クラス
	int GetPlayerAnimBoneMoveGameHdl() const;

	// プレイヤーのシネマ移動ボーンハンドル取得
	// 参照元 ... PlayerLoad::m_anim_bone_move_cinema_hdl
	// 参照先 ... Player関連クラス
	int GetPlayerAnimBoneMoveCinemaHdl() const;

	// プレイヤーのブルームボーンハンドル取得
	// 参照元 ... PlayerLoad::m_anim_bone_bloom_game_hdl
	// 参照先 ... Player関連クラス
	int GetPlayerAnimBoneBloomGameHdl() const;

	// プレイヤーのダンスボーンハンドル取得
	// 参照元 ... PlayerLoad::m_anim_bone_dance_game_hdl
	// 参照先 ... Player関連クラス
	int GetPlayerAnimBoneDanceGameHdl() const;

	// プレイヤーのダンスシネマボーンハンドル取得
	// 参照元 ... PlayerLoad::m_anim_bone_dance_cinema_hdl
	// 参照先 ... Player関連クラス
	int GetPlayerAnimBoneDanceCinemaHdl() const;

	// プレイヤーの移動速度取得
	// 参照元 ... PlayerLoad::m_move_speed
	// 参照先 ... PlayerMove
	float GetPlayerMoveSpeed() const;

	// プレイヤーの移動回転取得
	// 参照元 ... PlayerLoad::m_rotate_speed
	// 参照先 ... PlayerMove
	float GetPlayerMoveRot() const;

	// プレイヤーの宙返り総時間取得
	// 参照元 ... PlayerLoad::m_salto_total_time
	// 参照先 ... PlayerMove
	float GetPlayerSaltoTotalTime() const;

	// プレイヤーの宙返り半径取得
	// 参照元 ... PlayerLoad::m_salto_radius
	// 参照先 ... PlayerMove
	float GetPlayerSaltoRadius() const;

	// プレイヤーの宙返り移動速度取得
	// 参照元 ... PlayerLoad::m_salto_move_speed
	// 参照先 ... PlayerMove
	float GetPlayerSaltoMoveSpeed() const;

	// playerMove

	// Player移動による座標と回転の更新処理
	// 参照元 ... PlayerMove::Update(float delta_time)
	// 参照先 ... Player::Update(float delta_time)
	void UpdatePlayerMoveMatrix(const float delta_time);

	// playerDraw

	// Playerモデル描画の初期化処理
	// 参照元 ... PlayerDraw::Initialize()
	// 参照先 ... Player::Initialize()
	void InitializePlayerDraw();

	// Playerモデルのアニメーション更新処理
	// 参照元 ... PlayerDraw::Update(float delta_time)
	// 参照先 ... Player::Update(float delta_time)
	void UpdatePlayerAnim(const float delta_time);

	// Playerモデルの描画処理
	// 参照元 ... PlayerDraw::Draw()
	// 参照先 ... Player::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawPlayerModel();

	// シネマプレイヤーのダンス経過時間設定
	// 参照元 ... Player::m_elapsed_time_dance
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetAnimElapsedTimeDance(float elapsed_time_dance);

	// イベントによるダンスアニメーションフラグ設定
	// 参照元 ... PlayerDraw::m_is_event_dance
	// 参照先 ... CameraTargetPlayer::Update(float delta_time)
	void SetIsPlayerEventDance(bool is_dance);

	// ブルームフラグ取得
	// 参照元 ... PlayerDraw::m_is_bloom
	// 参照先 ... ブルームフラグが必要な全クラス
	bool GetIsPlayerBloom() const;

	// ダンスフラグ取得
	// 参照元 ... PlayerDraw::m_is_dance
	// 参照先 ... ダンスフラグが必要な全クラス
	bool GetIsPlayerDance() const;

	// イベントによるダンスアニメーションフラグ取得
	// 参照元 ... PlayerDraw::m_is_event_dance
	// 参照先 ... PhaseManager::Update(float delta_time)
	bool GetIsPlayerEventDance() const;

	// イベントによるidleアニメーション処理
	// 参照元 ... PlayerDraw::CinemaAnimIdle(float delta_time)
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void CinemaPlayerAnimIdle(const float delta_time);

	// イベントによるmoveアニメーション処理
	// 参照元 ... PlayerDraw::CinemaAnimMove(float delta_time)
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void CinemaPlayerAnimMove(const float delta_time);
	
	// イベントによるdanceアニメーション処理
	// 参照元 ... PlayerDraw::CinemaAnimDance(float delta_time)
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void CinemaPlayerAnimDance(const float delta_time);

	// playerCollision

	// プレイヤーの当たり判定の登録
	// 参照元 ... PlayerCollision::CollisionRegister()
	// 参照先 ... Player::Initialize()
	void InitCollisionRegister();

	// プレイヤーの当たり判定の更新
	// 参照元 ... PlayerCollision::CollisionCheck()
	// 参照先 ... Player::Update(float delta_time)
	void UpdateCollisionCheck();

	// CinemaPlayer

	// シネマプレイヤーの座標取得
	// 参照元 ... Player::m_pos
	// 参照先 ... Playerの座標が必要な全クラス
	const tnl::Vector3& GetCinemaPlayerPos() const;

	// シネマプレイヤーのダンスフラグ取得
	// 参照元 ... Player::m_is_dance
	// 参照先 ... Player関連クラス
	bool GetCinemaPlayerIsDance() const;

	//--------------------------//


	//---------Partner---------//

	// Partner

	// パートナーの座標設定
	// 参照元 ... Partner::m_pos
	// 参照先 ... Partnerの座標が必要な全クラス
	void SetPartnerPos(tnl::Vector3& pos);

	// パートナーの座標取得
	// 参照元 ... Partner::m_pos
	// 参照先 ... Partnerの座標が必要な全クラス
	const tnl::Vector3& GetPartnerPos() const;

	// パートナーの回転設定
	// 参照元 ... Partner::m_rot
	// 参照先 ... Partnerの回転が必要な全クラス
	void SetPartnerRot(tnl::Quaternion& rot);

	// パートナーの当たり判定サイズ取得
	// 参照元 ... Partner::m_collision_size
	// 参照先 ... PartnerMove::Update(float delta_time)
	const float GetPartnerCollisionSize() const;

	// パートナーの回転取得
	// 参照元 ... Partner::m_rot
	// 参照先 ... Partnerの回転が必要な全クラス
	const tnl::Quaternion& GetPartnerRot() const;

	// PartnerLoad

	// パートナーモデルハンドルの取得
	// 参照元 ... PartnerLoad::m_model_hdl
	// 参照先 ... Partner関連クラス
	int GetPartnerModelHdl() const;

	// パートナーのアイドルボーンハンドル取得
	// 参照元 ... PartnerLoad::m_anim_bone_idle_hdl
	// 参照先 ... Partner関連クラス
	int GetPartnerAnimBoneIdleHdl() const;

	// パートナーの移動ボーンハンドル取得
	// 参照元 ... PartnerLoad::m_anim_bone_move_hdl
	// 参照先 ... Partner関連クラス
	int GetPartnerAnimBoneMoveHdl() const;

	// PartnerMove

	// Partner移動による座標と回転の更新処理
	// 参照元 ... PartnerMove::Update(float delta_time)
	// 参照先 ... Partner::Update(float delta_time)
	void UpdatePartnerMoveMatrix(const float delta_time);

	// パートナーの衝突フラグの設定
	// 参照元 ... PartnerMove::m_is_pushed
	// 参照先 ... Partner::Update(float delta_time)
	void SetIsPartnerPushed(bool is_pushed);

	// PartnerDraw

	// Partnerモデル描画の初期化処理
	// 参照元 ... PartnerDraw::Initialize()
	// 参照先 ... Partner::Initialize()
	void InitializePartnerDraw();

	// Partnerモデルのアニメーション更新処理
	// 参照元 ... PartnerDraw::Update(float delta_time)
	// 参照先 ... Partner::Update(float delta_time)
	void UpdatePartnerAnim(const float delta_time);

	// Partnerモデルの描画処理
	// 参照元 ... PartnerDraw::Draw()
	// 参照先 ... Partner::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawPartnerModel();

	//------------------------------//


	//------CameraTargetPlayer------//

	// CameraTargetPlayer

	// カメラのターゲット座標取得
	// 参照元 ... CameraTargetPlayer::GetPos()
	// 参照先 ... OriginalCamera::target_
	const tnl::Vector3& GetCameraTargetPlayerPos() const;

	// 現在のカメラタイプ取得
	// 参照元 ... CameraTargetPlayer::m_camera_info
	// 参照先 ... 
	const GameCamera::sCameraInfo& GetTargetCameraInfo() const;

	// 現在の足元カメラ取得
	// 参照元 ... Partner::CurrentCameraLane()
	// 参照先 ... GimmickGenerator::CalcGimmickRandomPos()
	GameCamera::sCamera CurrentTargetCameraLane();

	// キャラクターの足元イベントレーンを取得
	// 参照元 ... Character::m_event
	// 参照先 ... イベントレーンが必要な全クラス
	const Lane::sLaneEvent& GetCurrentEventLane() const;

	// ターゲットのスピードアップフラグ
	// 参照元 ... Character::m_is_speed_up
	// 参照先 ... LaneMove::自動移動に関連するクラス
	bool GetIsTargetSpeedUp() const;

	//-------------------------------//


	//------CinemaCameraTarget------//

	// CinemaCameraTarget

	// シネマカメラのターゲット座標取得
	// 参照元 ... CinemaCameraTarget::m_pos
	// 参照先 ... OriginalCamera::target_
	const tnl::Vector3& GetCinemaCameraTargetPos() const;

	//-----------------------------//


	//----------Butterfly----------//

	// Butterfly

	// バタフライの座標取得
	// 参照元 ... Butterfly::m_pos
	// 参照先 ... Butterflyの座標が必要な全クラス
	const tnl::Vector3& GetButterflyPos() const;

	// バタフライのOP描画フラグ設定
	// 参照元 ... Butterfly::m_is_op_active
	// 参照先 ... OpCamera::Update(float delta_time)
	void SetButterflyIsOpActive(bool is_op_active);

	// バタフライのシネマフラグ設定
	// 参照元 ... Butterfly::m_is_cinema_active
	// 参照先 ... OpCamera::Update(float delta_time)
	void SetButterflyIsCinemaActive(bool is_cinema_active);

	// バタフライの鱗粉フラグ取得
	// 参照元 ... Butterfly::m_is_clear
	// 参照先 ... Opに関連する関数
	bool GetButterflyIsClear() const;

	// バタフライの進行方向取得
	// 参照元 ... Butterfly::m_next_direction
	// 参照先 ... Effect::EffectButerfly
	const tnl::Vector3& GetButterflyNextDirection() const;

	// バタフライのシネマフラグ取得
	// 参照元 ... Butterfly::m_is_cinema_active
	// 参照先 ... CinemaCamera::Fixed(const tnl::Vector3& offset)
	bool GetButterflyIsCinemaActive() const;

	// ButterflyLoad

	// バタフライモデルハンドルの取得
	// 参照元 ... ButterflyLoad::m_model_hdl
	// 参照先 ... Butterfly関連クラス
	int GetButterflyModelHdl() const;

	//-----------------------------//


	//-----------Gimmick-----------//

	// Gimmick

	// ギミックの座標取得
	// 参照元 ... Gimmick::m_pos
	// 参照先 ... Effect::EffectGimmick
	const tnl::Vector3& GetGimmickPos() const;

	// ギミックの当たり判定取得
	// 参照元 ... Gimmick::m_is_collision
	// 参照先 ... Gimmick::Update(float delta_time)
	bool GetGimmickIsCollision() const ;

	// GimmickPool

	// ギミックプールのベクター取得
	// 参照元 ... GimmickPool::GetGimmickPools()
	// 参照先 ... GimmickGenerator::関連する関数
	std::vector<std::shared_ptr<Gimmick>>& GetGimmickTypePools(Gimmick::eGimmickType type);

	// GimmickGenerator

	// アイテムフラワーのアクティブ状態取得
	// 参照元 ... GimmickGenerator::m_is_flower_active
	// 参照先 ... 
	bool GetIsGimmickFlowerActive() const ; 

	// 地面ギミックのアクティブ状態取得
	// 参照元 ... GimmickGenerator::m_is_ground_active
	// 参照先 ... Model::Draw(std::shared_ptr<GameCamera> gameCamera)
	bool GetIsGimmickGroundActive() const;

	//--------------------------//


	//----------Effect----------//

	// Effect

	// スクリーンエフェクトのアクティブ状態設定
	// 参照元 ... Effect::m_is_active
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetEffectIsScreen(bool is_screen);

	// EffectLoad

	// エフェクト情報の取得
	// 参照元 ... EffectLoad::m_effect_info
	// 参照先 ... Effect::関連する関数
	const std::vector<Effect::sEffectType>& GetEffectLoadInfo() const;

	//--------------------------//


	//----------Score-----------//

	// Score
	
	// スコア加算判定フラグの設定
	// 参照元 ... Score::m_is_add
	// 参照先 ... Gimmick::Update(float delta_time)
	void SetIsScoreAdd(bool is_add) ;

	//--------------------------//


	//------------Text-----------//

	// Text

	// テキストウィンドウのα値取得
	// 参照元 ... Text::m_window_alpha
	// 参照先 ... CharaGraph::Update(float delta_time)
	int GetTextWindowAlpha() const;

	// TextLoad

	// テキスト全データの取得
	// 参照元 ... TextLoad::m_texts_all
	// 参照先 ... Text::関連する関数
	const std::vector<Text::sTextData>& GetTextsLoadAll() const;

	// TextDraw

	// テキストの初期化
	// 参照元 ... TextDraw::Initialize()
	// 参照先 ... Text::Initialize()
	void InitializeText();

	// テキストの処理
	// 参照元 ... TextDraw::Update(const float delta_time)
	// 参照先 ... Text::Update(float delta_time)
	void UpdateText(const float delta_time);

	// テキストの描画
	// 参照元 ... TextDraw::Draw()
	// 参照先 ... Text::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawTextMessage();

	// テキストの描画終了フラグの取得
	// 参照元 ... TextDraw::m_is_end
	// 参照先 ... TextLoad
	bool GetIsTextDrawEnd();

	// 現在のテキストID取得
	// 参照元 ... TextDraw::m_now_text_id
	// 参照先 ... Text::関連する関数
	int GetNowTextDrawID() const;

	// 現在のレーンの全テキストデータ取得
	// 参照元 ... TextDraw::m_lane_text_data
	// 参照先 ... Text::関連する関数
	const std::vector<Text::sTextData>& GetLaneTextDrawData() const;

	//---------------------------//

	
	//--------CharaGraph---------//

	// CharaGraph

	// プレイヤー画像スライドアウトフラグ設定
	// 参照元 ... CharaGraph::m_is_slide_out_player
	// 参照先 ... Text::Update(float delta_time)
	void SetGraphIsSlidOutPlayer(bool is_slide_out_player);

	// パートナー画像スライドアウトフラグ設定
	// 参照元 ... CharaGraph::m_is_slide_out_partner
	// 参照先 ... Text::Update(float delta_time)
	void SetGraphIsSlidOutPartner(bool is_slide_out_partner);

	// CharaGraphLoad

	// グラフィックデータ取得
	// 参照元 ... CharaGraphLoad::m_graph_info
	// 参照先 ... CharaGraph
	const std::vector<CharaGraph::sGraphInfo>& GetCharaGraphLoadInfo() const;

	//---------------------------//


	//------------Title-----------//

	// Title
	
	// タイトルの描画フラグ設定
	// 参照元 ... Title::m_is_draw
	// 参照先 ... OpCamera::Update(float delta_time)
	void SetTitleIsDraw(bool is_draw);

	// タイトル文字消去フラグ取得
	// 参照元 ... Title::m_is_disappear
	// 参照先 ... OpCamera::Update(float delta_time)
	bool GetTitleIsDisappear() const;

	//---------------------------//


	//------------Gate-----------//

	// GateLoad

	// ゲートの情報取得
	// 参照元 ... GateLoad::m_gates
	// 参照先 ... Gate::モデル情報が必要な全関数
	const std::vector<Gate::sGateInfo>& GetGatesInfo() const;

	//---------------------------//


	//--------OtherGraph---------//

	// EnterGraph

	// ゲートの情報取得
	// 参照元 ... EnterGraph::m_is_active
	// 参照先 ... エンター画像を管理する
	void SetEnterGraphIsActive(bool is_active);

	// ChangeGraph

	// グラフィックの描画フラグ設定
	// 参照元 ... ChangeGraph::m_is_flower
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetChangeGraphIsFlower(bool is_active);

	// グラフィックの描画フラグ設定
	// 参照元 ... ChangeGraph::m_is_wood
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetChangeGraphIsWood(bool is_active);

	// グラフィックの描画フラグ設定
	// 参照元 ... ChangeGraph::m_is_active_white
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetChangeGraphIsActiveWhite(bool is_active);

	// ChildChangeGraph

	// グラフィックの描画フラグ設定
	// 参照元 ... ChangeGraph::m_is_flower
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetChildGraphIsFlower(bool is_active);

	// グラフィックの描画フラグ設定
	// 参照元 ... ChangeGraph::m_is_wood
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetChildGraphIsWood(bool is_active);

	// グラフィックの描画フラグ設定
	// 参照元 ... ChangeGraph::m_is_active_white
	// 参照先 ... CinemaPlayer::Update(float delta_time)
	void SetChildGraphIsActiveWhite(bool is_active);

	// OtherGraphLoad

	// 画像データを取得
	// 参照元 ... OtherGraphLoad::m_graph_info
	// 参照先 ... ChangeGraph::関連する関数
	const std::vector<ChangeGraph::sChangeGraphInfo>& GetChangeGraphInfo() const;

	//---------------------------//


	//-----------Camera----------//

	// GameCamera

	// カメラの座標取得
	// 参照元 ... GameCamera::m_pos
	// 参照先 ... Effect::SffectScreen()
	const tnl::Vector3& GetGameCameraPos() const;

	// カメラの前方向取得
	// 参照元 ... GameCamera::forward()
	// 参照先 ... PlayerMove::ControlMoveMatrix(float delta_time)
	const tnl::Vector3& GetCameraForward() const;

	// カメラの右方向取得
	// 参照元 ... GameCamera::right()
	// 参照先 ... PlayerMove::ControlMoveMatrix(float delta_time)
	const tnl::Vector3& GetCameraRight() const;

	// カメラのフラスタム当たり判定
	// 参照元 ... GameCamera::IsInFlustum()
	// 参照先 ... PlayerMove::
	void IsInCameraFlustum();

	// カメラの固定フラグ取得
	// 参照元 ... GameCamera::m_is_fixed
	// 参照先 ... GimmickGenerator::CheckGimmicks(const float delta_time,)
	bool IsCameraFixed() const;

	// CameraLoad

	// カメラ配列の情報取得
	// 参照元 ... CameraLoad::m_cameras
	// 参照先 ... Camera::関連する関数
	const std::vector<GameCamera::sCamera>& GetCameraLaneVector() const;

	// カメラ情報の取得
	// 参照元 ... CameraLoad::GetCameraInfoById(int id)
	// 参照先 ... Camera::関連する関数
	GameCamera::sCameraInfo GetCameraTypeInfoById(int id);

	// CinemaCamera

	// シネマカメラの座標取得
	// 参照元 ... CinemaCamera::m_pos
	// 参照先 ... Effect::EffectScreen()
	const tnl::Vector3& GetCinemaCameraPos() const;

	// シネマカメラの活性化フラグ設定
	// 参照元 ... CinemaCamera::m_is_active
	// 参照先 ... シネマカメラの活性化フラグが必要な全クラス
	void SetCinemaCameraIsActive(bool is_active);

	// シネマカメラの活性化フラグ取得
	// 参照元 ... CinemaCamera::m_is_active
	// 参照先 ... シネマカメラの活性化フラグが必要な全クラス
	bool GetCinemaCameraIsActive() const;

	//---------------------------//


	//---------ScreenShot--------//

	// ScreenShot

	// スクリーンショットフラグ設定
	// 参照元 ... ScreenShot::m_is_shot
	// 参照先 ... CharaGraph::	void DrawScreenShotGraph();
	bool GetIsScreenShot() const;

	//---------------------------//


	//------------------------------------------------//


	//-----------------ポインタSetter-----------------//

	void SetCameraPhase(std::shared_ptr<CameraPhase>& cameraPhase)
	{
		m_cameraPhase = cameraPhase;
	}

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

	void SetButterfly(std::shared_ptr<Butterfly>& e_butterfly)
	{
		m_butterfly = e_butterfly;
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

	void SetEffect(std::shared_ptr<Effect>& effect)
	{
		m_effect = effect;
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

	void SetCharaGraph(std::shared_ptr<CharaGraph>& charaGraph)
	{
		m_charaGraph = charaGraph;
	}
	
	void SetCharaGraphLoad(std::shared_ptr<CharaGraphLoad>& charaGraphLoad)
	{
		m_charaGraphLoad = charaGraphLoad;
	}

	void SetTitle(std::shared_ptr<Title>& title)
	{
		m_title = title;
	}

	void SetGateLoad(std::shared_ptr<GateLoad>& gateLoad)
	{
		m_gateLoad = gateLoad;
	}

	void SetEnterGraph(std::shared_ptr<EnterGraph>& enterGraph)
	{
		m_enterGraph = enterGraph;
	}

	void SetChangeGraph(std::shared_ptr<ChangeGraph>& changeGraph)
	{
		m_changeGraph = changeGraph;
	}

	void SetChildChangeGraph(std::shared_ptr<ChildChangeGraph>& childCharaGraph)
	{
		m_childChangeGraph = childCharaGraph;
	}

	void SetOtherGraphLoad(std::shared_ptr<OtherGraphLoad>& otherGraphLoad)
	{
		m_otherGraphLoad = otherGraphLoad;
	}

	void SetGameCamera(std::shared_ptr<GameCamera>& gameCamera)
	{
		m_gameCamera = gameCamera;
	}

	void SetCameraLoad(std::shared_ptr<CameraLoad>& cameraLoad)
	{
		m_cameraLoad = cameraLoad;
	}

	void SetCinemaCamera(std::shared_ptr<CinemaCamera>& cinemaCamera)
	{
		m_cinemaCamera = cinemaCamera;
	}

	void SetScreenShot(std::shared_ptr<ScreenShot>& screenShot)
	{
		m_screenShot = screenShot;
	}

	//------------------------------------------------//
};