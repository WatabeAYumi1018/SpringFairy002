#pragma once
#include "../Character.h"



class GameCameraTarget : public Character
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	GameCameraTarget(){}
	~GameCameraTarget() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	GameCamera::sCameraInfo m_camera_info;

	Lane::sLaneEvent m_event;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GameCameraTarget, &GameCameraTarget::SeqNormal);

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �����ړ��ɂ��X�V����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void MoveMatrix(const float delta_time);

	// �ʏ�̈ړ�����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqNormal(const float delta_time);

	// ��~����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqStop(const float delta_time);

public:

	void Initialize() override;
	
	void Update(const float delta_time) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �J�������̎擾
	const GameCamera::sCameraInfo& GetCameraInfo() const { return m_camera_info; }

	// �C�x���g���̎擾
	const Lane::sLaneEvent& GetCurrentEvent() const { return m_event; }

	//---------------------------------------------------------------------------------//
};
