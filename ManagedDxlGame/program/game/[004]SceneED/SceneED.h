#pragma once
#include "../[000]GameEngine/[000]Scene/SceneBase.h"


class ScreenShot;

class EnterGraph;

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// End�V�[���̈ꊇ�������s���N���X
// �g�p�N���X���w�ǂȂ��Ӗ����Ȃ����߁A���N���X�̓I�u�W�F�N�g�w�����g�p���Ȃ�
//
///////////////////////////////////////////////////////////////////////////


class SceneEd : public SceneBase
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	SceneEd();
	~SceneEd();

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�ϐ�-----------------------------------//

private:

	// �e�N���X�̃|�C���^
	std::shared_ptr<ScreenShot> m_screen_shot = nullptr;
	std::shared_ptr<EnterGraph> m_enter_graph = nullptr;
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �V�[�P���X
	tnl::Sequence<SceneEd> m_sequence
		= tnl::Sequence<SceneEd>(this, &SceneEd::SeqStart);

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �V�[�P���X�J�n
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqStart(const float delta_time);

public:

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//
};