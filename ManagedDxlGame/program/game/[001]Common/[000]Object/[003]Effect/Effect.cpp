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
	// �Q�[���̃t�F�[�Y�����擾
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

void Effect::EffectOffset(tnl::Vector3& pos, tnl::Vector3& forward)
{
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
			m_particles[i]->setPosition({ pos.x, pos.y + m_offset,pos.z });
			m_particles[i]->setDiffDirection(forward);
			// �A�j���[�V�����ƃG�t�F�N�g�̍Đ����Ԓ���
			m_particles[i]->setTimeScale(2);
		}

		// Dance�G�t�F�N�g�̏ꍇ
		if (m_mediator->GetIsPlayerDance()
			|| m_mediator->GetCinemaPlayerIsDance())
		{
			m_particles[i]->start();
			m_particles[i]->setPosition({ pos.x, pos.y + m_offset,pos.z });
			// �A�j���[�V�����ƃG�t�F�N�g�̍Đ����Ԓ���
			m_particles[i]->setTimeScale(1.5f);
		}
	}
}

void Effect::EffectPlayerAction(int start, int end,bool is_game)
{
	m_start_id = start;
	m_end_id = end;

	// �v���C���[�̈ʒu���擾
	tnl::Vector3 pos;
	// �L�����̐��ʌ������擾
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
		// �i�s�������擾
		direction = m_mediator->GetButterflyNextDirection();
	}

	m_particles[36]->start();
	m_particles[36]->setPosition(pos);
	// �����Ƃ͋t�ɐݒ�
	m_particles[36]->setDiffDirection(-direction);
}

void Effect::EffectButterfly()
{
	tnl::Vector3 pos = m_mediator->GetButterflyPos();

	// ������u�ԂɃG�t�F�N�g���Đ�
	if (m_mediator->GetButterflyIsClear())
	{
		// �Y���G�t�F�N�g���w��
		m_particles[19]->start();
		m_particles[19]->setPosition(pos);
		// �A�j���[�V�����ƃG�t�F�N�g�̍Đ����Ԓ���
		m_particles[19]->setTimeScale(1.5f);
	}
}

void Effect::EffectGimmick()
{
	tnl::Vector3 pos = m_mediator->GetGimmickPos();

		// �M�~�b�N�G�t�F�N�g�i�P���Đ��j
	if (m_mediator->GetGimmickIsCollision())
	{
		// �Y���G�t�F�N�g���w��
		m_particles[39]->start();
		m_particles[39]->setPosition(pos);
	}
}

void Effect::EffectScreen(int start,int end)
{
	// �X�N���[���G�t�F�N�g�i���[�v�Đ��j
	for (int i = start; i <= end; ++i)
	{
		m_particles[i]->start();
	}
}

void Effect::EffectTransCinema()
{
	// �_���X�Ɋ֘A����G�t�F�N�g�Đ�
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
		// �L�����O�ՃG�t�F�N�g�i���[�v�Đ��j
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
		// �L�����O�ՃG�t�F�N�g�i���[�v�Đ��j
		EffectPath();
		// �X�N���[���G�t�F�N�g�i���[�v�Đ��j
		EffectScreen(16, 18);
		EffectScreen(25, 34);
	}
}