#include "MusicManager.h"



// BGM‚Ì“Ç‚İ‚İ
void MusicManager::LoadBGM(const std::string& path)
{
    m_bgm = std::make_unique<MusicBGM>(path);
}

// Œø‰Ê‰¹‚Ì“Ç‚İ‚İ
void MusicManager::LoadSE(const std::string& key, const std::string& path)
{
    m_se[key] = std::make_unique<MusicSE>(path);
}

// BGM‚ÌÄ¶
void MusicManager::PlayBGM()
{
    if (m_bgm)
    {
        m_bgm->Play();
    }
}

// BGM‚Ì’â~
void MusicManager::StopBGM()
{
    if (m_bgm)
    {
        m_bgm->Stop();
    }
}

// Œø‰Ê‰¹‚ÌÄ¶
void MusicManager::PlaySE(const std::string& key)
{
    auto it = m_se.find(key);

    if (it != m_se.end())
    {
        it->second->Play();
    }
}

// Œø‰Ê‰¹‚Ì’â~
void MusicManager::StopSE(const std::string& key)
{
    auto it = m_se.find(key);

    if (it != m_se.end())
    {
        it->second->Stop();
    }
}
