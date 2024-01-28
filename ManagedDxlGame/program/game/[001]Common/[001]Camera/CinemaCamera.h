#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"


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

	// カメラの固定処理
	void Fixed();

public:

	void update(const float delta_time) override;

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};