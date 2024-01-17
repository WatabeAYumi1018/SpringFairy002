#include "../dxlib_ext/dxlib_ext.h"
#include "GamePhase.h"


void GamePhase::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

// ストーリー画面
bool GamePhase::SeqStory(const float delta_time)
{
	// 再生が終了したら
	//if ()
	//{
	//	tnl_sequence_.change(&GamePhase::SeqPlay);
	//}

	// 再生が終了するまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		m_now_game_phase = eGamePhase::e_story;
	});

	TNL_SEQ_CO_END;
}

// プレイ画面
bool GamePhase::SeqPlay(const float delta_time)
{
	// プレイ処理が終了したら
	//if ()
	//{
	//	tnl_sequence_.change(&GamePhase::SeqStory);
	//}

	// ミッションを全て終えるまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		m_now_game_phase = eGamePhase::e_play;
	});

	TNL_SEQ_CO_END;

}