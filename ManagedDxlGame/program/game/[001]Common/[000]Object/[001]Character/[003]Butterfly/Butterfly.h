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

private:

	//-----------------------------------メンバ変数------------------------------------//

	// moveアニメーションのインデックス
	int m_anim_index = 0;

	float m_speed = 100.0f;

	// moveアニメーションの速度
	float m_anim_speed = 100.0f;
	
	float m_elapsed_time_circle = 0.0f;
	
	// moveアニメーション経過時間
	float m_elapsed_time = 0.0f;
	// moveアニメーションのループ時間
	float m_time_count= 0.0f;
	
	// シネマ3で回転するまでのプレイヤーとの距離
	float m_to_player_distance = 100.0f;

	 //進行方向
	tnl::Vector3 m_next_direction;

	// オープニング描画フラグ
	bool m_is_op_active = false;
	// 消滅フラグ
	bool m_is_clear = false;
	// シネマ描画フラグ
	bool m_is_cinema_active = false;

	// csvにて管理された各種パラメーターのベクター
	// 使用頻度の多さから変数名を簡略化
	std::vector<sButterflyParameter> m_paras;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Butterfly, &Butterfly::SeqMove);

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;


	void AnimMove(const float delta_time);

	void MoveStraightHeight(const float delta_time);

	void MoveStraightWidth(const float delta_time);

	void MoveRound(const float delta_time);

	bool SeqMove(const float delta_time);

	bool SeqRound(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetIsOpActive(bool is_op_active) { m_is_op_active = is_op_active; }

	void SetIsCinemaActive(bool is_cinema_active)
	{
		m_is_cinema_active = is_cinema_active; 
	}

	const tnl::Vector3& GetNextDirection() const 
	{
		return m_next_direction; 
	}

	bool GetIsClear() const { return m_is_clear; }

	bool GetIsCinemaActive() const { return m_is_cinema_active; }

	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}
};