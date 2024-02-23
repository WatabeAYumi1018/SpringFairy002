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
    ~MusicManager() {}

    //---------------------------------------------------------------------------------//


    //-----------------------------------�����o�ϐ�-----------------------------------//

    // BGM�̓ǂݍ��ݗp
    std::shared_ptr<MusicBGM> m_bgm = nullptr;
    // ���ʉ��̓ǂݍ��ݗp
    std::shared_ptr<MusicSE> m_se = nullptr;

    //--------------------------------------------------------------------------------//

public:

    //-----------------------------�V���O���g���p�֐�--------------------------------//

    // �ÓI�ϐ��Ƃ��ăV���O���g���C���X�^���X���쐬
    static MusicManager& GetInstance()
    {
        static MusicManager instance;

        return instance;
    }

    // ���������
    static void DeleteInstance()
	{
		MusicManager& instance = GetInstance();
	
        delete &instance;

        instance.m_bgm.reset();
        instance.m_se.reset();
	}

    //------------------------------------------------------------------------------//


    //----------------------------------�����o�֐�----------------------------------//

    // BGM�̓ǂݍ���
    // tips ... BGM��ݒ肷�鎞�ɌĂяo���܂�
    void LoadBGM();

    // ���ʉ��̓ǂݍ���
    // tips ... ���ʉ���ݒ肷�鎞�ɌĂяo���܂�
    void LoadSE();

    // BGM�̍Đ�
    // arg1 ... delta_time(�O�t���[������̌o�ߎ���)
    // arg2 ... �Y������BGM��ID
    // tips ... BGM�����[�v�Đ�����Ƃ��ɌĂяo���܂�
    void PlayBGM(const float delta_time, int id);

    // BGM�̒�~
    // arg ... �Y������BGM��ID 
    // tips ... BGM���~����Ƃ��ɌĂяo���܂�
    void StopBGM(int id);

    // BGM�̒�~�t���O
    // arg ... �Y������BGM��ID
    // tips ... BGM�̒�~�t���O���擾����Ƃ��ɌĂяo���܂�
    bool IsStopBGM(int id);

    // ���ʉ��̍Đ�
    // arg ... �Y��������ʉ���ID
    // tips ... ���ʉ����Đ�����Ƃ��ɌĂяo���܂�
    void PlaySE(int id);

    // ���ʉ��̒�~
    // arg ... �Y��������ʉ���ID
    // tips ... ���ʉ����~����Ƃ��ɌĂяo���܂�
    void StopSE(int id);

    //------------------------------------------------------------------------------//
};
