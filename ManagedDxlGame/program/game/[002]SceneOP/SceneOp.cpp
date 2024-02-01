#include "SceneOp.h"
#include "../[001]Common/[005]Factory/OpFactory.h"
#include "../[000]GameEngine/[001]Scene/SceneManager.h"
#include "../[001]Common/[001]Camera/OpCamera.h"


SceneOp::SceneOp() : m_factory(std::make_shared<OpFactory>())
{
	Initialize();

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetDefaultLightParameter("directional_light_parameter.bin");
}

SceneOp::~SceneOp()
{
	Finalize();
}

bool SceneOp::SeqStart(const float delta_time)
{
	SceneManager* scene = SceneManager::GetInstance();

	scene->ChangeScene(new SceneOp());

	return true;
}

void SceneOp::Initialize()
{
	// �e�I�u�W�F�N�g�̎Q�Ƃ�Factory�N���X����擾
	m_objects = m_factory->GetObjects();
	// �J�����̎擾
	m_opCamera = m_factory->GetOpCamera();

	//m_gameCamera->Initialize();

	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Initialize();
	}
}

void SceneOp::Update(const float delta_time)
{
	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Update(delta_time);
	}
}

void SceneOp::Draw(const float delta_time)
{
	DrawGridGround(m_opCamera);

	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Draw(m_opCamera);
	}

	// Fps�\��
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

void SceneOp::Finalize()
{
	m_objects.clear();

	m_factory.reset();
}