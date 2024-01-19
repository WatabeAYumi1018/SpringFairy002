#pragma once
#include "../Object.h"
#include "../../[001]Camera/GameCamera.h"
#include "../[000]Stage/[001]Lane/Lane.h"
#include "../[002]Item/Item.h"


class Character : public Object
{

protected:

	int m_model_hdl = 0;

	// ���f�B�G�[�^�[
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �L�����N�^�[�̏����ʒu
	void StartPos();

	// �L�����N�^�[�̍s��v�Z
	MATRIX CalcMatrix();

	// �����̃J�������[�����擾
	GameCamera::sCamera CurrentCamera();

public:

	// ���������ړ����[�����擾
	Lane::sLane CurrentMoveLane();
	// �����A�C�e�����[�����擾
	Item::sItem CurrentItemLane();

	// �����̃J���������擾
	GameCamera::sCameraInfo CurrentCameraType();

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};