#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// ゲームカメラの更新処理を行うクラス
// ※処理を他のクラス同様分割化した場合、参照渡しが複雑になり扱いにくくなるため
// 　今回は1クラスにまとめている
//
///////////////////////////////////////////////////////////////////////////



class GameCamera : public dxe::Camera
{

public:

	//-----------------------------------enum class------------------------------------//

	// カメラの種類
	enum class eCameraType
	{
		// 固定された視点
		e_fixed,
		// サイドビュー(キャラクターを右側から見る)
		e_right_side,
		// サイドビュー(キャラクターを左側から見る)
		e_left_side,
		// サイドビュー(キャラクターは後ろから)
		e_right_side_back,
		// サイドビュー(キャラクターは後ろから)
		e_left_side_back,
		// 正面からの視点
		e_front,
		// 上からの視点
		e_bottom,
		// プレイヤー周りの回転
		e_rotate,
		// プレイヤー追従(必要であれば)
		e_follow,
		// カメラ独自の操作(デバッグ用)
		e_control,
		// アクセス不可
		e_none
	};

	//--------------------------------------------------------------------------------//


	//-------------------------------------構造体--------------------------------------//

	// カメラレーン情報
	struct sCamera
	{
		int s_id;
		tnl::Vector3 s_pos;
	};

	// カメラ情報
	struct sCameraInfo
	{
		int s_id;
		eCameraType s_type;
	};

	//--------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ---------------------------//

	GameCamera();
	~GameCamera() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// 回転角度
	float m_rot_angle = 0.0f;
	// 軌道半径
	float m_orbit_radius = 400.0f;
	// 軌道高さ
	float m_orbit_height = 500.0f;
	// スライド時の速度(基本値)
	float m_slide_speed = 2.0f;
	// スライド時の速度(変動値)
	// ※スライドスタート時は少しゆったりさせたいため大きめに設定
	float m_slide_start_speed = 5.0f;

	// 固定フラグ
	bool m_is_fixed = false;

	// 追従する対象(疑似プレイヤーを想定)
	// 各数値 : 疑似プレイヤーとの距離感
	// 通常のカメラ固定時のオフセット
	tnl::Vector3 m_fix_offset = { 0, 0, -400 };
	
	// 右サイドビュー時のオフセット
	tnl::Vector3 m_right_side_offset = { 400, 0, 0 };

	// 左サイドビュー時のオフセット
	tnl::Vector3 m_left_side_offset = { -400, 0, 0 };

	// 正面からの視点時のオフセット
	tnl::Vector3 m_front_offset = { 0, 0, 400 };

	// 自動経路による回転
	tnl::Quaternion m_rot;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(GameCamera, &GameCamera::SeqFixed);

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// 線形補間関数
	// arg1 ... 開始座標
	// arg2 ... 終了座標
	// arg3 ... 補間係数
	tnl::Vector3 Lerp(const tnl::Vector3& start
					  , const tnl::Vector3& end, float t);

	// カメラの状態を取得
	void ConditionType();

	// 固定
	// arg ... オフセット座標
	void Fixed(const tnl::Vector3& offset);
	
	// スライド処理
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... オフセット座標
	// arg3 ... 移動速度
	void ToSlide(const float delta_time, const tnl::Vector3& offset, float speed);
	
	// 360度回転処理
	// arg ... delta_time(前フレームからの経過時間)
	void Rotate(const float delta_time);

	// 固定された視点
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFixed(const float delta_time);

	// 右サイドビュー
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqRightSide(const float delta_time);

	// 右サイドからfixへ移行
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqRightSideToFix(const float delta_time);

	//	左サイドビュー
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqLeftSide(const float delta_time);

	// 左サイドからfixへ移行
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqLeftSideToFix(const float delta_time);

	// 正面からの視点
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFront(const float delta_time);

	// 正面からfixへ移行
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFrontToFix(const float delta_time);

	// プレイヤー周りの回転
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqRotate(const float delta_time);

	// プレイヤー周りの回転からfixへ移行
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqRotateToFix(const float delta_time);


	//-----デバッグ用-----//

	//マウスの回転動作制御
	// arg ... delta_time(前フレームからの経過時間)
	void Control(const float delta_time);

	// 周辺を360度回転制御
	// arg1 ... 回転座標
	// arg2 ... 点座標
	// arg3 ... 回転軸
	// arg4 ... 回転角度
	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
									, const tnl::Vector3& pivot
									, const tnl::Vector3& axis
									, float angle);

	// プレイヤー追従
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFollow(const float delta_time);

	// プレイヤー操作
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqControl(const float delta_time);

	//--------------------//

public:

	void update(const float delta_time) override;

	// フラスタムとの当たり判定
	void IsInFlustum();

	// ターゲットの概念を無くした姿勢処理
	inline tnl::Vector3 up()
	{
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_rot);
		return up_;
	}

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 固定カメラかどうか取得
	bool GetIsFixed() const { return m_is_fixed; }

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//
};