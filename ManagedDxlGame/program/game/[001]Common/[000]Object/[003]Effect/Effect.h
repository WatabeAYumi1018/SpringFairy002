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

	//-------------------------------------�\����--------------------------------------//

	struct sEffectType
	{
		int s_id;
		std::string s_effect_path;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	Effect() {}
	~Effect();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �I�t�Z�b�g�l
	float m_offset = 150.0f;

	// �X�N���[���G�t�F�N�g�̊������t���O
	bool m_is_screen = false;
	// �`����s��Ȃ��t���O�i���[�v�Đ��Ŗ��t���[���̃X�^�[�g��h�����߁j
	bool m_is_not_draw = false;

	// �J�����t�F�[�Y
	CameraPhase::eCameraPhase m_camera_phase
		= CameraPhase::eCameraPhase::e_cinema;

	// �X�e�[�W�t�F�[�Y
	StagePhase::eStagePhase m_stage_phase
		= StagePhase::eStagePhase::e_flower;

	// �p�[�e�B�N���|�C���^�̃x�N�^�[
	std::vector<std::shared_ptr<dxe::Particle>> m_particles;
	
	// �G�t�F�N�g�^�C�v�̃x�N�^�[
	std::vector<Effect::sEffectType> m_effects_type;
	
	// �G�t�F�N�g��ID�ƃA�N�e�B�u���
	std::unordered_map<int,bool> m_active_effects;

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;
	
	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �V�l�}��ʂ̃G�t�F�N�g����
	void EffectTransCinema();
	// �Q�[����ʂ̃G�t�F�N�g����
	void EffectTransGame();

	// �G�t�F�N�g�̃A�N�e�B�u�ݒ�
	// arg1 ... �J�nID
	// arg2 ... �I��ID
	// arg3 ... �������񊈐����̐ݒ�
	void SetEffectActive(int start, int end, bool is_active);

	// �G�t�F�N�g�̃I�t�Z�b�g�ݒ�
	// arg1 ... �J�nID
	// arg2 ... �I��ID
	// arg3 ... ���W
	void EffectOffset(int start,int end,tnl::Vector3& pos);

	// �v���C���[�A�N�V�����G�t�F�N�g�ݒ�
	// arg1 ... �J�nID
	// arg2 ... �I��ID
	// arg3 ... �Q�[����ʂ��ǂ���(�f�t�H���g�ŃQ�[����ʁBfalse�ŃV�l�}���)
	void EffectPlayerAction(int start, int end,bool is_game = true);

	// �O�ՃG�t�F�N�g�ݒ�
	// arg1 ... �J�nID
	// arg2 ... �I��ID
	// arg3 ... �v���C���[���ǂ���(�f�t�H���g�Ńv���C���[�Bfalse�Œ�)
	void EffectPath(int start, int end, bool is_player = true);

	// ���G�t�F�N�g�ݒ�
	// arg ... �Y��ID
	void EffectButterfly(int id);

	// �M�~�b�N�G�t�F�N�g�ݒ�
	// arg ... �Y��ID
	void EffectGimmick(int id);

	// �X�N���[���G�t�F�N�g�ݒ�
	// arg1 ... �J�nID
	// arg2 ... �I��ID
	// arg3 ... �Q�[����ʂ��ǂ���(�f�t�H���g�ŃQ�[����ʁBfalse�ŃV�l�}���)
	void EffectScreen(int start, int end, bool is_game = true);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �X�N���[���G�t�F�N�g�̊������t���O�̐ݒ�
	void SetIsScreen(bool is_screen) { m_is_screen = is_screen; }

	// ���f�B�G�[�^�̐ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};