#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../../../../../[000]GamEngine/[000]Engine/Engine.h"
#include "../../../../[003]Phase/StagePhase.h"
#include "../../../[000]Stage/[001]Lane/Lane.h"


class Mediator;

// Mover�N���X�i�v���C���[�A�G�l�~�[�Ȃǈړ��Ɋւ��鏈�����s���j

class PlayerMove
{

private:

	//// ���݂̃X�e�b�v�C���f�b�N�X
	//int m_current_step = 0;

	/// �ړ����x
	//float m_move_speed = 0;
	//// �ړ���]���x
	//float m_move_rotation = 0;
	//// �󋵂ɂ��ړ����x�ω�
	//float m_move_change_speed = 1;

	//// ���Ԃ�̈ړ����x
	//float m_salto_move_speed = 0;
	//// ���Ԃ�̉�]���x
	//float m_salto_rotation = 0;
	//// ���Ԃ�̋O�����a
	//float m_salto_radius = 0;
	//// ���Ԃ�̏��v����
	//float m_salto_total_time = 0;
	
	// ���Ԃ�̌o�ߎ���
	float m_salto_elapsed_time = 0;

	// ���[���̉�]���x
	float m_rolling_rotation = 10;
	// ���̎��̉�]���x
	float m_figure_eight_rotation = 10;


	tnl::Vector3 m_pos;
	// �^�[�Q�b�g�v�Z�ňꎞ�I�Ɏg�p
	tnl::Quaternion m_target_rot;
	//���f���̉�]�擾�p
	tnl::Quaternion m_rot;

	//// �����ړ��ɂ��v���C���[�̐V�������W��](�J�����ƘA��)
	//tnl::Vector3 m_new_player_pos;
	//tnl::Quaternion m_new_player_rot;


	// �㉺���E�̕���
	eDirection direction = eDirection::none;
	// ���݂̃X�e�[�W�t�F�[�Y
	StagePhase::eStagePhase m_stage_phase = StagePhase::eStagePhase::e_fly;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(PlayerMove, &PlayerMove::SeqFly);


	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	// �v���C���[���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �󒆈ړ��ł̃��f����]��`
	void ControlMoveMatrix(float delta_time);
	// ���Ԃ�A�N�V�����ł̃��f����]��`
	void SaltoActionMatrix(float delta_time);
	// ���[����]�A�N�V�����ł̃��f����]��`
	void RollingActionMatrix(float delta_time);
	// ���̎��A�N�V�����ł̃��f����]��`
	void FigureEightActionMatrix(float delta_time);

	//// �n��ł̃��f����]��`
	//void GroundMoveMatrix(float delta_time);

	// �����̃^�C��ID���擾
	//int CurrentMoveLaneID();
	//// A�X�^�[�ɂ��ړ����`
	//void MoveAstar(const float delta_time);
	//// �����ړ��ɂ����W�Ɖ�]�̍X�V
	//void AutoMoveMatrix(const float delta_time
	//					,tnl::Vector3& goal_pos);
	//// �S�[���擾
	//Lane::sLane GoalTile();

	//// ���̃��[���ɓ��B����������
	//bool ReachedNextLane(const tnl::Vector3 goal_pos);

	// ��
	bool SeqFly(const float delta_time);
	//// �n��
	//bool SeqGround(const float delta_time);
	// ���Ԃ�A�N�V����
	bool SeqSaltoAction(const float delta_time);
	// ���[����]�A�N�V���� 
	bool SeqRollingAction(const float delta_time);
	// ���̎��A�N�V����
	bool SeqFigureEightAction(const float delta_time);

public:

	// �{�^�������`
	bool PushButton();
	//// �����o�H�̎擾����
	//void GetAutoMove();

	void Update(float delta_time);


	//int GetCurrentStep()
	//{
	//	return m_current_step;
	//}

	//tnl::Vector3 GetNewPlayerPos()
	//{
	//	return m_new_player_pos;
	//}

	//tnl::Quaternion GetNewPlayerRot()
	//{
	//	return m_new_player_rot;
	//}

	//// �ړ����x�ω���ݒ�
	//void SetMoveChangeSpeed(float speed)
	//{
	//	m_move_change_speed = speed;
	//}

	//std::vector<std::pair<int, int>> GetGoalProcess()
	//{
	//	return m_goal_process;
	//}

	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>> astar)
	{
		m_astar = astar;
	}

	void SetMediator(std::shared_ptr<Mediator> mediator)
	{
		m_mediator = mediator;
	}
};