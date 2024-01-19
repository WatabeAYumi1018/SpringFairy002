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
	m_pos = m_mediator->GetPlayerPos();

    // �L�����̐��ʌ������擾
    tnl::Vector3 forward = m_mediator->PlayerForward();

    // �I�t�Z�b�g�l
    float offset = 100.0f;

    // ���ʕ����ɃI�t�Z�b�g���������V�����ʒu���v�Z
    m_pos = m_pos + forward * offset;

    m_pos.y += offset;

    // �U���{�^���̃t���O�������Ă�������Đ�
    for (sEffectType& effect_type : m_effect_types)
    {
        if (ContainsAttack(effect_type.s_effect_path)
            && m_mediator->GetIsPlayerAttack())
        {
            m_particles[effect_type.s_id]->start();

            m_particles[effect_type.s_id]->setPosition(m_pos);
        }
      //  else
      //  {
    		//m_particles[effect_type.s_id]->setPosition(m_pos);
      //  }
    }
}

void Effect::Draw(std::shared_ptr<GameCamera> gameCamera)
{
    // �p�[�e�B�N���̕`��J�n
    dxe::DirectXRenderBegin();

    // �p�[�e�B�N����`��
    for (std::shared_ptr<dxe::Particle>& particle : m_particles)
    {
        particle->render(gameCamera);
    }
    
    // �p�[�e�B�N���̕`��I��
    dxe::DirectXRenderEnd();
}

bool Effect::ContainsAttack(const std::string& str)
{
    // npos : �����񂪌�����Ȃ������ꍇ�̕Ԃ�l
    return str.find("attack") != std::string::npos;
}

