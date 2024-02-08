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

void LaneMove::MoveAstarTarget(const float delta_time, tnl::Vector3& pos) 
{	
	// �S�[���܂ł̌o�H���擾���A�Ō�̃O���b�h���ǂ������m�F
	if (m_now_step >= m_goal_process.size()) 
	{
		m_goal_process.clear();
	
		return; // �������I��
	}
	
	// �S�[���܂ł̌o�H���擾
	m_current_grid = m_goal_process[m_now_step];
	m_next_grid = m_goal_process[m_now_step + 1];

	// ���̃O���b�h�̒��S���W���擾
	tnl::Vector3 next_center_pos
		= wta::ConvertGridIntToFloat(m_next_grid, Lane::LANE_SIZE)
		+ tnl::Vector3(Lane::LANE_SIZE / 2, 0, Lane::LANE_SIZE / 2);

	// ���݂̈ʒu���璆�S���W�ւ̕����x�N�g�����v�Z
	m_target_direction = next_center_pos - pos;

	// ���S���W�܂ł̋������v�Z
	float distance_to_center = abs(m_target_direction.length());
	
	// ���S�t�߂ɓ��B������X�e�b�v�X�V
	StepUpdate(delta_time, distance_to_center, pos);
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

	// �΂߈ړ��̏ꍇ
	if (m_current_grid.first != m_next_grid.first
		&& m_current_grid.second != m_next_grid.second)
	{
		// �^�[�Q�b�g�����̃O���b�h�̒��S�ɋ߂Â��܂Œ��i
		// ���S���W�܂ł̋������v�Z
		float distance_to_center = abs(m_target_direction.length());
		
		// �^�[�Q�b�g�����S�ɋ߂Â��܂Œ��i
		if (distance_to_center <= Lane::LANE_SIZE / 100)
		{
			m_chara_direction = m_target_direction;

			m_chara_direction.normalize();
		}
		// ���̃O���b�h�̒��S�֌������Ē��i
		else
		{
			m_chara_direction= m_target_direction;
			
			m_chara_direction.normalize();
		}
	}

	// �����̏ꍇ
	else
	{
		// ���O���b�h�̒��S���W���v�Z
		tnl::Vector3 current_grid_pos
			= wta::ConvertGridIntToFloat(m_current_grid, Lane::LANE_SIZE);

		tnl::Vector3 next_grid_pos
			= wta::ConvertGridIntToFloat(m_next_grid, Lane::LANE_SIZE);

		// ���̃O���b�h�ւ̕����x�N�g�����v�Z
		m_chara_direction = (next_grid_pos - current_grid_pos);
		m_chara_direction.normalize();
	}

	// �����x�N�g�������݂���ꍇ
	if (m_chara_direction.length() > 0)
	{
		if (m_mediator->GetIsTargetSpeedUp())
		{
			// �ړ����x���グ��
			pos += m_chara_direction * m_move_speed * delta_time * 5;
		}
		else
		{
			// �v���C���[�̈ړ�
			pos += m_chara_direction * m_move_speed * delta_time * 2;
		}
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

	// ��]���x���Z�o
	float rot_speed = delta_time * m_move_rotation / 4;
	// ���炩�ɉ�]���X�V
	rot.slerp(new_rot, rot_speed);
}

void LaneMove::StepUpdate(const float delta_time, float distance, tnl::Vector3& pos)
{
	// ���S���W�܂ł̋��������ȉ��ɂȂ�����
	if (distance <= Lane::LANE_SIZE / 100)
	{
		// ���̃O���b�h�ɐi��
		m_now_step++;

		// �X�e�b�v�X�V��̃O���b�h��ݒ�
		UpdateGrids();
	}
	else
	{
		// �P�ʃx�N�g���ɕϊ�
		m_target_direction.normalize();

		if (m_mediator->GetIsTargetSpeedUp())
		{
			// �ړ����x���グ��
			pos += m_target_direction * m_move_speed * delta_time * 5;
		}
		else
		{
			// ���݂̃O���b�h�̒��S�֌������Ĉړ�
			pos += m_target_direction * m_move_speed * delta_time * 2;
		}
	}
}

void LaneMove::UpdateGrids()
{
	// ���̃O���b�h�ʒu���X�V
	if (m_now_step < m_goal_process.size())
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
		if (goal.s_id == 2)
		{
			return goal;
		}
	}
}



