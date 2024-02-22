#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[001]Camera/GameCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Partner.h"


Partner::Partner()
{
	m_collision_size = 60;
}

Partner::~Partner()
{
	MV1DeleteModel(m_model_hdl);
}

void Partner::Initialize()
{
	StartPos();

	m_mediator->InitializePartnerDraw();

	m_model_hdl = m_mediator->GetPartnerModelHdl();

	SetLight(m_model_hdl);
}

void Partner::Update(const float delta_time)
{
	// アニメーション更新処理
	m_mediator->UpdatePartnerAnim(delta_time);

	// 行列計算の更新
	UpdateMatrix(delta_time);
}

void Partner::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// モデル描画処理
	m_mediator->DrawPartnerModel();

	if (m_mediator->GetNowStagePhaseState()
		== StagePhase::eStagePhase::e_wood)
	{
		// パートナーを徐々に明るくするためemmisiveを変更
		// ※本来はデバッグ処理で外部から変更するのが好ましい
		// 　処理の複雑化を避けるため、ここで処理を行っている
		DxLib::COLOR_F emissive = { 0.7f,0.7f,0.7f,1 };

		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	}
	else if (m_mediator->GetNowStagePhaseState()
		== StagePhase::eStagePhase::e_fancy)
	{
		// パートナーを徐々に明るくするためemmisiveを変更
		// ※本来はデバッグ処理で外部から変更するのが好ましい
		// 　処理の複雑化を避けるため、ここで処理を行っている
		DxLib::COLOR_F emissive = { 0.9f,0.9f,0.9f,1 };

		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	}
}

void Partner::UpdateMatrix(const float delta_time)
{
	// 移動による座標と回転の更新
	m_mediator->UpdatePartnerMoveMatrix(delta_time);

	// 回転と座標から行列を計算
	m_matrix = CalcMatrix();

	// モデルに行列を適用
	MV1SetMatrix(m_model_hdl, m_matrix);
}