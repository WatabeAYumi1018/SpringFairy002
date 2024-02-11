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

    // �S�p�[�e�B�N�����i�[
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

    // �V�l�}�J�����̎�
    if (m_camera_phase == CameraPhase::eCameraPhase::e_cinema)
    {
        EffectTransCinema();
    }
    // �Q�[���J�����̎�
    else
    {
        EffectTransGame();
    }
}

void Effect::Draw(std::shared_ptr<dxe::Camera> camera)
{
    // �p�[�e�B�N���̕`��J�n
    dxe::Particle::renderBegin();

	for (int i = m_start_id; i <= m_end_id; ++i)
	{
		// �p�[�e�B�N����`��
		m_particles[i]->render(camera);
	}

    // �p�[�e�B�N���̕`��I��
    dxe::Particle::renderEnd();
}

void Effect::EffectOffset(int start, int end)
{
	m_start_id = start;
	m_end_id = end;

	// �I�t�Z�b�g�l
	float offset = 150.0f;

	// �L�����̐��ʌ������擾
	tnl::Vector3 forward = m_mediator->PlayerForward();

	// �v���C���[�̈ʒu���擾
	tnl::Vector3 m_pos = m_mediator->GetPlayerPos();

	for (int i = m_start_id; i <= m_end_id; ++i)
	{
		// �͈͊O�̃G�t�F�N�g�̓X�L�b�v
		if (i < 0 || i >= m_particles.size())
		{
			continue;
		}

		// Bloom�G�t�F�N�g�̏ꍇ
		if (m_mediator->GetIsPlayerBloom())
		{
			m_particles[i]->start();
			m_particles[i]->setPosition({ m_pos.x, m_pos.y + offset,m_pos.z });
			m_particles[i]->setDiffDirection(forward);
		}
		// Dance�G�t�F�N�g�̏ꍇ
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
		// �L�����O�ՃG�t�F�N�g�i���[�v�Đ��j
		if (m_mediator->GetButterflyIsCinemaActive())
		{
			EffectOffset(26, 26);
		}
		// ���̃N���A�G�t�F�N�g�i�P���Đ��j
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

		// �X�N���[���G�t�F�N�g�i���[�v�Đ��j
		EffectOffset(20, 24);
		// �L�����O�ՃG�t�F�N�g�i���[�v�Đ��j
		EffectOffset(26, 26);
	}

	// �M�~�b�N�G�t�F�N�g�i�P���Đ��j
	if (m_mediator->GetGimmickIsCollision())
	{
		EffectOffset(25, 25);
	}

}