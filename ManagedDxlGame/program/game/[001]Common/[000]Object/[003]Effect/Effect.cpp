#include "../../[002]Mediator/Mediator.h"
#include "Effect.h"


Effect::Effect()
{

}

Effect::~Effect()
{
	
}

void Effect::Initialize()
{
    m_mediator->InitializeEffectHandle();
}

void Effect::Update(float delta_time)
{
    m_mediator->UpdateEffectHandle();

    GetActiveParticle();
}

void Effect::Draw(std::shared_ptr<dxe::Camera> camera)
{
    // パーティクルの描画開始
    dxe::Particle::renderBegin();

    ActiveEffect(camera, m_player_action_particles);

    //ActiveEffect(camera, m_gimmick_particles);

    //ActiveEffect(camera, m_chara_path_particles);

    //ActiveEffect(camera, m_screen_particles);

    //ActiveEffect(camera, m_event_particles);
    
    // パーティクルの描画終了
    dxe::Particle::renderEnd();
}

void Effect::GetActiveParticle()
{
    m_player_action_particles = m_mediator->GetEffectPlayerActionParticles();

    m_gimmick_particles = m_mediator->GetEffectGimmickParticles();

    m_chara_path_particles = m_mediator->GetEffectCharaPathParticles();

    m_screen_particles = m_mediator->GetEffectScreenParticles();

    m_event_particles = m_mediator->GetEffectEventParticles();
}

void Effect::ActiveEffect(std::shared_ptr<dxe::Camera> camera
                          ,std::vector<std::shared_ptr<dxe::Particle>>& particles)
{
    // ベクターが空じゃない場合に描画
    if (!particles.empty())
    {
        for (std::shared_ptr<dxe::Particle>& particle : particles)
        {
            particle->render(camera);
        }
    }
}
