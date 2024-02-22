#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../Character.h"


class Mediator;

// Mover�N���X�i�v���C���[�A�G�l�~�[�Ȃǈړ��Ɋւ��鏈�����s���j

class PartnerMove
{

private:

	// �o�ߎ���
	float m_elapsed_time = 0;
	// �ړ�����
	float m_move_time = 0.0f;
	// �O��̈ړ�����
	float m_last_move_time = 0.0f;

	// �������g��
	float m_orbit_frequency = 0.2f; 

	// �����o���t���O
	bool m_is_pushed = false;

	// ���ݍ��W
	tnl::Vector3 m_pos;
	// �ړ����W�I�t�Z�b�g
	tnl::Vector3 m_offset;

	// ���݉�]
	tnl::Quaternion m_rot;
	// �ڕW��]
	tnl::Quaternion m_target_rot;


	// �v���C���[���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	void UpdatePos(const float delta_time);

	void CorrectPos(const float delta_time);

public:

	void Update(float delta_time);


	void SetIsPushed(bool is_pushed) { m_is_pushed = is_pushed ; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};