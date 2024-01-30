#pragma once
#include "../Character.h"



class CameraTargetPlayer : public Character
{

public:

	CameraTargetPlayer(){}

	~CameraTargetPlayer() {}

	//----------------------------------------//

private:

	GameCamera::sCameraInfo m_camera_info;

	Lane::sLaneEvent m_event;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CameraTargetPlayer, &CameraTargetPlayer::SeqTrigger);

	void MoveMatrix(const float delta_time);

	// �ʏ�̈ړ�����
	bool SeqTrigger(const float delta_time);
	// ��~����
	bool SeqStop(const float delta_time);
	// �㏸����
	bool SeqUpMove(const float delta_time);
	// ���~����
	bool SeqDownMove(const float delta_time);

public:

	// ������
	void Initialize() override;
	// �X�V
	void Update(float delta_time) override;
	// �`�揈��
	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	const GameCamera::sCameraInfo& GetCameraInfo() const
	{
		return m_camera_info; 
	}

	const Lane::sLaneEvent& GetEvent() const
	{
		return m_event;
	}
};
