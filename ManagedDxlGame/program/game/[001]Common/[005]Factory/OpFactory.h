#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class Object;

class SkyBox;
class BackLoad;

class Butterfly;
class ButterflyLoad;

class Title;

class Gate;
class GateLoad;

class EnterGraph;

class Mediator;

class OpCamera;


///////////////////////////////////////////////////////////////////////////
//
// OP�V�[���̃I�u�W�F�N�g�����N���X
//
///////////////////////////////////////////////////////////////////////////


class OpFactory 
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	OpFactory();
	~OpFactory();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// ���������I�u�W�F�N�g���i�[����list
	std::list<std::shared_ptr<Object>> m_objects;

	// �e�N���X�̃|�C���^

	std::shared_ptr<Object> m_object = nullptr;

	std::shared_ptr<SkyBox> m_skyBox = nullptr;
	std::shared_ptr<BackLoad> m_backLoad = nullptr;

	std::shared_ptr<Butterfly> m_butterfly = nullptr;
	std::shared_ptr<ButterflyLoad> m_butterflyLoad = nullptr;

	std::shared_ptr<Title> m_title = nullptr;

	std::shared_ptr<Gate> m_gate = nullptr;
	std::shared_ptr<GateLoad> m_gateLoad = nullptr;

	std::shared_ptr<EnterGraph> m_enterGraph = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;
	std::shared_ptr<OpCamera> m_opCamera = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �����s���Ƃ��āACreateObject() -> SetObjectReference() -> StorageObject()
	
	// �e�I�u�W�F�N�g�̐����Ə�����
	// tips ... ���������Ɉ�x�����Ăяo��
	void CreateObject();

	// �e�I�u�W�F�N�g���m�̎Q�Ƃ�ݒ�
	// tips ... ���������Ɉ�x�����Ăяo��
	//          �����̏��Ԃ��l�������A��t���ŎQ�Ƃł���悤��
	void SetObjectReference();
	
	// ���������I�u�W�F�N�g��list�Ɋi�[
	// tips ... ���������Ɉ�x�����Ăяo��
	//          �I�u�W�F�N�g�^�݂̂��i�[���A�|�����[�t�B�Y���ň���
	void StorageObject();

	//	�f�X�g���N�^�ɂďz�Q�Ƃ𖾎��I�ɉ���
	//	����A�e�N���X���烁�f�B�G�[�^�ւ̎Q�Ƃ�shared�ōs���Ă��邽�߁A
	//	�J�E���g��0�ɂȂ�Ȃ��Ǝv���鎖�Ă������B
	//	���P��Ƃ��āA���f�B�G�[�^�ւ�weak�Q�Ƃ��������܂����A
	//	���t���[����ʂ�shared_ptr�𐶐����鎖�ɂȂ邽�߁A
	//	�p�t�H�[�}���X�ւ̉e�������O�B
	//	�쐬�I�Ղ̌��i�K�Ő݌v�̌������͌����I�łȂ����߁A
	//	����͖����I�ɉ������鎖�ɂ��܂����B
	//  ����̑傫�ȉۑ�Ƃ��āA�݌v�̌��������s�������������܂��B
	void SharedExReset();
	//--------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// list�Ɋi�[�����I�u�W�F�N�g�̎擾
	const std::list<std::shared_ptr<Object>>& GetObjects() const
	{
		return m_objects;
	}

	// �J�����̎擾
	const std::shared_ptr<OpCamera>& GetGameCamera() const
	{
		return m_opCamera;
	}

	//--------------------------------------------------------------------------------//
};