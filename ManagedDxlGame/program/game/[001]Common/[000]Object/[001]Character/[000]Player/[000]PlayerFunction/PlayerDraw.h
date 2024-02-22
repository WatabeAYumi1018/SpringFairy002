#pragma once
#include "../../../../../../library/tnl_sequence.h"
#include "../../Character.h"

class Mediator;

/////////////////////////////////////////////////////////////////////////////////////////
// 
// �v���C���[�̃A�j���[�V�����`����Ǘ�����N���X(�Q�[���A�V�l�}����)
//
/////////////////////////////////////////////////////////////////////////////////////////


class PlayerDraw
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	PlayerDraw() {}

	~PlayerDraw();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���f���n���h��
	// �n���h�������ꂼ�ꕪ���Ȃ��Ƌ����G���[�ɂȂ�

	//-----Player�p�ϐ�-----//

	int m_model_game_hdl = 0;
	// move�{�[��
	int m_anim_bone_move_game_hdl = 0;
	// bloom�{�[��
	int m_anim_bone_bloom_game_hdl = 0;
	// dance�{�[��
	int m_anim_bone_dance_game_hdl = 0;

	//----------------------//

	//--CinemaPlayer�p�ϐ�--//

	int m_model_cinema_hdl = 0;
	// idle�{�[��
	int m_anim_bone_idle_cinema_hdl = 0;
	int m_anim_bone_dance_cinema_hdl = 0;

	//----------------------//


	//-------���p�ϐ�-------//

	// �e��A�j���[�V�����̃C���f�b�N�X�ԍ�
	int m_anim_idle_index = 0;
	int m_anim_move_index = 0;
	int m_anim_bloom_index = 0;
	int m_anim_dance_index = 0;

	// �e��o�ߎ���
	float m_elapsed_time_idle = 0;
	float m_elapsed_time_move = 0;
	float m_elapsed_time_bloom = 0;
	float m_elapsed_time_dance = 0;

	// �e��Đ����Ԃ̃J�E���g
	float m_time_count_idle = 0;
	float m_time_count_move = 0;
	float m_time_count_bloom = 0;
	float m_time_count_dance = 0;

	// �A�j���[�V�����̑��x
	float m_anim_speed = 10;
	// �u�����h����
	float m_blend_timer = 0;
	// �u�����h������
	float m_blend_total_time = 1.0f;
	
	// �u���[���U���t���O
	bool m_is_bloom = false;
	// �_���X�U���t���O
	bool m_is_dance = false;

	//----------------------//


	//--CinemaPlayer�p�ϐ�--//

	// �{�[���̃f�^�b�`�ݒ�t���O(�V�l�}�v���C���[�p)
	bool m_is_touch_idle = false;
	bool m_is_touch_dance = false;

	//----------------------//

	// �L�����N�^�[�̌���
	Character::eDirection m_direction
		= Character::eDirection::e_none;
	
	// �X�e�[�W�̃t�F�[�Y
	StagePhase::eStagePhase m_stage_phase 
		= StagePhase::eStagePhase::e_flower;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(PlayerDraw, &PlayerDraw::SeqMove);

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �A�j���[�V�����̃u�����h����
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... ���f���n���h��
	// arg3 ... ���݂̃A�j���[�V�����̃C���f�b�N�X�ԍ�
	// arg4 ... ���̃A�j���[�V�����̃C���f�b�N�X�ԍ�
	// tips ... �A�j���[�V�����̃u�����h�������s��
	//			Dxlib��MV1SetAttachAnimBlendRate�֐������ɏ�����
	void AnimBlend(const float delta_time,int model_hdl
					, int current_anim_index, int next_anim_index);

	// �A�j���[�V�����̃A�^�b�`����
	// arg1 ... ���f���n���h��
	// arg2 ... �A�j���[�V�����̃C���f�b�N�X�ԍ�
	// arg3 ... �A�j���[�V�������A�^�b�`����{�[���̃n���h��
	// arg4 ... �A�j���[�V�����̍Đ����ԃJ�E���g
	// Dxlib,MV1AttachAnim, MV1GetAttachAnimTotalTime�֐������ɏ�����
	// ��anim_index�Atime_count�̂ݎQ�Ɠn��
	void AnimAttach(int model_hdl, int& anim_index
					, int anim_bone_hdl, float& time_count);

	// move ���[�v�Đ��̎��Ԑݒ�
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... ���f���n���h��
	void AnimMove(const float delta_time, int model_hdl);

	// bloom �P���Đ��̎��Ԑݒ�
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void AnimBloom(const float delta_time);

	// dance �P���Đ��̎��Ԑݒ�
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... ���f���n���h��
	void AnimDance(const float delta_time, int model_hdl);

	// idle ���[�v�Đ��̎��Ԑݒ�@
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void AnimIdle(const float delta_time);

	// �ړ����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqMove(const float delta_time);
	
	// �u���[�����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqBloom(const float delta_time);
	
	// move�A�j���[�V�����ւ̑J��
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqBloomToMove(const float delta_time);
	
	// �_���X���
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqDance(const float delta_time);

	// dance�A�j���[�V�����ւ̑J��
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqDanceToMove(const float delta_time);

public:

	void Initialize();
	
	void Update(const float delta_time);
	
	void Draw();
	

	//--CinemaPlayer�p�֐�--//

	// �V�l�}�J�����p��idle�A�j���[�V����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void CinemaAnimIdle(const float delta_time);

	// �V�l�}�J�����p��dance�A�j���[�V����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void CinemaAnimDance(const float delta_time);

	//----------------------//

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �_���X�ɂ��o�ߎ��Ԃ̐ݒ�i�f�t�H���g0�̂��߁A�����͊�{��Ŏg�p�j
	// arg ... �o�ߎ���
	// tips ...�_���X���Ԃ̃��Z�b�g�̂��߂Ɏg�p
	// ���Z�b�^�[�Ȃ̂Ɉ������f�t�H���g�l�����͍̂D�܂����̂���V��
	void SetElapsedTimeDance(float elapsed_time_dance = 0) 
	{ 
		m_elapsed_time_dance = elapsed_time_dance; 
	}

	// bloom�t���O���擾
	bool GetIsBloom() const { return m_is_bloom; }
	
	// dance�t���O���擾
	bool GetIsDance() const { return m_is_dance; }

	// ���f�B�G�[�^�̃|�C���^�ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};