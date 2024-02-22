#include "../../[002]Mediator/Mediator.h"
#include "Effect.h"


Effect::~Effect()
{
	m_effects_type.clear();

	for (std::shared_ptr<dxe::Particle>& particle : m_particles)
	{
		particle.reset();
	}

	m_particles.clear();
}

void Effect::Initialize()
{
	// 二つのオブジェクトで実行されるため、二回目の初期化防止
	if (!m_particles.empty()) 
	{
		return;
	}

    m_effects_type = m_mediator->GetEffectLoadInfo();

    // 全パーティクルを格納
    for (Effect::sEffectType& effect_type : m_effects_type)
    {
        std::shared_ptr<dxe::Particle> particle = nullptr;

        particle = std::make_shared<dxe::Particle>(effect_type.s_effect_path.c_str());

        m_particles.emplace_back(particle);
    }

	for (int i = 0; i < m_particles.size(); ++i) 
	{
		// 初期状態では非アクティブ
		m_active_effects[i] = false; 
	}
}

void Effect::Update(float delta_time)
{
	if (m_mediator->GetCurrentEventLane().s_id == 12)
	{
		m_is_not_draw = true;

		SetEffectActive(22, 31, false);
	}

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

	for (size_t i = 0; i < m_particles.size(); ++i)
	{
		// エフェクトがアクティブな場合のみ描画
		if (m_active_effects[i]) 
		{
			m_particles[i]->render(camera);
		}
	}

    // パーティクルの描画終了
    dxe::Particle::renderEnd();
}

void Effect::EffectTransCinema()
{
	// ダンスに関連するエフェクト再生
	if (m_mediator->GetCinemaPlayerIsDance())
	{
		SetEffectActive(12, 15, true);
		EffectPlayerAction(12, 15, false);
	}

	if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		SetEffectActive(20, 20, true);
		SetEffectActive(16, 19, true);

		EffectScreen(16, 19, false);
		EffectButterfly(20);

		if (m_is_screen)
		{
			SetEffectActive(21, 21, true);
			EffectScreen(21, 21, false);
		}
	}
}

void Effect::EffectTransGame()
{
	if (m_mediator->GetIsPlayerBloom())
	{
		SetEffectActive(0, 11, true);
		EffectPlayerAction(0, 11);
	}

	if (m_mediator->GetIsPlayerDance())
	{
		SetEffectActive(12, 15, true);
		EffectPlayerAction(12, 15);
	}

	if (m_mediator->GetGimmickIsCollision())
	{
		SetEffectActive(35, 35, true);
		EffectGimmick(35);
	}

	if (m_stage_phase == StagePhase::eStagePhase::e_fancy)
	{
		// スクリーンエフェクト（ループ再生）
		if (!m_is_not_draw)
		{
			SetEffectActive(22, 31, true);
		}

		EffectScreen(22, 31);
	}
}

void Effect::SetEffectActive(int start, int end, bool is_active)
{
	for (int i = start; i <= end; ++i)
	{
		// 範囲外のエフェクトはスキップ
		if (i < 0 || i >= m_particles.size())
		{
			continue;
		}

		// エフェクトのアクティブ状態を設定
		m_active_effects[i] = is_active;
	}
}

void Effect::EffectOffset(int start, int end, tnl::Vector3& pos)
{
	// キャラの正面向きを取得
	tnl::Vector3 forward = m_mediator->PlayerForward();

	for (int i = start; i <= end; ++i)
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
	// プレイヤーの位置を取得
	tnl::Vector3 pos;

	if (is_game)
	{
		pos = m_mediator->GetPlayerPos();
	}
	else
	{
		pos = m_mediator->GetCinemaPlayerPos();
	}

	EffectOffset(start,end,pos);
}

void Effect::EffectPath(int start,int end,bool is_player)
{
	tnl::Vector3 pos;
	// 進行方向を取得
	tnl::Vector3 direction;

	if (is_player)
	{
		pos = m_mediator->GetPlayerPos();
		direction = m_mediator->PlayerForward();
	}
	else
	{
		pos = m_mediator->GetButterflyPos();
		direction = m_mediator->GetButterflyNextDirection();
	}

	for (int i = start; i <= end; ++i)
	{
		m_particles[i]->start();
		m_particles[i]->setPosition({ pos.x,pos.y + m_offset,pos.z });
		m_particles[i]->setSizeX(5);
		m_particles[i]->setSizeY(5);
		// 方向とは逆に設定
		m_particles[i]->setDiffDirection(-direction);
	}
}

void Effect::EffectButterfly(int id)
{
	tnl::Vector3 pos = m_mediator->GetButterflyPos();

	// 消える瞬間にエフェクトを再生
	if (m_mediator->GetButterflyIsClear())
	{
		// 該当エフェクトを指定
		m_particles[id]->start();
		m_particles[id]->setPosition(pos);
	}
}

void Effect::EffectGimmick(int id)
{
	tnl::Vector3 pos = m_mediator->GetGimmickPos();

	// 該当エフェクトを指定
	m_particles[id]->start();
	m_particles[id]->setPosition(pos);
	m_particles[id]->setTimeScale(1);
}

void Effect::EffectScreen(int start,int end, bool is_game)
{
	tnl::Vector3 pos;

	if (is_game)
	{
		pos = m_mediator->GetGameCameraPos();
	}
	else
	{
		pos = m_mediator->GetCinemaCameraPos();
	}

	// スクリーンエフェクト（ループ再生）
	for (int i = start; i <= end; ++i)
	{
		m_particles[i]->start();
		m_particles[i]->setPosition(pos);
	}
}

