#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../library/tnl_sequence.h"


class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// プレイ中のカメラを管理するクラス
//
///////////////////////////////////////////////////////////////////////////


class CameraPhase
{

public:

	//-----------------------------------enum class------------------------------------//

	// カメラのフェーズ
	enum class eCameraPhase
	{
		e_cinema,
		e_game
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ---------------------------//

	CameraPhase() {}
	~CameraPhase() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// 最初はシネマカメラを再生
	eCameraPhase m_now_camera = eCameraPhase::e_cinema;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CameraPhase, &CameraPhase::SeqCinema);

	// コルーチンシーケンス
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// フェーズ遷移
	void PhaseChange();

	// シネマ画面
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqCinema(const float delta_time);
	
	// メイン画面
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqGame(const float delta_time);

public:

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 現在のカメラフェーズを取得
	const eCameraPhase& GetNowCameraPhase() const { return m_now_camera; }

	// メディエーターを設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};