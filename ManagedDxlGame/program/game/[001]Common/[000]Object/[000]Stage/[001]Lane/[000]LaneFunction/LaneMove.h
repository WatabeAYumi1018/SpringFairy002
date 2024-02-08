#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../wta_library/wta_Astar.h"
#include "../Lane.h"

class Mediator;


class LaneMove
{

public:
	
	LaneMove() {}

	~LaneMove();

private:

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

	tnl::Vector3 m_target_direction;
	tnl::Vector3 m_chara_direction;
	// ���݂̃O���b�h�̒��S�_
	tnl::Vector3 m_current_center_pos;

	// ���݂̃O���b�h�ʒu
	std::pair<int, int> m_current_grid;
	// ���̃O���b�h�ʒu
	std::pair<int, int> m_next_grid;


	// A*����̌o�H
	std::vector<std::pair<int, int>> m_goal_process;

	std::shared_ptr<wta::Astar<Lane::sLane>> m_astar = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �^�[�Q�b�g�����S�ɓ��B����������
	void StepUpdate(const float delta_time,float distance, tnl::Vector3& pos);
	// ���W�X�V�̑��x����
	void MoveSpeed(const float delta_time, tnl::Vector3& pos);
	// �O���b�h�̍X�V����
	void UpdateGrids();

	// �S�[���̃��[��ID���擾
	Lane::sLane GoalTile();


public:

	// �S�[���܂ł̌o�H���擾
	void GetAutoMove();

	// �L�����N�^�[�̍��W�X�V
	void MoveAstarCharaPos(const float delta_time, tnl::Vector3 & pos);
	
	void MoveAstarCharaRot(const float delta_time, tnl::Vector3& pos, tnl::Quaternion& rot);
	// �^�[�Q�b�g�̍��W�ƃ��[���X�V
	void MoveAstarTarget(const float delta_time, tnl::Vector3& pos);



	void SetLookSideRight(bool look_side_right) { m_look_side_right = look_side_right; }

	bool GetLookSideRight() const { return m_look_side_right; }

	void SetLookSideLeft(bool look_side_left) { m_look_side_left = look_side_left; }

	bool GetLookSideLeft() const { return m_look_side_left; }

	const tnl::Vector3& GetCharaDirection() const
	{
		return m_chara_direction;
	}

	void SetAstar(std::shared_ptr<wta::Astar<Lane::sLane>>& astar)
	{
		m_astar = astar;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};


//void SetNowPos(tnl::Vector3 pos) { m_now_pos = pos; }

//tnl::Vector3 GetNewPos() const { return m_new_pos; }

//void SetNowRot(tnl::Quaternion rot) { m_now_rot = rot; }

//tnl::Quaternion GetNewRot() const { return m_new_rot; }


	//// �����^�]�ɂ��s��X�V
	//void AutoMoveMatrix(const float delta_time
	//					, tnl::Vector3& goal_pos
	//					, tnl::Vector3& pos
	//					, tnl::Quaternion& rot);

	//// �����^�]�ɂ����W�X�V
	//void AutoMovePos(float delta_time
	//				 , tnl::Vector3& goal_pos
	//				 , tnl::Vector3& pos);

	// A�X�^�[�ɂ�鎩���^�]�s��X�V����
	//void MoveAstar(const float delta_time
	//				, tnl::Vector3& pos
	//				, tnl::Quaternion& rot);


	//void MoveToGridCenter(const float delta_time, tnl::Vector3& pos, tnl::Quaternion& rot);

	//// ���̃��[���ɓ��B����������(���N���X�ł̎g�p�̂��߂̊ȈՏ����֐�)
	//bool NextLane();

	//// ���̃��[���ɓ��B����������
	//bool ReachedNextLane(tnl::Vector3& goal_pos, tnl::Vector3& pos);

	//void UpdateRotation(const tnl::Vector3& direction, tnl::Quaternion& rot, const float delta_time);
