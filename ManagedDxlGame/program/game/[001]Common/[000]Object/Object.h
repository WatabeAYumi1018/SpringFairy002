#pragma once
#include "../../[000]GameEngine/[002]Transform/Transform.h"

class GameCamera;


///////////////////////////////////////////////////////////////////////////
//
// Tranform�����S�ẴI�u�W�F�N�g�̊��N���X(�Ǝ��̍��W�����Ă�object�ƂȂ�)
//
///////////////////////////////////////////////////////////////////////////


class Object : public Transform
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Object() {}
	virtual ~Object() {}

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// ���C�g�̐ݒ�
	// arg ... ���f���n���h��
	virtual void SetLight(int model_hdl);
	// ������
	virtual void Initialize() {}
	// �X�V
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	virtual void Update(const float delta_time) {}
	// �`��
	// arg ... �J����
	virtual void Draw(std::shared_ptr<dxe::Camera> camera) {}

	//--------------------------------------------------------------------------------//
};
