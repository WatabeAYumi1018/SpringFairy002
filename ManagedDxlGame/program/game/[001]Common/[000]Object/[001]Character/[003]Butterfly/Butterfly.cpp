#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Butterfly.h"


Butterfly::Butterfly()
{
	m_pos = { 0,0,0 };

	m_model_hdl = MV1LoadModel("model/gimmick/ground/plant/flower002.mv1");

	SetLight(m_model_hdl);

	// �o�^�t���C���^���I�Ƀ��[���h���W�ɍ��킹�邽�߂Ƀ��b�V���쐬
	m_mesh = dxe::Mesh::CreateSphereMV(50);
	m_mesh->pos_ = m_pos;
}

Butterfly::~Butterfly()
{
	// ���f���̃A�����[�h
	MV1DeleteModel(m_model_hdl);
}

void Butterfly::Update(const float delta_time)
{	
	AnimMove(delta_time);

	if (!m_is_circle)
	{
		MoveRound(delta_time);
	}
	else
	{
		MoveStraight(delta_time);
	}

	m_mesh->pos_ = m_pos;

	// ��]�ƍ��W����s����v�Z
	m_matrix = CalcMatrix();

    // ���f���ɍs���K�p
    MV1SetMatrix(m_model_hdl, m_matrix);

	// �f�o�b�O�p�ɍ��W��\��
	DrawStringEx(0, 0,-1, "pos.x:%f", GetPos().x);	
	DrawStringEx(0, 20,-1, "pos.y:%f", GetPos().y);
	DrawStringEx(0, 40,-1, "pos.z:%f", GetPos().z);

}

void Butterfly::Draw(std::shared_ptr<dxe::Camera> camera)
{
	m_mesh->render(camera);

	MV1DrawModel(m_model_hdl);
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
	m_elapsed_time_circle += delta_time;

	// ���Ԃ�̑S�̂̐i�s���ԂɊ�Â����p�x�v�Z
	float angle = (m_elapsed_time_circle / m_total_time) * tnl::ToRadian(360);

	// ����]�ɂ��X�������̈ړ�
	m_pos.x = m_pos.x + sin(angle) * m_radius; 
	// ����]�ɂ��Z�������̈ړ�
	m_pos.z = m_pos.z + cos(angle) * m_radius; 

	// ��]����Y���ɕύX
	tnl::Quaternion target_rot
		= tnl::Quaternion::LookAtAxisY(m_pos,tnl::Vector3(0,0,0));

	// ���݂̉�]����ڕW�̉�]�Ɍ�����slerp���s��
	m_rot.slerp(target_rot, delta_time * m_speed);

	// 2�T������move�ֈڍs
	if (m_elapsed_time_circle >= m_total_time * 2)
	{
		m_is_circle = true;
	}
}

void Butterfly::MoveStraight(const float delta_time)
{
	if (!m_mediator->GetGateIsActive())
	{
		// ���x���v�Z
		float move_speed = m_speed * delta_time * 50;

		m_pos.z += move_speed;
	}
}
