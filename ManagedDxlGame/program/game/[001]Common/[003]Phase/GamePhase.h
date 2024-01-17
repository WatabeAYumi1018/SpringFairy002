#pragma once
#include "../../../library/tnl_sequence.h"

// フェーズ管理クラス
// ゲームの進行状況を管理する

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

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(GamePhase, &GamePhase::SeqStory);


	// ストーリー画面
	bool SeqStory(const float delta_time);
	// プレイ画面
	bool SeqPlay(const float delta_time);

public:

	void Update(float delta_time);
};