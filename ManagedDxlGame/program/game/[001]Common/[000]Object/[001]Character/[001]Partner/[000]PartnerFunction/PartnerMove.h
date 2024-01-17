#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../[000]GamEngine/[000]Engine/Engine.h"


class Mediator;

// Mover�N���X�i�v���C���[�A�G�l�~�[�Ȃǈړ��Ɋւ��鏈�����s���j

class PartnerMove
{

private:

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

	// ���݉�]
	tnl::Quaternion m_rot;
	// �ڕW��]
	tnl::Quaternion m_target_rot;

	// �ړ������t���O
	bool m_is_moved = false;

	//// �㉺���E�̕���
	//eDirection direction = eDirection::none;

	//// �R���[�`���V�[�P���X
	//TNL_CO_SEQUENCE(PartnerMove, &PartnerMove::SeqNormal);

	// �v���C���[���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	//// �����_���ȍs��v�Z����
	//void CalcRandomPos(const tnl::Vector3& player_pos);

	void UpdatePos(float delta_time);

	void UpdateRot(float delta_time);

	//// ��Ղ̈ړ�����
	//bool SeqNormal(const float delta_time);
	//// �^�[�Q�b�g���W�v�Z����
	//bool SeqTargetCalc(const float delta_time);
	//// �`���I�Ȉړ�����
	//bool SeqMove(const float delta_time);
	//// �s�K���ȗ�������
	//bool SeqFall(const float delta_time);
	//// �s�K���ȋt�ړ�����
	//bool SeqInverse(const float delta_time);

public:

	void Update(float delta_time);


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};