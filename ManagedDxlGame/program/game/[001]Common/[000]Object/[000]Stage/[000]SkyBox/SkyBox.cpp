#include "SkyBox.h"
#include "../../../[001]Camera/GameCamera.h"

SkyBox::SkyBox()
{
	LoadSkyBoxInfo();

	CreateSkyBox();
}

void SkyBox::LoadSkyBoxInfo()
{
	// csvファイルの読み込み
	m_csv_skybox_info
		= tnl::LoadCsv<tnl::CsvCell>("csv/stage/sky/skyBox_Info.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_skybox_info.size();

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		sSkyBoxInfo sky_info;

		sky_info.s_id = m_csv_skybox_info[y][0].getInt();

		sky_info.s_texture_path = m_csv_skybox_info[y][1].getString();

		sky_info.s_material_path = m_csv_skybox_info[y][2].getString();

		m_skybox_info.emplace_back(sky_info);
	}
}

void SkyBox::CreateSkyBox()
{
	for (sSkyBoxInfo& sky_info : m_skybox_info)
	{
		m_mesh = dxe::Mesh::CreateCubeMV(50000, 40, 40);
		m_mesh->setTexture(dxe::Texture::CreateFromFile(sky_info.s_texture_path));
		m_mesh->loadMaterial(sky_info.s_material_path);

		m_meshs.emplace_back(m_mesh);
	}
}

void SkyBox::Update(float delta_time)
{
	m_rot *= tnl::Quaternion::RotationAxis({ 0, 0, 1 }, tnl::ToRadian(180.0f));
}

void SkyBox::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	if (m_stage_phase == StagePhase::eStagePhase::flower) 
	{
		m_meshs[0]->render(gameCamera);
	}

	if (m_stage_phase == StagePhase::eStagePhase::wood)
	{
		m_meshs[1]->render(gameCamera);
	}

	if (m_stage_phase == StagePhase::eStagePhase::fancy)
	{
		m_meshs[2]->render(gameCamera);
	}
}