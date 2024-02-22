#pragma once
#include "../../Object.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �X�J�C�{�b�N�X�̒�`�ƍX�V�`�揈�����s���N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class SkyBox : public Object
{

public:

	//-------------------------------------�\����--------------------------------------//

	// �X�J�C�{�b�N�X�̏��
	struct sSkyBoxInfo
	{
		int s_id;
		std::string s_texture_path;
		std::string s_material_path;
		std::string s_screen_effect_path;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	SkyBox() {}

	~SkyBox();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// OP�݂̂̃t���O(Op�J�����ł̂ݐݒ�)
	bool m_is_op = false;

	// �X�J�C�{�b�N�X�̏��
	std::vector<sSkyBoxInfo> m_skybox_info;
	// �X�J�C�{�b�N�X�̃��b�V��
	std::vector<std::shared_ptr<dxe::Mesh>> m_meshs;
	// ���b�V���̃|�C���^
	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;
	// �X�N���[���G�t�F�N�g�̃|�C���^
	std::shared_ptr<dxe::ScreenEffect> m_screen_effect = nullptr;
	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//----------------------------------�����o�֐�----------------------------------//

	// �X�J�C�{�b�N�X�̍쐬
	void CreateSkyBox();

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �X�J�C�{�b�N�X��OP�t���O�̐ݒ�
	// arg ... OP�`��t���O
	void SetIsOp(bool is_op) { m_is_op = is_op; }

	// ���f�B�G�[�^�̐ݒ�
	// arg ... ���f�B�G�[�^�̃|�C���^
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};