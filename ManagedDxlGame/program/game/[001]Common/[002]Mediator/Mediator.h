#pragma once
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"
#include "../[000]Object/[000]Stage/[003]Model/Model.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelLoad.h"
#include "../[000]Object/[000]Stage/[003]Model/[000]ModelFunction/ModelPool.h"
#include "../[000]Object/[002]Item/[000]ItemFunction/ItemLoad.h"
#include "../[000]Object/[003]Effect/Effect.h"
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

class Item;
class ItemLoad;
class ItemGenerator;
class ItemPool;

class EffectLoad;

class Text;
class TextLoad;
class TextDraw;

class CharaGraphLoad;
class CharaGraphDraw;

class GameCamera;
class CameraLoad;
class CameraFlustum;

class Mediator
{

private:

	//--------------------ポインタ--------------------//

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

	std::shared_ptr<Item> m_item = nullptr;
	std::shared_ptr<ItemLoad> m_itemLoad = nullptr;
	std::shared_ptr<ItemGenerator> m_itemGenerator = nullptr;
	std::shared_ptr<ItemPool> m_itemPool = nullptr;

	std::shared_ptr<EffectLoad> m_effectLoad = nullptr;

	std::shared_ptr<Text> m_text = nullptr;
	std::shared_ptr<TextLoad> m_textLoad = nullptr;
	std::shared_ptr<TextDraw> m_textDraw = nullptr;

	std::shared_ptr<CharaGraphLoad> m_charaGraphLoad = nullptr;
	std::shared_ptr<CharaGraphDraw> m_charaGraphDraw = nullptr;

	std::shared_ptr<GameCamera> m_gameCamera = nullptr;
	std::shared_ptr<CameraLoad> m_cameraLoad = nullptr;
	std::shared_ptr<CameraFlustum> m_cameraFlustum = nullptr;

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

	//// イベント配列の情報取得
	//// 参照元 ... LaneLoad::m_lane_events
	//// 参照先 ... イベント配列の情報が必要な全クラス
	//const std::vector<Lane::sLane>& GetStageLaneEvent() const;

	// LaneMove

	// 自動移動による座標と回転更新
	// 参照元 ... LoadMove::MoveAstar(float delta_time)
	// 参照先 ... 自動経路による更新が必要な全クラス
	void MoveAstarCharaMatrix(const float delta_time
							 ,tnl::Vector3& pos
							 ,tnl::Quaternion& rot);

	// 自動移動による座標更新
	// 参照元 ... LoadMove::MoveAstarPos(float delta_time)
	// 参照先 ... 自動経路による更新が必要な全クラス
	void MoveAstarTargetPos(const float delta_time, tnl::Vector3& pos);

	// キャラの回転右フラグ設定
	// 参照元 ... Player::m_look_side_right
	// 参照先 ... GameCamera::ConditionType()
	void SetPlayerLookSideRight(bool look_side);

	// キャラの回転左フラグ取得
	// 参照元 ... Player::m_look_side_left
	// 参照先 ... GameCamera::ConditionType()
	void SetPlayerLookSideLeft(bool look_side);

	//// 自動移動による次のレーン到達判定
	//// 参照元 ... LoadMove::NextLane()
	//// 参照先 ... Item::Update(float delta_time)
	//bool NextLaneMove();

	//// 自動移動による移動前座標設定
	//// 参照元 ... LoadMove::m_now_pos
	//// 参照先 ... 自動経路による更新が必要な全クラス
	//void SetMoveNowPos(tnl::Vector3 pos);

	//// 自動移動による移動後座標取得
	//// 参照元 ... LoadMove::m_new_pos
	//// 参照先 ... 自動経路による更新が必要な全クラス
	//tnl::Vector3 GetMoveNewPos() const;

	//// 自動移動による移動前回転設定
	//// 参照元 ... LoadMove::m_now_rot
	//// 参照先 ... 自動経路による更新が必要な全クラス
	//void SetMoveNowRot(tnl::Quaternion rot);

	//// 自動移動による移動後回転取得
	//// 参照元 ... LoadMove::m_new_rot
	//// 参照先 ... 自動経路による更新が必要な全クラス
	//tnl::Quaternion GetMoveNewRot() const;

