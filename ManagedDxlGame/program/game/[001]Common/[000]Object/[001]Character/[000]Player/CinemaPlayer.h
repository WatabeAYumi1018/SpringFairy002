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
	// それぞれの詳しい説明は、逐一csvファイル（cinemaPlayer_move）を参照
	struct sCinemaPlayerParameter
	{
		int s_id;
		float s_num;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ--------------------------//

	CinemaPlayer();
	~CinemaPlayer();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// 円運動の経過時間
	float m_elapsed_time_circle = 0.0f;

	// idleフラグ
	bool m_is_idle = false;
	// danceフラグ
	bool m_is_dance = false;
	
	// プレイヤーの自己発光初期値
	DxLib::COLOR_F m_emissive = { 0.5f,0.5f,0.5f,1 };

	// csvにて管理された各種パラメーターのベクター
	// 使用頻度の多さから変数名を簡略化
	std::vector<sCinemaPlayerParameter> m_paras;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CinemaPlayer, &CinemaPlayer::SeqTrigger);

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// 線形補間関数
	// arg1 ... 開始値
	// arg2 ... 終了値
	// arg3 ... 補間係数
	float Lerp(float start, float end, float t);

	// フロントからバックへ円移動
	// arg ... delta_time(前フレームからの経過時間)
	void MoveRoundFrontToBack(const float delta_time);
	
	// 回転上下移動
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... 移動速度
	// arg3 ... 上移動か下移動か（デフォルトで上）
	void MoveRotUpDown(const float delta_time, float speed , bool up = true);
	
	// バックへ勢いよく移動
	// arg ... delta_time(前フレームからの経過時間)
	void MoveBackCenter(const float delta_time);
	
	// バックからフロントへ円移動
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... 半径
	// arg3 ... 上移動か下移動か(デフォルトで上)
	void MoveRoundBackToFront(const float delta_time, float radian, bool up = true);

	// 待機
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqTrigger(const float delta_time);

	// 紹介
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFirst(const float delta_time);

	// エリア２への移行
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqSecond(const float delta_time);

	// エリア３への移行
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqThird(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ダンスフラグの取得
	bool GetIsDance() const { return m_is_dance; }

	//---------------------------------------------------------------------------------//
};