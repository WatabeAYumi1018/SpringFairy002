#pragma once
#include "../../../library/tnl_sequence.h"

// フェーズ管理クラス
// ゲームの進行状況を管理する

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

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CameraPhase, &CameraPhase::SeqCinema);


	// メイン画面
	bool SeqGame(const float delta_time);
	// シネマ画面
	bool SeqCinema(const float delta_time);

public:

	void Update(float delta_time);
};