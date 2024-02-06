#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Butterfly.h"


Butterfly::Butterfly()
{
	m_pos = { 0,0,0 };

	// モデルをカメラ座標に反映させるため、目にみえないメッシュを生成
	m_mesh = dxe::Mesh::CreateSphereMV(0.001f);

	m_scale = { 5 };
}

Butterfly::~Butterfly()
{
	// モデルのアンロード
	MV1DeleteModel(m_model_hdl);
}

void Butterfly::Initialize()
{
	m_model_hdl = m_mediator->GetButterflyModelHdl();

	m_anim_index = MV1AttachAnim(m_model_hdl, 0);

	m_time_count = MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_index);

	SetLight(m_model_hdl);

	m_rot = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(180));

	//// エミッシブカラーを設定してモデルを発光させる
	//DxLib::COLOR_F emissive = {10.0f, 10.0f, 10.0f, 1 }; // 強い発光
	//
	//MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);

	//DxLib::COLOR_F diffuse = { 10,10,10,1 };

	//MV1SetMaterialDifColor(m_model_hdl, 0, diffuse);
}

void Butterfly::Update(const float delta_time)
{	
	AnimMove(delta_time);

	if (m_is_cinema_active)
	{
		MoveStraightWidth(delta_time);
	}

	m_mesh->pos_ = m_pos;

	// 回転と座標から行列を計算
	m_matrix = CalcMatrix();

    // モデルに行列を適用
    MV1SetMatrix(m_model_hdl, m_matrix);
}

void Butterfly::Draw(std::shared_ptr<dxe::Camera> camera)
{
	m_mesh->render(camera);

	// 描画モードを変更して、発光を強調
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	MV1DrawModel(m_model_hdl);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Butterfly::AnimMove(const float delta_time)
{
	// idleアニメーション更新処理
	m_elapsed_time += m_anim_speed * delta_time;

	if (m_elapsed_time > m_time_count)
	{
		m_elapsed_time -= m_time_count;
	}

	MV1SetAttachAnimTime(m_model_hdl, 0, m_elapsed_time);
}

//void Butterfly::MoveRoundFrontToBack(const float delta_time)
//{
//	m_elapsed_time_circle += delta_time;
//
//	// 宙返りの全体の進行時間に基づいた角度計算
//	float angle = (m_elapsed_time_circle / m_total_time) * tnl::ToRadian(360);
//
//	// 横回転によるX軸方向の移動
//	m_pos.x = m_pos.x + sin(angle) * m_radius; 
//	// 横回転によるZ軸方向の移動
//	m_pos.z = m_pos.z + cos(angle) * m_radius; 
//
//	// 回転軸をY軸に変更
//	tnl::Quaternion target_rot
//		= tnl::Quaternion::LookAtAxisY(m_pos,tnl::Vector3(0,0,0));
//
//	// 現在の回転から目標の回転に向けてslerpを行う
//	m_rot.slerp(target_rot, delta_time * m_speed);
//
//	// 2週したらmoveへ移行
//	if (m_elapsed_time_circle >= m_total_time * 2)
//	{
//		m_is_circle = true;
//	}
//}

void Butterfly::MoveStraightHeight(const float delta_time)
{
	// 速度を計算
	float move_speed = m_speed * delta_time * 50;

	m_pos.z += move_speed;
}

void Butterfly::MoveStraightWidth(const float delta_time)
{
	// 速度を計算
	float move_speed = m_speed * delta_time * 100;

	m_pos.x -= move_speed;
}

