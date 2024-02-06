#pragma once
#include "../Object.h"
#include "../../[001]Camera/GameCamera.h"
#include "../[000]Stage/[001]Lane/Lane.h"
#include "../[002]Gimmick/Gimmick.h"


class Character : public Object
{

protected:

	int m_model_hdl = 0;
	// スピードアップフラグ
	bool m_is_speed_up = false;
	// 上昇フラグ
	bool m_is_move_up = false;
	// 下降フラグ
	bool m_is_move_down = false;

	// メディエーター
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// キャラクターの初期位置
	void StartPos();

	// キャラクターの行列計算
	MATRIX CalcMatrix();


public:

	// 足元のカメラレーンを取得
	GameCamera::sCamera CurrentCamera();

	// 足元自動移動レーンを取得
	Lane::sLane CurrentMoveLane();
	//// 足元アイテムレーンを取得
	//Gimmick::sGimmick CurrentGimmickLane();
	// 足元のイベントレーンを取得
	Lane::sLaneEvent CurrentEventLane();
	// 足元のカメラ情報を取得
	GameCamera::sCameraInfo CurrentCameraType();

	bool GetIsSpeedUp() const { return m_is_speed_up; }

	//bool GetIsSpeedUp() const { return m_is_move_up; }

	bool GetIsMoveDown() const { return m_is_move_down; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};