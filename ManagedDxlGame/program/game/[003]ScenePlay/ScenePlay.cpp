#include "ScenePlay.h"
#include "../[000]GameEngine/[001]Scene/SceneManager.h"
#include "../[001]Common/[005]Factory/PlayFactory.h"
#include "../[001]Common/[001]Camera/GameCamera.h"
#include "../[001]Common/[001]Camera/[001]CinemaCamera/CinemaCamera.h"
#include "../[003]ScenePlay/ScenePlay.h"
#include "../[001]Common/[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickGenerator.h"
#include "../[001]Common/[004]ScreenShot/ScreenShot.h"


ScenePlay::ScenePlay() : m_factory(std::make_shared<PlayFactory>())
{
	Initialize();

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetDefaultLightParameter("directional_light_parameter.bin");
}

ScenePlay::~ScenePlay()
{
	Finalize();
}

bool ScenePlay::SeqStart(const float delta_time)
{
	SceneManager* scene = SceneManager::GetInstance();

	scene->ChangeScene(new ScenePlay());

	return true;
}

void ScenePlay::Initialize()
{
	// 各オブジェクトの参照をFactoryクラスから取得
	m_objects_gameCamera = m_factory->GetObjectsGameCamera();
	m_objects_cinemaCamera = m_factory->GetObjectsCinemaCamera();
	// カメラの取得
	m_gameCamera = m_factory->GetGameCamera();
	// シネマカメラの取得
	m_cinemaCamera = m_factory->GetCinemaCamera();
	// ステージの取得
	m_stagePhase = m_factory->GetStagePhase();
	// アイテムジェネレータの取得
	m_gimmickGenerator = m_factory->GetGimmickGenerator();
	// スクリーンショットの取得
	m_screenShot = m_factory->GetScreenShot();

	//m_gimmickGenerator->Initialize();

	for (std::shared_ptr<Object>& object : m_objects_gameCamera)
	{
		object->Initialize();
	}

	for (std::shared_ptr<Object>& object : m_objects_cinemaCamera)
	{
		object->Initialize();
	}
}

void ScenePlay::Update(const float delta_time)
{
	m_stagePhase->Update(delta_time);

	m_gameCamera->update(delta_time);

	m_cinemaCamera->update(delta_time);
	
	m_gimmickGenerator->Update(delta_time);

	for (std::shared_ptr<Object>& object : m_objects_gameCamera)
	{
		//SetDrawArea(0, 0, DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT);

		object->Update(delta_time);
	}

	for (std::shared_ptr<Object>& object : m_objects_cinemaCamera)
	{
		SetDrawArea(DXE_WINDOW_WIDTH / 2, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

		object->Update(delta_time);
	}

	// 描画領域をリセット
	//SetDrawArea(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
}

void ScenePlay::Draw(const float delta_time)
{
	//DrawGridGround(m_gameCamera);

	//DrawGridGround(m_cinemaCamera);

	//DrawDefaultLightGuiController();

	m_screenShot->SaveScreenShot();

	for (std::shared_ptr<Object>& object : m_objects_gameCamera)
	{
		object->Draw(m_gameCamera);
	}

	for (std::shared_ptr<Object>& object : m_objects_cinemaCamera)
	{
		object->Draw(m_cinemaCamera);
	}

	// Fps表示
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

void ScenePlay::Finalize()
{
	m_objects_gameCamera.clear();

	m_objects_cinemaCamera.clear();

	m_factory.reset();
}