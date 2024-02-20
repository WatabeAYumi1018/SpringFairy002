#include "MusicManager.h"



// BGM‚Ì“Ç‚İ‚İ
void MusicManager::LoadBGM()
{
    m_bgm = std::make_shared<MusicBGM>();
}

// Œø‰Ê‰¹‚Ì“Ç‚İ‚İ
void MusicManager::LoadSE()
{
    m_se = std::make_shared<MusicSE>();
}

// BGM‚ÌÄ¶
void MusicManager::PlayBGM(const float delta_time,int id)
{
    if (m_bgm)
    {
        m_bgm->Play(id);
    }
}

// BGM‚Ì’â~
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


// Œø‰Ê‰¹‚ÌÄ¶
void MusicManager::PlaySE(int id)
{
    if (m_se)
    {
        m_se->Play(id);
    }
}

// Œø‰Ê‰¹‚Ì’â~
void MusicManager::StopSE(int id)
{
    if (m_se)
    {
        m_se->Stop(id);
    }
}
