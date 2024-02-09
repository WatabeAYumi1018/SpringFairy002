#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../library/tnl_sequence.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../../../../../[000]GameEngine/[000]Engine/Engine.h"
#include "../../../../[003]Phase/StagePhase.h"
#include "../../../[000]Stage/[001]Lane/Lane.h"


class Mediator;

// Mover�N���X�i�v���C���[�A�G�l�~�[�Ȃǈړ��Ɋւ��鏈�����s���j

class PlayerMove
{

private:
	
	// ���Ԃ�̌o�ߎ���
	float m_salto_elapsed_time = 0;

	// ���[���̉�]���x
	float m_rolling_rotation = 10;
	// ���̎��̉�]���x
	float m_figure_eight_rotation = 10;

	tnl::Vector3 m_game_pos;
	// �^�[�Q�b�g�v�Z�ňꎞ�I�Ɏg�p
	tnl::Quaternion m_target_rot;
	//���f���̉�]�擾�p
	tnl::Quaternion m_rot;

	// �㉺���E�̕���
	eDirection direction = eDirection::e_none;
	// ���݂̃X�e�[�W�t�F�[�Y
	//StagePhase::eStagePhase m_stage_phase = StagePhase::eStagePhase::e_flower;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(PlayerMove, &PlayerMove::SeqNormal);


	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	// �v���C���[���f�B�G�[�^�̃X�}�[�g�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	void MoveMatrix(float delta_time);

	// �󒆈ړ��ł̃��f����]��`
	void ControlMoveMatrix(float delta_time);
	// ���Ԃ�A�N�V�����ł̃��f����]��`
	void SaltoActionMatrix(float delta_time);
	// ���[����]�A�N�V�����ł̃��f����]��`
	void RollingActionMatrix(float delta_time);
	// ���̎��A�N�V�����ł̃��f����]��`
	void FigureEightActionMatrix(float delta_time);


	// �ʏ�̈ړ�����
	bool SeqNormal(const float delta_time);
	// ��~����
	bool SeqStop(const float delta_time);
	// �㏸����
	bool SeqUpMove(const float delta_time);
	// ���~����
	bool SeqDownMove(const float delta_time);

	// ���Ԃ�A�N�V����
	bool SeqSaltoAction(const float delta_time);
	// ���[����]�A�N�V���� 
	bool SeqRollingAction(const float delta_time);
	// ���̎��A�N�V����
	bool SeqFigureEightAction(const float delta_time);

public:

	// �{�^�������`
	bool PushButton();

	void Update(float delta_time);


	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>>& astar)
	{
		m_astar = astar;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};