//void LaneMove::MoveAstarTarget(const float delta_time, tnl::Vector3& pos)
//{
//	// �S�[���܂ł̌o�H���擾���A�Ō�̃O���b�h���ǂ������m�F
//	if (m_now_step >= m_goal_process.size())
//	{
//		m_goal_process.clear();
//
//		return; // �������I��
//	}
//	// �S�[���܂ł̌o�H���擾
//	std::pair<int, int> current_grid = m_goal_process[m_now_step];
//	// ���݂̃O���b�h�̒��S���W���擾
//	tnl::Vector3 current_center_pos
//		= wta::ConvertGridIntToFloat(current_grid, Lane::LANE_SIZE)
//		+ tnl::Vector3(Lane::LANE_SIZE / 2, 0, Lane::LANE_SIZE / 2);
//
//	// ���݂̈ʒu���璆�S���W�ւ̕����x�N�g�����v�Z
//	m_target_direction = current_center_pos - pos;
//
//	// ���S���W�܂ł̋������v�Z
//	float distance_to_center = abs(m_target_direction.length());
//
//	// ���S���W�܂ł̋��������ȉ��ɂȂ�����
//	if (distance_to_center <= Lane::LANE_SIZE / 100)
//	{
//		// ���̃O���b�h�ɐi��
//		m_now_step++;
//	}
//	else
//	{
//		// �P�ʃx�N�g���ɕϊ�
//		m_target_direction.normalize();
//
//		if (m_mediator->GetIsTargetSpeedUp())
//		{
//			// �ړ����x���グ��
//			pos += m_target_direction * m_move_speed * delta_time * 5;
//		}
//		else
//		{
//			// ���݂̃O���b�h�̒��S�֌������Ĉړ�
//			pos += m_target_direction * m_move_speed * delta_time * 2;
//		}
//	}
//}
//
//void LaneMove::MoveAstarCharaPos(const float delta_time, tnl::Vector3& pos)
//{
//	if (m_now_step >= m_goal_process.size())
//	{
//		// ���ɃS�[���v���Z�X���I�����Ă���ꍇ�͉������Ȃ�
//		return;
//	}
//
//	// ���݂̃O���b�h�ʒu
//	std::pair<int, int> current_grid = m_goal_process[m_now_step];
//	// ���̃O���b�h�ʒu
//	std::pair<int, int> next_grid;
//
//	if (m_now_step + 1 < m_goal_process.size())
//	{
//		// ���̃O���b�h�����݂���ꍇ�́A������擾
//		next_grid = m_goal_process[m_now_step + 1];
//	}
//	else
//	{
//		// �Ō�̃O���b�h�ɂ���ꍇ�́A���݂̃O���b�h�����̃O���b�h�Ƃ��Ĉ���
//		// ���݂̕������ێ�
//		next_grid = current_grid;
//	}
//	// ���O���b�h�̒��S���W���v�Z
//	tnl::Vector3 current_grid_pos
//		= wta::ConvertGridIntToFloat(current_grid, Lane::LANE_SIZE);
//
//	tnl::Vector3 next_grid_pos
//		= wta::ConvertGridIntToFloat(next_grid, Lane::LANE_SIZE);
//
//	// ���̃O���b�h�ւ̕����x�N�g�����v�Z
//	m_chara_direction = (next_grid_pos - current_grid_pos);
//	m_chara_direction.normalize();
//
//	// �����x�N�g�������݂���ꍇ
//	if (m_chara_direction.length() > 0)
//	{
//		if (m_mediator->GetIsTargetSpeedUp())
//		{
//			// �ړ����x���グ��
//			pos += m_chara_direction * m_move_speed * delta_time * 5;
//		}
//		else
//		{
//			// �v���C���[�̈ړ�
//			pos += m_chara_direction * m_move_speed * delta_time * 2;
//		}
//	}
//	else
//	{
//		// �����ŃQ�[���I������
//		pos.z += m_move_speed * delta_time;
//	}
//
//	// �΂߈ړ��̔���
//	if (current_grid.first != next_grid.first
//		&& current_grid.second != next_grid.second)
//	{
//		// current_time���X�V
//		m_current_time += delta_time;
//
//		// current_time��blend_time�𒴂��Ȃ��悤�ɐ���
//		if (m_current_time > m_blend_time) m_current_time = m_blend_time;
//
//		// UniformLerp���g�p���Č��݂̕����ƖڕW�̕�������
//		m_chara_direction
//			= tnl::Vector3::UniformLerp(m_chara_direction, m_target_direction, m_blend_time, m_current_time);
//	}
//	else
//	{
//		// �΂߈ړ��łȂ��ꍇ��current_time�����Z�b�g
//		m_current_time = 0.0f;
//	}
//}



//void LaneMove::UpdateRotation(const tnl::Vector3& direction, tnl::Quaternion& rot, const float delta_time) {
//	// �V������]���Z�o
//	tnl::Quaternion new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + direction);
//
//	// ���炩�ɉ�]���X�V
//	rot.slerp(new_rot, delta_time * m_move_rotation);
//}

