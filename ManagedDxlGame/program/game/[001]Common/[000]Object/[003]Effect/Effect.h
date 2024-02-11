#pragma once
#include "../../[003]Phase/CameraPhase.h"
#include "../../[003]Phase/StagePhase.h"
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

	int m_start_id = 0;
	int m_end_id = 0;

	CameraPhase::eCameraPhase m_camera_phase
		= CameraPhase::eCameraPhase::e_cinema;

	StagePhase::eStagePhase m_stage_phase
		= StagePhase::eStagePhase::e_flower;

	std::vector<std::shared_ptr<dxe::Particle>> m_particles;

	std::vector<Effect::sEffectType> m_effects_type;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 各アクティブエフェクトの取得
	void EffectOffset(int start, int end);

	// シネマ画面のエフェクト遷移
	void EffectTransCinema();

	// ゲーム画面のエフェクト遷移
	void EffectTransGame();

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};