	//---------------------------//


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

	// プレイヤーの足元レーンを取得
	// 参照元 ... Player::CurrentLane
	// 参照先 ... ItemGenerator::GenerateItem()
	Lane::sLane CurrentPlayerLane();

	// プレイヤーの直線当たり判定用メッシュを取得
	// 参照元 ... Player::m_meshs
	// 参照先 ... PlayerCollision::CollisionCheck()
	const std::vector<std::shared_ptr<dxe::Mesh>>& PlayerGetMeshs() const;


	// playerLoad

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

	//// プレイヤーの現在のレーンID取得
	//// 参照元 ... PlayerMove::m_current_step
	//// 参照先 ... OriginalCamera::RotateBackToPlayer(float delta_time)
	//int GetMoveCurrentStep() const;

	// Player移動による座標と回転の更新処理
	// 参照元 ... PlayerMove::Update(float delta_time)
	// 参照先 ... Player::Update(float delta_time)
	void UpdatePlayerMoveMatrix(const float delta_time);
	
	//// 自動移動に関する処理
	//// 参照元 ... PlayerMove::GetAutoMove()
	//// 参照先 ... Player::Initialize()
	//void GetPlayerMoveAutoMove();

	// プレイヤー操作のフラグ取得
	// 参照元 ... PlayerMove::PushButton()
	// 参照先 ... OriginalCamera::RotateBackToPlayer(float delta_time)
	bool GetPushButton();

	//// 自動運転によるプレイヤーの新しい座標取得
	//// 参照元 ... PlayerMove::m_new_player_pos
	//// 参照先 ... OriginalCamera::RotateBackToPlayer(float delta_time)
	//tnl::Vector3 GetNewPlayerMovePos();

	//// 自動運転によるプレイヤーの新しい回転取得
	//// 参照元 ... PlayerMove::m_new_player_rot
	//// 参照先 ... OriginalCamera::RotateBackToPlayer(float delta_time)
	//tnl::Quaternion GetNewPlayerMoveRot();


	//std::vector<std::pair<int, int>> GetMoveGoalProcess();


	// playerDraw

	// Playerモデルのアニメーション更新処理
	// 参照元 ... PlayerDraw::Update(float delta_time)
	// 参照先 ... Player::Update(float delta_time)
	void UpdatePlayerAnim(const float delta_time);

	// Playerモデルの描画処理
	// 参照元 ... PlayerDraw::Draw()
	// 参照先 ... Player::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawPlayerModel();

	// プレイヤーのモデルハンドル取得
	// 参照元 ... PlayerDraw::m_model_hdl
	// 参照先 ... Player::Player()
	int GetPlayerModelHdl() const ;

	// 攻撃フラグ取得
	// 参照元 ... PlayerDraw::m_is_attack
	// 参照先 ... Player::Update(float delta_time)
	bool GetIsPlayerAttack() const;

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

	// パートナーのスケール設定
	// 参照元 ... Partner::m_scale
	// 参照先 ... Partnerのスケールが必要な全クラス
	void SetPartnerScale(tnl::Vector3& scale);

	// パートナーの当たり判定サイズ取得
	// 参照元 ... Partner::m_collision_size
	// 参照先 ... PartnerMove::Update(float delta_time)
	const float GetPartnerCollisionSize() const;

	// パートナーの回転取得
	// 参照元 ... Partner::m_rot
	// 参照先 ... Partnerの回転が必要な全クラス
	const tnl::Quaternion& GetPartnerRot() const;

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

	// Partnerモデルのアニメーション更新処理
	// 参照元 ... PartnerDraw::Update(float delta_time)
	// 参照先 ... Partner::Update(float delta_time)
	void UpdatePartnerAnim(const float delta_time);

	// Partnerモデルの描画処理
	// 参照元 ... PartnerDraw::Draw()
	// 参照先 ... Partner::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawPartnerModel();

	// Partnerのモデルハンドル取得
	// 参照元 ... PartnerDraw::m_model_hdl
	// 参照先 ... Partner::Initialize()
	int GetPartnerModelHdl() const;

	//--------------------------//


	//----CameraTargetPlayer----//

	// CameraTargetPlayer

