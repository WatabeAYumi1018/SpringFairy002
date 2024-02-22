#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// �V�l�}�J�����̍X�V�������s���N���X
// �������𑼂̃N���X���l�����������ꍇ�A�Q�Ɠn�������G�ɂȂ舵���ɂ����Ȃ邽��
// �@�����1�N���X�ɂ܂Ƃ߂Ă���
//
///////////////////////////////////////////////////////////////////////////


class CinemaCamera : public dxe::Camera
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	CinemaCamera();
	~CinemaCamera() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �X�N���[���n���h��
	int m_screen_hdl = 0;

	// �V�l�}�J�����̊������t���O
	bool m_is_active = true;

	// �e���l : �^���v���C���[�Ƃ̋�����
	tnl::Vector3 m_offset = { 0, 0, -400 };
	// �Ǐ]�ɂ����W�␳
	tnl::Vector3 m_fix_pos = { 0,0,0 };

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// ���`��Ԋ֐�
	// arg1 ... �J�n���W
	// arg2 ... �I�����W
	// arg3 ... ��ԌW��
	tnl::Vector3 Lerp(const tnl::Vector3& start
					, const tnl::Vector3& end, float t);

	// �Œ�
	// arg ... �I�t�Z�b�g���W
	void Fixed(const tnl::Vector3& offset);

	// �X���C�h����
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �I�t�Z�b�g���W
	// arg3 ... �ړ����x
	void ToSlide(const float delta_time, const tnl::Vector3& offset, float speed);

	//-------

	// �ҋ@
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqTrigger(const float delta_time);

	// �Љ�
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFirst(const float delta_time);

	// �G���A�Q�ւ̈ڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqSecond(const float delta_time);

	// �G���A�R�ւ̈ڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqThird(const float delta_time);

public:

	void update(const float delta_time) override;

	// �L�����o�X�̐ݒ�
	// tips ... ScenePlay�N���X�ɂčX�V����
	// �@�@�@�@ �O�̕`����������A�V���ȕ`����s������
	void SetCanvas();

	// �`�悳�ꂽ�I�u�W�F�N�g�𗠉�ʂɕ`�悷�鏈��
	// tips ... ScenePlay�N���X�ɂčX�V����(�X�̃I�u�W�F�N�g���`��I�������A���t���[�����s)
	void Render();

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//


	// �X�N���[���n���h�����擾
	int GetAllHdl() const { return m_screen_hdl; }

	// �V�l�}�J�����̊������t���O��ݒ�
	void SetIsActive(bool is_active) { m_is_active = is_active; }

	// �V�l�}�J�����̊������t���O���擾
	bool GetIsActive() const { return m_is_active; }

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//

};



