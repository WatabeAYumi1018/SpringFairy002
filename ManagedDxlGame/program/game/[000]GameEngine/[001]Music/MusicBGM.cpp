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

		// 初期音量を設定
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
	// BGMの種類読み取り専用（csvファイル）
	m_csv_bgm_info = tnl::LoadCsv<tnl::CsvCell>("csv/music/bgm.csv");

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < m_csv_bgm_info.size(); ++y)
	{
		MusicBGM::sMusicBGM bgm_info;

		bgm_info.s_id = m_csv_bgm_info[y][0].getInt();

		bgm_info.s_bgm_hdl = LoadSoundMem(m_csv_bgm_info[y][1].getString().c_str());

		m_bgms_info.emplace_back(bgm_info);
	}
}

// フェードイン
void MusicBGM::FadeIn(const float delta_time, int id)
{
	// 再生開始
	Play(id); 
	// 現在の音量を変更
	m_current_volume += m_fade_speed * delta_time;

	if (m_current_volume >= m_target_volume)
	{
		m_current_volume = m_target_volume;

		m_is_playing = true;
	}
}

// フェードアウト
void MusicBGM::FadeOut(const float delta_time, int id)
{
	if (m_is_playing)
	{
		// 目標音量
		m_target_volume = 0; 
		// 現在の音量を変更
		m_current_volume -= m_fade_speed * delta_time;

		if (m_current_volume <= m_target_volume)
		{
			// 再生停止
			Stop(id); 
		}
	}
}
