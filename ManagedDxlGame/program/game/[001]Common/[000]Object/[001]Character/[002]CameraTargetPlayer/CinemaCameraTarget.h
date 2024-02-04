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

	// •`‰æˆ—
	void Draw(std::shared_ptr<dxe::Camera> camera) override;
};