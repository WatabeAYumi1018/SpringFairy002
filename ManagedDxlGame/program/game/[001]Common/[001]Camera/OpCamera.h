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
	tnl::Vector3 m_offset = { 0, 300, -300 };
	tnl::Vector3 m_new_offset = { 0,300,-300 };
	// 回転
	tnl::Quaternion m_rot;

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

public:

	void update(const float delta_time) override;

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};