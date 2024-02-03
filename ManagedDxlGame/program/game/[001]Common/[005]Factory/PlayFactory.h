#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"
#include "../[000]Object/[002]Gimmick/Gimmick.h"


// ���O��ԁ{�e���v���[�g�̑O���錾
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

class Model;
class ModelLoad;
class ModelPool;
//class ModelGenerator;

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

class GimmickLoad;
class GimmickPool;
class GimmickGenerator;

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
class CinemaCamera;

class Mediator;

class ScreenShot;

class PlayFactory
{

public:

	PlayFactory();
	
	~PlayFactory();

private:

	// �I�u�W�F�N�g���i�[����list(�Q�[���J����)
	std::list<std::shared_ptr<Object>> m_objects_gameCamera;

	// �I�u�W�F�N�g���i�[����list�i�V�l�}�J�����j
	std::list<std::shared_ptr<Object>> m_objects_cinemaCamera_all;
	std::list<std::shared_ptr<Object>> m_objects_cinemaCamera_half;
	std::list<std::shared_ptr<Object>> m_objects_cinemaCamera_third_left;
	std::list<std::shared_ptr<Object>> m_objects_cinemaCamera_third_right;

	// �v���C���[�Փ˃I�u�W�F�N�g���i�[����list
	std::vector<std::shared_ptr<Gimmick>> m_gimmicks;

	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	std::shared_ptr<wta::Collision<Player, Gimmick>> m_collision_player_item = nullptr;
	std::shared_ptr<wta::Collision<dxe::Mesh, Gimmick>> m_collision_mesh_item = nullptr;
	std::shared_ptr<wta::Collision<Player, Partner>> m_collision_player_partner = nullptr;

	std::shared_ptr<StagePhase> m_stagePhase = nullptr;

	std::shared_ptr<SkyBox> m_skyBox = nullptr;

	std::shared_ptr<LaneLoad> m_laneLoad = nullptr;
	std::shared_ptr<LaneMove> m_laneMove = nullptr;

	std::shared_ptr<Floor> m_floor = nullptr;

	std::shared_ptr<Model> m_model = nullptr;
	std::shared_ptr<ModelLoad> m_modelLoad = nullptr;
	std::shared_ptr<ModelPool> m_modelPool = nullptr;

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

	std::shared_ptr<CinemaCamera> m_cinemaCamera_all = nullptr;
	std::shared_ptr<CinemaCamera> m_cinemaCamera_half = nullptr;
	std::shared_ptr<CinemaCamera> m_cinemaCamera_third_left = nullptr;
	std::shared_ptr<CinemaCamera> m_cinemaCamera_third_right = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	std::shared_ptr<ScreenShot> m_screenShot = nullptr;


	// �e�I�u�W�F�N�g�̐����Ə�����
	void CreateObject();
	// �e�I�u�W�F�N�g���m�̎Q�Ƃ�ݒ�
	// �����̏��Ԃ��l�������A��t���ŎQ�Ƃł���悤��
	void SetObjectReference();
	// ���f���I�u�W�F�N�g�̃v�[��
	//void PoolModelObject();
	// �A�C�e���I�u�W�F�N�g�̃v�[��
	void PoolGimmickType(const std::vector<Gimmick::sGimmickTypeInfo>& gimmick_types);
	// ���������I�u�W�F�N�g��list�Ɋi�[
	void StorageObjectGameCamera();
	void StorageObjectCinemaCamera();

public:

	// list�Ɋi�[�����I�u�W�F�N�g�̎擾(�Q�[���J����)
	const std::list<std::shared_ptr<Object>>& GetObjectsGameCamera() const
	{
		return m_objects_gameCamera;
	}

	// list�Ɋi�[�����I�u�W�F�N�g�̎擾(�V�l�}�J����)
	const std::list<std::shared_ptr<Object>>& GetObjectsCinemaCamera() const
	{
		return m_objects_cinemaCamera_all;
	}

	// �J�����̎擾
	const std::shared_ptr<GameCamera>& GetOpCamera() const
	{
		return m_gameCamera;
	}

	// �V�l�}�J�����̎擾
	const std::shared_ptr<CinemaCamera>& GetCinemaCameraAll() const
	{
		return m_cinemaCamera_all;
	}

	const std::shared_ptr<CinemaCamera>& GetCinemaCameraHalf() const
	{
		return m_cinemaCamera_half;
	}

	const std::shared_ptr<CinemaCamera>& GetCinemaCameraThirdLeft() const
	{
		return m_cinemaCamera_third_left;
	}

	const std::shared_ptr<CinemaCamera>& GetCinemaCameraThirdRight() const
	{
		return m_cinemaCamera_third_right;
	}

	// �t�F�[�Y�̎擾
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