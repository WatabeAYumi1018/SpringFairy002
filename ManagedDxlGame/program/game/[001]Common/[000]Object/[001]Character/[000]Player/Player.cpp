#include "../../../../../library/tnl_intersect.h"
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[001]Camera/GameCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Player.h"


Player::Player() 
{
	m_collision_size =  100;

	for (int i = 0; i < 15; ++i)
	{
		std::shared_ptr<dxe::Mesh> mesh
				= dxe::Mesh::CreateSphereMV(70);

		m_meshs.emplace_back(mesh);
	}
}

void Player::Initialize()
{
	StartPos();

	m_mediator->InitializePlayerDraw();

	m_model_hdl = m_mediator->GetPlayerModelGameHdl();

	SetLight(m_model_hdl);

	m_mediator->InitCollisionRegister();
}

void Player::Update(float delta_time)
{
	// アニメーション更新処理
	m_mediator->UpdatePlayerAnim(delta_time);

	// 行列計算の更新
	UpdateMatrix(delta_time);

	UpdateMesh(delta_time);

	m_mediator->UpdateCollisionCheck();

	m_mediator->IsInCameraFlustum();
}

void Player::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// モデル描画処理
	m_mediator->DrawPlayerModel();

	if (m_mediator->GetNowStagePhaseState()
		== StagePhase::eStagePhase::e_wood)
	{
		DxLib::COLOR_F emissive = { 0.7f,0.7f,0.7f,1 };
		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	}
	else if (m_mediator->GetNowStagePhaseState()
			== StagePhase::eStagePhase::e_fancy)
	{
		DxLib::COLOR_F emissive = { 0.9f,0.9f,0.9f,1 };
		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	}
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

void Player::UpdateMesh(float delta_time)
{
	tnl::Vector3 forward = Forward();

	float distance = 100.0f;

	for (int i = 0; i < m_meshs.size(); ++i)
	{
		std::shared_ptr<dxe::Mesh>& mesh = m_meshs[i];

		// メッシュの位置を設定（プレイヤーの位置に前方向ベクトルを加算）
		mesh->pos_ = m_pos + forward * distance;

		// Y軸におけるオフセット（必要に応じて設定）
		mesh->pos_.y += 150;

		// 次のメッシュのために距離を更新
		distance += 100.0f;
	}
}

tnl::Vector3 Player::Forward()
{
	// 基準の前方向ベクトル
	tnl::Vector3 base_forward(0, 0, 1);

	// プレイヤーの回転から行列を生成
	tnl::Matrix rotMatrix = m_rot.getMatrix();

	// 前方向ベクトルを回転行列で変換
	tnl::Vector3 forward 
		= tnl::Vector3::Transform(base_forward, rotMatrix);

	return forward;
}