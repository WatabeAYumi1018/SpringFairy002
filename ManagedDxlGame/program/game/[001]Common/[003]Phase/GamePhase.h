#pragma once
#include "../../../library/tnl_sequence.h"

// �t�F�[�Y�Ǘ��N���X
// �Q�[���̐i�s�󋵂��Ǘ�����

class GamePhase
{

public:

	enum class eGamePhase
	{
		e_story,
		e_play
	};

private:

	eGamePhase m_now_game_phase = eGamePhase::e_story;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GamePhase, &GamePhase::SeqStory);


	// �X�g�[���[���
	bool SeqStory(const float delta_time);
	// �v���C���
	bool SeqPlay(const float delta_time);

public:

	void Update(float delta_time);
};