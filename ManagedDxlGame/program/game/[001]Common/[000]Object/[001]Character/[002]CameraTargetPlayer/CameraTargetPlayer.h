#pragma once
#include "../Character.h"



class CameraTargetPlayer : public Character
{

public:

	CameraTargetPlayer(){}

	~CameraTargetPlayer() {}

	//----------------------------------------//

private:

	GameCamera::sCameraInfo m_camera_info;

	Item::sItem m_item;

public:

	// ‰Šú‰»
	void Initialize() override;
	// XV
	void Update(float delta_time) override;
	// •`‰æˆ—
	void Draw(std::shared_ptr<GameCamera> gameCamera) override;

	const GameCamera::sCameraInfo& GetCameraInfo() const
	{
		return m_camera_info; 
	}
};
