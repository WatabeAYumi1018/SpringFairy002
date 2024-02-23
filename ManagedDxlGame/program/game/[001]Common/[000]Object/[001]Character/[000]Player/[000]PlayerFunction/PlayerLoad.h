#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �v���C���[��csv�t�@�C���̓ǂݍ��݃N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class PlayerLoad
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	PlayerLoad();

	~PlayerLoad();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	//-----Player�p�ϐ�-----//

	// ���f��
	int m_model_game_hdl = 0;
	// move�{�[��
	int m_anim_bone_move_game_hdl = 0;
	// bloom�{�[��
	int m_anim_bone_bloom_game_hdl = 0;
	// dance�{�[��
	int m_anim_bone_dance_game_hdl = 0;
	// �e�N�X�`��
	int m_texture_game_hdl = 0;
	
	//----------------------//


	//--CinemaPlayer�p�ϐ�--//

	// ���f��
	int m_model_cinema_hdl = 0;
	// idle�{�[��
	int m_anim_bone_idle_cinema_hdl = 0;
	// dance�{�[��
	int m_anim_bone_dance_cinema_hdl = 0;
	// �e�N�X�`��
	int m_texture_cinema_hdl = 0;

	//----------------------//


	//-------���p�ϐ�-------//

	// �ړ����x
	float m_move_speed = 0;
	// �ړ���]���x
	float m_move_rot = 0;

	//----------------------//


	//----------------------//
	// ���ȉ��p�����[�^�ɂ��Ă͌��ݎg�p���Ă��܂���
	// �@����̊g�����l���Ďc���Ă܂��B(�����͑�������ς݂Ŏg�p�ӏ���͍���)
	 
	// �󋵂ɂ��ړ����x�ω�
	float m_move_change_speed = 0;

	// ���Ԃ�̈ړ����x
	float m_salto_move_speed = 0;
	// ���Ԃ�̉�]���x
	float m_salto_rot = 0;
	// ���Ԃ�̋O�����a
	float m_salto_radius = 0;
	// ���Ԃ�̏��v����
	float m_salto_total_time = 6.0f;

	// ���[���̉�]���x
	float m_rolling_rot = 10;
	// ���̎��̉�]���x
	float m_figure_eight_rot = 10;

	//----------------------//

	// �v���C���[�̈ړ����ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<float>> m_csv_move;
	// �v���C���[�̃��f�����ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<std::string>> m_csv_model;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �v���C���[�̃p�����[�^���ǂݎ���p�icsv�t�@�C���j
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadPlayerMoveInfo();

	// �v���C���[�̃��f�����ǂݎ���p�icsv�t�@�C���j
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadPlayerModelInfo();

	//---------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// �Q�[���v���C���[�̃��f���n���h���擾
	int GetModelGameHdl() const { return m_model_game_hdl; }
	
	// �V�l�}�v���C���[�̃��f���n���h���擾
	int GetModelCinemaHdl() const { return m_model_cinema_hdl; }
	
	// �Q�[���v���C���[��move�{�[���n���h���擾
	int GetAnimBoneMoveGameHdl() const { return m_anim_bone_move_game_hdl; }
	
	// �Q�[���v���C���[��bloom�{�[���n���h���擾
	int GetAnimBoneBloomGameHdl() const { return m_anim_bone_bloom_game_hdl; }
	
	// �Q�[���v���C���[��dance�{�[���n���h���擾
	int GetAnimBoneDanceGameHdl() const { return m_anim_bone_dance_game_hdl; }
	
	// �V�l�}�v���C���[��idle�{�[���n���h���擾
	int GetAnimBoneIdleCinemaHdl() const { return m_anim_bone_idle_cinema_hdl; }
	
	// �V�l�}�v���C���[��dance�{�[���n���h���擾
	int GetAnimBoneDanceCinemaHdl() const { return m_anim_bone_dance_cinema_hdl; }

	// �ړ����x�擾
	float GetMoveSpeed() const { return m_move_speed; }

	// �ړ���]���x�擾
	float GetMoveRot() const { return m_move_rot; }

	//----------------------//
	// ���ȉ��p�����[�^�ɂ��Ă͌��ݎg�p���Ă��܂���
	// �@����̊g�����l���Ďc���Ă܂��B(�����͑�������ς݂Ŏg�p�ӏ���͍���)

	// ���Ԃ�̑����Ԏ擾
	float GetSaltoTotalTime() const { return m_salto_total_time; }
	// ���Ԃ�̋O�����a�擾
	float GetSaltoRadius() const { return m_salto_radius; }
	// ���Ԃ�̉�]���x�擾
	float GetSaltoMoveSpeed() const { return m_salto_move_speed; }

	//----------------------//

	//---------------------------------------------------------------------------------//
};