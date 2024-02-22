#pragma once
#include "../Character.h"


///////////////////////////////////////////////////////////////////////////
//
// �v���C���[�̍X�V�`����s���N���X
//
///////////////////////////////////////////////////////////////////////////


class Player : public Character
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Player();
	~Player();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���b�V���̐�����
	int m_mesh_create_num = 20;

	// ���b�V���|�C���^�̃x�N�^�[
	std::vector<std::shared_ptr<dxe::Mesh>> m_meshs;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �s��̍X�V����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void UpdateMatrix(const float delta_time);

	// ���b�V���̍X�V����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void UpdateMesh(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;
	
	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	// �O�����̃x�N�g���Z�o
	tnl::Vector3 Forward();

	//---------------------------------------------------------------------------------//

	
	//----------------------------------Setter&Getter----------------------------------//

	// ���b�V���|�C���^�̃x�N�^�[�擾
	// tips ... �����蔻��ȂǂŎg�p
	const std::vector<std::shared_ptr<dxe::Mesh>>& GetMeshs() const
	{
		return m_meshs;
	}

	//---------------------------------------------------------------------------------//
};