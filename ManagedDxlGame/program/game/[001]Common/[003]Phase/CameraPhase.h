#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"


///////////////////////////////////////////////////////////////////////////
//
// �v���C���̃J�������Ǘ�����N���X
//
///////////////////////////////////////////////////////////////////////////


class Mediator;


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

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �t�F�[�Y�J��
	void PhaseChange();
	// �V�l�}���
	bool SeqCinema(const float delta_time);
	// ���C�����
	bool SeqGame(const float delta_time);

public:

	void Update(float delta_time);

	const eCameraPhase& GetNowCameraPhase() const { return m_now_camera; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};