#pragma once
#include "../../[000]GamEngine/[003]Transform/Transform.h"

class GameCamera;


///////////////////////////////////////////////////////////////////////////
//
// Tranform�����S�ẴI�u�W�F�N�g�̊��N���X
//
///////////////////////////////////////////////////////////////////////////


//���f�������N���X�̑��̂Ƃ���

class Object : public Transform
{

public:

	Object() {}

	virtual ~Object() {}


	virtual void Initialize() {}

	virtual void Update(const float delta_time) {}

	virtual void Draw(std::shared_ptr<GameCamera> gameCamera) {}
};
