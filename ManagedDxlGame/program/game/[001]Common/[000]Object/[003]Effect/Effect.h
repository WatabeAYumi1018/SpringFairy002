#pragma once
#include "../Object.h"

class Mediator;

class Effect : public Object
{

public:

	enum eEffectGroup
	{
		e_bloom,
		e_dance,
		e_cinema,
		e_screen,
		e_other
	};

	struct sEffectType
	{
		int s_id;
		eEffectGroup e_group;
		std::string s_effect_path;
	};

	Effect();
	~Effect();


private:


	bool m_is_bloom = false;
	bool m_is_dance = false;
	bool m_is_event_dance = false;

	std::vector<sEffectType> m_effect_types;

	std::vector<std::shared_ptr<dxe::Particle>> m_particles;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ファイルパスの文字列中にattackがあるかどうか
	bool ContainsAttack(const std::string& str);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};