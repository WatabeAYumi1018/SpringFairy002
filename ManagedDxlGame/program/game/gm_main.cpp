#pragma once
#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "[000]GameEngine/[000]Scene/SceneManager.h"
#include "[000]GameEngine/[001]Music/MusicManager.h"
#include "[004]SceneED/SceneEd.h"

#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() 
{
	srand(time(0));
	
	// ウィンドウタイトル
	SetWindowText("Spring Fairy");

	SceneManager::GetInstance(new SceneEd());

	// 音楽の読み込み
	MusicManager::GetInstance().LoadBGM();
	MusicManager::GetInstance().LoadSE();
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) 
{
	SceneManager::GetInstance()->Update(delta_time);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() 
{
	SceneManager::GetInstance()->Finalize();
	

	// メモリリークのチェック
	_CrtDumpMemoryLeaks();
}