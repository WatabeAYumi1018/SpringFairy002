#pragma once
#include "../Character.h"



class GameCameraTarget : public Character
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	GameCameraTarget(){}
	~GameCameraTarget() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	GameCamera::sCameraInfo m_camera_info;

	Lane::sLaneEvent m_event;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(GameCameraTarget, &GameCameraTarget::SeqNormal);

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// 自動移動による更新処理
	// arg ... delta_time(前フレームからの経過時間)
	void MoveMatrix(const float delta_time);

	// 通常の移動処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqNormal(const float delta_time);

	// 停止処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqStop(const float delta_time);

public:

	void Initialize() override;
	
	void Update(const float delta_time) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// カメラ情報の取得
	const GameCamera::sCameraInfo& GetCameraInfo() const { return m_camera_info; }

	// イベント情報の取得
	const Lane::sLaneEvent& GetCurrentEvent() const { return m_event; }

	//---------------------------------------------------------------------------------//
};
