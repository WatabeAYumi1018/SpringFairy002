#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../[003]Phase/StagePhase.h"
#include "../../Object.h"

class SkyBox : public Object
{

public:

	struct sSkyBoxInfo
	{
		int s_id;
		std::string s_texture_path;
		std::string s_material_path;
	};

	SkyBox();

	~SkyBox() {}

private:

	StagePhase::eStagePhase m_stage_phase = StagePhase::eStagePhase::e_flower;

	std::vector<std::vector<tnl::CsvCell>> m_csv_skybox_info;

	std::vector<sSkyBoxInfo> m_skybox_info;

	std::vector<std::shared_ptr<dxe::Mesh>> m_meshs;

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	void LoadSkyBoxInfo();
	
	void CreateSkyBox();

public:

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<GameCamera> gameCamera) override;
};