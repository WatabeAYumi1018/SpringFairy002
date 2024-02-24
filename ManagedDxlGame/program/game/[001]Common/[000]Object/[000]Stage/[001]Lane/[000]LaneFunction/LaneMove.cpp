#include "LaneMove.h"
#include "../../../../[002]Mediator/Mediator.h"


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

void LaneMove::MoveAstarTarget(const float delta_time, tnl::Vector3& pos) 
{	
	// �S�[���܂ł̌o�H���擾���A�Ō�̃O���b�h���ǂ������m�F
	if (m_now_step >= m_goal_process.size()) 
	{
		// �S�[���܂ł̌o�H���N���A
		m_goal_process.clear();
		// �������I��
		return; 
	}
	
	// ���݂̃O���b�h��ݒ�
	m_current_grid = m_goal_process[m_now_step];
	// ���̃O���b�h��ݒ�
	UpdateGrids();

	// ���̃O���b�h�̒��S���W���擾
	// 2 : ���S���W���擾���邽�߂̒萔
	tnl::Vector3 next_center_pos
		= wta::ConvertGridIntToFloat(m_next_grid, Lane::LANE_SIZE)
		+ tnl::Vector3(Lane::LANE_SIZE / 2, 0, Lane::LANE_SIZE / 2);

	// ���݂̈ʒu���璆�S���W�ւ̕����x�N�g�����v�Z
	m_target_direction = next_center_pos - pos;

	// ���S���W�܂ł̋������v�Z
	float distance_to_center = m_target_direction.length();
	
	// ���S�t�߂ɓ��B������X�e�b�v�X�V
	StepUpdate(delta_time, distance_to_center, pos);

	// �ړ��̂��߃x�N�g�����K��
	m_target_direction.normalize();
	// �ړ����x���X�V
	MoveSpeed(delta_time, m_target_direction, pos);
}

void LaneMove::MoveAstarCharaPos(const float delta_time, tnl::Vector3& pos)
{
	if (m_now_step >= m_goal_process.size())
	{
		// ���ɃS�[���v���Z�X���I�����Ă���ꍇ�͉������Ȃ�
		return;
	}

	// ���݂̃O���b�h�ʒu
	UpdateGrids();

	// ���O���b�h�̍��W���v�Z
	tnl::Vector3 current_grid_pos
			= wta::ConvertGridIntToFloat(m_current_grid, Lane::LANE_SIZE);

	tnl::Vector3 next_grid_pos
		= wta::ConvertGridIntToFloat(m_next_grid, Lane::LANE_SIZE);

	// ���̃O���b�h�ւ̕����x�N�g�����v�Z
	m_chara_direction = next_grid_pos - current_grid_pos;
	m_chara_direction.normalize();
	
	// �����x�N�g�������݂���ꍇ
	if (m_chara_direction.length() > 0)
	{
		// �ړ����x���X�V
		MoveSpeed(delta_time, m_chara_direction, pos);
	}
	else
	{
		// �����ŃQ�[���I������
		pos.z += m_move_speed * delta_time;
	}
}

void LaneMove::MoveAstarCharaRot(const float delta_time, tnl::Vector3& pos, tnl::Quaternion& rot)
{
	// �V������]���Z�o
	tnl::Quaternion new_rot
		= tnl::Quaternion::LookAtAxisY(pos, pos + m_chara_direction);

	if (m_look_side_right || m_look_side_left)
	{
		tnl::Vector3 camera_direction = m_mediator->GetCameraForward();

		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + camera_direction);
	}

	if (m_chara_direction.length() < 0)
	{
		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + tnl::Vector3(0, 0, 1));
	}

	// ��]���x���Z�o
	float rot_speed = delta_time * m_move_rotation / 4;
	// ���炩�ɉ�]���X�V
	rot.slerp(new_rot, rot_speed);
}

void LaneMove::MoveSpeed(const float delta_time, tnl::Vector3& direction,tnl::Vector3& pos)
{
	float max_move_speed = 5;
	float normal_move_speed = 2;

	if (m_mediator->GetIsTargetSpeedUp())
	{
		// �ړ����x���グ��
		pos += direction * m_move_speed * delta_time * max_move_speed;
	}
	else
	{
		// ���݂̃O���b�h�̒��S�֌������Ĉړ�
		pos += direction * m_move_speed * delta_time * normal_move_speed;
	}
}

void LaneMove::StepUpdate(const float delta_time, float distance, tnl::Vector3& pos)
{
	// ���S���W�܂ł̋��������ȉ��ɂȂ�����
	// 100 : ���S�_����̋����i�w�ǕύX�\��Ȃ����ߌŒ�l�j
	if (distance <= Lane::LANE_SIZE / 100)
	{
		// ���̃O���b�h�ɐi��
		m_now_step++;

		// �X�e�b�v�X�V��̃O���b�h��ݒ�
		UpdateGrids();
	}
}

void LaneMove::UpdateGrids()
{
	// ���̃O���b�h�ʒu���X�V
	if (m_now_step + 1 < m_goal_process.size())
	{
		m_next_grid = m_goal_process[m_now_step + 1];
	}
	else
	{
		// �Ō�̃O���b�h�ɂ���ꍇ�́A���݂̃O���b�h�����̃O���b�h�Ƃ��Ĉ���
		// ���݂̕������ێ�
		m_next_grid = m_current_grid;
	}
}

Lane::sLane LaneMove::GoalTile()
{
	std::vector<Lane::sLane> goal_process
					= m_mediator->GetStageLane();

	for (Lane::sLane& goal : goal_process)
	{
		// �S�[���̃��[��ID���擾
		if (goal.s_id == 2)
		{
			return goal;
		}
	}
}