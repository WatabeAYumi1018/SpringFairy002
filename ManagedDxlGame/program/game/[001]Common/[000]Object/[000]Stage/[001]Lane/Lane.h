#pragma once
#include "../../../[001]Camera/GameCamera.h"
#include "../../Object.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// レーンの基本情報を管理するクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class Lane : public Object
{

public:

	struct sLane
	{
		int s_id;
		tnl::Vector3 s_pos;
	};

	struct sLaneEvent
	{
		int s_id;
		tnl::Vector3 s_pos;
	};


	Lane() {}

	~Lane() {}

	static const int LANE_SIZE = 1500;
};
