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


	//--------------------ポインタ--------------------//

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

	//-------------------メンバ関数-------------------//

	//---------StagePhase---------//

	// stagePhase

	// ステージフェーズ取得
	// 参照元 ... StagePhase::m_stage_phase
	// 参照先 ... フェーズ状態の取得が必要な全クラス（フェーズ遷移の影響を持つクラス）
	StagePhase::eStagePhase GetNowStagePhaseState() const;

	//---------------------------//


	//---------CinemaBack---------//

	// CinemaBack

	// シネマバック一番フラグ設定
	// 参照元 ... CinemaBack::m_is_first
	// 参照先 ... CinemaCamera::Update(float delta_time)
	void SetCinemaBackIsFirst(bool is_first);

	// シネマバック二番フラグ設定
	// 参照元 ... CinemaBack::m_is_second
	// 参照先 ... CinemaCamera::Update(float delta_time)
	void SetCinemaBackIsSecond(bool is_second);

	// シネマバック三番フラグ設定
	// 参照元 ... CinemaBack::m_is_third
	// 参照先 ... CinemaCamera::Update(float delta_time)
	void SetCinemaBackIsThird(bool is_third);

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

	// modelLoad

	// ステージモデルの情報取得
	// 参照元 ... ModelLoad::m_model_info
	// 参照先 ... ModelPool::関連する関数
	const std::vector<Model::sModelInfo>& GetStageModelInfo() const;

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
	// 参照先 ... 
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

	// イベントによるダンスアニメーションフラグ設定
	// 参照元 ... PlayerDraw::m_is_event_dance
	// 参照先 ... CameraTargetPlayer::Update(float delta_time)
	void SetIsPlayerEventDance(bool is_dance);

	// ブルームフラグ取得
	// 参照元 ... PlayerDraw::m_is_bloom
	// 参照先 ... ブルームフラグが必要な全クラス
	bool GetIsPlayerBloom() const;

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

	// playerSkill

	// プレイヤースキルの更新処理
	// 参照元 ... PlayerSkill::Update(float delta_time)
	// 参照先 ... Player::Update(float delta_time)
	void UpdatePlayerSkill(const float delta_time);

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

	// 現在の足元カメラ取得
	// 参照元 ... Partner::CurrentCamera()
	// 参照先 ... GimmickGenerator::CalcGimmickRandomPos()
	GameCamera::sCamera CurrentCameraLane();

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

	// キャラクターの足元イベントレーンを取得
	// 参照元 ... Character::m_event
	// 参照先 ... イベントレーンが必要な全クラス
	const Lane::sLaneEvent& GetEventLane() const;

	// ターゲットのスピードアップフラグ
	// 参照元 ... Character::m_is_speed_up
	// 参照先 ... LaneMove::自動移動に関連するクラス
	bool GetIsTargetSpeedUp() const;

	//// ターゲットの上昇移動フラグ
	//// 参照元 ... Character::m_is_move_up
	//// 参照先 ... LaneMove::自動移動に関連するクラス
	//bool GetIsTargetMoveUp() const;

	// ターゲットの下降移動フラグ
	// 参照元 ... Character::m_is_move_down
	// 参照先 ... LaneMove::自動移動に関連するクラス
	bool GetIsTargetMoveDown() const;

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

	// バタフライの鱗粉フラグ取得
	// 参照元 ... Butterfly::m_is_powder
	// 参照先 ... Opに関連する関数
	bool GetButterflyIsPowder() const;

	// バタフライのシネマフラグ設定
	// 参照元 ... Butterfly::m_is_cinema_active
	// 参照先 ... OpCamera::Update(float delta_time)
	void SetButterflyIsCinemaActive(bool is_cinema_active);

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

	// GimmickPool

	// アイテムプールのアクティブ状態取得
	// 参照元 ... GimmickPool::GetNotActiveGimmick(std::vector<std::shared_ptr<Gimmick>>& gimmicks)
	// 参照先 ... GimmickGenerator::
	std::shared_ptr<Gimmick> GetNotActiveGimmickPool(std::vector<std::shared_ptr<Gimmick>>& gimmicks);

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

	// TextLoad

	// レーンIDに該当するテキスト文字の取得
	// 参照元 ... TextLoad::GetTextsLane()
	// 参照先 ... Text::関連する関数
	void GetTextsLoadLane();
	
	// レーンIDに該当す全ての構造体データの取得
	// 参照元 ... TextLoad::m_texts_for_lane
	// 参照先 ... Text::関連する関数
	const std::vector<Text::sTextData>& GetTextsLoadForLane() const;

	// TextDraw

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
	void SetIsTextDrawEnd(bool is_end);

	//---------------------------//

	
	//--------CharaGraph---------//

	// CharaGraphLoad

	// グラフィックデータ取得
	// 参照元 ... CharaGraphLoad::m_graph_info
	// 参照先 ... CharaGraph
	const std::vector<CharaGraph::sGraphInfo>& GetCharaGraphLoadInfo() const;

	// CharaGraphDraw

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


	//-----------Camera----------//

	// GameCamera

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

	// ゲームカメラのアクティブ状態設定
	// 参照元 ... GameCamera::m_is_active_game
	// 参照先 ... カメラ切り替えに関連する関数
	void SetIsActiveGameCamera(bool is_active_game);

	// ゲームカメラのアクティブ状態取得
	// 参照元 ... GameCamera::m_is_active_game
	// 参照先 ... ゲームカメラで描画する関数
	bool GetIsActiveGameCamera() const;

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


	//---------------------------//


	//------------------------------------------------//


	//-----------------ポインタSetter-----------------//

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