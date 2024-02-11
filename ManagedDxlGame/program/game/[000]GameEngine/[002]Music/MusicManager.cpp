#include "MusicManager.h"



// BGM�̓ǂݍ���
void MusicManager::LoadBGM()
{
    m_bgm = std::make_shared<MusicBGM>();
}

// ���ʉ��̓ǂݍ���
void MusicManager::LoadSE()
{
    m_se = std::make_shared<MusicSE>();
}

// BGM�̍Đ�
void MusicManager::PlayBGM(const float delta_time,int id)
{
    if (m_bgm)
    {
        m_bgm->Play(id);
    }
}

// BGM�̒�~
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


// ���ʉ��̍Đ�
void MusicManager::PlaySE(int id)
{
    if (m_se)
    {
        m_se->Play(id);
    }
}

// ���ʉ��̒�~
void MusicManager::StopSE(int id)
{
    if (m_se)
    {
        m_se->Stop(id);
    }
}
