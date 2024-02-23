#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


///////////////////////////////////////////////////////////////////////////
//
// �M�~�b�N��csv�t�@�C���̓ǂݍ��݃N���X
//
///////////////////////////////////////////////////////////////////////////


class GimmickLoad
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	GimmickLoad();
	~GimmickLoad();

	//---------------------------------------------------------------------------------//

private:
	
	//-----------------------------------�����o�ϐ�------------------------------------//

	// �@���Ԃ̃M�~�b�N���f��(�ÓI)
	// csv�t�@�C���̏��
	std::vector<std::vector<tnl::CsvCell>> m_csv_ground_flowers;
	// �n��̑��Ԃ̃M�~�b�N���f��
	std::vector<Gimmick::sGimmickTypeInfo> m_ground_flowers;
	
	// �A���؂̃M�~�b�N���f��(�ÓI)
	// csv�t�@�C���̏��
	std::vector<std::vector<tnl::CsvCell>> m_csv_woods;
	// ���؂̃M�~�b�N���f��
	std::vector<Gimmick::sGimmickTypeInfo> m_woods;
	
	// �B�����Ԃ̃M�~�b�N���f��(���I)
	// csv�t�@�C���̏��
	std::vector<std::vector<tnl::CsvCell>> m_csv_sky_flowers;
	// �����Ԃ̃M�~�b�N���f��
	std::vector<Gimmick::sGimmickTypeInfo> m_sky_flowers;
	
	// �C���̃M�~�b�N���f��(���I)
	// csv�t�@�C���̏��
	std::vector<std::vector<tnl::CsvCell>> m_csv_butterflys;
	// ���̃M�~�b�N���f��
	std::vector<Gimmick::sGimmickTypeInfo> m_butterflys;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ���f���̏��ǂݍ���
	// arg1 ... csv�t�@�C���̃x�N�^�[
	// arg2 ... �M�~�b�N�̏��
	void LoadGimmickTypeInfo(std::vector<std::vector<tnl::CsvCell>>& csv_gimmick
							 ,std::vector<Gimmick::sGimmickTypeInfo>& gimmicks);

	//---------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// �M�~�b�N�^�C�v�̎擾
	// arg ... �M�~�b�N�̎��
	// ���M�~�b�N�^�C�v�ɂ���ĕԂ��x�N�^�[���قȂ鏈���̂��߁Acpp�ɂĎ���
	const std::vector<Gimmick::sGimmickTypeInfo>& GetGimmicksType(Gimmick::eGimmickType type) const;

	//---------------------------------------------------------------------------------//
};
