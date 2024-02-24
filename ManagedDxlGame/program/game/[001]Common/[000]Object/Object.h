#pragma once
#include "../../[000]GameEngine/[002]Transform/Transform.h"

class GameCamera;


///////////////////////////////////////////////////////////////////////////
//
// Tranformを持つ全てのオブジェクトの基底クラス(独自の座標を持てばobjectとなる)
//
///////////////////////////////////////////////////////////////////////////


class Object : public Transform
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Object() {}
	virtual ~Object() {}

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// ライトの設定
	// arg ... モデルハンドル
	virtual void SetLight(int model_hdl);
	// 初期化
	virtual void Initialize() {}
	// 更新
	// arg ... delta_time(前フレームからの経過時間)
	virtual void Update(const float delta_time) {}
	// 描画
	// arg ... カメラ
	virtual void Draw(std::shared_ptr<dxe::Camera> camera) {}

	//--------------------------------------------------------------------------------//
};
