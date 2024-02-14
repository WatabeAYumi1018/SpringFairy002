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
	// ゲームのフェーズ情報を取得
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

void Effect::EffectOffset(tnl::Vector3& pos, tnl::Vector3& forward)
{
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
			m_particles[i]->setPosition({ pos.x, pos.y + m_offset,pos.z });
			m_particles[i]->setDiffDirection(forward);
			// アニメーションとエフェクトの再生時間調整
			m_particles[i]->setTimeScale(2);
		}

		// Danceエフェクトの場合
		if (m_mediator->GetIsPlayerDance()
			|| m_mediator->GetCinemaPlayerIsDance())
		{
			m_particles[i]->start();
			m_particles[i]->setPosition({ pos.x, pos.y + m_offset,pos.z });
			// アニメーションとエフェクトの再生時間調整
			m_particles[i]->setTimeScale(1.5f);
		}
	}
}

void Effect::EffectPlayerAction(int start, int end,bool is_game)
{
	m_start_id = start;
	m_end_id = end;

	// プレイヤーの位置を取得
	tnl::Vector3 pos;
	// キャラの正面向きを取得
	tnl::Vector3 forward = m_mediator->PlayerForward();

	if (is_game)
	{
		pos = m_mediator->GetPlayerPos();
	}
	else
	{
		pos = m_mediator->GetCinemaPlayerPos();
	}

	EffectOffset(pos, forward);
}

void Effect::EffectPath(bool is_player)
{
	tnl::Vector3 pos;
	tnl::Vector3 direction;

	if (is_player)
	{
		pos = m_mediator->GetPlayerPos();
		direction = m_mediator->PlayerForward();
	}
	else
	{
		pos = m_mediator->GetButterflyPos();
		// 進行方向を取得
		direction = m_mediator->GetButterflyNextDirection();
	}

	m_particles[36]->start();
	m_particles[36]->setPosition(pos);
	// 方向とは逆に設定
	m_particles[36]->setDiffDirection(-direction);
}

void Effect::EffectButterfly()
{
	tnl::Vector3 pos = m_mediator->GetButterflyPos();

	// 消える瞬間にエフェクトを再生
	if (m_mediator->GetButterflyIsClear())
	{
		// 該当エフェクトを指定
		m_particles[19]->start();
		m_particles[19]->setPosition(pos);
		// アニメーションとエフェクトの再生時間調整
		m_particles[19]->setTimeScale(1.5f);
	}
}

void Effect::EffectGimmick()
{
	tnl::Vector3 pos = m_mediator->GetGimmickPos();

		// ギミックエフェクト（単発再生）
	if (m_mediator->GetGimmickIsCollision())
	{
		// 該当エフェクトを指定
		m_particles[39]->start();
		m_particles[39]->setPosition(pos);
	}
}

void Effect::EffectScreen(int start,int end)
{
	// スクリーンエフェクト（ループ再生）
	for (int i = start; i <= end; ++i)
	{
		m_particles[i]->start();
	}
}

void Effect::EffectTransCinema()
{
	// ダンスに関連するエフェクト再生
	if (m_mediator->GetCinemaPlayerIsDance())
	{
		EffectPlayerAction(12, 15,false);

		if (m_stage_phase == StagePhase::eStagePhase::e_wood)
		{
			EffectScreen(16,18);
		}

		if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
		{
			EffectScreen(20, 23);
		}
	}
	
	if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		// キャラ軌跡エフェクト（ループ再生）
		if (m_mediator->GetButterflyIsCinemaActive())
		{
			EffectButterfly();
			EffectPath(false);
		}
	}
}

void Effect::EffectTransGame()
{
	if (m_mediator->GetIsPlayerBloom())
	{
		EffectPlayerAction(0, 11);
	}
	else if (m_mediator->GetIsPlayerDance())
	{
		EffectPlayerAction(12, 15);
	}
	
	if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		// キャラ軌跡エフェクト（ループ再生）
		EffectPath();
		// スクリーンエフェクト（ループ再生）
		EffectScreen(16, 18);
		EffectScreen(25, 34);
	}
}