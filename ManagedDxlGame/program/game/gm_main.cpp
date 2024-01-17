#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "[000]GamEngine/[001]Scene/SceneManager.h"
#include "[002]SceneOP/SceneOp.h"
#include "[003]ScenePlay/ScenePlay.h"

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() 
{
	tnl::SetSeedMersenneTwister32(time(0));

	srand(time(0));
	SetWindowText("FLOWER LAND");

	// 背景の色を設定(さくら色)
	SetBackgroundColor(255, 222, 233);

	SceneManager::GetInstance(new ScenePlay());


	//tnl::Quaternion q;
	//tnl::Matrix mat = q.getMatrix();
	//MATRIX dxm;
	//memcpy(&dxm, &mat.m, sizeof(float) * 16);
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
}
