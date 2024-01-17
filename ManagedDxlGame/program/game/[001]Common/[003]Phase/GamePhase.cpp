#include "../dxlib_ext/dxlib_ext.h"
#include "GamePhase.h"


void GamePhase::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

// �X�g�[���[���
bool GamePhase::SeqStory(const float delta_time)
{
	// �Đ����I��������
	//if ()
	//{
	//	tnl_sequence_.change(&GamePhase::SeqPlay);
	//}

	// �Đ����I������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		m_now_game_phase = eGamePhase::e_story;
	});

	TNL_SEQ_CO_END;
}

// �v���C���
bool GamePhase::SeqPlay(const float delta_time)
{
	// �v���C�������I��������
	//if ()
	//{
	//	tnl_sequence_.change(&GamePhase::SeqStory);
	//}

	// �~�b�V������S�ďI����܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		m_now_game_phase = eGamePhase::e_play;
	});

	TNL_SEQ_CO_END;

}