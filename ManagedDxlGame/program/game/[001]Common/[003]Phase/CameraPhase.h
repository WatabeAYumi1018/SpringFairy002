#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"


///////////////////////////////////////////////////////////////////////////
//
// プレイ中のカメラを管理するクラス
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

	// 最初はシネマカメラを再生
	eCameraPhase m_now_camera = eCameraPhase::e_cinema;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CameraPhase, &CameraPhase::SeqCinema);

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// フェーズ遷移
	void PhaseChange();
	// シネマ画面
	bool SeqCinema(const float delta_time);
	// メイン画面
	bool SeqGame(const float delta_time);

public:

	void Update(float delta_time);

	const eCameraPhase& GetNowCameraPhase() const { return m_now_camera; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};