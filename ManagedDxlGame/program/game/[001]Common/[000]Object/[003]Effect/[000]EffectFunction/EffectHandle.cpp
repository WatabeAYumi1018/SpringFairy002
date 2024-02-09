#include "../../../[002]Mediator/Mediator.h"
#include "EffectHandle.h"



EffectHandle::EffectHandle()
{
	
}

EffectHandle::~EffectHandle()
{
	for (std::shared_ptr<dxe::Particle>& particle : m_particles)
	{
		particle.reset();
	}

	for (std::shared_ptr<dxe::Particle>& particle : m_particles)
	{
		particle.reset();
	}

	for (std::shared_ptr<dxe::Particle>& particle : m_player_action_particles)
	{
		particle.reset();
	}

	for (std::shared_ptr<dxe::Particle>& particle : m_gimmick_particles)
	{
		particle.reset();
	}

	for (std::shared_ptr<dxe::Particle>& particle : m_chara_path_particles)
	{
		particle.reset();
	}

	for (std::shared_ptr<dxe::Particle>& particle : m_screen_particles)
	{
		particle.reset();
	}

	for (std::shared_ptr<dxe::Particle>& particle : m_event_particles)
	{
		particle.reset();
	}

	m_particles.clear();
	m_player_action_particles.clear();
	m_gimmick_particles.clear();
	m_chara_path_particles.clear();
	m_screen_particles.clear();
	m_event_particles.clear();
}

void EffectHandle::Initialize()
{
	m_effects_type = m_mediator->GetEffectLoadInfo();

	for (Effect::sEffectType& effect_type : m_effects_type)
	{
		std::shared_ptr<dxe::Particle> particle = nullptr;

		particle = std::make_shared<dxe::Particle>(effect_type.s_effect_path.c_str());

		m_particles.emplace_back(particle);
	}
}

void EffectHandle::Update()
{
	m_camera_phase = m_mediator->GetNowCameraPhaseState();
	m_stage_phase = m_mediator->GetNowStagePhaseState();

	// シネマカメラの時
	if (m_camera_phase == CameraPhase::eCameraPhase::e_cinema)
	{
		EffectTransCinema();
	}
	// ゲームカメラの時
	else
	{
		EffectTransGame();
	}

	AttackOffset();
}

void EffectHandle::EffectStocker(int start, int end
								 , std::vector<std::shared_ptr<dxe::Particle>>& particles)
{
	for (int i = start; i <= end; ++i)
	{
		particles.emplace_back(m_particles[i]);
	}
}

void EffectHandle::EffectTransCinema()
{
	m_player_action_particles.clear();
	m_chara_path_particles.clear();
	m_event_particles.clear();

	if (m_stage_phase == StagePhase::eStagePhase::e_flower)
	{
		if (m_mediator->GetCinemaPlayerIsDance())
		{
			EffectStocker(16, 17, m_player_action_particles);
		}
	}

	else if (m_stage_phase == StagePhase::eStagePhase::e_wood)
	{
		if (m_mediator->GetCinemaPlayerIsDance())
		{
			EffectStocker(22, 23, m_player_action_particles);
		}
	}
	
	else if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		// キャラ軌跡エフェクト（ループ再生）
		if (m_mediator->GetButterflyIsCinemaActive())
		{
			EffectStocker(26, 26, m_chara_path_particles);
		}
		// 蝶のクリアエフェクト（単発再生）
		if (m_mediator->GetButterflyIsClear())
		{
			EffectStocker(19, 19, m_event_particles);
		}
	}
}

void EffectHandle::EffectTransGame()
{
	m_player_action_particles.clear();

	if(m_stage_phase == StagePhase::eStagePhase::e_flower)
	{
		if(tnl::Input::IsKeyDownTrigger(eKeys::KB_X))
		{
			EffectStocker(0, 13, m_player_action_particles);
		}
		else if (m_mediator->GetIsPlayerDance())
		{
			EffectStocker(16, 17, m_player_action_particles);
		}
	}
	else if (m_stage_phase == StagePhase::eStagePhase::e_wood)
	{
		if (m_mediator->GetIsPlayerBloom())
		{
			EffectStocker(0, 15, m_player_action_particles);
		}
		else if (m_mediator->GetIsPlayerDance())
		{
			EffectStocker(16, 17, m_player_action_particles);
		}
	}
	else if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		if (m_mediator->GetIsPlayerBloom())
		{
			EffectStocker(0, 15, m_player_action_particles);
		}
		else if (m_mediator->GetIsPlayerDance())
		{
			EffectStocker(16, 17, m_player_action_particles);
		}

		// スクリーンエフェクト（ループ再生）
		EffectStocker(20, 24, m_screen_particles);
		// キャラ軌跡エフェクト（ループ再生）
		EffectStocker(26, 26, m_chara_path_particles);
	}

	// ギミックエフェクト（単発再生）
	if (m_mediator->GetGimmickIsCollision())
	{
		EffectStocker(25, 25, m_gimmick_particles);
	}
}

void EffectHandle::AttackOffset()
{
	// オフセット値
	float offset = 150.0f;

	// キャラの正面向きを取得
	tnl::Vector3 forward = m_mediator->PlayerForward();

	// ゲームプレイヤーの位置を取得
	m_game_pos = m_mediator->GetPlayerPos();
	// シネマプレイヤーの位置を取得
	m_cinema_pos = m_mediator->GetCinemaPlayerPos();

	for (std::shared_ptr<dxe::Particle>& particle : m_player_action_particles)
	{
		if (m_mediator->GetIsPlayerBloom())
		{
			particle->start();
			particle->setPosition({ m_game_pos.x, m_game_pos.y + offset, m_game_pos.z });
			particle->setDiffDirection(forward);
		}

		if (m_mediator->GetIsPlayerDance())
		{
			particle->start();
			particle->setPosition({ 0, m_game_pos.y + offset, 0 });
			particle->setSizeX(5);
			particle->setSizeY(5);
		}

		if (m_mediator->GetCinemaPlayerIsDance())
		{
			particle->start();
			particle->setPosition({ 0, m_cinema_pos.y + offset, 0 });
			particle->setSizeX(5);
			particle->setSizeY(5);
		}
	}
}