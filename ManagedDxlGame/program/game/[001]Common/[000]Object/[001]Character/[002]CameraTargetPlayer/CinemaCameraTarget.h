#pragma once
#include "../Character.h"


class CinemaCameraTarget : public Character
{

public:

	CinemaCameraTarget();

	~CinemaCameraTarget() {}

private:

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

public:

	// �`�揈��
	void Draw(std::shared_ptr<dxe::Camera> camera) override;
};