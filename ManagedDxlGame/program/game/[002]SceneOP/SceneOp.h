#pragma once
#include "../[000]GameEngine/[000]Scene/SceneBase.h"
#include "../[001]Common/[000]Object/Object.h"

class OpFactory;
class OpCamera;


///////////////////////////////////////////////////////////////////////////
//
// OP�V�[���̈ꊇ�������s���N���X
//
///////////////////////////////////////////////////////////////////////////


class SceneOp : public SceneBase
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	SceneOp();
	~SceneOp();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �I�u�W�F�N�g���X�g
 	std::list<std::shared_ptr<Object>> m_objects;
	
	// Op�t�@�N�g���[�̃|�C���^
	std::shared_ptr<OpFactory> m_factory = nullptr;
	// Op�J�����̃|�C���^
	std::shared_ptr<OpCamera> m_opCamera = nullptr;


	// �V�[�P���X
	tnl::Sequence<SceneOp> m_sequence
		= tnl::Sequence<SceneOp>(this, &SceneOp::SeqStart);

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �V�[�P���X�J�n
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqStart(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//
};