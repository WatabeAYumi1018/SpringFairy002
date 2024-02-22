#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../Character.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// パートナーの移動処理に関するクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class PartnerMove
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	PartnerMove() {}
	~PartnerMove() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// 経過時間
	float m_elapsed_time = 0;
	// 移動時間
	float m_move_time = 0.0f;
	// 前回の移動時間
	float m_last_move_time = 0.0f;

	// 初期周波数
	float m_orbit_frequency = 0.2f; 

	// 押し出しフラグ
	bool m_is_pushed = false;

	// 現在座標
	tnl::Vector3 m_pos;
	// 移動座標オフセット
	tnl::Vector3 m_offset;

	// 現在回転
	tnl::Quaternion m_rot;
	// 目標回転
	tnl::Quaternion m_target_rot;

	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//

	
	//-----------------------------------メンバ関数------------------------------------//

	// 座標のランダム更新処理（殆どはプレイヤー同様の自動移動＋少量の独自の移動を持つ）
	// arg ... delta_time(前フレームからの経過時間)
	void UpdateRandomPos(const float delta_time);

	// プレイヤーとの衝突による補正処理
	// arg ... delta_time(前フレームからの経過時間)
	void CorrectPos(const float delta_time);

public:

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 座標補正フラグの設定
	void SetIsPushed(bool is_pushed) { m_is_pushed = is_pushed ; }

	// メディエータのポインタの設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};