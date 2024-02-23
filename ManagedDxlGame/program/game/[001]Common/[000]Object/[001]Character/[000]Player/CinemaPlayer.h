#pragma once
#include "../Character.h"


class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// シネマ演出時のプレイヤーの更新描画を行うクラス
// ※責任超過のため、移動に関する処理はCinemaMoveクラスを実装予定。
//
/////////////////////////////////////////////////////////////////////////////////////////


class CinemaPlayer : public Character
{

public:

	//-------------------------------------構造体--------------------------------------//

	// 演出のための細かな数値が多いため、
	// 構造体で一括管理しメディエータでの参照を簡略化
	// パラメーター名については全てを記載すると膨大になるため、
	// 今回はIDと数値で管理する。
	// ※実際の開発ではパラメーター名も記載することが推奨される。
	// それぞれの詳しい説明は、逐一csvファイル（CinemaPlayer_move）を参照
	struct sCinemaPlayerParameter
	{
		int s_id;
		float s_num;
	};

	//---------------------------------------------------------------------------------//

	CinemaPlayer();
	~CinemaPlayer();

private:

	// 円運動の経過時間
	float m_elapsed_time_circle = 0.0f;

	bool m_is_idle = false;
	bool m_is_dance = false;
	
	// プレイヤーの自己発光
	DxLib::COLOR_F m_emissive = { 0.5f,0.5f,0.5f,1 };

	// csvにて管理された各種パラメーターのベクター
	// 使用頻度の多さから変数名を簡略化
	std::vector<sCinemaPlayerParameter> m_paras;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CinemaPlayer, &CinemaPlayer::SeqTrigger);

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 線形補間関数
	float Lerp(float start, float end, float t);

	// フロントからバックへ円移動
	void MoveRoundFrontToBack(const float delta_time);
	// 回転上下移動
	void MoveRotUpDown(const float delta_time, float speed , bool up);
	// バックへ勢いよく移動
	void MoveBackCenter(const float delta_time);
	// バックからフロントへ円移動
	void MoveRoundBackToFront(const float delta_time, float radian, bool up);


	// 待機
	bool SeqTrigger(const float delta_time);
	// 紹介
	bool SeqFirst(const float delta_time);
	// エリア２への移行
	bool SeqSecond(const float delta_time);
	// エリア３への移行
	bool SeqThird(const float delta_time);


public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	bool GetIsDance() const { return m_is_dance; }


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};