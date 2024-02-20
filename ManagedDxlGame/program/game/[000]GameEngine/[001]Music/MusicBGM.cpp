#include "MusicBGM.h"


MusicBGM::MusicBGM()
{
	LoadBGMInfo();
}

MusicBGM::~MusicBGM()
{
	for (int i = 0; i < m_bgms_info.size(); ++i)
	{
		DeleteSoundMem(m_bgms_info[i].s_bgm_hdl);
	}
}

void MusicBGM::Play(int id)
{
	if (!m_is_playing)
	{
		m_is_playing = true;

		// �������ʂ�ݒ�
		ChangeVolumeSoundMem(m_current_volume, m_bgms_info[id].s_bgm_hdl); 

		PlaySoundMem(m_bgms_info[id].s_bgm_hdl, DX_PLAYTYPE_LOOP);

	}
}

void MusicBGM::Stop(int id)
{
	if (m_is_playing)
	{
		m_is_playing = false;

		StopSoundMem(m_bgms_info[id].s_bgm_hdl);
	}
}

void MusicBGM::LoadBGMInfo()
{
	// BGM�̎�ޓǂݎ���p�icsv�t�@�C���j
	m_csv_bgm_info = tnl::LoadCsv<tnl::CsvCell>("csv/music/bgm.csv");

	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	for (int y = 1; y < m_csv_bgm_info.size(); ++y)
	{
		MusicBGM::sMusicBGM bgm_info;

		bgm_info.s_id = m_csv_bgm_info[y][0].getInt();

		bgm_info.s_bgm_hdl = LoadSoundMem(m_csv_bgm_info[y][1].getString().c_str());

		m_bgms_info.emplace_back(bgm_info);
	}
}

// �t�F�[�h�C��
void MusicBGM::FadeIn(const float delta_time, int id)
{
	// �Đ��J�n
	Play(id); 
	// ���݂̉��ʂ�ύX
	m_current_volume += m_fade_speed * delta_time;

	if (m_current_volume >= m_target_volume)
	{
		m_current_volume = m_target_volume;

		m_is_playing = true;
	}
}

// �t�F�[�h�A�E�g
void MusicBGM::FadeOut(const float delta_time, int id)
{
	if (m_is_playing)
	{
		// �ڕW����
		m_target_volume = 0; 
		// ���݂̉��ʂ�ύX
		m_current_volume -= m_fade_speed * delta_time;

		if (m_current_volume <= m_target_volume)
		{
			// �Đ���~
			Stop(id); 
		}
	}
}
