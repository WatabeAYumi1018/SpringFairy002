#include "LaneMove.h"
#include "../../../../[002]Mediator/Mediator.h"



LaneMove::~LaneMove()
{
	m_goal_process.clear();
}

void LaneMove::GetAutoMove()
{
	// csv�̃��[�������擾
	std::vector<Lane::sLane> lanes = m_mediator->GetStageLane();
	// �S�[���̃��[��ID���擾
	Lane::sLane goal_tile = GoalTile();
	// ���[���̕����擾
	int width = m_mediator->GetStageLaneWidth();
	// ���[���̍������擾
	int height = m_mediator->GetStageLaneHeight();
	// �v���C���[�̍��W���擾
	tnl::Vector3 pos = m_mediator->GetPlayerPos();
	// �v���C���[�̏����ʒu����Z�o
	m_astar->SearchTileID_AStar(pos, goal_tile, Lane::LANE_SIZE, lanes, width, height);
	// �S�[���܂ł̌o�H���擾
	m_goal_process = m_astar->GetGoalProcess();
}

void LaneMove::MoveAstar(const float delta_time
						 , tnl::Vector3& pos
						 , tnl::Quaternion& rot)
{
	if (m_now_step < m_goal_process.size())
	{
		// �S�[���܂ł̌o�H���擾
		std::pair<int, int> process_pos = m_goal_process[m_now_step];
		//�S�[���܂ł̌o�H�����[���h���W�ɕϊ�
		tnl::Vector3 goal_process_pos
			= wta::ConvertGridIntToFloat(process_pos, Lane::LANE_SIZE);
		// �v���C���[�̍��W�Ɖ�]�̍X�V
		AutoMoveMatrix(delta_time, goal_process_pos, pos,rot);
	}
}

void LaneMove::MoveAstarPos(const float delta_time, tnl::Vector3& pos)
{
	if (m_now_step < m_goal_process.size())
	{
		// �S�[���܂ł̌o�H���擾
		std::pair<int, int> process_pos = m_goal_process[m_now_step];
		//�S�[���܂ł̌o�H�����[���h���W�ɕϊ�
		tnl::Vector3 goal_process_pos
			= wta::ConvertGridIntToFloat(process_pos, Lane::LANE_SIZE);
		// �^�[�Q�b�g�̍��W�Ɖ�]�̍X�V
		AutoMovePos(delta_time, goal_process_pos, pos);
		// �^�[�Q�b�g���ڕW�n�_�ɓ��B�����ꍇ
		if (ReachedNextLane(goal_process_pos, pos))
		{
			// ���̃X�e�b�v�ɐi��
			m_now_step++;
		}
	}
	else
	{
		// �S�[���ɓ��B������I��
		m_goal_process.clear();
	}
}

void LaneMove::AutoMoveMatrix(const float delta_time
							  , tnl::Vector3& goal_pos
							  , tnl::Vector3& pos
							  , tnl::Quaternion& rot)
{
	AutoMovePos(delta_time, goal_pos, pos);
	// �V������]���Z�o�idirection�����������悤�Ɂj
	tnl::Quaternion new_rot;

	if (m_look_side_right)
	{
		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(-1, 0, 0));
	}
	else if (m_look_side_left)
	{
		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(1, 0, 0));
	}
	else
	{
		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + m_new_pos);
	}
	// ��]���x���Z�o
	float rot_speed = delta_time * m_move_rotation / 4;
	// ���炩�ɉ�]���X�V
	rot.slerp(new_rot, rot_speed);
}

void LaneMove::AutoMovePos(float delta_time
							, tnl::Vector3& goal_pos
							, tnl::Vector3& pos)
{
	// ���݂̍��W�ƃS�[���܂ł̍��W�̍����Z�o
	m_new_pos = goal_pos - pos;
	// ���K��
	m_new_pos.normalize();
	// ���W���X�V
	pos += m_new_pos * m_move_speed * delta_time;
}


Lane::sLane LaneMove::GoalTile()
{
	for (const auto& goal : m_mediator->GetStageLane())
	{
		if (goal.s_id == 2)
		{
			return goal;
		}
	}
}

bool LaneMove::ReachedNextLane(tnl::Vector3& goal_pos,tnl::Vector3& pos)
{
	// �v���C���[���W�ƃS�[���̍����Z�o
	float distance_pos = (goal_pos - pos).length();
	// ��r�̂��߂Ɍ^�ϊ�
	int distance = static_cast<int>(distance_pos);

	return distance < Lane::LANE_SIZE;
}

//bool LaneMove::NextLane()
//{
//	// ���̃X�e�b�v�ɐi�񂾏ꍇ
//	if (m_now_step != m_old_step)
//	{
//		// �V�������[���Ɉړ��������Ƃ����o
//		m_old_step = m_now_step;
//
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}