#include "../../[002]Mediator/Mediator.h"
#include "Effect.h"


Effect::Effect()
{

}

Effect::~Effect()
{
    m_effect_types.clear();

    for (std::shared_ptr<dxe::Particle>& particle : m_particles)
    {
        particle.reset();
    }

    m_particles.clear();
}

void Effect::Initialize()
{
    m_effect_types = m_mediator->GetEffectLoadInfo();

    for (sEffectType& effect_type : m_effect_types)
    {
        std::shared_ptr<dxe::Particle> particle = nullptr;

        particle = std::make_shared<dxe::Particle>(effect_type.s_effect_path.c_str());
    
        m_particles.emplace_back(particle);
    }
}

void Effect::Update(float delta_time)
{
    // オフセット値
    float offset = 150.0f;

    // キャラの正面向きを取得
    tnl::Vector3 forward = m_mediator->PlayerForward();

    // プレイヤーの位置を取得
    m_pos = m_mediator->GetPlayerPos();

    // 攻撃ボタンのフラグが立っていたら一回再生
    for (sEffectType& effect_type : m_effect_types)
    {
        if (ContainsAttack(effect_type.s_effect_path)
            && m_mediator->GetIsPlayerBloom())
        {
            m_particles[effect_type.s_id]->start();
            m_particles[effect_type.s_id]->setPosition({ m_pos.x, m_pos.y + offset,m_pos.z });
            m_particles[effect_type.s_id]->setDiffDirection(forward);
        }
      //  else
      //  {
    		//m_particles[effect_type.s_id]->setPosition(m_pos);
      //  }
    }
}

void Effect::Draw(std::shared_ptr<dxe::Camera> camera)
{
    // パーティクルの描画開始
    dxe::Particle::renderBegin();

    // パーティクルを描画
    for (std::shared_ptr<dxe::Particle>& particle : m_particles)
    {
        particle->render(camera);
    }
    
    // パーティクルの描画終了
    dxe::Particle::renderEnd();
}

bool Effect::ContainsAttack(const std::string& str)
{
    // npos : 文字列が見つからなかった場合の返り値
    return str.find("attack") != std::string::npos;
}

