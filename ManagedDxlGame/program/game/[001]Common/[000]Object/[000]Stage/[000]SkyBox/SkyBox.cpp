#include "../../../[002]Mediator/Mediator.h"
#include "SkyBox.h"


SkyBox::SkyBox()
{
	LoadSkyBoxInfo();

	CreateSkyBox();
}

void SkyBox::LoadSkyBoxInfo()
{
	// csvファイルの読み込み
	m_csv_skybox_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/stage/sky/skyBox_info.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_skybox_info.size();

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		SkyBox::sSkyBoxInfo sky_info;

		sky_info.s_id = m_csv_skybox_info[y][0].getInt();

		sky_info.s_texture_path = m_csv_skybox_info[y][1].getString().c_str();

		sky_info.s_material_path = m_csv_skybox_info[y][2].getString().c_str();

		sky_info.s_screen_effect_path = m_csv_skybox_info[y][3].getString().c_str();

		m_skybox_info.emplace_back(sky_info);
	}
}

void SkyBox::CreateSkyBox()
{
	for (sSkyBoxInfo& sky_info : m_skybox_info)
	{
		m_mesh = dxe::Mesh::CreateCubeMV(60000);
		m_mesh->setTexture(dxe::Texture::CreateFromFile(sky_info.s_texture_path));
		m_mesh->loadMaterial(sky_info.s_material_path);
		m_screen_effect = std::make_shared<dxe::ScreenEffect>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
		m_screen_effect->loadStatus(sky_info.s_screen_effect_path);
		// -10000 : 座標の調整(デフォルトで{0}になっていて端っこまで到達してしまうため)
		m_mesh->pos_ = { 20000, 0, 0 };

		m_meshs.emplace_back(m_mesh);
	}
}

void SkyBox::Update(float delta_time)
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
			== StagePhase::eStagePhase::e_fancy)
		{
			m_meshs[3]->render(camera);
		}
	}
	m_screen_effect->renderEnd();
}