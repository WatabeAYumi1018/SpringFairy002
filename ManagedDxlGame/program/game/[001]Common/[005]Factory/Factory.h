#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"


// 名前空間＋テンプレートの前方宣言
namespace wta 
{
	template <class T>
	class Astar;
}

namespace wta
{
	template <class T1,class T2>
	class Collision;
}

class StagePhase;

class Object;

class SkyBox;

class LaneLoad;
class LaneMove;

class Floor;

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

class Model;
class ModelLoad;
class ModelPool;

class Gimmick;
class GimmickLoad;
class GimmickGenerator;
class GimmickPool;

class Effect;
class EffectLoad;

class Score;

class CharaGraph;
class CharaGraphLoad;
class CharaGraphDraw;

class Text;
class TextLoad;
class TextDraw;

class GameCamera;
class CameraLoad;

class Mediator;

class ScreenShot;

class Factory
{

public:

	Factory();
	
	~Factory();

private:

	// オブジェクトを格納するlist
	std::list<std::shared_ptr<Object>> m_objects;

	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	std::shared_ptr<wta::Collision<Player, Gimmick>> m_collision_player_item = nullptr;
	std::shared_ptr<wta::Collision<dxe::Mesh, Gimmick>> m_collision_mesh_item = nullptr;
	std::shared_ptr<wta::Collision<Player, Partner>> m_collision_player_partner = nullptr;
	//std::shared_ptr<wta::Collision<Player, GameCamera>> m_collision_camera = nullptr;

	std::shared_ptr<StagePhase> m_stagePhase = nullptr;

	std::shared_ptr<SkyBox> m_skyBox = nullptr;

	std::shared_ptr<LaneLoad> m_laneLoad = nullptr;
	std::shared_ptr<LaneMove> m_laneMove = nullptr;

	std::shared_ptr<Floor> m_floor = nullptr;

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

	std::shared_ptr<GimmickLoad> m_gimmickLoad = nullptr;
	std::shared_ptr<GimmickGenerator> m_gimmickGenerator = nullptr;
	std::shared_ptr<GimmickPool> m_gimmickPool = nullptr;

	std::shared_ptr<Effect> m_effect = nullptr;
	std::shared_ptr<EffectLoad> m_effectLoad = nullptr;

	std::shared_ptr<Score> m_score = nullptr;

	std::shared_ptr<Text> m_text = nullptr;
	std::shared_ptr<TextLoad> m_textLoad = nullptr;
	std::shared_ptr<TextDraw> m_textDraw = nullptr;

	std::shared_ptr<CharaGraph> m_charaGraph = nullptr;
	std::shared_ptr<CharaGraphLoad> m_charaGraphLoad = nullptr;
	std::shared_ptr<CharaGraphDraw> m_charaGraphDraw = nullptr;

	std::shared_ptr<GameCamera> m_gameCamera = nullptr;
	std::shared_ptr<CameraLoad> m_cameraLoad = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	std::shared_ptr<ScreenShot> m_screenShot = nullptr;


	// 各オブジェクトの生成と初期化
	void CreateObject();
	// 各オブジェクト同士の参照を設定
	// 生成の順番を考慮せず、後付けで参照できるように
	void SetObjectReference();
	// モデルオブジェクトのプール
	//void PoolModelObject();
	// アイテムオブジェクトのプール
	void PoolGimmickObject();
	// 生成したオブジェクトをlistに格納
	void StorageObject();


public:

	// listに格納したオブジェクトの取得
	const std::list<std::shared_ptr<Object>>& GetObjects() const
	{
		return m_objects;
	}

	// カメラの取得
	const std::shared_ptr<GameCamera>& GetGameCamera() const
	{
		return m_gameCamera;
	}

	// フェーズの取得
	const std::shared_ptr<StagePhase>& GetStagePhase() const
	{
		return m_stagePhase;
	}

	const std::shared_ptr<GimmickGenerator>& GetGimmickGenerator() const
	{
		return m_gimmickGenerator;
	}

	const std::shared_ptr<ScreenShot>& GetScreenShot() const
	{
		return m_screenShot;
	}
};