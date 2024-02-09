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
	// BGMの種類読み取り専用（csvファイル）
	m_csv_bgm_info = tnl::LoadCsv<tnl::CsvCell>("csv/music/bgm.csv");

	// マップタイルの総数を取得
	int max_num = m_csv_bgm_info.size();

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{
		m_bgms_info[y].s_id = m_csv_bgm_info[y][0].getInt();

		m_bgms_info[y].s_bgm_hdl = LoadSoundMem(m_csv_bgm_info[y][1].getString().c_str());

		m_bgms_info.emplace_back(m_bgms_info[y]);
	}
}
