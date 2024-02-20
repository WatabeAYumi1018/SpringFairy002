#include "../[000]GameEngine/[000]Scene/SceneManager.h"
#include "../[000]GameEngine/[001]Music/MusicManager.h"
#include "../[001]Common/[001]Camera/OpCamera.h"
#include "../[001]Common/[005]Factory/OpFactory.h"
#include "../[003]ScenePlay/ScenePlay.h"
#include "SceneOp.h"


SceneOp::SceneOp() : m_factory(std::make_shared<OpFactory>())
{
	Initialize();

	//ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetDefaultLightParameter("directional_light002.bin");
}

SceneOp::~SceneOp()
{
	Finalize();
}

bool SceneOp::SeqStart(const float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
		//(m_opCamera->GetPos().z >= 1400)
	{
		MusicManager::GetInstance().PlaySE(0);
	
		SceneManager* scene = SceneManager::GetInstance();

		scene->ChangeScene(new ScenePlay());
	}

	return true;
}

void SceneOp::Initialize()
{
	// 各オブジェクトの参照をFactoryクラスから取得
	m_objects = m_factory->GetObjects();
	// カメラの取得
	m_opCamera = m_factory->GetGameCamera();

	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Initialize();
	}
}

void SceneOp::Update(const float delta_time)
{
	m_sequence.update(delta_time);

	MusicManager::GetInstance().PlayBGM(delta_time, 0);

	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Update(delta_time);
	}

	m_opCamera->update(delta_time);
}


void SceneOp::Draw(const float delta_time)
{
	DrawGridGround(m_opCamera);

	for (std::shared_ptr<Object>& object : m_objects)
	{
		object->Draw(m_opCamera);
	}
}

void SceneOp::Finalize()
{
	MusicManager::GetInstance().StopBGM(0);

	m_objects.clear();

	m_factory.reset();
}