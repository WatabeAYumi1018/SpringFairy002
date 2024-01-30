#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[003]Phase/StagePhase.h"


class Mediator;


class CinemaCamera : public dxe::Camera
{

public:

	CinemaCamera();

	~CinemaCamera() {}

private:

	// 追従する対象(疑似プレイヤーを想定)
	// 各数値 : 疑似プレイヤーとの距離感
	tnl::Vector3 m_offset = { 0, 200, -200 };
	// 追従による座標補正
	tnl::Vector3 m_fix_pos = { 0,0,0 };

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);


	// カメラの動作処理

	// 待機
	bool SeqTrigger(const float delta_time);
	// アップ
	bool SeqUp(const float delta_time);
	// サイド
	bool SeqSide(const float delta_time);
	// 引き
	bool SeqBack(const float delta_time);

public:

	void update(const float delta_time) override;

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};