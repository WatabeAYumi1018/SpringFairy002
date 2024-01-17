//#include "SceneTitle.h"
//#include "../[002]ScenePlay/[005]Factory/Factory.h"
//#include "../[000]GamEngine/[001]Scene/SceneManager.h"
//#include "[001]Camera/GameCamera.h"
//
//
//SceneTitle::SceneTitle() : m_factory(std::make_shared<Factory>())
//{
//	Initialize();
//
//	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
//	SetDefaultLightParameter("directional_light_parameter.bin");
//}
//
//SceneTitle::~SceneTitle()
//{
//	Finalize();
//}
//
//bool SceneTitle::SeqStart(const float delta_time)
//{
//	SceneManager* scene = SceneManager::GetInstance();
//
//	scene->ChangeScene(new SceneTitle());
//
//	return true;
//}
//
//void SceneTitle::Initialize()
//{
//	// 各オブジェクトの参照をFactoryクラスから取得
//	m_objects = m_factory->GetObjects();
//	// カメラの取得
//	m_gameCamera = m_factory->GetGameCamera();
//
//	//m_gameCamera->Initialize();
//
//	for (std::shared_ptr<Object>& object : m_objects)
//	{
//		object->Initialize();
//	}
//}
//
//void SceneTitle::Update(const float delta_time)
//{
//	for (std::shared_ptr<Object>& object : m_objects)
//	{
//		object->Update(delta_time);
//	}
//}
//
//void SceneTitle::Draw(const float delta_time)
//{
//	//DrawDefaultLightGuiController();
//	DrawGridGround(m_gameCamera);
//
//	for (std::shared_ptr<Object>& object : m_objects)
//	{
//		object->Draw(m_gameCamera);
//	}
//
//	// Fps表示
//	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
//}
//
//void SceneTitle::Finalize()
//{
//	m_objects.clear();
//
//	m_factory.reset();
//}