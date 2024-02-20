#pragma once
#include "../../../[003]Phase/StagePhase.h"
#include "../../Object.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �X�J�C�{�b�N�X�̍X�V�`�揈���N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class SkyBox : public Object
{

public:

	//-------------------------------------�\����--------------------------------------//

	struct sSkyBoxInfo
	{
		int s_id;
		std::string s_texture_path;
		std::string s_material_path;
		std::string s_screen_effect_path;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	SkyBox();

	~SkyBox() {}

	//---------------------------------------------------------------------------------//

private:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	// OP�݂̂̃t���O(Op�J�����ł̂ݐݒ�)
	bool m_is_op = false;

	std::vector<std::vector<tnl::CsvCell>> m_csv_skybox_info;

	std::vector<sSkyBoxInfo> m_skybox_info;

	std::vector<std::shared_ptr<dxe::Mesh>> m_meshs;

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<dxe::ScreenEffect> m_screen_effect = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//----------------------------------�����o�֐�----------------------------------//

	void LoadSkyBoxInfo();

	void CreateSkyBox();

public:

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	void SetIsOp(bool is_op) { m_is_op = is_op; }


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};