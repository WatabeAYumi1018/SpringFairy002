#pragma once
#include "../../[000]GameEngine/[003]Transform/Transform.h"

class GameCamera;


///////////////////////////////////////////////////////////////////////////
//
// Tranformを持つ全てのオブジェクトの基底クラス
//
///////////////////////////////////////////////////////////////////////////


//モデルを持つクラスの総称とする

class Object : public Transform
{

public:

	Object() {}

	virtual ~Object() {}

	// ライトの設定
	virtual void SetLight(int model_hdl);
	// 初期化
	virtual void Initialize() {}
	// 更新
	virtual void Update(const float delta_time) {}
	// 描画
	virtual void Draw(std::shared_ptr<dxe::Camera> camera) {}
};
