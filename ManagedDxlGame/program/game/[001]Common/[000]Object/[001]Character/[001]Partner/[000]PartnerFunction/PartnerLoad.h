#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �p�[�g�i�[��csv�t�@�C���̓ǂݍ��݃N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class PartnerLoad
{

public:

	PartnerLoad();

	~PartnerLoad();

private:

	// ���f��
	int m_model_hdl = 0;
	// idle�{�[��
	int m_anim_bone_idle_cinema_hdl = 0;
	// move�{�[��
	int m_anim_bone_move_game_hdl = 0;
	// �e�N�X�`��
	int m_texture_game_hdl = 0;

	// �p�[�g�i�[�̈ړ����ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<std::string>> m_csv_model;

	void LoadPartnerModelInfo();

public:

	int GetModelGameHdl() const { return m_model_hdl; }

	int GetAnimBoneIdleHdl() const { return m_anim_bone_idle_cinema_hdl; }

	int GetAnimBoneMoveGameHdl() const { return m_anim_bone_move_game_hdl; }
};