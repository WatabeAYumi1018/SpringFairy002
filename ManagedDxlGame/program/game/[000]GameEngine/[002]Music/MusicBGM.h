#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// BGM�N���X�i�Đ��ƒ�~�j
//
/////////////////////////////////////////////////////////////////////////////////////////


class MusicBGM
{

public:

	struct sMusicBGM
	{
		int s_id;
		int s_bgm_hdl = 0;
	};

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	MusicBGM();

	~MusicBGM();

	//-------------------------------------------------------------------------------//

private:

	// BGM�Đ���Ԃ�ǐՂ���t���O
	bool m_is_playing = false; 

	// ���݂̃{�����[��
	float m_current_volume = 100.0f;
	// �ړI�̃{�����[��
	float m_target_volume = 100.0f;
	// �t�F�[�h���x
	float m_fade_speed =10.0f;

		// BGM�̎�ޓǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_bgm_info;
	// BGM�̎�ޏ��i�[�p
	std::vector<MusicBGM::sMusicBGM> m_bgms_info;

	// BGM�p�X�̏��ǂݍ���
	void LoadBGMInfo();

public:

	//----------------------------------�����o�֐�----------------------------------//

	// BGM�̍Đ�
	void Play(int id);

	// BGM�̒�~
	void Stop(int id);

	// �t�F�[�h�C���Đ��J�n
	// tips ... BGM���t�F�[�h�C���Đ�����Ƃ��ɌĂяo���܂�
	void FadeIn(const float delta_time, int id);

	// �t�F�[�h�A�E�g�Đ���~
	// tips ... BGM���t�F�[�h�A�E�g�Đ�����Ƃ��ɌĂяo���܂�
	void FadeOut(const float delta_time, int id);

	// BGM�̉��ʂ��擾���郁�\�b�h
	// tips ... �V�[���`�F���W��BGM�̉��ʂ��擾����Ƃ��ɌĂяo���܂�
	float GetCurrentVolume(int id) 
	{
		return GetVolumeSoundMem2(m_bgms_info[id].s_bgm_hdl);
	}


	//-----------------------------------------------------------------------------//
};
