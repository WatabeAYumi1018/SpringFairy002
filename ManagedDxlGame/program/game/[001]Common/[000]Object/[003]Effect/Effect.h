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

	// プレイヤーのアクションエフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_player_action_particles;
	// ギミックエフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_gimmick_particles;
	// キャラクターの軌道エフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_chara_path_particles;
	// スクリーンエフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_screen_particles;
	// イベントエフェクト
	std::vector<std::shared_ptr<dxe::Particle>> m_event_particles;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 各アクティブエフェクトの取得
	void GetActiveParticle();

	// アクティブエフェクトのレンダー処理
	void ActiveEffect(std::shared_ptr<dxe::Camera> camera
					 , std::vector<std::shared_ptr<dxe::Particle>>& particles);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};