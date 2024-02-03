#pragma once
#include "../../Character.h"


class Mediator;
// update‚É‚ÄƒCƒxƒ“ƒg”­¶‚Ì‚İˆ—‚ğ‚·‚é‚æ‚¤‚É‚·‚é

class CinemaPlayer : public Character
{

public:

	CinemaPlayer();

	~CinemaPlayer();

private:

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};