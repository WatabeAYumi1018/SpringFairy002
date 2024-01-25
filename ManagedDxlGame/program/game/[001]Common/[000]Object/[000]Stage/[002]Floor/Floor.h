#pragma once
#include "../../../[000]Object/Object.h"

class Mediator;


class Floor : public Object
{

public:

	Floor();
	~Floor() {}

	static const int DRAW_DISTANCE = -500;

private:

	std::shared_ptr<dxe::Mesh> m_floor = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;


public:

	void Draw(std::shared_ptr<GameCamera> gameCamera) override;
};
