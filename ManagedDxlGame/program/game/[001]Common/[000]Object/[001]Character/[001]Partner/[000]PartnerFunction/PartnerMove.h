#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../[000]GameEngine/[000]Engine/Engine.h"


class Mediator;

// Moverクラス（プレイヤー、エネミーなど移動に関する処理を行う）

class PartnerMove
{

private:

	// めり込む時間
	const float SINK_DURATION = 0.5f;
	// めり込み具合
	const float SINK_VALUE = 10;
	// 弾かれる時間
	const float PUSH_DURATION = 1;
	// 弾かれる具合
	const float PUSH_VALUE = 8;

	// 経過時間
	float m_elapsed_time = 0;

	// 乱数
	int m_random = -1;

	// 移動時間
	float m_move_time = 0.0f;
	// 前回の移動時間
	float m_last_move_time = 0.0f;
	// 初期周波数
	float m_orbit_frequency = 0.2f; 

	// 回転時間
	float m_rotation_time = 0.0f;
	// 前回の回転時間
	float m_last_rotation_time = 0.0f;

	// 現在座標
	tnl::Vector3 m_pos;
	// 移動座標オフセット
	tnl::Vector3 m_offset;
	// 衝突時の中点
	tnl::Vector3 m_center;
	// 衝突時の逆ベクトル（正規化）
	tnl::Vector3 m_reverse;

	// 現在回転
	tnl::Quaternion m_rot;
	// 目標回転
	tnl::Quaternion m_target_rot;

	// 移動完了フラグ
	bool m_is_moved = false;

	// 衝突フラグ
	bool m_is_pushed = false;

	//// 上下左右の方向
	//eDirection direction = eDirection::none;

	//// コルーチンシーケンス
	//TNL_CO_SEQUENCE(PartnerMove, &PartnerMove::SeqNormal);

	// プレイヤーメディエータのスマートポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//// コルーチンシーケンス
	//TNL_CO_SEQUENCE(PartnerMove, &PartnerMove::SeqPartnerIn);


	//// ランダムな行先計算処理
	//void CalcRandomPos(const tnl::Vector3& player_pos);

	void UpdatePos(const float delta_time);

	void UpdateRot(const float delta_time);

	void CorrectPos(const float delta_time);
	//void ApplyForce();
	//// パートナーが若干のめり込み処理
	//bool SeqPartnerIn(const float delta_time);
	////// めり込み中の処理
	////bool SeqPartnerStay(const float delta_time);
	//// 離れる処理
	//bool SeqPartnerOut(const float delta_time);

	//// 基盤の移動処理
	//bool SeqNormal(const float delta_time);
	//// ターゲット座標計算処理
	//bool SeqTargetCalc(const float delta_time);
	//// 形式的な移動処理
	//bool SeqMove(const float delta_time);
	//// 不規則な落下処理
	//bool SeqFall(const float delta_time);
	//// 不規則な逆移動処理
	//bool SeqInverse(const float delta_time);

public:

	void Update(float delta_time);


	void SetIsPushed(bool is_pushed) { m_is_pushed = is_pushed ; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};