	// カメラのターゲット座標取得
	// 参照元 ... CameraTargetPlayer::GetPos()
	// 参照先 ... OriginalCamera::target_
	const tnl::Vector3& GetCameraTargetPlayerPos() const;

	// 現在のカメラタイプ取得
	// 参照元 ... CameraTargetPlayer::m_camera_info
	// 参照先 ... 
	const GameCamera::sCameraInfo& GetTargetCameraInfo() const;

	// キャラクターの足元アイテムレーンを取得
	// 参照元 ... Character::Item::sItem CurrentItemLane()
	// 参照先 ... ItemGenerator::GenerateItem()
	Item::sItem CurrentTargetItemLane();

	//--------------------------//


	//----------Model-----------//

	// model

	// モデルの座標設定
	// 参照元 ... Model::m_pos
	// 参照先 ... PlayerSkill::SeqBloom(float delta_time)
	const tnl::Vector3& GetModelPos() const;

	////モデルの世界属性取得
	//// 参照元 ... Model::m_world_type
	//// 参照先 ... PlayerSkill::SeqBloom(float delta_time)
	//Model::eWorldType GetWorldModelType() const;

	//// モデルの個別アクティブフラグ設定
	//// 参照元 ... Model::m_is_alive_active
	//// 参照先 ... PlayerSkill::SeqBloom(float delta_time)
	//void SetIsModelAliveActive(bool is_active);

	//// モデルの個別アクティブフラグ取得
	//// 参照元 ... Model::m_is_alive_active
	//// 参照先 ... PlayerSkill::SeqBloom(float delta_time)
	//int GetIsModelAliveActive() const;

	//// アクティブ化切り替え
	//// 参照元 ... Model::ToggleActive(bool is_world_active)
	//// 参照先 ... PlayerSkill::SeqBloom(float delta_time)
	//void ToggleModelActive(bool is_world_active);

	// modelLoad

	// ステージモデルの総数取得
	// 参照元 ... ModelLoad::m_model_total_num
	// 参照先 ... ModelPool::関連する関数
	int GetStageModelTotalNum() const;

	// ステージモデルのベクター高さ取得
	// 参照元 ... ModelLoad::m_model_vec_height
	// 参照先 ... Model::Initialize()
	int GetStageModelVecHeight() const ;

	// ステージモデルのベクター幅取得
	// 参照元 ... ModelLoad::m_model_vec_width
	// 参照先 ... Model::Initialize()
	int GetStageModelVecWidth() const ;

	// ステージモデルのベクター取得
	// 参照元 ... ModelLoad::m_stage_tree
	// 参照先 ... Model::関連する関数
	const std::vector<Model::sStageModel>& GetStageTreeVector() const;

	// ステージモデルのベクター取得
	// 参照元 ... ModelLoad::m_stage_grass
	// 参照先 ... Model::関連する関数
	const std::vector<Model::sStageModel>& GetStageGrassVector() const;

	// ステージモデルの情報取得
	// 参照元 ... ModelLoad::m_model_info
	// 参照先 ... ModelPool::関連する関数
	const std::vector<Model::sStageModelType>& GetStageModelTypeInfo() const;

	// ステージモデルのid取得
	// 参照元 ... ModelLoad::GetModelInfoById(int id)
	// 参照先 ... ModelPool::関連する関数
	Model::sStageModelType GetStageModelInfoById(int id);

	// modelPool

	//// 世界変更によるモデルの一斉アクティブ化
	//// 参照元 ... ModelPool::DeactivateAllModels(Model::eWorldType world_type)
	//// 参照先 ... StagePhase::シーケンス関数
	//void IsActivatePoolAllModels(Model::eWorldType world_type);

	// 現実世界のベクター取得
	// 参照元 ... ModelPool::GetModels()
	// 参照先 ... StagePhase::シーケンス関数
	std::vector<std::shared_ptr<Model>>& GetPoolModels() const;

	//// ランダムなモデルのポインタを取得
	//// 参照元 ... ModelPool::GetRandomModel(Model::eWorldType world_type)
	//// 参照先 ... PlayerSkill::SeqBloom(float delta_time)
	//std::shared_ptr<Model> GetPoolRandomModel(Model::eWorldType world_type);


	//--------------------------//


	//-----------ltem-----------//

	// Item

