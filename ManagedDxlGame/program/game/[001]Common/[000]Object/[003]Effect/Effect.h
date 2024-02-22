#pragma once
#include "../../[003]Phase/CameraPhase.h"
#include "../../[003]Phase/StagePhase.h"
#include "../Object.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// �G�t�F�N�g�p�[�e�B�N���̒�`�ƍX�V�`�揈�����s���N���X
//
///////////////////////////////////////////////////////////////////////////


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

	int m_start_id = 0;
	int m_end_id = 0;

	// �I�t�Z�b�g�l
	float m_offset = 150.0f;

	bool m_is_screen = false;
	bool m_is_not_draw = false;

	CameraPhase::eCameraPhase m_camera_phase
		= CameraPhase::eCameraPhase::e_cinema;

	StagePhase::eStagePhase m_stage_phase
		= StagePhase::eStagePhase::e_flower;

	std::vector<std::shared_ptr<dxe::Particle>> m_particles;

	std::vector<Effect::sEffectType> m_effects_type;
	// �G�t�F�N�g�̃A�N�e�B�u���
	std::unordered_map<int,bool> m_active_effects;

	std::shared_ptr<Mediator> m_mediator = nullptr;
	
	// �V�l�}��ʂ̃G�t�F�N�g����
	void EffectTransCinema();
	// �Q�[����ʂ̃G�t�F�N�g����
	void EffectTransGame();

	// �G�t�F�N�g�̃A�N�e�B�u�ݒ�
	void SetEffectActive(int start, int end, bool is_active);
	// �G�t�F�N�g�̃I�t�Z�b�g�ݒ�
	void EffectOffset(int start,int end,tnl::Vector3& pos);
	// �v���C���[�A�N�V�����G�t�F�N�g�ݒ�
	void EffectPlayerAction(int start, int end,bool is_game = true);
	// �O�ՃG�t�F�N�g�ݒ�
	void EffectPath(int start, int end, bool is_player = true);
	// ���G�t�F�N�g�ݒ�
	void EffectButterfly(int id);
	// �M�~�b�N�G�t�F�N�g�ݒ�
	void EffectGimmick(int id);
	// �X�N���[���G�t�F�N�g�ݒ�
	void EffectScreen(int start, int end, bool is_game = true);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetIsScreen(bool is_screen) { m_is_screen = is_screen; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};