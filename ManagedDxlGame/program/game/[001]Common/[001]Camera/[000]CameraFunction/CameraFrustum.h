//#pragma once
//#include "../../../../wta_library/wta_Collision.h"
//#include "../dxlib_ext/dxlib_ext.h"
//
//class Mediator;
//
////class Player;
////class Camera;
//
//
//class CameraFrustum
//{
//
//public:
//
//	// フラスタムカリングのパラメータ
//	struct sFrustumParam
//	{
//		// 平面の法線ベクトル
//		// 3D空間内の各平面に垂直なベクトル
//		// フラスタムカリングでは、カメラのビューフラスタムを構成する各平面に対して、
//		// その平面に垂直な方向を指すベクトルを計算
//		// s_normal : 該当するフラスタム平面に垂直な方向を示す3次元ベクトル
//		tnl::Vector3 s_normal;
//		// 平面方程式の定数項
//		// 原点から平面までの距離を示す値
//		float s_d;
//	};
//
//
//	CameraFrustum() {}
//	
//	~CameraFrustum() {}
//
//private:
//
//	int m_frustum_plane_num = 4;
//
//	tnl::Vector3 m_pos;
//
//	tnl::Matrix m_view;
//
//	tnl::Matrix m_proj;
//
//	// フラスタムの4平面のパラメータ
//	sFrustumParam m_frustum_param[4];
//
//
//	//std::shared_ptr<Player> m_player = nullptr;
//
//	//std::shared_ptr<GameCamera> m_gameCamera = nullptr;
//
//	//std::shared_ptr<wta::Collision<Player, GameCamera>> m_collision = nullptr;
//
//	std::shared_ptr<Mediator> m_mediator = nullptr;
//
//
//	// 境界平面の更新
//	void UpdateFrustumPlane();
//	// フラスタムカリングの境界内判定
//	bool IsInFrustum(const tnl::Vector3& pos);
//	// プレイヤーの座標をフラスタム内に戻す
//	void ReturnPlayerPos(const tnl::Vector3& player_pos);
//
//	//// フラスタムカリングのコーナー計算
//	//std::vector<tnl::Vector3> CalculateFrustumCorners(const tnl::Matrix& invViewProj);
//	//// フラスタムカリングの6平面描画
//	//void DrawFrustumPlane();
//
//	//// フラスタムカリングの6平面のパラメータを取得
//	//sFrustumParam GetFrustumParam(int index)
//	//{
//	//	return m_frustum_param[index];
//	//}
//
//	//void DrawFrustumPlane(const tnl::Vector3& normal, float d) ;
//
//public:
//
//	void Update();
//
//	//// 当たり判定処理の登録
//	//void CollisionRegister();
//	//// キャラとの当たり判定
//	//void CollisionCheck();
//
//	// フラスタムカリングの6平面のパラメータを取得
//	sFrustumParam GetFrustumParam(int index)
//	{
//		return m_frustum_param[index];
//	}
//
//	//void SetGameCamera(std::shared_ptr<GameCamera> gameCamera)
//	//{
//	//	m_gameCamera = gameCamera;
//	//}
//
//	//void SetPlayer(std::shared_ptr<Player> player)
//	//{
//	//	m_player = player;
//	//}
//
//	//void SetCollision(std::shared_ptr<wta::Collision<Player, GameCamera>> collision)
//	//{
//	//	m_collision = collision;
//	//}
//
//	// プレイヤーのメディエーターを設定	
//	void SetMediator(std::shared_ptr<Mediator>& mediator)
//	{
//		m_mediator = mediator;
//	}
//};