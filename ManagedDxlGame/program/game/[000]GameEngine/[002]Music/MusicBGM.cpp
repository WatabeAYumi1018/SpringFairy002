#include "MusicBGM.h"



MusicBGM::MusicBGM()
{
	LoadBGMInfo();
}

MusicBGM::~MusicBGM()
{
	for (int i = 1; i < m_bgms_info.size(); ++i)
	{
		DeleteSoundMem(m_bgms_info[i].s_bgm_hdl);
	}
}

void MusicBGM::Play()
{
	for (int i = 1; i < m_bgms_info.size(); ++i)
	{
		PlaySoundMem(m_bgms_info[i].s_bgm_hdl, DX_PLAYTYPE_LOOP);
	}
}

void MusicBGM::Stop()
{
	for (int i = 1; i < m_bgms_info.size(); ++i)
	{
		StopSoundMem(m_bgms_info[i].s_bgm_hdl);
	}
}

void MusicBGM::LoadBGMInfo()
{
	// BGM�̎�ޓǂݎ���p�icsv�t�@�C���j
	m_csv_bgm_info = tnl::LoadCsv<tnl::CsvCell>("csv/music/bgm.csv");

	// �}�b�v�^�C���̑������擾
	int max_num = m_csv_bgm_info.size();

	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	for (int y = 1; y < max_num; ++y)
	{
		m_bgms_info[y].s_id = m_csv_bgm_info[y][0].getInt();

		m_bgms_info[y].s_bgm_hdl = LoadSoundMem(m_csv_bgm_info[y][1].getString().c_str());

		m_bgms_info.emplace_back(m_bgms_info[y]);
	}
}
