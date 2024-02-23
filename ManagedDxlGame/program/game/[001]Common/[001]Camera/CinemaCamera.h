#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// シネマカメラの更新処理を行うクラス
// シネマ演出はプランナーさんも適宜調整する事が多いため、csvにて管理。
// 
// ※処理を他のクラス同様分割化した場合、参照渡しが複雑になり扱いにくくなるため
// 　今回は1クラスにまとめている。
// 
// ※csv読み取りにて、objectでない本クラスの初期化で
// 　他クラスとの参照をするとなると、ScenePlayの処理が見にくくなるため、
// 　今回は本クラスにてcsv読み取りを行っている。
//
///////////////////////////////////////////////////////////////////////////


class CinemaCamera : public dxe::Camera
{

public:

	//-------------------------------------構造体--------------------------------------//

	// 演出のための細かな数値が多いため、
	// 構造体で一括管理しメディエータでの参照を簡略化
	// パラメーター名については全てを記載すると膨大になるため、
	// 今回はIDと数値で管理する。
	// ※実際の開発ではパラメーター名も記載することが推奨される。
	// それぞれの詳しい説明は、逐一csvファイル（cinemaPlayer_move）を参照
	struct sCinemaCameraParameter
	{
		int s_id;
		float s_num;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ---------------------------//

	CinemaCamera();
	~CinemaCamera();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// スクリーンハンドル
	int m_screen_hdl = 0;

	// シネマカメラの活性化フラグ
	bool m_is_active = true;

	// 各数値 : 疑似プレイヤーとの距離感
	tnl::Vector3 m_offset = { 0, 0, -400 };

	// 追従による座標補正
	tnl::Vector3 m_fix_pos = { 0,0,0 };

	// シネマカメラのパラメーター読み取り専用(csvファイル)
	std::vector<std::vector<tnl::CsvCell>> m_csv_parameters;

	// csvにて管理された各種パラメーターのベクター
	// 使用頻度の多さから変数名を簡略化
	std::vector<sCinemaCameraParameter> m_paras;

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// パラメーターの読み込み
	// tips ... 初期化時に一度だけ実行
	void LoadParameter();

	// 線形補間関数
	// arg1 ... 開始座標
	// arg2 ... 終了座標
	// arg3 ... 補間係数
	tnl::Vector3 Lerp(const tnl::Vector3& start
					, const tnl::Vector3& end, float t);

	// 固定
	// arg ... オフセット座標
	void Fixed(const tnl::Vector3& offset);

	// スライド処理
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... オフセット座標
	// arg3 ... 移動速度
	void ToSlide(const float delta_time, const tnl::Vector3& offset, float speed);

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

	void update(const float delta_time) override;

	// キャンバスの設定
	// tips ... ScenePlayクラスにて更新処理
	// 　　　　 前の描画を消去し、新たな描画を行う処理
	void SetCanvas();

	// 描画されたオブジェクトを裏画面に描画する処理
	// tips ... ScenePlayクラスにて更新処理(個々のオブジェクトが描画終えた時、毎フレーム実行)
	void Render();

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// スクリーンハンドルを取得
	int GetAllHdl() const { return m_screen_hdl; }

	// シネマカメラの活性化フラグを設定
	void SetIsActive(bool is_active) { m_is_active = is_active; }

	// シネマカメラの活性化フラグを取得
	bool GetIsActive() const { return m_is_active; }

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//
};