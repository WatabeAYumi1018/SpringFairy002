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
			// 初期音量を設定
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
	// SEの種類読み取り専用（csvファイル）
	m_csv_se_info = tnl::LoadCsv<tnl::CsvCell>("csv/music/se.csv");

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < m_csv_se_info.size(); ++y)
	{
		MusicSE::sMusicSE se_info;

		se_info.s_id = m_csv_se_info[y][0].getInt();

		se_info.s_se_hdl = LoadSoundMem(m_csv_se_info[y][1].getString().c_str());

		m_ses_info.emplace_back(se_info);
	}
}