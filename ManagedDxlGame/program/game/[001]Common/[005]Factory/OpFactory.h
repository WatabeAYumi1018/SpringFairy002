#pragma once
#include "../dxlib_ext/dxlib_ext.h"

///////////////////////////////////////////////////////////////////////////
//
// OP�V�[���̃I�u�W�F�N�g�����N���X
//
///////////////////////////////////////////////////////////////////////////


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


class OpFactory 
{

public:

	OpFactory();

	~OpFactory();

private:

	std::list<std::shared_ptr<Object>> m_objects;

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

	// �e�I�u�W�F�N�g�̐����Ə�����
	void CreateObject();
	// �e�I�u�W�F�N�g���m�̎Q�Ƃ�ݒ�
	// �����̏��Ԃ��l�������A��t���ŎQ�Ƃł���悤��
	void SetObjectReference();
	// ���������I�u�W�F�N�g��list�Ɋi�[
	void StorageObject();


public:

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
};