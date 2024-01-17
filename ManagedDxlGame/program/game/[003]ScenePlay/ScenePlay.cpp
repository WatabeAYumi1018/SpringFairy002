#include "ScenePlay.h"
#include "../[000]GamEngine/[001]Scene/SceneManager.h"
#include "../[002]ScenePlay/[005]Factory/Factory.h"
#include "[001]Camera/GameCamera.h"
#include "../[002]ScenePlay/[003]Phase/StagePhase.h"
#include "[000]Object/[002]Item/[000]ItemFunction/ItemGenerator.h"


ScenePlay::ScenePlay() : m_factory(std::make_shared<Factory>())
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

	//m_gameCamera->Initialize();

	// ステージの取得
	m_stagePhase = m_factory->GetStagePhase();
	// アイテムジェネレータの取得
	m_itemGenerator = m_factory->GetItemGenerator();

	m_itemGenerator->Initialize();

	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Initialize();
	}
}

void ScenePlay::Update(const float delta_time)
{
	m_stagePhase->Update(delta_time);

	m_itemGenerator->Update(delta_time);

	m_gameCamera->update(delta_time);

	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Update(delta_time);
	}
}

void ScenePlay::Draw(const float delta_time)
{
	//DrawDefaultLightGuiController();
	DrawGridGround(m_gameCamera);

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