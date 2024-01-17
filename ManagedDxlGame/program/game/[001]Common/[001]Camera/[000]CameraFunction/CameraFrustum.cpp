//#include "../../[002]Mediator/Mediator.h"
//#include "CameraFrustum.h"
//
//
//
//void CameraFrustum::Update()
//{
//	m_pos = m_mediator->GetCameraPos();
//
//	m_view = m_mediator->GetCameraView();
//
//	m_proj = m_mediator->GetCameraProj();
//
//	UpdateFrustumPlane();
//
//	ReturnPlayerPos(m_mediator->GetPlayerPos());
//
//	// 座標デバッグ用
//	DrawStringEx(1000, 500, -1, "CameraFrustumPos_x:%f", m_pos.x);
//	DrawStringEx(1000, 520, -1, "CameraFrustumPos_y:%f", m_pos.y);
//	DrawStringEx(1000, 540, -1, "CameraFrustumPos_z:%f", m_pos.z);
//}
//
//// フラスタムの各平面の法線ベクトルを計算し、
//// 定数項でその平面の位置を特定することにより、フラスタムの境界を定義
//void CameraFrustum::UpdateFrustumPlane()
//{
//	// ビュー行列と射影行列を合成
//	// オブジェクトの世界座標系から2D画面空間への直接的な変換
//	tnl::Matrix view_proj = m_view * m_proj ;
//
//	// ☆行列の乗算 : 座標変換（回転、拡大縮小、平行移動）
//	// ☆行列の加算 : 座標変換の合成（複数の座標変換を一度に行い、新しいベクトル生成）
//
//	// 左平面
//	// 左平面の法線ベクトル(平面に対する垂直ベクトル)を算出
//	// view_proj._11 ～ view_proj._31 : 合成行列の1行目（カメラ空間における右方向ベクトル）
//	// view_proj._12 ～ view_proj._32 : 合成行列の2行目（カメラ空間における上方向ベクトル）
//	// view_proj._13 ～ view_proj._33 : 合成行列の3行目（カメラ空間における前方向ベクトル）
//	// view_proj._14 ～ view_proj._34 : 合成行列の4行目（カメラ空間の原点からの変換ベクトル）
//	// 加算することで左平面の法線ベクトルを算出（フラスタムの左平面と他の部分との境界）
//
//	float d = view_proj._44 + view_proj._14;
//	float a = ( view_proj._41 + view_proj._11 ) ;
//	float b = ( view_proj._42 + view_proj._12 ) ;
//	float c = ( view_proj._43 + view_proj._13 ) ;
//
//	m_frustum_param[0].s_normal = tnl::Vector3(view_proj._41 + view_proj._11,
//												view_proj._42 + view_proj._12,
//												view_proj._43 + view_proj._13);
//
//	//m_frustum_param[0].s_normal = m_mediator->GetCameraRight();
//
//	// フラスタム平面左平面の方程式における定数項を算出
//	// 方程式 : Ax+By+Cz+D=0 (A,B,C : 法線ベクトルの成分 ・　D : 定数項)
//	// 結果が 0 より大きい場合: 点は平面の一方の側（通常は「内側」）
//	// 結果が 0 より小さい場合: 点は平面の他方の側（通常は「外側」）
//	// 結果が 0 の場合: 点は平面上
//	// _44 : Z軸に沿った深度（奥行き）の情報をスケール
//	// _41 : X軸に沿った横幅の位置情報をスケール
//	// 加算することで左平面が3D空間内でどのように位置するかを特定（カメラから見てどれだけ左側か）
//	m_frustum_param[0].s_d = view_proj._44 + view_proj._14;
//
//	// 右平面
//	m_frustum_param[1].s_normal = tnl::Vector3(view_proj._41 - view_proj._11,
//												view_proj._42 - view_proj._12,
//												view_proj._43 - view_proj._13);
//
////	m_frustum_param[1].s_normal = m_mediator->GetCameraLeft();
//
//	m_frustum_param[1].s_d = view_proj._44 - view_proj._14;
//
//	//// 上平面
//	m_frustum_param[2].s_normal = tnl::Vector3(view_proj._41 - view_proj._21,
//												view_proj._42 - view_proj._22,
//												view_proj._43 - view_proj._23);
//
//	//m_frustum_param[1].s_normal = m_mediator->GetCameraBack();
//
//
//	m_frustum_param[2].s_d = view_proj._44 - view_proj._24;
//
//	//// 下平面
//	m_frustum_param[3].s_normal = tnl::Vector3(view_proj._41 + view_proj._21,
//												view_proj._42 + view_proj._22,
//												view_proj._43 + view_proj._23);
//
////	m_frustum_param[3].s_normal = m_mediator->GetCameraForward();
//
//	m_frustum_param[3].s_d = view_proj._44 + view_proj._24;
//
//	// 各平面の法線ベクトルを正規化
//	// 法線ベクトルの長さが一定（通常は1）であることを保証することで、
//	// フラスタムの平面とオブジェクトとの距離計算が一貫したものになる
//	// 点と平面との距離は、点の位置ベクトルと法線ベクトルの内積
//	// そして定数項を加算するだけで算出できる
//	for (int i = 0; i < m_frustum_plane_num; i++)
//	{
//		m_frustum_param[i].s_normal.normalize();
//	}
//}
//
//bool CameraFrustum::IsInFrustum(const tnl::Vector3& pos)
//{
//	for (int i = 0; i < m_frustum_plane_num; i++)
//	{
//		// 内積を計算し、定数項を加算
//		// 点と平面との距離を算出
//		// 点と平面との距離が0より小さい場合、点は平面の外側にある
//		float dot = tnl::Vector3::Dot(m_frustum_param[i].s_normal, pos);
//
//		dot += m_frustum_param[i].s_d;
//
//		if (dot < 0)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//void CameraFrustum::ReturnPlayerPos(const tnl::Vector3& player_pos)
//{
//	// フラスタム境界外にプレイヤーの座標が移動した場合
//	if (!IsInFrustum(player_pos))
//	{
//		DrawStringEx(1000, 700, -1, "外側");
//
//		// フラスタムの各面とプレイヤーの距離を格納する配列
//		float distance[4];
//
//		int min_index = -1;
//
//		float min_distance = 1e38f;
//
//		// フラスタムの各面とプレイヤーの距離を計算
//		for (int i = 0; i < m_frustum_plane_num; i++)
//		{
//			distance[i] = tnl::Vector3::Dot(m_frustum_param[i].s_normal, player_pos)
//				+ m_frustum_param[i].s_d;
//
//			// 距離が正であり、最も小さいものを見つける
//			if (distance[i] > 0 && distance[i] < min_distance) 
//			{
//				min_distance = distance[i];
//				min_index = i;
//			}
//		}
//		//// 一番近いフラスタムの面にプレイヤーを戻す
//		//  // フラスタムの境界に最も近い平面を見つける
//		//int min_index
//		//	= std::min_element(distance, distance + m_frustum_plane_num) - distance;
//
//		if (min_index != -1)
//		{
//			tnl::Vector3 return_pos 
//				= player_pos - m_frustum_param[min_index].s_normal * min_distance;
//			m_mediator->SetPlayerPos(return_pos);
//		}
//	}
//}
//
//
////// 近平面
////// 近平面はカメラの法線ベクトルは前方向ベクトルと平行
////m_frustum_param[4].s_normal = tnl::Vector3(view_proj._13,
////	view_proj._23,
////	view_proj._33);
////m_frustum_param[4].s_d = view_proj._44 + view_proj._43;
//
////// 遠平面
////m_frustum_param[5].s_normal = tnl::Vector3(view_proj._14 - view_proj._13,
////	view_proj._24 - view_proj._23,
////	view_proj._34 - view_proj._33);
////m_frustum_param[5].s_d = view_proj._44 - view_proj._43;
//
////void CameraFrustum::CollisionRegister()
////{
////	std::string key
////		= typeid(Player).name() + std::string(typeid(GameCamera).name());
////
////	m_collision->registerIntersect( key
////									, [this](std::shared_ptr<Player> player
////									, std::shared_ptr<GameCamera> gameCamera)
////	{
////		for (int i = 0; i < m_frustum_plane_num; ++i)
////		{
////			// フラスタムの面を取得
////			sFrustumParam frustum_plane = m_frustum_param[i];
////			// フラスタムの半分のサイズを取得
////			float frustum_half_size_height = gameCamera->screen_h_ / 2;
////			float frustum_half_size_width = gameCamera->screen_w_ / 2;
////
////			if (m_collision->IsIntersectSphereAABB( player, player->GetCollisionSize()
////													, gameCamera, frustum_half_size_width
////													, frustum_half_size_height,0))
////			{
////
////				DrawStringEx(1000, 500, -1, "外側");
////			}
////		}
////	});
////}
////
////void CameraFrustum::CollisionCheck()
////{
////	m_collision->Intersect(m_player,m_gameCamera);
////
////	// 座標デバッグ用
////	DrawStringEx(0, 100, -1, "CameraFrustum_x:%f", pos_.x);
////	DrawStringEx(0, 120, -1, "CameraFrustum_y:%f", pos_.y);
////	DrawStringEx(0, 140, -1, "CameraFrustum_z:%f", pos_.z);
////}
//
////// 球体の中心座標と半径を定義
////Vector3 sphereCenter = // 球体の中心座標
////float sphereRadius = // 球体の半径
////
////// 各フラスタム面に対して距離を計算し、当たり判定をチェック
////for (int i = 0; i < NUM_FRUSTUM_PLANES; i++) {
////	float distance = abs(Vector3::Dot(frustumPlanes[i].normal, sphereCenter) + frustumPlanes[i].d);
////	if (distance < sphereRadius) {
////		// 当たり判定が発生
////		Vector3 correction = frustumPlanes[i].normal * (sphereRadius - distance);
////		sphereCenter += correction;
////		// 補正後の座標を使用
////	}
////}