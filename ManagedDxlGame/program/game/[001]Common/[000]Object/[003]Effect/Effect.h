#pragma once
#include "../Object.h"

class Mediator;

class Effect : public Object
{

public:

	struct sEffectType
	{
		int s_id;
		std::string s_effect_path;
	};

	Effect();
	~Effect();


private:

	std::vector<sEffectType> m_effect_types;

	std::vector<std::shared_ptr<dxe::Particle>> m_particles;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ファイルパスの文字列中にattackがあるかどうか
	bool ContainsAttack(const std::string& str);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<GameCamera> gameCamera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};