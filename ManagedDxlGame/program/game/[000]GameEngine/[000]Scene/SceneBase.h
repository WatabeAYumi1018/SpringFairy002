#pragma once


/////////////////////////////////////////////////////////////////////////////////////////
// 
// scene�؂�ւ��p�̊��N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class SceneBase
{

protected:

	// ���ʂ̃t�F�[�h�A�E�g�t���O
	bool m_is_fade_out = false;

public:

	//-----------------------------------�����o�֐�-----------------------------------//

	// ������
	virtual void Initialize() {}
	// �X�V
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	virtual void Update(const float delta_time) {}
	// �`��
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	virtual void Draw(const float delta_time) {}
	// �j��
	virtual void Finalize() {}

	//---------------------------------------------------------------------------------//
};