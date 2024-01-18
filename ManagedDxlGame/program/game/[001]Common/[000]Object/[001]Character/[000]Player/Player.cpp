#include "../../../../../library/tnl_intersect.h"
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[001]Camera/GameCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Player.h"


Player::Player() 
{
	m_collision_size =  120;
	m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));
}

Player::~Player()
{
	MV1DeleteModel(m_model_hdl);
}

void Player::Initialize()
{
	StartPos();
	m_model_hdl = m_mediator->GetPlayerModelHdl();
	//m_mediator->GetPlayerMoveAutoMove();
	m_mediator->InitCollisionRegister();
}

void Player::Update(float delta_time)
{
	// スキル更新
	//m_mediator->UpdatePlayerSkill(delta_time);

	// アニメーション更新処理
	m_mediator->UpdatePlayerAnim(delta_time);

	// 行列計算の更新
	UpdateMatrix(delta_time);

	m_mediator->UpdateCollisionCheck();

	// 座標デバッグ用
	DrawStringEx(0, 0, 1, "PlayerPos_x:%f",m_pos.x);
	DrawStringEx(0, 20, 1, "PlayerPos_y:%f", m_pos.y);
	DrawStringEx(0, 40, 1, "PlayerPos_z:%f", m_pos.z);
	//// 大体7秒で2000くらい？
	//
	////// 当たり判定デバッグ用
	//VECTOR pos = wta::ConvertToVECTOR(m_pos);
	//pos.y += m_collision_size;
	//DrawSphere3D(pos, m_collision_size,32, GetColor(255, 0, 0), GetColor(255,0,0), true);
}

void Player::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	// モデル描画処理
	m_mediator->DrawPlayerModel();
}

tnl::Vector3 Player::Back()
{
	tnl::Vector3 forward = Forward();

	return -forward;
}

void Player::UpdateMatrix(float delta_time)
{
	// 移動による座標と回転の更新
	m_mediator->UpdatePlayerMoveMatrix(delta_time);

	// 回転と座標から行列を計算
	m_matrix = CalcMatrix();

	// モデルに行列を適用
	MV1SetMatrix(m_model_hdl, m_matrix);
}

tnl::Vector3 Player::Forward()
{
	// 標準的な前方向ベクトル（例えば、Z軸方向）
	tnl::Vector3 init_forward(0, 0, -1);

	// m_rot の共役を計算
	tnl::Quaternion rot_conjugate(-m_rot.x, -m_rot.y, -m_rot.z, m_rot.w);

	// 現在の回転に基づいて前方向ベクトルを計算
	tnl::Quaternion rot_forward_vec 
		= m_rot * tnl::Quaternion(init_forward.x, init_forward.y, init_forward.z, 0) * rot_conjugate;

	// 回転後の前方向ベクトルを返す
	return tnl::Vector3(rot_forward_vec.x, rot_forward_vec.y, rot_forward_vec.z);
}