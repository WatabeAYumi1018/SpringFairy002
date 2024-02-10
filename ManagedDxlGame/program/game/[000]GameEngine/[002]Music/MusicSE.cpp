#include "MusicSE.h"


MusicSE::MusicSE()
{
	LoadSEInfo();
}

MusicSE::~MusicSE()
{
	for (int i = 0; i < m_ses_info.size(); ++i)
	{
		DeleteSoundMem(m_ses_info[i].s_se_hdl);
	}
}

void MusicSE::Play(int id)
{
	if (!m_is_playing)
	{
		m_is_playing = true;

		if (id != 0)
		{
			// �������ʂ�ݒ�
			ChangeVolumeSoundMem(m_current_volume, m_ses_info[id].s_se_hdl);
		}

		PlaySoundMem(m_ses_info[id].s_se_hdl, DX_PLAYTYPE_BACK);
	}
}

void MusicSE::Stop(int id)
{
	if (m_is_playing)
	{
		m_is_playing = false;

		StopSoundMem(m_ses_info[id].s_se_hdl);
	}
}

void MusicSE::LoadSEInfo()
{
	// SE�̎�ޓǂݎ���p�icsv�t�@�C���j
	m_csv_se_info = tnl::LoadCsv<tnl::CsvCell>("csv/music/se.csv");

	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	for (int y = 1; y < m_csv_se_info.size(); ++y)
	{
		MusicSE::sMusicSE se_info;

		se_info.s_id = m_csv_se_info[y][0].getInt();

		se_info.s_se_hdl = LoadSoundMem(m_csv_se_info[y][1].getString().c_str());

		m_ses_info.emplace_back(se_info);
	}
}