//void LaneMove::MoveAstar(const float delta_time
//						 , tnl::Vector3& pos
//						 , tnl::Quaternion& rot)
//{
//	if (m_now_step < m_goal_process.size())
//	{
//		// �S�[���܂ł̌o�H���擾
//		std::pair<int, int> process_pos = m_goal_process[m_now_step];
//		//�S�[���܂ł̌o�H�����[���h���W�ɕϊ�
//		tnl::Vector3 goal_process_pos
//			= wta::ConvertGridIntToFloat(process_pos, Lane::LANE_SIZE);
//		// �v���C���[�̍��W�Ɖ�]�̍X�V
//		AutoMoveMatrix(delta_time, goal_process_pos, pos,rot);
//	}
//}
//
//void LaneMove::MoveAstarPos(const float delta_time, tnl::Vector3& pos)
//{
//	if (m_now_step < m_goal_process.size())
//	{
//		// �S�[���܂ł̌o�H���擾
//		std::pair<int, int> process_pos = m_goal_process[m_now_step];
//		//�S�[���܂ł̌o�H�����[���h���W�ɕϊ�
//		tnl::Vector3 goal_process_pos
//			= wta::ConvertGridIntToFloat(process_pos, Lane::LANE_SIZE);
//		// �^�[�Q�b�g�̍��W�Ɖ�]�̍X�V
//		AutoMovePos(delta_time, goal_process_pos, pos);
//		// �^�[�Q�b�g���ڕW�n�_�ɓ��B�����ꍇ
//		if (ReachedNextLane(goal_process_pos, pos))
//		{
//			// ���̃X�e�b�v�ɐi��
//			m_now_step++;
//		}
//		else
//		{
//			// �i�s�s�G���A�i-1�j�ɓ��������ǂ����̃`�F�b�N
//			int current_tile_id = m_astar->getTileID(wta::ConvertFloatToGridInt(pos, Lane::LANE_SIZE), m_mediator->GetStageLane(), Lane::LANE_SIZE);
//			
//			// ���ݒn���i�s�s�G���A�Ȃ�
//			if (current_tile_id == -1) 
//			{
//				// �C�����邽�߂Ɏ��̐i�s�\�ȃ^�C����T��
//				int next_step = m_now_step + 1;
//				if (next_step < m_goal_process.size())
//				{
//					std::pair<int, int> next_process_pos = m_goal_process[next_step];
//					tnl::Vector3 next_goal_process_pos = wta::ConvertGridIntToFloat(next_process_pos, Lane::LANE_SIZE);
//
//					// ���ɐi�ނׂ��^�C���ւ̕����x�N�g�����v�Z
//					tnl::Vector3 correction_direction = next_goal_process_pos - pos;
//					correction_direction.normalize();
//
//					// ���W�𑦍��ɏC��
//					pos += correction_direction * m_move_speed * delta_time;
//				}
//			}
//		}
//	}
//	else
//	{
//		// �S�[���ɓ��B������I��
//		m_goal_process.clear();
//	}
//}

//void LaneMove::AutoMoveMatrix(const float delta_time
//							  , tnl::Vector3& goal_pos
//							  , tnl::Vector3& pos
//							  , tnl::Quaternion& rot)
//{
//	AutoMovePos(delta_time, goal_pos, pos);
//	// �V������]���Z�o�idirection�����������悤�Ɂj
//	tnl::Quaternion new_rot;
//
//	// ���݂̈ʒu����ڕW�ʒu�ւ̕����x�N�g�����v�Z
//	tnl::Vector3 direction = pos - goal_pos;
//	// �K�v�ɉ����Đ��K��
//	direction.normalize();
//
//	// ��]���Z�o
//	new_rot = tnl::Quaternion::LookAtAxisY(pos, pos + direction);
//
//	if (m_look_side_right || m_look_side_left)
//	{
//		tnl::Vector3 camera_direction = m_mediator->GetCameraForward();
//
//		new_rot = tnl::Quaternion::LookAtAxisY(pos, pos - camera_direction);
//	}
//
//	// ��]���x���Z�o
//	float rot_speed = delta_time * m_move_rotation / 4;
//	// ���炩�ɉ�]���X�V
//	rot.slerp(new_rot, rot_speed);
//}
//
//void LaneMove::AutoMovePos(float delta_time
//							, tnl::Vector3& goal_pos
//							, tnl::Vector3& pos)
//{
//	// ���݂̍��W�ƃS�[���܂ł̍��W�̍����Z�o
//	m_new_pos = goal_pos - pos;
//	// ���K��
//	m_new_pos.normalize();
//	// ���W���X�V
//	pos += m_new_pos * m_move_speed * delta_time;
//}
//
//

//
//bool LaneMove::ReachedNextLane(tnl::Vector3& goal_pos,tnl::Vector3& pos)
//{
//	// �v���C���[���W�ƃS�[���̍����Z�o
//	float distance_pos = (goal_pos - pos).length();
//	// ��r�̂��߂Ɍ^�ϊ�
//	int distance = static_cast<int>(distance_pos);
//
//	return distance < Lane::LANE_SIZE;
//}

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