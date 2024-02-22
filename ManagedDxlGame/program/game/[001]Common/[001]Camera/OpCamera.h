#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// OPカメラの更新処理を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class OpCamera : public dxe::Camera
{

public:

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	OpCamera();
	~OpCamera() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// 追従する対象(疑似プレイヤーを想定)
	// 各数値 : 疑似プレイヤーとの距離感

	// カメラのオフセット
	tnl::Vector3 m_offset = { 0, 300, -100 };
	// カメラのスライドによる新しいオフセット
	tnl::Vector3 m_new_offset = { 0,0,-5000 };

	// 回転
	tnl::Quaternion m_rot;

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(OpCamera, &OpCamera::SeqNormal);

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// 線形補間関数
	// arg1 ... 開始座標
	// arg2 ... 終了座標
	// arg3 ... 補間係数
	tnl::Vector3 Lerp(const tnl::Vector3& start
			 		, const tnl::Vector3& end, float t);

	// 固定カメラ
	// arg ... オフセット座標
	void Fixed(tnl::Vector3& offset);

	// カメラ移行
	// arg ... delta_time(前フレームからの経過時間)
	void ToOffset(const float delta_time, tnl::Vector3& offset);

	// 通常
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqNormal(const float delta_time);

	// 通常からアップへ移行
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqNormalToUp(const float delta_time);

	// アップ
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqUp(const float delta_time);

	// アップから引きへ移行
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqUpToBack(const float delta_time);
	
	// 引き
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqBack(const float delta_time);

public:

	void update(const float delta_time) override;

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// メディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//
};