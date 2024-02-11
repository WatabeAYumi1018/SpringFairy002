#include "MusicManager.h"



// BGMの読み込み
void MusicManager::LoadBGM()
{
    m_bgm = std::make_shared<MusicBGM>();
}

// 効果音の読み込み
void MusicManager::LoadSE()
{
    m_se = std::make_shared<MusicSE>();
}

// BGMの再生
void MusicManager::PlayBGM(const float delta_time,int id)
{
    if (m_bgm)
    {
        m_bgm->Play(id);
    }
}

// BGMの停止
void MusicManager::StopBGM(int id)
{
    if (m_bgm)
    {
        m_bgm->Stop(id);
    }
}

bool MusicManager::IsStopBGM(int id)
{
    if (m_bgm)
    {
        m_bgm->Stop(id);
	}
	return false;
}


// 効果音の再生
void MusicManager::PlaySE(int id)
{
    if (m_se)
    {
        m_se->Play(id);
    }
}

// 効果音の停止
void MusicManager::StopSE(int id)
{
    if (m_se)
    {
        m_se->Stop(id);
    }
}
