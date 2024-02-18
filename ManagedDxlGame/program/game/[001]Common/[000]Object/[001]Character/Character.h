#pragma once
#include "../Object.h"
#include "../../[001]Camera/GameCamera.h"
#include "../[000]Stage/[001]Lane/Lane.h"
#include "../[002]Gimmick/Gimmick.h"


///////////////////////////////////////////////////////////////////////////
//
// キャラクターに順準ずる基底クラス
//
///////////////////////////////////////////////////////////////////////////


class Character : public Object
{

protected:

	// モデルハンドル
	int m_model_hdl = 0;

	// スピードアップフラグ
	bool m_is_speed_up = false;

	// メディエーターポインタ
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
	// 足元のイベントレーンを取得
	Lane::sLaneEvent CurrentEventLane();
	// 足元のカメラ情報を取得
	GameCamera::sCameraInfo CurrentCameraType();
	// スピードアップフラグを取得
	bool GetIsSpeedUp() const { return m_is_speed_up; }
	// メディエーターポインタを設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};