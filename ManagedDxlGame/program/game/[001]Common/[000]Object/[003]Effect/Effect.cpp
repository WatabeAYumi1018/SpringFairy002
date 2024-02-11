#include "../../[002]Mediator/Mediator.h"
#include "Effect.h"


Effect::Effect()
{

}

Effect::~Effect()
{
	for (std::shared_ptr<dxe::Particle>& particle : m_particles)
	{
		particle.reset();
	}

	m_particles.clear();
}

void Effect::Initialize()
{
    m_effects_type = m_mediator->GetEffectLoadInfo();

    // 全パーティクルを格納
    for (Effect::sEffectType& effect_type : m_effects_type)
    {
        std::shared_ptr<dxe::Particle> particle = nullptr;

        particle = std::make_shared<dxe::Particle>(effect_type.s_effect_path.c_str());

        m_particles.emplace_back(particle);
    }
}

void Effect::Update(float delta_time)
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
}

void Effect::Draw(std::shared_ptr<dxe::Camera> camera)
{
    // パーティクルの描画開始
    dxe::Particle::renderBegin();

	for (int i = m_start_id; i <= m_end_id; ++i)
	{
		// パーティクルを描画
		m_particles[i]->render(camera);
	}

    // パーティクルの描画終了
    dxe::Particle::renderEnd();
}

void Effect::EffectOffset(int start, int end)
{
	m_start_id = start;
	m_end_id = end;

	// オフセット値
	float offset = 150.0f;

	// キャラの正面向きを取得
	tnl::Vector3 forward = m_mediator->PlayerForward();

	// プレイヤーの位置を取得
	tnl::Vector3 m_pos = m_mediator->GetPlayerPos();

	for (int i = m_start_id; i <= m_end_id; ++i)
	{
		// 範囲外のエフェクトはスキップ
		if (i < 0 || i >= m_particles.size())
		{
			continue;
		}

		// Bloomエフェクトの場合
		if (m_mediator->GetIsPlayerBloom())
		{
			m_particles[i]->start();
			m_particles[i]->setPosition({ m_pos.x, m_pos.y + offset,m_pos.z });
			m_particles[i]->setDiffDirection(forward);
		}
		// Danceエフェクトの場合
		else if (m_mediator->GetIsPlayerDance())
		{
			m_particles[i]->start();
			m_particles[i]->setPosition({ m_pos.x, m_pos.y + offset,m_pos.z });
		}
	}
}

void Effect::EffectTransCinema()
{
	if (m_stage_phase == StagePhase::eStagePhase::e_flower)
	{
		if (m_mediator->GetCinemaPlayerIsDance())
		{
			EffectOffset(16, 17);
		}
	}

	else if (m_stage_phase == StagePhase::eStagePhase::e_wood)
	{
		if (m_mediator->GetCinemaPlayerIsDance())
		{
			EffectOffset(22, 23);
		}
	}

	else if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		// キャラ軌跡エフェクト（ループ再生）
		if (m_mediator->GetButterflyIsCinemaActive())
		{
			EffectOffset(26, 26);
		}
		// 蝶のクリアエフェクト（単発再生）
		if (m_mediator->GetButterflyIsClear())
		{
			EffectOffset(19, 19);
		}
	}
}

void Effect::EffectTransGame()
{
	if (m_stage_phase == StagePhase::eStagePhase::e_flower)
	{
		if (m_mediator->GetIsPlayerBloom())
		{
			EffectOffset(0, 13);
		}
		else if (m_mediator->GetIsPlayerDance())
		{
			EffectOffset(16, 17);
		}
	}
	else if (m_stage_phase == StagePhase::eStagePhase::e_wood)
	{
		if (m_mediator->GetIsPlayerBloom())
		{
			EffectOffset(0, 15);
		}
		else if (m_mediator->GetIsPlayerDance())
		{
			EffectOffset(16, 17);
		}
	}
	else if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		if (m_mediator->GetIsPlayerBloom())
		{
			EffectOffset(0, 15);
		}
		else if (m_mediator->GetIsPlayerDance())
		{
			EffectOffset(16, 17);
		}

		// スクリーンエフェクト（ループ再生）
		EffectOffset(20, 24);
		// キャラ軌跡エフェクト（ループ再生）
		EffectOffset(26, 26);
	}

	// ギミックエフェクト（単発再生）
	if (m_mediator->GetGimmickIsCollision())
	{
		EffectOffset(25, 25);
	}

}