#pragma once
#include "../Character.h"


class Mediator;


class Butterfly : public Character
{
	
public:

	//-------------------------------------構造体--------------------------------------//

	// 演出のための細かな数値が多いため、
	// 構造体で一括管理しメディエータでの参照を簡略化
	// パラメーター名については全てを記載すると膨大になるため、
	// 今回はIDと数値で管理する。
	// ※実際の開発ではパラメーター名も記載することが推奨される。
	// それぞれの詳しい説明は、逐一csvファイル（butterfly_move）を参照
	struct sButterflyParameter
	{
		int s_id;
		float s_num;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Butterfly();
	~Butterfly();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// moveアニメーションのインデックス
	int m_anim_index = 0;
	
	// moveアニメーション経過時間
	float m_elapsed_time = 0.0f;
	// moveアニメーションのループ時間
	float m_time_count= 0.0f;

	// 円運動の経過時間
	float m_elapsed_time_circle = 0.0f;
	// シネマ3で回転開始するまでのプレイヤーとの距離
	float m_to_player_distance = 100.0f;

	// オープニング描画フラグ
	bool m_is_op_active = false;
	// シネマ描画フラグ
	bool m_is_cinema_active = false;
	// 消滅フラグ
	bool m_is_clear = false;

	// 進行方向
	tnl::Vector3 m_next_direction;

	// csvにて管理された各種パラメーターのベクター
	// 使用頻度の多さから変数名を簡略化
	std::vector<sButterflyParameter> m_paras;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Butterfly, &Butterfly::SeqMove);

	// メッシュのポインタ
	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;
	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// アニメーションの更新処理
	// arg ... delta_time(前フレームからの経過時間)
	void AnimMove(const float delta_time);

	// ｚ軸方向の移動（奥へ進行）
	// arg ... delta_time(前フレームからの経過時間)
	void MoveStraightHeight(const float delta_time);

	// ｘ軸方向の移動（右へ進行）
	// arg ... delta_time(前フレームからの経過時間)
	void MoveStraightWidth(const float delta_time);

	// 円運動の移動処理
	// arg ... delta_time(前フレームからの経過時間)
	void MoveRound(const float delta_time);

	// 真っすぐな移動
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqMove(const float delta_time);

	// 円運動
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqRound(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// オープニング描画フラグの設定
	void SetIsOpActive(bool is_op_active) { m_is_op_active = is_op_active; }

	// シネマ描画フラグの設定
	void SetIsCinemaActive(bool is_cinema_active)
	{
		m_is_cinema_active = is_cinema_active; 
	}

	// 次の進行方向の取得
	const tnl::Vector3& GetNextDirection() const { return m_next_direction; }

	// 消滅フラグの取得
	bool GetIsClear() const { return m_is_clear; }

	// シネマ描画フラグの取得
	bool GetIsCinemaActive() const { return m_is_cinema_active; }

	// メディエータの設定
	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}

	//---------------------------------------------------------------------------------//
};