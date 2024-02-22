#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../CinemaBack.h"
#include "../SkyBox.h"

/////////////////////////////////////////////////////////////////////////////////////////
// 
// �w�i�摜csv�t�@�C���̓ǂݍ���(�V�l�}�w�i�摜�A�X�J�C�{�b�N�X�摜)
//
/////////////////////////////////////////////////////////////////////////////////////////


class BackLoad
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	BackLoad();

	~BackLoad();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �V�l�}�w�i�摜�̓ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_cinemaBack_info;
	// �V�l�}�w�i�摜�f�[�^���i�[
	std::vector<CinemaBack::sCinemaBackInfo> m_cinemaBack_info;

	// �X�J�C�{�b�N�X�摜�̓ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_skyBox_info;
	// �X�J�C�{�b�N�X�摜�f�[�^���i�[
	std::vector<SkyBox::sSkyBoxInfo> m_skyBox_info;

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �V�l�}�w�i�摜�̓ǂݎ��
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadCinemaGraphInfo();

	// �X�J�C�{�b�N�X�摜�̓ǂݎ��
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadSkyBoxInfo();

	//---------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// �V�l�}�w�i�摜�f�[�^���擾
	const std::vector<CinemaBack::sCinemaBackInfo>& GetCinemaGraphInfo() const
	{
		return m_cinemaBack_info;
	}

	// �X�J�C�{�b�N�X�摜�f�[�^���擾
	const std::vector<SkyBox::sSkyBoxInfo>& GetSkyGraphInfo() const
	{
		return m_skyBox_info;
	}

	//--------------------------------------------------------------------------------//
};