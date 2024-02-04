#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Butterfly.h"


Butterfly::Butterfly()
{
	m_pos = { 0,0,0 };

	// ���f�����J�������W�ɔ��f�����邽�߁A�ڂɂ݂��Ȃ����b�V���𐶐�
	m_mesh = dxe::Mesh::CreateSphereMV(0.0001f);

	m_scale = { 5 };
}

Butterfly::~Butterfly()
{
	// ���f���̃A�����[�h
	MV1DeleteModel(m_model_hdl);
}

void Butterfly::Initialize()
{
	m_model_hdl = m_mediator->GetButterflyModelHdl();

	m_anim_index = MV1AttachAnim(m_model_hdl, 0);

	m_time_count = MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_index);

	SetLight(m_model_hdl);

	//DxLib::COLOR_F emissive = { 0.8f,0.8f,0.8f,1 };
	//MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
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
}

void Butterfly::Draw(std::shared_ptr<dxe::Camera> camera)
{
	m_mesh->render(camera);

	MV1DrawModel(m_model_hdl);
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
