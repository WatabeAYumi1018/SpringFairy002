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
	// ��̃I�u�W�F�N�g�Ŏ��s����邽�߁A���ڂ̏������h�~
	if (!m_particles.empty()) 
	{
		return;
	}

    m_effects_type = m_mediator->GetEffectLoadInfo();

    // �S�p�[�e�B�N�����i�[
    for (Effect::sEffectType& effect_type : m_effects_type)
    {
        std::shared_ptr<dxe::Particle> particle = nullptr;

        particle = std::make_shared<dxe::Particle>(effect_type.s_effect_path.c_str());

        m_particles.emplace_back(particle);
    }

	for (int i = 0; i < m_particles.size(); ++i) 
	{
		// ������Ԃł͔�A�N�e�B�u
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

	for (size_t i = 0; i < m_particles.size(); ++i)
	{
		// �G�t�F�N�g���A�N�e�B�u�ȏꍇ�̂ݕ`��
		if (m_active_effects[i]) 
		{
			m_particles[i]->render(camera);
		}
	}

    // �p�[�e�B�N���̕`��I��
    dxe::Particle::renderEnd();
}

void Effect::EffectTransCinema()
{
	// �_���X�Ɋ֘A����G�t�F�N�g�Đ�
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
		// �X�N���[���G�t�F�N�g�i���[�v�Đ��j
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
		// �͈͊O�̃G�t�F�N�g�̓X�L�b�v
		if (i < 0 || i >= m_particles.size())
		{
			continue;
		}

		// �G�t�F�N�g�̃A�N�e�B�u��Ԃ�ݒ�
		m_active_effects[i] = is_active;
	}
}

void Effect::EffectOffset(int start, int end, tnl::Vector3& pos)
{
	// �L�����̐��ʌ������擾
	tnl::Vector3 forward = m_mediator->PlayerForward();

	for (int i = start; i <= end; ++i)
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
	// �v���C���[�̈ʒu���擾
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
	// �i�s�������擾
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
		// �����Ƃ͋t�ɐݒ�
		m_particles[i]->setDiffDirection(-direction);
	}
}

void Effect::EffectButterfly(int id)
{
	tnl::Vector3 pos = m_mediator->GetButterflyPos();

	// ������u�ԂɃG�t�F�N�g���Đ�
	if (m_mediator->GetButterflyIsClear())
	{
		// �Y���G�t�F�N�g���w��
		m_particles[id]->start();
		m_particles[id]->setPosition(pos);
	}
}

void Effect::EffectGimmick(int id)
{
	tnl::Vector3 pos = m_mediator->GetGimmickPos();

	// �Y���G�t�F�N�g���w��
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

	// �X�N���[���G�t�F�N�g�i���[�v�Đ��j
	for (int i = start; i <= end; ++i)
	{
		m_particles[i]->start();
		m_particles[i]->setPosition(pos);
	}
}

