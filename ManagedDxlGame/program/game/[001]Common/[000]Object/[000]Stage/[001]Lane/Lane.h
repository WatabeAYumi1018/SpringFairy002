#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../Object.h"


class Lane : public Object
{

public:

	struct sLane
	{
		int s_id;
		tnl::Vector3 s_pos;
	};

	struct sLaneCameraInfo
	{
		int s_id;
		std::string s_type;
	};

	struct sLaneEventInfo
	{
		int s_id;
		std::string s_type;
	};

	Lane() {}

	~Lane() {}

	static const int LANE_SIZE = 800;

};
