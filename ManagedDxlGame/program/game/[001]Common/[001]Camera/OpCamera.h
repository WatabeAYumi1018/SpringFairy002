#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;


class OpCamera : public dxe::Camera
{

public:

	OpCamera();

	~OpCamera() {}

private:

	// 追従する対象(疑似プレイヤーを想定)
	// 各数値 : 疑似プレイヤーとの距離感
	tnl::Vector3 m_offset = { 0, 400, -400 };
	// 追従による座標補正
	tnl::Vector3 m_fix_pos = { 0,0,0 };

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;



	//-----デバッグ用-----//

	//マウスの回転動作制御
	void Control(const float delta_time);

	// 周辺を360度回転制御
	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
		, const tnl::Vector3& pivot
		, const tnl::Vector3& axis
		, float angle);

public:

	void update(const float delta_time) override;

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};