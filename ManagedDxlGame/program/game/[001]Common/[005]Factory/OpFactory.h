#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[000]Object/[002]Gimmick/Gimmick.h"
#include "../[000]Object/Object.h"

class GameCamera;


class OpFactory 
{

public:

	OpFactory() {}

	~OpFactory() {}

private:

	std::list<std::shared_ptr<Object>> m_objects;

	std::shared_ptr<GameCamera> m_gameCamera = nullptr;

	// �e�I�u�W�F�N�g�̐����Ə�����
	void CreateObject();
	// �e�I�u�W�F�N�g���m�̎Q�Ƃ�ݒ�
	// �����̏��Ԃ��l�������A��t���ŎQ�Ƃł���悤��
	void SetObjectReference();
	// ���f���I�u�W�F�N�g�̃v�[��
	//void PoolModelObject();
	// �A�C�e���I�u�W�F�N�g�̃v�[��
	void PoolGimmickType(const std::vector<Gimmick::sGimmickTypeInfo>& gimmick_types);
	// ���������I�u�W�F�N�g��list�Ɋi�[
	void StorageObject();


public:

	// list�Ɋi�[�����I�u�W�F�N�g�̎擾
	const std::list<std::shared_ptr<Object>>& GetObjects() const
	{
		return m_objects;
	}

	// �J�����̎擾
	const std::shared_ptr<GameCamera>& GetGameCamera() const
	{
		return m_gameCamera;
	}
};