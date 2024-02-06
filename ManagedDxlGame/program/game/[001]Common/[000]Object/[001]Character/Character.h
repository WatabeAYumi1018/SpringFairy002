#pragma once
#include "../Object.h"
#include "../../[001]Camera/GameCamera.h"
#include "../[000]Stage/[001]Lane/Lane.h"
#include "../[002]Gimmick/Gimmick.h"


class Character : public Object
{

protected:

	int m_model_hdl = 0;
	// �X�s�[�h�A�b�v�t���O
	bool m_is_speed_up = false;
	// �㏸�t���O
	bool m_is_move_up = false;
	// ���~�t���O
	bool m_is_move_down = false;

	// ���f�B�G�[�^�[
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �L�����N�^�[�̏����ʒu
	void StartPos();

	// �L�����N�^�[�̍s��v�Z
	MATRIX CalcMatrix();


public:

	// �����̃J�������[�����擾
	GameCamera::sCamera CurrentCamera();

	// ���������ړ����[�����擾
	Lane::sLane CurrentMoveLane();
	//// �����A�C�e�����[�����擾
	//Gimmick::sGimmick CurrentGimmickLane();
	// �����̃C�x���g���[�����擾
	Lane::sLaneEvent CurrentEventLane();
	// �����̃J���������擾
	GameCamera::sCameraInfo CurrentCameraType();

	bool GetIsSpeedUp() const { return m_is_speed_up; }

	//bool GetIsSpeedUp() const { return m_is_move_up; }

	bool GetIsMoveDown() const { return m_is_move_down; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};