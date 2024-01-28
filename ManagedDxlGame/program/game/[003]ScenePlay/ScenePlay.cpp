#include "ScenePlay.h"
#include "../[000]GameEngine/[001]Scene/SceneManager.h"
#include "../[001]Common/[005]Factory/PlayFactory.h"
#include "../[001]Common/[001]Camera/GameCamera.h"
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
	m_objects = m_factory->GetObjects();
	// カメラの取得
	m_gameCamera = m_factory->GetGameCamera();
	// ステージの取得
	m_stagePhase = m_factory->GetStagePhase();
	// アイテムジェネレータの取得
	m_gimmickGenerator = m_factory->GetGimmickGenerator();
	// スクリーンショットの取得
	m_screenShot = m_factory->GetScreenShot();

	//m_gimmickGenerator->Initialize();

	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Initialize();
	}
}

void ScenePlay::Update(const float delta_time)
{
	m_stagePhase->Update(delta_time);

	m_gimmickGenerator->Update(delta_time);


	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Update(delta_time);
	}

	m_gameCamera->update(delta_time);
}

void ScenePlay::Draw(const float delta_time)
{
	//DrawDefaultLightGuiController();
	DrawGridGround(m_gameCamera);

	m_screenShot->SaveScreenShot();

	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Draw(m_gameCamera);
	}

	// Fps表示
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

void ScenePlay::Finalize()
{
	m_objects.clear();

	m_factory.reset();
}