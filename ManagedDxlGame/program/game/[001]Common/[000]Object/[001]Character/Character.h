#pragma once
#include "../Object.h"
#include "../../[001]Camera/GameCamera.h"
#include "../[000]Stage/[001]Lane/Lane.h"
#include "../[002]Gimmick/Gimmick.h"


///////////////////////////////////////////////////////////////////////////
//
// �L�����N�^�[�ɏ���������N���X
//
///////////////////////////////////////////////////////////////////////////


class Character : public Object
{

public:

	// �������`
	enum class eDirection
	{
		e_none,
		e_front,
		e_back,
		e_right,
		e_left,
		e_front_right,
		e_back_right,
		e_front_left,
		e_back_left
	};

	Character() {}
	~Character() {}

protected:

	// ���f���n���h��
	int m_model_hdl = 0;

	// �X�s�[�h�A�b�v�t���O
	bool m_is_speed_up = false;

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �L�����N�^�[�̏����ʒu
	void StartPos();

	// �L�����N�^�[�̍s��v�Z
	MATRIX CalcMatrix();
	// ���������ړ����[�����擾
	Lane::sLane CurrentMoveLane();
	// �����̃C�x���g���[�����擾
	Lane::sLaneEvent CurrentEventLane();
	// �����̃J���������擾
	GameCamera::sCameraInfo CurrentCameraType();


public:

	// �����̃J�������[�����擾
	GameCamera::sCamera CurrentCameraLane();
	// �X�s�[�h�A�b�v�t���O���擾
	bool GetIsSpeedUp() const { return m_is_speed_up; }
	// ���f�B�G�[�^�[�|�C���^��ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};