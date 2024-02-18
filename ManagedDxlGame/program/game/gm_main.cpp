#pragma once
#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "[000]GameEngine/[001]Scene/SceneManager.h"
#include "[000]GameEngine/[002]Music/MusicManager.h"
#include "[002]SceneOP/SceneOp.h"


//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() 
{
	srand(time(0));
	
	// �E�B���h�E�^�C�g��
	SetWindowText("Spring Fairy");

	//�����t�H���g
	SetFontSize(20);
	tnl::AddFontTTF("font/Yomogi-Regular.ttf");
	ChangeFont("Yomogi", DX_CHARSET_DEFAULT);

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
}