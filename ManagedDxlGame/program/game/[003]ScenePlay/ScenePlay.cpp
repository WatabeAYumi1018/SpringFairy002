#include "../[000]GameEngine/[001]Scene/SceneManager.h"
#include "../[001]Common/[000]Object/[002]Gimmick/[000]GimmickFunction/GimmickGenerator.h"
#include "../[001]Common/[001]Camera/GameCamera.h"
#include "../[001]Common/[001]Camera/CinemaCamera.h"
#include "../[001]Common/[003]Phase/CameraPhase.h"
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
	m_objects_cinemaCamera 
		= m_factory->GetObjectsCinemaCamera();
	// カメラの取得
	m_gameCamera = m_factory->GetOpCamera();
	// シネマカメラの取得
	m_cinemaCamera = m_factory->GetCinemaCamera();
	// カメラフェーズの取得
	m_cameraPhase = m_factory->GetCameraPhase();
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
	m_sequence.update(delta_time);

	m_cameraPhase->Update(delta_time);

	m_stagePhase->Update(delta_time);

	m_gimmickGenerator->Update(delta_time);

	m_gameCamera->update(delta_time);

	for (std::shared_ptr<Object>& object : m_objects_gameCamera)
	{
		object->Update(delta_time);
	}

	if (m_cameraPhase->GetNowCameraPhase()
		== CameraPhase::eCameraPhase::e_cinema)
	{
		m_cinemaCamera->SetCanvas();

		m_cinemaCamera->update(delta_time);

		for (std::shared_ptr<Object>& object : m_objects_cinemaCamera)
		{
			object->Update(delta_time);
		}
	}
}

void ScenePlay::Draw(const float delta_time)
{
	if (m_cameraPhase->GetNowCameraPhase()
		== CameraPhase::eCameraPhase::e_game)
	{
		//DrawGridGround(m_gameCamera);

		for (std::shared_ptr<Object>& object : m_objects_gameCamera)
		{
			object->Draw(m_gameCamera);
		}
	}
	else
	{
		//DrawGridGround(m_cinemaCamera);

		for (std::shared_ptr<Object>& object : m_objects_cinemaCamera)
		{
			object->Draw(m_cinemaCamera);
		}
	
		m_cinemaCamera->Render();
	}

	m_screenShot->SaveScreenShot();

	// Fps表示
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}

void ScenePlay::Finalize()
{
	m_objects_gameCamera.clear();

	m_objects_cinemaCamera.clear();

	m_factory.reset();
}