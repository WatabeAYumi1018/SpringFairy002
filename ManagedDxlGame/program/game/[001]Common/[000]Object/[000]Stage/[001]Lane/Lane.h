#pragma once
#include "../../../[001]Camera/GameCamera.h"
#include "../../Object.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// レーンを定義するクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class Lane : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

	// レーンの情報
	struct sLane
	{
		int s_id;
		tnl::Vector3 s_pos;
	};

	// イベントレーンの情報
	struct sLaneEvent
	{
		int s_id;
		tnl::Vector3 s_pos;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Lane() {}

	~Lane() {}

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ変数------------------------------------//

	// レーンのグリッドサイズ（定数）
	static const int LANE_SIZE = 1500;
};