	// アイテムのアクティブ化設定
	// 参照元 ... Item::m_is_active
	// 参照先 ... ItemGenerator::Update(const float delta_time)
	void SetItemIsActive(bool is_active);

	// アイテムの当たり判定状態取得
	// 参照元 ... Item::m_is_hit
	// 参照先 ... 当たり判定が必要な全クラス
	bool GetItemIsHit() const;

	// ItemLoad

	// アイテムモデルの総数取得
	// 参照元 ... ItemLoad::m_id_num
	// 参照先 ... Item::Initialize()
	int GetItemIdNum() const;

	// アイテムレーン配列を取得
	// 参照元 ... ItemLoad::m_item_lane
	// 参照先 ... Item::関連する関数
	const std::vector<Item::sItem>& GetItemLoadLane() const;

	// アイテム情報配列を取得
	// 参照元 ... ItemLoad::m_item_info
	// 参照先 ... Item::関連する関数
	const std::vector<Item::sItemType>& GetItemTypeInfo() const;

	// アイテムモデルのid取得
	// 参照元 ... ItemLoad::GetItemInfoById()
	// 参照先 ... Item::
	Item::sItemType GetItemLoadInfoById(int id);

	// ItemPool

	// アイテムプールのアクティブ状態取得
	// 参照元 ... ItemPool::GetNotActiveItem()
	// 参照先 ... ItemGenerator::
	std::shared_ptr<Item> GetNotActiveItemPool();

	// アイテムプールのベクター取得
	// 参照元 ... ItemPool::GetItems()
	// 参照先 ... ItemGenerator::SeqDelete(float delta_time)
	const std::vector<std::shared_ptr<Item>>& GetPoolItems() const;

	// ItemGenerator

	// アイテムフラワーのアクティブ状態取得
	// 参照元 ... ItemGenerator::m_is_flower_active
	// 参照先 ... 
	bool GetIsItemFlowerActive() const ; 


	//// アイテムの生成フラグ設定
	//// 参照元 ... ItemGenerator::m_is_create
	//// 参照先 ... LaneMove::MoveAstar( ... );
	//void SetItemIsCreate(bool is_create);

	//// アイテムの削除フラグ設定
	//// 参照元 ... ItemGenerator::m_is_delete
	//// 参照先 ... LaneMove::MoveAstar( ... );
	//void SetItemIsDelete(bool is_delete);

	//--------------------------//


	//----------Effect----------//

	// EffectLoad

	// エフェクト情報の取得
	// 参照元 ... EffectLoad::m_effect_info
	// 参照先 ... Effect::関連する関数
	const std::vector<Effect::sEffectType>& GetEffectLoadInfo() const;

	//--------------------------//

	//------------Text-----------//

	// TextDraw

	// テキストの処理
	// 参照元 ... TextDraw::Update()
	// 参照先 ... Text::Update(float delta_time)
	void UpdateTextMessage(const float delta_time);

	// テキストの描画
	// 参照元 ... TextDraw::Draw()
	// 参照先 ... Text::Draw(std::shared_ptr<OriginalCamera> originalCamera)
	void DrawTextMessage();

	//---------------------------//

	
	//--------CharaGraph---------//

	// CharaGraphLoad

	//// グラフィックの総数取得
	//// 参照元 ... CharaGraphLoad::m_graph_total_num
	//// 参照先 ... CharaGraph
	//const int GetCharaGraphLoadTotalNum() const ;

	// グラフィックデータ取得
	// 参照元 ... CharaGraphLoad::m_graph_info
	// 参照先 ... CharaGraph
	const std::vector<CharaGraph::sGraphInfo>& GetCharaGraphLoadInfo() const;

	// CharaGraphDraw

	// キャラクターグラフィックのロード
	// 参照元 ... CharaGraphDraw::LoadCharaGraph()
	// 参照先 ... CharaGraph
	void LoadCharacterGraph();

	// キャラクターグラフィックの描画
	// 参照元 ... CharaGraphDraw::DrawCharaGraph()
	// 参照先 ... CharaGraph
	void DrawCharacterGraph(int graph_id);


	//---------------------------//


	//----------Camera---------//

	// GameCamera

