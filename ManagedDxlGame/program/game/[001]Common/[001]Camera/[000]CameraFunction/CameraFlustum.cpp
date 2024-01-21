#include "../../[002]Mediator/Mediator.h"
#include "../GameCamera.h"
#include "CameraFlustum.h"


void CameraFlustum::IsIntersectFlustum(const float delta_time)
{
	tnl::Vector3 player_pos = m_mediator->GetPlayerPos();

	float player_radius = m_mediator->GetPlayerCollisionSize();

	// �㉺���E�̃t���X�^���ʂƂ̓����蔻��ƕ␳����
	InFlustumPlane(delta_time,player_pos, player_radius);
}

void CameraFlustum::InFlustumPlane(const float delta_time,tnl::Vector3& pos,float size)
{
	// meshpos,flustomvec,camerapos
	//tnl::Vector3 GetNearestPointPlane(const tnl::Vector3 & v, const tnl::Vector3 & pn, const tnl::Vector3 & pv)
	//{
	//	float d = tnl::Vector3::Dot(pn, pv);
	//	float t = tnl::Vector3::Dot(pn, v) - d;
	//	return v - (pn * t);
	//}

	// 6 : �t���X�^���ʂ̐��������[�v
	for (int i = 0; i < static_cast<int>(dxe::Camera::eFlustum::Max); ++i)
	{
		// �t���X�^���ʂ̖@�����擾
		tnl::Vector3 flustum_normal
			= m_mediator->GetFlustumNormal(static_cast<dxe::Camera::eFlustum>(i));

		float D = tnl::Vector3::Dot(flustum_normal, m_mediator->GetCameraPos());

		float distance = tnl::Vector3::Dot(flustum_normal, pos) - D;

		// �v���C���[���J�����ʂ̊O���ɂ���ꍇ

		// �v���C���[���t���X�^�����ɗ��߂邽�߂̕␳���s��
		pos -= (flustum_normal * (distance + size));
		

		// �ߕ��ʂƉ����ʂƂ̓����蔻��ƕ␳����
		if (i == 4 || i == 5)
		{
			CorrectPlayer(delta_time, size, pos);
		}

		// �␳�����ʒu���Z�b�g
		m_mediator->SetPlayerPos(pos);
	}
}

void CameraFlustum::CorrectPlayer(const float delta_time, float size,tnl::Vector3& pos)
{
	// �J�����̈ʒu���擾
	tnl::Vector3 camera_pos = m_mediator->GetCameraPos();

	// �J��������v���C���[�ւ̕����x�N�g���𐳋K��
	tnl::Vector3 direction = pos - camera_pos;
	direction.normalize();

	float distance = (pos - camera_pos).length();

	// �ߕ��ʂ̕␳
	if (distance < 300.0f + size)
	{
		// �v���C���[���ߕ��ʂ̓����Ɉړ�
		pos = camera_pos + direction * delta_time * (300 + size);
	}
	// �����ʂ̕␳
	else if (distance > 700.0f - size)
	{
		// �v���C���[�������ʂ̓����Ɉړ�
		pos = camera_pos + direction * delta_time * (700 - size);
	}

	// �␳�����ʒu���Z�b�g
	m_mediator->SetPlayerPos(pos);
}
