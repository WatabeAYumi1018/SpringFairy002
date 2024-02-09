#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"


class CameraPhase
{

public:

	enum class eCameraPhase
	{
		e_cinema,
		e_game
	};

private:

	// �ŏ��̓V�l�}�J�������Đ�
	eCameraPhase m_now_camera = eCameraPhase::e_cinema;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CameraPhase, &CameraPhase::SeqCinema);


	// �V�l�}���
	bool SeqCinema(const float delta_time);
	// ���C�����
	bool SeqGame(const float delta_time);

public:

	void Update(float delta_time);

	void SetNowCameraPhase(eCameraPhase& camera)
	{
		m_now_camera = camera;
	}

	const eCameraPhase& GetNowCameraPhase() const { return m_now_camera; }
};