#pragma once
#include "../Butterfly.h"


class ButterflyLoad
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	ButterflyLoad();
	~ButterflyLoad();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	//�@���f���n���h��
	int m_model_hdl = 0;
	
	//�@�e�N�X�`���n���h��
	int m_texture_hdl = 0;
	
	// �e�N�X�`���n���h��(tip)
	// �������\���̂��߂̃e�N�X�`��
	// ����ł�3D���f���̒m���s���ɂ��g�����Ȃ��Ă��܂���
	int m_texture_tip_hdl = 0;
	
	// �e�N�X�`���n���h��(mask)
	// �������\���̂��߂̃e�N�X�`��
	// ����ł�3D���f���̒m���s���ɂ��g�����Ȃ��Ă��܂���
	int m_tecxture_mask_hdl = 0;

	// ���f�����ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_model_info;

	// �e��p�����[�^�̏��ǂݎ���p(csv�t�@�C��)
	std::vector<std::vector<tnl::CsvCell>> m_csv_parameters;

	// �e��p�����[�^
	std::vector<Butterfly::sButterflyParameter> m_parameters;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ���f�����ǂݎ���p�icsv�t�@�C���j
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadModelInfo();

	// �p�����[�^���ǂݎ���p�icsv�t�@�C���j
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadParameter();

	//---------------------------------------------------------------------------------//
	
	
	//----------------------------------Setter&Getter----------------------------------//

public:

	// ���f���n���h�����擾
	int GetModelHdl() const { return m_model_hdl; }

	// �e��p�����[�^���擾
	const std::vector<Butterfly::sButterflyParameter>& GetParameters() const
	{
		return m_parameters; 
	}
	
	//---------------------------------------------------------------------------------//
};