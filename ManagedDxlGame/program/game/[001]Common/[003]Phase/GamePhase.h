#pragma once
#include "../../../library/tnl_sequence.h"

// �t�F�[�Y�Ǘ��N���X
// �Q�[���̐i�s�󋵂��Ǘ�����

class CameraPhase
{

public:

	enum class eCameraState
	{
		e_game,
		e_cinema
	};

private:

	eCameraState m_now_state = eCameraState::e_cinema;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CameraPhase, &CameraPhase::SeqCinema);


	// ���C�����
	bool SeqGame(const float delta_time);
	// �V�l�}���
	bool SeqCinema(const float delta_time);

public:

	void Update(float delta_time);
};