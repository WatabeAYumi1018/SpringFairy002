//#include "SceneOp.h"
//#include "../[002]ScenePlay/[005]Factory/Factory.h"
//#include "../[000]GamEngine/[001]Scene/SceneManager.h"
//#include "[001]Camera/GameCamera.h"
//
//
//SceneOp::SceneOp() : m_factory(std::make_shared<Factory>())
//{
//	Initialize();
//
//	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
//	SetDefaultLightParameter("directional_light_parameter.bin");
//}
//
//SceneOp::~SceneOp()
//{
//	Finalize();
//}
//
//bool SceneOp::SeqStart(const float delta_time)
//{
//	SceneManager* scene = SceneManager::GetInstance();
//
//	scene->ChangeScene(new SceneOp());
//
//	return true;
//}
//
//void SceneOp::Initialize()
//{
//	// �e�I�u�W�F�N�g�̎Q�Ƃ�Factory�N���X����擾
//	m_objects = m_factory->GetObjects();
//	// �J�����̎擾
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
//void SceneOp::Update(const float delta_time)
//{
//	for (std::shared_ptr<Object>& object : m_objects)
//	{
//		object->Update(delta_time);
//	}
//}
//
//void SceneOp::Draw(const float delta_time)
//{
//	//DrawDefaultLightGuiController();
//	DrawGridGround(m_gameCamera);
//
//	for (std::shared_ptr<Object>& object : m_objects)
//	{
//		object->Draw(m_gameCamera);
//	}
//
//	// Fps�\��
//	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
//}
//
//void SceneOp::Finalize()
//{
//	m_objects.clear();
//
//	m_factory.reset();
//}