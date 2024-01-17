#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[001]Camera/GameCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Partner.h"


Partner::Partner(){}

void Partner::Initialize()
{
	m_model_hdl = m_mediator->GetPartnerModelHdl();
}

void Partner::Update(float delta_time)
{
	// アニメーション更新処理
	m_mediator->UpdatePartnerAnim(delta_time);

	// 行列計算の更新
	UpdateMatrix(delta_time);

	//if (m_mediator->GetPlayerMovePushButton())
	//{
	//	// 行列計算の更新
	//	UpdateMatrix(delta_time);
	//}
}

void Partner::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	// モデル描画処理
	m_mediator->DrawPartnerModel();

	// 座標デバッグ用
	DrawStringEx(1000, 0, 1, "PartnerPos_x:%f", m_pos.x);
	DrawStringEx(1000, 20, 1, "PartnerPos_y:%f", m_pos.y);
	DrawStringEx(1000, 40, 1, "PartnerPos_z:%f", m_pos.z);
}

void Partner::UpdateMatrix(float delta_time)
{
	// 移動による座標と回転の更新
	m_mediator->UpdatePartnerMoveMatrix(delta_time);

	// 回転と座標から行列を計算
	m_matrix = CalcMatrix();

	// モデルに行列を適用
	MV1SetMatrix(m_model_hdl, m_matrix);
}


