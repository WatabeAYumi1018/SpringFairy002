#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "[000]GamEngine/[001]Scene/SceneManager.h"
#include "[001]SceneTitle/SceneTitle.h"
#include "[002]ScenePlay/ScenePlay.h"

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() 
{
	tnl::SetSeedMersenneTwister32(time(0));

	srand(time(0));
	SetWindowText("FLOWER LAND");

	// �w�i�̐F��ݒ�(������F)
	SetBackgroundColor(255, 222, 233);

	SceneManager::GetInstance(new ScenePlay());


	//tnl::Quaternion q;
	//tnl::Matrix mat = q.getMatrix();
	//MATRIX dxm;
	//memcpy(&dxm, &mat.m, sizeof(float) * 16);
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
