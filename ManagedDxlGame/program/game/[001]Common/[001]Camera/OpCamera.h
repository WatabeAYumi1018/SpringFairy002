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
	tnl::Vector3 m_offset = { 0, 300, -100 };
	tnl::Vector3 m_new_offset = { 0,0,-5000 };
	tnl::Vector3 m_stage_in_offset = { 0,0,1200 };
	// 回転
	tnl::Quaternion m_rot;

	bool m_is_mouse = false;

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;


	// コルーチンシーケンス
	TNL_CO_SEQUENCE(OpCamera, &OpCamera::SeqNormal);

	// 線形補間関数
	tnl::Vector3 Lerp(const tnl::Vector3& start
			 		, const tnl::Vector3& end, float t);

	// 固定カメラ
	void Fixed(tnl::Vector3& offset);
	// カメラ移行
	void ToOffset(const float delta_time, tnl::Vector3& offset);

	// 通常
	bool SeqNormal(const float delta_time);
	// 通常からアップへ移行
	bool SeqNormalToUp(const float delta_time);
	// アップ
	bool SeqUp(const float delta_time);
	// アップから引きへ移行
	bool SeqUpToBack(const float delta_time);
	// 引き
	bool SeqBack(const float delta_time);
	// ステージIN
	bool SeqStageIn(const float delta_time);

	void Control(const float delta_time);

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