#pragma once
#include "../[000]GameEngine/[000]Scene/SceneBase.h"
#include "../[001]Common/[000]Object/Object.h"


class PlayFactory;

class GameCamera;
class CinemaCamera;

class CameraPhase;
class StagePhase;

class GimmickGenerator;

class ScreenShot;


///////////////////////////////////////////////////////////////////////////
//
// Play�V�[���̈ꊇ�������s���N���X
//
///////////////////////////////////////////////////////////////////////////


class ScenePlay : public SceneBase
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	ScenePlay();
	~ScenePlay();

	//--------------------------------------------------------------------------------//

private:
	
	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �Q�[���J�����Ǌ��̃I�u�W�F�N�glist
	std::list<std::shared_ptr<Object>> m_objects_gameCamera;
	// �V�l�}�J�����Ǌ��̃I�u�W�F�N�glist
	std::list<std::shared_ptr<Object>> m_objects_cinemaCamera;

	// �e�N���X�̃|�C���^

	std::shared_ptr<PlayFactory> m_factory = nullptr;

	std::shared_ptr<GameCamera> m_gameCamera = nullptr;
	std::shared_ptr<CinemaCamera> m_cinemaCamera = nullptr;

	std::shared_ptr<CameraPhase> m_cameraPhase = nullptr;
	std::shared_ptr<StagePhase> m_stagePhase = nullptr;

	std::shared_ptr<GimmickGenerator> m_gimmickGenerator = nullptr;

	std::shared_ptr<ScreenShot> m_screenShot = nullptr;

	// �V�[�P���X
	tnl::Sequence<ScenePlay> m_sequence
		= tnl::Sequence<ScenePlay>(this, &ScenePlay::SeqStart);

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �t�@�N�g���[�N���X����̎擾
	// tips ... ���������Ɉ�x�����Ăяo��
	void GetFromFactory();

	// �V�[�P���X�J�n
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqStart(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//
};