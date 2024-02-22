#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../../../[000]Stage/[001]Lane/Lane.h"
#include "../../Character.h"

class Mediator;

/////////////////////////////////////////////////////////////////////////////////////////
// 
// プレイヤーの移動処理のクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class PlayerMove
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	PlayerMove() {}
	~PlayerMove() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// 上下による移動速度
	float m_move_high_and_low_speed = 10.0f;
	// 傾ける角度
	float m_rot_angle = 0.05f;
	// サイド時の傾き具合
	float m_side_rot_rate = 10.0f;

	// 宙返りの経過時間
	float m_salto_elapsed_time = 0;

	// ロールの回転速度
	float m_rolling_rotation = 10;
	// 八の字の回転速度
	float m_figure_eight_rotation = 10;

	// モデルの座標（Playerクラスのm_posと同期）
	tnl::Vector3 m_pos;

	// ターゲット計算で一時的に使用
	tnl::Quaternion m_target_rot;
	//モデルの回転（Playerクラスのm_rotと同期）
	tnl::Quaternion m_rot;

	// プレイヤーの方向
	Character::eDirection m_direction 
		= Character::eDirection::e_none;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(PlayerMove, &PlayerMove::SeqNormal);

	// A*のポインタ
	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// 移動によるモデルの行列変換
	// arg ... delta_time(前フレームからの経過時間)
	void MoveMatrix(const float delta_time);

	// 操作によるモデル回転定義
	// arg ... delta_time(前フレームからの経過時間)
	void ControlMoveMatrix(const float delta_time);

	// 宙返りアクションでのモデル回転定義
	// arg ... delta_time(前フレームからの経過時間)
	void SaltoActionMatrix(const float delta_time);

	// 通常の移動処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqNormal(const float delta_time);
	
	// 停止処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqStop(const float delta_time);
	
	// 上昇処理
	// arg ... delta_time(前フレームからの経過時間)
	// ※今後の拡張で使用する可能性があるため残しています。実装は完了済み。
	bool SeqUpMove(const float delta_time);
	
	// 下降処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqDownMove(const float delta_time);

	// 宙返りアクション
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqSaltoAction(const float delta_time);

public:

	// ボタン操作定義とフラグ関数
	bool PushButton();

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// A*のポインタを設定
	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>>& astar)
	{
		m_astar = astar;
	}

	// メディエータのポインタを設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};