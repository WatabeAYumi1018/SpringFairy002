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

	Player();

	~Player() {}


	//----------------------------------------//

private:

	// ���b�V��
	std::vector<std::shared_ptr<dxe::Mesh>> m_meshs;

	// �s��̍X�V����
	void UpdateMatrix(float delta_time);
	// ���b�V���̍X�V����
	void UpdateMesh(float delta_time);

public:

	// �O�����̎Z�o
	tnl::Vector3 Forward();

	// ������
	void Initialize() override;
	// �X�V
	void Update(float delta_time) override;
	// �`�揈��
	void Draw(std::shared_ptr<dxe::Camera> camera) override;
	
	// ���b�V���̎擾
	const std::vector<std::shared_ptr<dxe::Mesh>>& GetMeshs() const
	{
		return m_meshs;
	}
};