#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../Character.h"


class Mediator;

// Mover�N���X�i�v���C���[�A�G�l�~�[�Ȃǈړ��Ɋւ��鏈�����s���j

class PartnerMove
{

private:

	// �߂荞�ގ���
	const float SINK_DURATION = 0.5f;
	// �߂荞�݋
	const float SINK_VALUE = 10;
	// �e����鎞��
	const float PUSH_DURATION = 1;
	// �e�����
	const float PUSH_VALUE = 8;

	// �o�ߎ���
	float m_elapsed_time = 0;

	// ����
	int m_random = -1;

	// �ړ�����
	float m_move_time = 0.0f;
	// �O��̈ړ�����
	float m_last_move_time = 0.0f;
	// �������g��
	float m_orbit_frequency = 0.2f; 

	// ��]����
	float m_rotation_time = 0.0f;
	// �O��̉�]����
	float m_last_rotation_time = 0.0f;

	// ���ݍ��W
	tnl::Vector3 m_pos;
	// �ړ����W�I�t�Z�b�g
	tnl::Vector3 m_offset;
	// �Փˎ��̒��_
	tnl::Vector3 m_center;
	// �Փˎ��̋t�x�N�g���i���K���j
	tnl::Vector3 m_reverse;

	// ���݉�]
	tnl::Quaternion m_rot;
	// �ڕW��]
	tnl::Quaternion m_target_rot;

	// �ړ������t���O
	bool m_is_moved = false;

	// �Փ˃t���O
	bool m_is_pushed = false;


	// �v���C���[���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	void UpdatePos(const float delta_time);

	void UpdateRot(const float delta_time);

	void CorrectPos(const float delta_time);

public:

	void Update(float delta_time);


	void SetIsPushed(bool is_pushed) { m_is_pushed = is_pushed ; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};