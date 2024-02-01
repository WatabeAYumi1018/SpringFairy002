#include "Butterfly.h"


Butterfly::Butterfly()
{
	m_pos = { 0 };

	m_model_hdl = MV1LoadModel("model/gimmick/sky/flower/flower.mv1");

	SetLight(m_model_hdl);
}

Butterfly::~Butterfly()
{
	// モデルのアンロード
	MV1DeleteModel(m_model_hdl);
}

void Butterfly::Update(const float delta_time)
{	
	AnimMove(delta_time);

	MoveRound(delta_time);

    // 回転と座標から行列を計算
    m_matrix = CalcMatrix();

    // モデルに行列を適用
    MV1SetMatrix(m_model_hdl, m_matrix);
}

void Butterfly::Draw(std::shared_ptr<dxe::Camera> camera)
{
	MV1DrawModel(m_model_hdl);
}



void Butterfly::SetAnim()
{
	//// テクスチャ
	//m_texture_hdl = LoadGraph("model/fairy/fairy.png");
	//// モデル読み取り
	//m_model_hdl = MV1LoadModel("model/fairy/fairy_new.mv1");
	//// moveボーン
	//m_anim_bone_move_hdl = MV1LoadModel("model/fairy/move_new.mv1");
	//// 材質の指定はないため引数は0
	//MV1SetTextureGraphHandle(m_model_hdl, 0, m_texture_hdl, FALSE);
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

void Butterfly::AnimDraw(const float delta_time)
{

}

void Butterfly::MoveRound(const float delta_time)
{
    // 円の角度を更新
    m_circle_angle += m_speed * delta_time;

    // 円運動のための新しい位置を計算
    // xとzを使って円運動を表現
    m_pos.x = cosf(m_circle_angle) * m_circle_radius;
    m_pos.z = sinf(m_circle_angle) * m_circle_radius;

    // 回転処理
    // 蝶のモデルが常に円運動の接線方向を向くようにする
    m_rot.y = - m_circle_angle;

    // 360度（2πラジアン）を超えたらリセット
    const float two_pi = tnl::ToRadian(360.0f);

    if (m_circle_angle > two_pi)
    {
        m_circle_angle -= two_pi;

		m_is_circle = true;
    }
}

void Butterfly::MoveStraight(const float delta_time)
{
	// 速度を計算
	float move_speed = m_speed * delta_time;

	// 位置を更新
	m_pos.z += move_speed;
}
