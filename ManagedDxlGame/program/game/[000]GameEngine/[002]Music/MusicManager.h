#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "MusicBGM.h"
#include "MusicSE.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// ���y�֌W�̃}�l�[�W���[�N���X�i�V���O���g���j
//
/////////////////////////////////////////////////////////////////////////////////////////

class MusicManager
{

private:

    //---------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

    MusicManager() {}

    //---------------------------------------------------------------------------------//


    //-----------------------------------�����o�֐�-----------------------------------//

    // BGM�̓ǂݍ��ݗp
    std::unique_ptr<MusicBGM> m_bgm;
    // ���ʉ��̓ǂݍ��ݗp
    std::map<std::string, std::unique_ptr<MusicSE>> m_se;

    //--------------------------------------------------------------------------------//

public:

    //-----------------------------�V���O���g���p�֐�--------------------------------//

    // �ÓI�ϐ��Ƃ��ăV���O���g���C���X�^���X���쐬
    static MusicManager& GetInstance()
    {
        static MusicManager instance;
        return instance;
    }

    //------------------------------------------------------------------------------//


    //----------------------------------�����o�֐�----------------------------------//

    // BGM�̓ǂݍ���
    // arg ... �Đ�������BGM�̃p�X
    // tips ... BGM��ݒ肷�鎞�ɌĂяo���܂�
    // ex ... 	MusicManager::GetInstance().LoadBGM("music/title.mp3");
    void LoadBGM(const std::string& path);

    // ���ʉ��̓ǂݍ���
    // arg1 ... ���ʉ��̃L�[
    // arg2 ... �Đ����������ʉ��̃p�X
    // tips ... ���ʉ���ݒ肷�鎞�ɌĂяo���܂�
    // ex ... 	MusicManager::GetInstance().LoadSE("jump", "se/jump.mp3");
    void LoadSE(const std::string& key, const std::string& path);

    // BGM�̍Đ�
    // tips ... BGM�����[�v�Đ�����Ƃ��ɌĂяo���܂�
    void PlayBGM();
    // BGM�̒�~
    // tips ... BGM���~����Ƃ��ɌĂяo���܂�
    void StopBGM();

    // ���ʉ��̍Đ�
    // arg ... �Đ����������ʉ��̃L�[
    // tips ... ���ʉ����Đ�����Ƃ��ɌĂяo���܂�
    void PlaySE(const std::string& key);
    // ���ʉ��̒�~
    // arg ... ��~���������ʉ��̃L�[
    // tips ... ���ʉ����~����Ƃ��ɌĂяo���܂�
    void StopSE(const std::string& key);

    //------------------------------------------------------------------------------//
};
