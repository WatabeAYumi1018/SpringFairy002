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
    // �I�t�Z�b�g�l
    float offset = 150.0f;

    // �L�����̐��ʌ������擾
    tnl::Vector3 forward = m_mediator->PlayerForward();

    // �v���C���[�̈ʒu���擾
    m_pos = m_mediator->GetPlayerPos();

    // �U���{�^���̃t���O�������Ă�������Đ�
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
    // �p�[�e�B�N���̕`��J�n
    dxe::Particle::renderBegin();

    // �p�[�e�B�N����`��
    for (std::shared_ptr<dxe::Particle>& particle : m_particles)
    {
        particle->render(camera);
    }
    
    // �p�[�e�B�N���̕`��I��
    dxe::Particle::renderEnd();
}

bool Effect::ContainsAttack(const std::string& str)
{
    // npos : �����񂪌�����Ȃ������ꍇ�̕Ԃ�l
    return str.find("attack") != std::string::npos;
}

