#include "../[000]GameEngine/[001]Scene/SceneManager.h"
#include "../[001]Common/[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickGenerator.h"
#include "../[001]Common/[001]Camera/GameCamera.h"
#include "../[001]Common/[001]Camera/CinemaCamera.h"
#include "../[001]Common/[004]ScreenShot/ScreenShot.h"
#include "../[001]Common/[005]Factory/PlayFactory.h"
#include "../[003]ScenePlay/ScenePlay.h"
#include "../[004]SceneED/SceneED.h"
#include "ScenePlay.h"


ScenePlay::ScenePlay() : m_factory(std::make_shared<PlayFactory>())
{
	Initialize();

	//ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetDefaultLightParameter("directional_light_parameter.bin");
}

ScenePlay::~ScenePlay()
{
	Finalize();
}

bool ScenePlay::SeqStart(const float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		SceneManager* scene = SceneManager::GetInstance();

		scene->ChangeScene(new SceneEd());
	}

	return true;
}

void ScenePlay::Initialize()
{
	// 各オブジェクトの参照をFactoryクラスから取得
	m_objects_gameCamera
		= m_factory->GetObjectsGameCamera();
	m_objects_cinemaCamera_all 
		= m_factory->GetObjectsCinemaCameraAll();
	m_objects_cinemaCamera_half_right
		= m_factory->GetObjectsCinemaCameraHalf();
	m_objects_cinemaCamera_third_left
		= m_factory->GetObjectsCinemaCameraThirdLeft();
	m_objects_cinemaCamera_third_right 
		= m_factory->GetObjectsCinemaCameraThirdRight();
	 
	// カメラの取得
	m_gameCamera = m_factory->GetOpCamera();
	// シネマカメラの取得
	m_cinemaCamera_all = m_factory->GetCinemaCameraAll();
	m_cinemaCamera_half_right = m_factory->GetCinemaCameraHalfRight();
	m_cinemaCamera_third_left = m_factory->GetCinemaCameraThirdLeft();
	m_cinemaCamera_third_right = m_factory->GetCinemaCameraThirdRight();
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

	for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_all)
	{
		object->Initialize();
	}

	for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_half_right)
	{
		object->Initialize();
	}

	for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_third_left)
	{
		object->Initialize();
	}

	for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_third_right)
	{
		object->Initialize();
	}
}

void ScenePlay::Update(const float delta_time)
{
	m_sequence.update(delta_time);

	m_stagePhase->Update(delta_time);

	m_gameCamera->update(delta_time);

	m_gimmickGenerator->Update(delta_time);

	for (std::shared_ptr<Object>& object : m_objects_gameCamera)
	{
		object->Update(delta_time);
	}

	if (!m_gameCamera->GetIsActiveGame())
	{
		m_cinemaCamera_all->SetCanvas(m_cinemaCamera_all->GetAllHdl());

		//m_cinemaCamera_half_right
		//	->SetCanvas(m_cinemaCamera_half_right->GetHalfRightHdl());

		//m_cinemaCamera_third_left
		//	->SetCanvas(m_cinemaCamera_third_left->GetThirdLeftHdl());

		//m_cinemaCamera_third_right
		//	->SetCanvas(m_cinemaCamera_third_right->GetThirdRightHdl());

		m_cinemaCamera_all->update(delta_time);

		//m_cinemaCamera_half_right->update(delta_time);

		//m_cinemaCamera_third_left->update(delta_time);

		//m_cinemaCamera_third_right->update(delta_time);

		for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_all)
		{
			object->Update(delta_time);
		}

		//for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_half_right)
		//{
		//	object->Update(delta_time);
		//}

		//for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_third_left)
		//{
		//	object->Update(delta_time);
		//}

		//for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_third_right)
		//{
		//	object->Update(delta_time);
		//}
	}
}

void ScenePlay::Draw(const float delta_time)
{
	if (m_gameCamera->GetIsActiveGame())
	{
		DrawGridGround(m_gameCamera);

		for (std::shared_ptr<Object>& object : m_objects_gameCamera)
		{
			object->Draw(m_gameCamera);
		}
	}
	else
	{
		DrawGridGround(m_cinemaCamera_all);

		for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_all)
		{
			object->Draw(m_cinemaCamera_all);
		}
	
		//for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_half_right)
		//{
		//	object->Draw(m_cinemaCamera_half_right);
		//}

		//for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_third_left)
		//{
		//	object->Draw(m_cinemaCamera_third_left);
		//}

		//for (std::shared_ptr<Object>& object : m_objects_cinemaCamera_third_right)
		//{
		//	object->Draw(m_cinemaCamera_third_right);
		//}

		m_cinemaCamera_all->Render(m_cinemaCamera_all->GetAllHdl());

		//m_cinemaCamera_half_right
		//	->Render(m_cinemaCamera_half_right->GetHalfRightHdl());

		//m_cinemaCamera_third_left
		//	->Render(m_cinemaCamera_third_left->GetThirdLeftHdl());

		//m_cinemaCamera_third_right
		//	->Render(m_cinemaCamera_third_right->GetThirdRightHdl());
	}

	m_screenShot->SaveScreenShot();

	// Fps表示
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

void ScenePlay::Finalize()
{
	m_objects_gameCamera.clear();

	m_objects_cinemaCamera_all.clear();

	m_objects_cinemaCamera_half_right.clear();

	m_objects_cinemaCamera_third_left.clear();

	m_objects_cinemaCamera_third_right.clear();

	m_factory.reset();
}