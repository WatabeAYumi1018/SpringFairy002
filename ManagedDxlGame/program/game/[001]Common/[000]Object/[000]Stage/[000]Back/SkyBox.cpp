#include "../../../[002]Mediator/Mediator.h"
#include "../../../[003]Phase/StagePhase.h"
#include "SkyBox.h"


SkyBox::~SkyBox()
{
	m_skybox_info.clear();
	m_meshs.clear();
}

void SkyBox::Initialize()
{
	m_skybox_info = m_mediator->GetSkyBoxGraphInfo();

	CreateSkyBox();
}

void SkyBox::CreateSkyBox()
{
	for (sSkyBoxInfo& sky_info : m_skybox_info)
	{
		float size = 60000.0f;

		m_mesh = dxe::Mesh::CreateCubeMV(size);
		m_mesh->setTexture(dxe::Texture::CreateFromFile(sky_info.s_texture_path.c_str()));
		m_mesh->loadMaterial(sky_info.s_material_path.c_str());
		
		m_screen_effect 
			= std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

		m_screen_effect->loadStatus(sky_info.s_screen_effect_path.c_str());
		
		// 20000 : 座標の調整。あまり変えることもないため直接入力
		// デフォルトで{0}。端っこまでの到達を防ぐ
		m_mesh->pos_ = { 20000, 0, 0 };

		m_meshs.emplace_back(m_mesh);
	}
}

void SkyBox::Update(const float delta_time)
{
	m_rot *= tnl::Quaternion::RotationAxis({ 0, 0, 1 }, tnl::ToRadian(180.0f));
}

void SkyBox::Draw(std::shared_ptr<dxe::Camera> camera)
{
	m_screen_effect->renderBegin();

	if (m_is_op)
	{
		m_meshs[0]->render(camera);
	}
	else
	{
		if (m_mediator->GetNowStagePhaseState()
			== StagePhase::eStagePhase::e_flower)
		{
			m_meshs[1]->render(camera);
		}

		if (m_mediator->GetNowStagePhaseState()
			== StagePhase::eStagePhase::e_wood)
		{
			m_meshs[2]->render(camera);
		}

		if (m_mediator->GetNowStagePhaseState()
				== StagePhase::eStagePhase::e_fancy
			|| m_mediator->GetNowStagePhaseState()
				== StagePhase::eStagePhase::e_end)
		{
			m_meshs[3]->render(camera);
		}
	}

	m_screen_effect->renderEnd();
}