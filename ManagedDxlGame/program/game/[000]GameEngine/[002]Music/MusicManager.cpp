#include "MusicManager.h"



// BGM�̓ǂݍ���
void MusicManager::LoadBGM(const std::string& path)
{
    m_bgm = std::make_unique<MusicBGM>(path);
}

// ���ʉ��̓ǂݍ���
void MusicManager::LoadSE(const std::string& key, const std::string& path)
{
    m_se[key] = std::make_unique<MusicSE>(path);
}

// BGM�̍Đ�
void MusicManager::PlayBGM()
{
    if (m_bgm)
    {
        m_bgm->Play();
    }
}

// BGM�̒�~
void MusicManager::StopBGM()
{
    if (m_bgm)
    {
        m_bgm->Stop();
    }
}

// ���ʉ��̍Đ�
void MusicManager::PlaySE(const std::string& key)
{
    auto it = m_se.find(key);

    if (it != m_se.end())
    {
        it->second->Play();
    }
}

// ���ʉ��̒�~
void MusicManager::StopSE(const std::string& key)
{
    auto it = m_se.find(key);

    if (it != m_se.end())
    {
        it->second->Stop();
    }
}
