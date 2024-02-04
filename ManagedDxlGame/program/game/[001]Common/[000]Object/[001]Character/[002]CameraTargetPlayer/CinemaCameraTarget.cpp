#include "CinemaCameraTarget.h"


CinemaCameraTarget::CinemaCameraTarget()
{
	m_mesh = dxe::Mesh::CreateSphereMV(5);
	m_mesh->pos_ = { 0 };
	m_pos = m_mesh->pos_;
}

void CinemaCameraTarget::Draw(std::shared_ptr<dxe::Camera> camera)
{
	m_mesh->render(camera);
}