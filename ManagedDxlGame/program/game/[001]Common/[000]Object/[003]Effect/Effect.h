#pragma once
#include "../Object.h"

class Mediator;


class Effect : public Object
{

public:

	struct sEffectType
	{
		int s_id;
		std::string s_effect_path;
	};

	Effect();

	~Effect();


private:

	// �v���C���[�̃A�N�V�����G�t�F�N�g
	std::vector<std::shared_ptr<dxe::Particle>> m_player_action_particles;
	// �M�~�b�N�G�t�F�N�g
	std::vector<std::shared_ptr<dxe::Particle>> m_gimmick_particles;
	// �L�����N�^�[�̋O���G�t�F�N�g
	std::vector<std::shared_ptr<dxe::Particle>> m_chara_path_particles;
	// �X�N���[���G�t�F�N�g
	std::vector<std::shared_ptr<dxe::Particle>> m_screen_particles;
	// �C�x���g�G�t�F�N�g
	std::vector<std::shared_ptr<dxe::Particle>> m_event_particles;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �e�A�N�e�B�u�G�t�F�N�g�̎擾
	void GetActiveParticle();

	// �A�N�e�B�u�G�t�F�N�g�̃����_�[����
	void ActiveEffect(std::shared_ptr<dxe::Camera> camera
					 , std::vector<std::shared_ptr<dxe::Particle>>& particles);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};