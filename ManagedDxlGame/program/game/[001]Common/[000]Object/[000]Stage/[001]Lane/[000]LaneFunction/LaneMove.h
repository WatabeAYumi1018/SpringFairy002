#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../Lane.h"

class Mediator;

/////////////////////////////////////////////////////////////////////////////////////////
// 
// �����^�]�ɂ��ړ������̃N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class LaneMove
{

public:
	
	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	LaneMove() {}
	~LaneMove() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���݂̃X�e�b�v�C���f�b�N�X
	int m_now_step = 0;

	// �ړ����x
	float m_move_speed = 200;
	// �ړ���]���x
	float m_move_rotation = 10;

	// ��Ԃ���������܂ł̎��ԁi�b�j
	float m_blend_time = 1.0f; 
	// ���݂̕�Ԏ���
	float m_current_time = 0.0f;

	// �΂߈ړ��J�n�̃t���O
	bool m_is_diagonal = false;
	// �E����̃T�C�h���_(������͍�)
	bool m_look_side_right = false;
	// ������̃T�C�h���_(������͉E)
	bool m_look_side_left = false;

	// �^�[�Q�b�g�v���C���[�̐i�s����
	tnl::Vector3 m_target_direction;
	// �L�����N�^�[�̐i�s����
	tnl::Vector3 m_chara_direction;
	// ���݂̃O���b�h�̒��S�_
	tnl::Vector3 m_current_center_pos;

	// ���݂̃O���b�h�ʒu
	std::pair<int, int> m_current_grid;
	// ���̃O���b�h�ʒu
	std::pair<int, int> m_next_grid;
	// A*����̌o�H
	std::vector<std::pair<int, int>> m_goal_process;

	// Astar�̃|�C���^
	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;
	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ���W�X�V�̑��x����
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �i�s�����̃x�N�g��
	// arg3 ... �Y���I�u�W�F�N�g�̍��W
	void MoveSpeed(const float delta_time, tnl::Vector3& direction, tnl::Vector3& pos);
	
	// �^�[�Q�b�g�����S�ɓ��B����������
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... ���̃O���b�h�܂ł̋���
	// arg3 ... �^�[�Q�b�g�̍��W
	void StepUpdate(const float delta_time,float distance, tnl::Vector3& pos);
	
	// �O���b�h�̍X�V����
	void UpdateGrids();
	
	// �S�[���̃��[��ID���擾
	Lane::sLane GoalTile();

public:

	// �S�[���܂ł̌o�H���擾
	void GetAutoMove();

	// �L�����N�^�[�̍��W�X�V
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �L�����N�^�[�̍��W
	void MoveAstarCharaPos(const float delta_time, tnl::Vector3 & pos);
	
	// �L�����N�^�[�̉�]�X�V
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �L�����N�^�[�̍��W
	// arg3 ... �L�����N�^�[�̉�]
	void MoveAstarCharaRot(const float delta_time, tnl::Vector3& pos, tnl::Quaternion& rot);
	
	// �^�[�Q�b�g�̍��W�ƃ��[���X�V
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �^�[�Q�b�g�̍��W
	void MoveAstarTarget(const float delta_time, tnl::Vector3& pos);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �E��]�̃t���O��ݒ�
	// arg ... �E��]�̃t���O
	void SetLookSideRight(bool look_side_right) { m_look_side_right = look_side_right; }

	// �E��]�̃t���O���擾
	bool GetLookSideRight() const { return m_look_side_right; }

	// ����]�̃t���O��ݒ�
	// arg ... ����]�̃t���O
	void SetLookSideLeft(bool look_side_left) { m_look_side_left = look_side_left; }

	// ����]�̃t���O���擾
	bool GetLookSideLeft() const { return m_look_side_left; }

	// �L�����̐i�s�������擾
	const tnl::Vector3& GetCharaDirection() const
	{
		return m_chara_direction;
	}

	// Astar�̃|�C���^��ݒ�
	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>>& astar)
	{
		m_astar = astar;
	}

	// ���f�B�G�[�^�̃|�C���^��ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};

