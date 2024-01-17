#pragma once
#include "../../[000]GamEngine/[003]Transform/Transform.h"

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


	virtual void Initialize() {}

	virtual void Update(const float delta_time) {}

	virtual void Draw(std::shared_ptr<GameCamera> gameCamera) {}
};
