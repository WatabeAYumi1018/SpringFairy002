#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mediator;


class CameraFlustum
{

public:

	CameraFlustum() {}

	~CameraFlustum() {}

private:

	std::shared_ptr<Mediator> m_mediator = nullptr;


	void InFlustumPlane(const float delta_time, tnl::Vector3& pos,float size);

	void CorrectPlayer(const float delta_time, float size, tnl::Vector3& pos);


public:

	// ƒtƒ‰ƒXƒ^ƒ€‚Æ‚Ì“–‚½‚è”»’è
	void IsIntersectFlustum(const float delta_time);

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};