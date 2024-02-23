#pragma once
#include "../Object.h"


class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// OP�Q�[�g�C���X�g�̒�`�ƍX�V�`�揈�����s���N���X
//
///////////////////////////////////////////////////////////////////////////


class Gate : public Object
{

public:

	//-------------------------------------�\����--------------------------------------//

	struct sGateInfo
	{
		int s_id;
		std::string s_texture_path;
		tnl::Vector3 s_pos;
		tnl::Vector3 s_scale;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	Gate() {}
	~Gate();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �Q�[�g�̓����J�n�t���O
	bool m_is_active = false;
	// �Q�[�g���J�����t���O
	bool m_is_opend = false;

	// ��ނ��Ƃ̃Q�[�g�f�[�^�̃x�N�^�[
	std::vector<sGateInfo> m_gates_info;

	// �Q�[�g���b�V���̃x�N�^�[
	std::vector<std::shared_ptr<dxe::Mesh>> m_meshes;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Gate, &Gate::SeqTrigger);

	// ���b�V���̃|�C���^
	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ���b�V���̐���
	void CreateMesh();

	// �g���K�[����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqTrigger(const float delta_time);

	// �C���X�g�̕ύX����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqStay(const float delta_time);

	// �Q�[�g�I�[�v������
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqOpen(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ���f�B�G�[�^�̐ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};
