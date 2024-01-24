#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../Object.h"

class SkyBox : public Object
{

public:

	SkyBox();

	~SkyBox() {}

private:

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	

public:

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<GameCamera> gameCamera) override;
};