	// カメラの座標取得
	// 参照元 ... GameCamera::pos_
	// 参照先 ... PlayerMove::Update(const float delta_time)
	const tnl::Vector3& GetCameraPos() const;

	// カメラの前方向取得
	// 参照元 ... dxe::GameCamera::forward()
	// 参照先 ... PlayerMove::ControlMoveMatrix(float delta_time)
	const tnl::Vector3& GetCameraForward() const;

	// カメラの右方向取得
	// 参照元 ... dxe::GameCamera::right()
	// 参照先 ... PlayerMove::ControlMoveMatrix(float delta_time)
	const tnl::Vector3& GetCameraRight() const;

	//// カメラの上方向取得
	//// 参照元 ... dxe::GameCamera::left()
	//// 参照先 ... PlayerMove::ControlMoveMatrix(float delta_time)
	//const tnl::Vector3& GetCameraLeft() const;

	//// カメラの下方向取得
	//// 参照元 ... dxe::GameCamera::back()
	//// 参照先 ... PlayerMove::ControlMoveMatrix(float delta_time)
	//const tnl::Vector3& GetCameraBack() const;

	//// カメラのビュー行列取得
	//// 参照元 ... dxe::Camera::view_
	//// 参照先 ... CameraFrustum::Update()
	//const tnl::Matrix& GetCameraView() const;

	//// カメラの射影行列取得
	//// 参照元 ... dxe::Camera::proj_
	//// 参照先 ... CameraFrustum::Update()
	//const tnl::Matrix& GetCameraProj() const;

	// フラスタムの法線ベクトル取得
	// 参照元 ... dxe::Camera::getFlustumNormal(eFlustum flustum)
	// 参照先 ... CameraFrustum
	tnl::Vector3 GetFlustumNormal(dxe::Camera::eFlustum flusum);


	// CameraLoad

	// カメラ配列の高さ取得
	// 参照元 ... CameraLoad::m_lane_height
	// 参照先 ... Camera::CurrentCamera()
	int GetCameraLaneHeight() const;

	// カメラ配列の幅取得
	// 参照元 ... CameraLoad::m_lane_width
	// 参照先 ... Camera::CurrentCamera()
	int GetCameraLaneWidth() const;

	// カメラ配列の情報取得
	// 参照元 ... CameraLoad::m_cameras
	// 参照先 ... Camera::関連する関数
	const std::vector<GameCamera::sCamera>& GetCameraLaneVector() const;

	// カメラ情報の取得
	// 参照元 ... CameraLoad::GetCameraInfoById(int id)
	// 参照先 ... Camera::関連する関数
	GameCamera::sCameraInfo GetCameraTypeInfoById(int id);

	// CameraFlustum

	//// フラスタムの更新
	//// 参照元 ... CameraFrustum::Update()
	//// 参照先 ... Camera::Update(float delta_time)
	//void UpdateCameraFrustum();

	//// フラスタムの当たり判定の登録
	//// 参照元 ... CameraFrustum::CollisionRegister()
	//// 参照先 ... Camera::Initialize()
	//void CollisionFrustumRegister();

	//// フラスタムの当たり判定の更新
	//// 参照元 ... CameraFrustum::CollisionCheck()
	//// 参照先 ... Camera::Update(float delta_time)
	//void CollisionFrustumCheck();

	// フラスタムの当たり判定処理
	// 参照元 ... CameraFlustum::IsIntersectFlustum(const float delta_time)
	// 参照先 ... Camera::Update(float delta_time)
	void IsIntersectCameraFlustum(const float delta_time);

	//---------------------------//


	//------------------------------------------------//


	//-----------------ポインタSetter-----------------//

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

	void SetItemLoad(std::shared_ptr<ItemLoad>& itemLoad)
	{
		m_itemLoad = itemLoad;
	}

	void SetItemGenerator(std::shared_ptr<ItemGenerator>& itemGenerator)
	{
		m_itemGenerator = itemGenerator;
	}

	void SetItemPool(std::shared_ptr<ItemPool>& itemPool)
	{
		m_itemPool = itemPool;
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

	void SetCameraFlustum(std::shared_ptr<CameraFlustum>& cameraFlustum)
	{
		m_cameraFlustum = cameraFlustum;
	}

	//------------------------------------------------//
};