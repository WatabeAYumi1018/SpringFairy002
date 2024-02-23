#pragma once
#include "../Object.h"
#include "../../[001]Camera/GameCamera.h"
#include "../[000]Stage/[001]Lane/Lane.h"
#include "../[002]Gimmick/Gimmick.h"


///////////////////////////////////////////////////////////////////////////
//
// キャラクターに準ずる基底クラス
//
///////////////////////////////////////////////////////////////////////////


class Character : public Object
{

public:

	//-----------------------------------enum class------------------------------------//

	// 方向を定義
	enum class eDirection
	{
		e_none,
		e_front,
		e_back,
		e_right,
		e_left,
		e_front_right,
		e_back_right,
		e_front_left,
		e_back_left
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ---------------------------//

	Character() {}
	~Character() {}

	//---------------------------------------------------------------------------------//

protected:

	//-----------------------------------メンバ変数------------------------------------//

	// モデルハンドル
	int m_model_hdl = 0;

	// スピードアップフラグ
	bool m_is_speed_up = false;

	// メディエーターポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// キャラクターの初期位置
	void StartPos();

	// キャラクターの行列計算
	MATRIX CalcMatrix();

	// 足元自動移動レーンを取得
	Lane::sLane CurrentMoveLane();

	// 足元のイベントレーンを取得
	Lane::sLaneEvent CurrentEventLane();

	// 足元のカメラ情報を取得
	GameCamera::sCameraInfo CurrentCameraType();

public:

	// 足元のカメラレーンを取得
	GameCamera::sCamera CurrentCameraLane();
	
	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// スピードアップフラグを取得
	bool GetIsSpeedUp() const { return m_is_speed_up; }
	
	// メディエーターポインタを設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};