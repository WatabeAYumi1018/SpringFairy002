#include "CinemaCameraTarget.h"


CinemaCameraTarget::CinemaCameraTarget()
{
	m_mesh = dxe::Mesh::CreateSphereMV(0.001f);
	m_mesh->pos_ = { 0 };
	m_pos = m_mesh->pos_;
}

void CinemaCameraTarget::Draw(std::shared_ptr<dxe::Camera> camera)
{
	m_mesh->render(camera);
}