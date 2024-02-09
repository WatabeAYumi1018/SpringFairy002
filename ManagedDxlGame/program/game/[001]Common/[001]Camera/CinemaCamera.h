#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"


class Mediator;


class CinemaCamera : public dxe::Camera
{

public:

	CinemaCamera();

	~CinemaCamera() {}

private:

	// スクリーンハンドル
	int m_screen_hdl = 0;

	bool m_move_mouse = false;
	// シネマカメラの活性化フラグ
	bool m_is_active = true;

	// 各数値 : 疑似プレイヤーとの距離感
	tnl::Vector3 m_offset = { 0, 0, -400 };
	// 追従による座標補正
	tnl::Vector3 m_fix_pos = { 0,0,0 };

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);

	// 線形補間関数
	tnl::Vector3 Lerp(const tnl::Vector3& start
					, const tnl::Vector3& end, float t);

	// 固定
	void Fixed(const tnl::Vector3& offset);
	// スライド処理
	void ToSlide(const float delta_time, const tnl::Vector3& offset, float speed);

	//-------

	// 待機
	bool SeqTrigger(const float delta_time);
	// 紹介
	bool SeqFirst(const float delta_time);
	// エリア２への移行
	bool SeqSecond(const float delta_time);
	// エリア３への移行
	bool SeqThird(const float delta_time);

	//-----デバッグ用-----//

	//マウスの回転動作制御
	void Control(const float delta_time);

	// 周辺を360度回転制御
	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
									, const tnl::Vector3& pivot
									, const tnl::Vector3& axis
									, float angle);

public:

	void SetCanvas();

	void update(const float delta_time) override;

	void Render();

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
};



//class CinemaCamera : public dxe::Camera
//{
//
//public:
//
//	//enum class eCameraSplitType
//	//{
//	//	e_all,
//	//	e_half_right,
//	//	e_third_left,
//	//	e_third_right
//	//};
//
//	// 全画面シネマカメラにするデフォルトコンストラクタ
//	CinemaCamera();
//	//// 状況に応じた画面分割をするコンストラクタ
//	//CinemaCamera(int width, int height, eCameraSplitType type);
//
//	~CinemaCamera() {}
//
//private:
//
//	// スクリーンハンドル
//	int m_all_hdl = 0;
//	//int m_half_right = 0;
//	//int m_third_left = 0;
//	//int m_third_right = 0;
//
//	//// 分割の幅
//	//int m_split_width_left = 0;
//	//int m_split_width_right = 0;
//
//	//// 最初の分割比率
//	//float split_rate = 1.0f / 3.0f;
//
//	bool m_move_mouse = false;
//
//	//bool m_is_half_right_active = false;
//	//bool m_is_third_left_active = false;
//	//bool m_is_third_right_active = false;
//
//	// 追従する対象(疑似プレイヤーを想定)
//	// 各数値 : 疑似プレイヤーとの距離感
//	tnl::Vector3 m_offset = { 0, 0, -400 };
//	// 追従による座標補正
//	tnl::Vector3 m_fix_pos = { 0,0,0 };
//
//	//eCameraSplitType m_type = eCameraSplitType::e_all;
//
//	// メディエーターのポインタ
//	std::shared_ptr<Mediator> m_mediator = nullptr;
//
//	// コルーチンシーケンス
//	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);
//
//	//// 画面作成
//	//void CreateScreen();
//	//// 分割の更新
//	//void UpdateSplit(const float delta_time);
//
//	// 線形補間関数
//	tnl::Vector3 Lerp(const tnl::Vector3& start
//		, const tnl::Vector3& end, float t);
//
//	// 固定
//	void Fixed(const tnl::Vector3& offset);
//	// スライド処理
//	void ToSlide(const float delta_time, const tnl::Vector3& offset, float speed);
//
//	//-------
//
//	// 待機
//	bool SeqTrigger(const float delta_time);
//	// 紹介
//	bool SeqFirst(const float delta_time);
//	// エリア２への移行
//	bool SeqSecond(const float delta_time);
//	// エリア３への移行
//	bool SeqThird(const float delta_time);
//
//	//-----デバッグ用-----//
//
//	//マウスの回転動作制御
//	void Control(const float delta_time);
//
//	// 周辺を360度回転制御
//	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
//		, const tnl::Vector3& pivot
//		, const tnl::Vector3& axis
//		, float angle);
//
//public:
//
//	void SetCanvas();
//
//	//void SetCanvas(int screen_hdl);
//
//	void update(const float delta_time) override;
//
//	void Render();
//
//	//void Render(int screen_hdl);
//
//	// スクリーンハンドルを取得
//	int GetAllHdl() const { return m_all_hdl; }
//
//	//int GetHalfRightHdl() const { return m_half_right; }
//	//
//	//int GetThirdRightHdl() const { return m_third_right; }
//	//
//	//int GetThirdLeftHdl() const { return m_third_left; }
//
//	//float GetSplitWidthLeft() const { return m_split_width_left; }
//
//	//float GetSplitWidthRight() const { return m_split_width_right; }
//
//	//bool GetIsHalfRightActive() const { return m_is_half_right_active; }
//
//	//bool GetIsThirdLeftActive() const { return m_is_third_left_active; }
//
//	//bool GetIsThirdRightActive() const { return m_is_third_right_active; }
//
//	//eCameraSplitType GetActiveType() const { return m_type; }
//
//	// プレイヤーのメディエーターを設定	
//	void SetMediator(std::shared_ptr<Mediator>& mediator)
//	{
//		m_mediator = mediator;
//	}
//};