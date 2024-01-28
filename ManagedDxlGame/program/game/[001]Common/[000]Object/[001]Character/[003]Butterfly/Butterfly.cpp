#include "Butterfly.h"


Butterfly::Butterfly()
{
	m_pos = { 0 };
}

Butterfly::~Butterfly()
{

}

void Butterfly::Update(const float delta_time)
{	
	AnimMove(delta_time);

	MoveRound(delta_time);

    // ��]�ƍ��W����s����v�Z
    m_matrix = CalcMatrix();

    // ���f���ɍs���K�p
    MV1SetMatrix(m_model_hdl, m_matrix);
}

void Butterfly::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	SetLight();

	MV1DrawModel(m_model_hdl);
}

void Butterfly::SetLight()
{
	//���Ȕ���
	DxLib::COLOR_F emissive = { 0.5f,0.5f,0.5f,1 };
	//����
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	//�g�U��
	DxLib::COLOR_F diffuse = { 0.5f,0.5f,0.5f,1 };
	//���^���b�N
	DxLib::COLOR_F specular = { 0,0,0,1 };

	MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	MV1SetMaterialAmbColor(m_model_hdl, 0, ambient);
	MV1SetMaterialDifColor(m_model_hdl, 0, diffuse);
	MV1SetMaterialSpcColor(m_model_hdl, 0, specular);
	// �����قǌ����s���Ȃ�
	MV1SetMaterialSpcPower(m_model_hdl, 0, 0.5f);
}


void Butterfly::SetAnim()
{
	//// �e�N�X�`��
	//m_texture_hdl = LoadGraph("model/fairy/fairy.png");
	//// ���f���ǂݎ��
	//m_model_hdl = MV1LoadModel("model/fairy/fairy_new.mv1");
	//// move�{�[��
	//m_anim_bone_move_hdl = MV1LoadModel("model/fairy/move_new.mv1");
	//// �ގ��̎w��͂Ȃ����߈�����0
	//MV1SetTextureGraphHandle(m_model_hdl, 0, m_texture_hdl, FALSE);
}

void Butterfly::AnimMove(const float delta_time)
{
	// idle�A�j���[�V�����X�V����
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
    // �~�̊p�x���X�V
    m_circle_angle += m_speed * delta_time;

    // �~�^���̂��߂̐V�����ʒu���v�Z
    // x��z���g���ĉ~�^����\��
    m_pos.x = cosf(m_circle_angle) * m_circle_radius;
    m_pos.z = sinf(m_circle_angle) * m_circle_radius;

    // ��]����
    // ���̃��f������ɉ~�^���̐ڐ������������悤�ɂ���
    m_rot.y = - m_circle_angle;

    // 360�x�i2�΃��W�A���j�𒴂����烊�Z�b�g
    const float two_pi = tnl::ToRadian(360.0f);

    if (m_circle_angle > two_pi)
    {
        m_circle_angle -= two_pi;
    }
}

void Butterfly::MoveStraight(const float delta_time)
{
	// ���x���v�Z
	float move_speed = m_speed * delta_time;

	// �ʒu���X�V
	m_pos.z += move_speed;
}
