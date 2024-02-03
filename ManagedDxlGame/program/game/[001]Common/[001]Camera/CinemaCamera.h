#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"


class Mediator;


class CinemaCamera : public dxe::Camera
{

public:

	// 全画面シネマカメラにするデフォルトコンストラクタ
	CinemaCamera();
	// 状況に応じた画面分割をするコンストラクタ
	CinemaCamera(int width, int height);

	~CinemaCamera() {}

private:

	// スクリーンハンドル
	int m_all_hdl = 0;
	int m_half_right = 0;
	int m_third_left = 0;
	int m_third_right = 0;

	int m_split_width_left = 0;
	int m_split_width_right = 0;

	// 最初の分割比率
	float split_rate = 1.0f / 3.0f;

	// カメラの状態
	bool m_is_active = false;

	bool m_move_mouse = false;

	// イベント終了フラグ
	bool m_is_completed = false;

	// 追従する対象(疑似プレイヤーを想定)
	// 各数値 : 疑似プレイヤーとの距離感
	tnl::Vector3 m_offset = { 0, 400, -400 };
	// 追従による座標補正
	tnl::Vector3 m_fix_pos = { 0,0,0 };

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);

	// 画面作成
	void CreateScreen();
	// 分割のアニメーション
	void SplitAnimation(const float delta_time);


	// 待機
	bool SeqTrigger(const float delta_time);
	// アップ
	bool SeqUp(const float delta_time);
	// サイド
	bool SeqSide(const float delta_time);
	// 引き
	bool SeqBack(const float delta_time);

	//-----デバッグ用-----//

	//マウスの回転動作制御
	void Control(const float delta_time);

	// 周辺を360度回転制御
	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
		, const tnl::Vector3& pivot
		, const tnl::Vector3& axis
		, float angle);

public:

	void update(const float delta_time) override;

	void Render(int x1,int y1,int x2,int y2,int screen_hdl);

	// スクリーンハンドルを取得
	int GetAllHdl() const { return m_all_hdl; }

	int GetHalfRightHdl() const { return m_half_right; }
	
	int GetThirdRightHdl() const { return m_third_right; }
	
	int GetThirdLeftHdl() const { return m_third_left; }

	void SetIsActive(bool is_active) { m_is_active = is_active; }

	bool GetIsActive() const{ return m_is_active; }

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};