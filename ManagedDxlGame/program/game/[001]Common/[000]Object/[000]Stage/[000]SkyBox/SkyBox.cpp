#include "SkyBox.h"
#include "../../../[001]Camera/GameCamera.h"

SkyBox::SkyBox()
{	
	m_mesh = dxe::Mesh::CreateCubeMV(50000,40,40);
	m_mesh->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/Magical.png"));
	m_mesh->loadMaterial("material.bin");
}

void SkyBox::Update(float delta_time)
{
	m_rot *= tnl::Quaternion::RotationAxis({ 0, 0, 1 }, tnl::ToRadian(180.0f));
}

void SkyBox::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	m_mesh->render(gameCamera);
}