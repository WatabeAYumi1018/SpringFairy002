#include "CinemaCameraTarget.h"


CinemaCameraTarget::CinemaCameraTarget()
{
	// �J�������W�ϊ��̂��߂ɕK�v�����ǁA�`��͂���Ȃ��悤����Ȃ�0�ɋ߂��T�C�Y
	float size = 0.001f;
	m_mesh = dxe::Mesh::CreateSphereMV(size);
	m_mesh->pos_ = { 0 };
	m_pos = m_mesh->pos_;
}

void CinemaCameraTarget::Draw(std::shared_ptr<dxe::Camera> camera)
{
	m_mesh->render(camera);
}