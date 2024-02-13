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

	Lane::sLaneEvent m_event;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(CameraTargetPlayer, &CameraTargetPlayer::SeqNormal);

	void MoveMatrix(const float delta_time);

	// 通常の移動処理
	bool SeqNormal(const float delta_time);
	// 停止処理
	bool SeqStop(const float delta_time);
	// 上昇処理
	bool SeqUpMove(const float delta_time);
	// 下降処理
	bool SeqDownMove(const float delta_time);

public:

	// 初期化
	void Initialize() override;
	// 更新
	void Update(float delta_time) override;

	const GameCamera::sCameraInfo& GetCameraInfo() const
	{
		return m_camera_info; 
	}

	const Lane::sLaneEvent& GetCurrentEvent() const
	{
		return m_event;
	}
};
