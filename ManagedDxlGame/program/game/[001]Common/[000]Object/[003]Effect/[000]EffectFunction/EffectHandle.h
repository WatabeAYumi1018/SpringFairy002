#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../[003]Phase/CameraPhase.h"
#include "../../../[003]Phase/StagePhase.h"
#include "EffectLoad.h"


class Mediator;

class EffectHandle 
{

public:

	EffectHandle();

	~EffectHandle();

private:

	tnl::Vector3 m_game_pos;
	tnl::Vector3 m_cinema_pos;

	CameraPhase::eCameraPhase m_camera_phase 
			= CameraPhase::eCameraPhase::e_cinema;
	
	StagePhase::eStagePhase m_stage_phase 
			= StagePhase::eStagePhase::e_flower;

	std::vector<Effect::sEffectType> m_effects_type;

	std::vector<std::shared_ptr<dxe::Particle>> m_particles;

	// �󋵂ɉ������G�t�F�N�g�̃x�N�^�[�𐶐�
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
	void EffectStocker(int start,int end
						,std::vector<std::shared_ptr<dxe::Particle>>& particles);

	// �V�l�}��ʂ̃G�t�F�N�g�J��
	void EffectTransCinema();

	// �Q�[����ʂ̃G�t�F�N�g�J��
	void EffectTransGame();

	// �e�A�N�e�B�u�G�t�F�N�g�̍��W�␳
	void AttackOffset();


public:

	void Initialize();

	// ���s�G�t�F�N�g�̍X�V
	void Update();

	const tnl::Vector3& GetGamePos() const	{ return m_game_pos; }

	const std::vector<std::shared_ptr<dxe::Particle>>& GetPlayerActionParticles() const
	{
		return m_player_action_particles;
	}

	const std::vector<std::shared_ptr<dxe::Particle>>& GetGimmickParticles() const
	{
		return m_gimmick_particles;
	}

	const std::vector<std::shared_ptr<dxe::Particle>>& GetCharaPathParticles() const
	{
		return m_chara_path_particles;
	}

	const std::vector<std::shared_ptr<dxe::Particle>>& GetScreenParticles() const
	{
		return m_screen_particles;
	}

	const std::vector<std::shared_ptr<dxe::Particle>>& GetEventParticles() const
	{
		return m_event_particles;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
