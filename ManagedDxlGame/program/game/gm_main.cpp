#pragma once
#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "[000]GameEngine/[000]Scene/SceneManager.h"
#include "[000]GameEngine/[001]Music/MusicManager.h"
#include "[002]SceneOP/SceneOp.h"

#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() 
{
	srand(time(0));
	
	// �E�B���h�E�^�C�g��
	SetWindowText("Spring Fairy");

	SceneManager::GetInstance(new SceneOp());

	// ���y�̓ǂݍ���
	MusicManager::GetInstance().LoadBGM();
	MusicManager::GetInstance().LoadSE();
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) 
{
	SceneManager::GetInstance()->Update(delta_time);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() 
{
	SceneManager::GetInstance()->Finalize();
	
	MusicManager::GetInstance().DeleteInstance();

	// ���������[�N�̃`�F�b�N
	_CrtDumpMemoryLeaks();
}