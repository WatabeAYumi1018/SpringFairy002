#include "CinemaCameraTarget.h"


CinemaCameraTarget::CinemaCameraTarget()
{
	// カメラ座標変換のために必要だけど、描画はされないよう限りなく0に近いサイズ
	float size = 0.001f;
	m_mesh = dxe::Mesh::CreateSphereMV(size);
	m_mesh->pos_ = { 0 };
	m_pos = m_mesh->pos_;
}

void CinemaCameraTarget::Draw(std::shared_ptr<dxe::Camera> camera)
{
	m_mesh->render(camera);
}