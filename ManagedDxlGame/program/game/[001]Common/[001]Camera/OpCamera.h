#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// OP�J�����̍X�V�������s���N���X
//
///////////////////////////////////////////////////////////////////////////


class OpCamera : public dxe::Camera
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	OpCamera();
	~OpCamera() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �Ǐ]����Ώ�(�^���v���C���[��z��)
	// �e���l : �^���v���C���[�Ƃ̋�����

	// �J�����̃I�t�Z�b�g
	tnl::Vector3 m_offset = { 0, 300, -100 };
	// �J�����̃X���C�h�ɂ��V�����I�t�Z�b�g
	tnl::Vector3 m_new_offset = { 0,0,-5000 };

	// ��]
	tnl::Quaternion m_rot;

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(OpCamera, &OpCamera::SeqNormal);

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// ���`��Ԋ֐�
	// arg1 ... �J�n���W
	// arg2 ... �I�����W
	// arg3 ... ��ԌW��
	tnl::Vector3 Lerp(const tnl::Vector3& start
			 		, const tnl::Vector3& end, float t);

	// �Œ�J����
	// arg ... �I�t�Z�b�g���W
	void Fixed(tnl::Vector3& offset);

	// �J�����ڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void ToOffset(const float delta_time, tnl::Vector3& offset);

	// �ʏ�
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqNormal(const float delta_time);

	// �ʏ킩��A�b�v�ֈڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqNormalToUp(const float delta_time);

	// �A�b�v
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqUp(const float delta_time);

	// �A�b�v��������ֈڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqUpToBack(const float delta_time);
	
	// ����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqBack(const float delta_time);

public:

	void update(const float delta_time) override;

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ���f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//
};