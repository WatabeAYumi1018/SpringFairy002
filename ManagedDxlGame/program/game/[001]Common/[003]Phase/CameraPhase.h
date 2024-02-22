#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"


class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// �v���C���̃J�������Ǘ�����N���X
//
///////////////////////////////////////////////////////////////////////////


class CameraPhase
{

public:

	//-----------------------------------enum class------------------------------------//

	// �J�����̃t�F�[�Y
	enum class eCameraPhase
	{
		e_cinema,
		e_game
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	CameraPhase() {}
	~CameraPhase() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �ŏ��̓V�l�}�J�������Đ�
	eCameraPhase m_now_camera = eCameraPhase::e_cinema;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CameraPhase, &CameraPhase::SeqCinema);

	// �R���[�`���V�[�P���X
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �t�F�[�Y�J��
	void PhaseChange();

	// �V�l�}���
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqCinema(const float delta_time);
	
	// ���C�����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqGame(const float delta_time);

public:

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ���݂̃J�����t�F�[�Y���擾
	const eCameraPhase& GetNowCameraPhase() const { return m_now_camera; }

	// ���f�B�G�[�^�[��ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};