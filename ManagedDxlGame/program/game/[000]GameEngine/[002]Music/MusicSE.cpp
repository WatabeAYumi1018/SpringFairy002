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

void MusicSE::Play()
{
	for (int i = 0; i < m_ses_info.size(); ++i)
	{
		PlaySoundMem(m_ses_info[i].s_se_hdl, DX_PLAYTYPE_BACK);
	}
}

void MusicSE::Stop()
{
	for (int i = 0; i < m_ses_info.size(); ++i)
	{
		StopSoundMem(m_ses_info[i].s_se_hdl);
	}
}

void MusicSE::LoadSEInfo()
{
	// SE�̎�ޓǂݎ���p�icsv�t�@�C���j
	m_csv_se_info = tnl::LoadCsv<tnl::CsvCell>("csv/music/se.csv");

	// �}�b�v�^�C���̑������擾
	int max_num = m_csv_se_info.size();

	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	for (int y = 1; y < max_num; ++y)
	{
		m_ses_info[y].s_id = m_csv_se_info[y][0].getInt();

		m_ses_info[y].s_se_hdl = LoadSoundMem(m_csv_se_info[y][1].getString().c_str());
	}
}