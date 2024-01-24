#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"


class Mediator;


class GameCamera : public dxe::Camera
{

public:

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

	struct sCamera
	{
		int s_id;
		tnl::Vector3 s_pos;
	};

	struct sCameraInfo
	{
		int s_id;
		eCameraType s_type;
	};

	GameCamera();

	~GameCamera() {}

private:

	// 回転角度
	float m_rot_angle = 0.0f;

	// 追従する対象(疑似プレイヤーを想定)
	// 各数値 : 疑似プレイヤーとの距離感
	tnl::Vector3 m_offset = { 0, 200, -400 };
	// 追従による座標補正
	tnl::Vector3 m_fix_pos = { 0,0,0 };
	// 自動経路による回転
	tnl::Quaternion m_rot;


	StagePhase::eStagePhase m_now_stage_phase = StagePhase::eStagePhase::e_fly;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(GameCamera, &GameCamera::SeqFixed);

	// メディエーターのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;


	//// 足元のカメラレーンを取得
	//sCamera CurrentCamera();

	//// 足元のカメラ情報を取得
	//sCameraInfo CurrentCameraType();

	// フラスタムとの当たり判定
	void IsInFlustum();
	// 線形補間関数
	tnl::Vector3 Lerp(const tnl::Vector3& start
					  , const tnl::Vector3& end, float t);
	// カメラの状態を取得
	void ConditionType();


	// カメラの固定処理
	void Fixed();
	// カメラのサイドビュー処理
	void Side(float offset);
	// カメラのサイドビューへ移行処理
	void ToSide(const float delta_time,float offset);
	// サイドから固定へ移行
	void ToFix(const float delta_time);
	// カメラの正面からの視点処理
	void Front();
	// 360度回転処理
	void rotate(const float delta_time);

	// 固定された視点
	bool SeqFixed(const float delta_time);
	// 右サイドビュー
	bool SeqRightSide(const float delta_time);
	// 右サイドからfixへ移行
	bool SeqRightSideToFix(const float delta_time);
	//	左サイドビュー
	bool SeqLeftSide(const float delta_time);
	// 左サイドからfixへ移行
	bool SeqLeftSideToFix(const float delta_time);
	// 正面からの視点
	bool SeqFront(const float delta_time);
	// 正面からfixへ移行
	bool SeqFrontToFix(const float delta_time);
	// プレイヤー周りの回転
	bool SeqRotate(const float delta_time);
	// プレイヤー周りの回転からfixへ移行
	bool SeqRotateToFix(const float delta_time);


	// 上からの視点処理
	void Bottom();
	// 下の視点
	bool SeqBottom(const float delta_time);
	// 下からfixへ移行
	bool SeqBottomToFix(const float delta_time);

	//-----デバッグ用-----//

	//マウスの回転動作制御
	void Control(const float delta_time);

	// 周辺を360度回転制御
	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
									, const tnl::Vector3& pivot
									, const tnl::Vector3& axis
									, float angle);

	// プレイヤー追従
	bool SeqFollow(const float delta_time);

	// プレイヤー操作
	bool SeqControl(const float delta_time);

	//--------------------//

	

public:

	void update(const float delta_time) override;

	//// ターゲットの概念を無くした姿勢処理
	inline tnl::Vector3 up()
	{
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_rot);
		return up_;
	}
	inline tnl::Vector3 down() { return -up(); }

	//inline tnl::Vector3 forward() override
	//{
	//	target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rot);
	//	return tnl::Vector3::Normalize(target_ - pos_);
	//}

	//inline tnl::Vector3 back() override { return -forward(); }

	//inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }

	//inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }

	// プレイヤーのメディエーターを設定	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};


//// フラスタムカリングのパラメータ
//struct sFrustumParam
//{
//	// 平面の法線ベクトル
//	// 3D空間内の各平面に垂直なベクトル
//	// フラスタムカリングでは、カメラのビューフラスタムを構成する各平面に対して、
//	// その平面に垂直な方向を指すベクトルを計算
//	// s_normal : 該当するフラスタム平面に垂直な方向を示す3次元ベクトル
//	tnl::Vector3 s_normal;
//	// 平面方程式の定数項
//	// 原点から平面までの距離を示す値
//	float s_d;
//};

//int m_frustum_plane_num = 4;


//// フラスタムカリングの6平面のパラメータ
//sFrustumParam m_frustum_param[6];

//// 次の目標位置を取得
//void GetPlayerAutoPathInfo( const float delta_time
//							,tnl::Vector3& pos
//							, tnl::Quaternion& rot);
//// プレイヤーの後ろから同じ方向を向く
//void RotateBackToPlayer(float delta_time);

//// 境界平面の更新
//void UpdateFrustumPlane();
//// フラスタムカリングの境界内判定
//bool IsInFrustum(const tnl::Vector3& pos);
//// プレイヤーの座標をフラスタム内に戻す
//void ReturnPlayerPos(const tnl::Vector3& pos);

////// フラスタムカリングのコーナー計算
////std::vector<tnl::Vector3> CalculateFrustumCorners(const tnl::Matrix& invViewProj);
////// フラスタムカリングの6平面描画
////void DrawFrustumPlane();

////// フラスタムカリングの6平面のパラメータを取得
////sFrustumParam GetFrustumParam(int index)
////{
////	return m_frustum_param[index];
////}

//void DrawFrustumPlane(const tnl::Vector3& normal, float d) ;
