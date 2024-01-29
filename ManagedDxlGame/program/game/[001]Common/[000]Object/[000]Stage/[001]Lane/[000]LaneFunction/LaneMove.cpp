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
	if (m_now_step >= m_goal_process.size()) 
	{
		// �S�[���ɓ��B�����珈�����I��
		m_goal_process.clear();
	
		return;
	}

	// �S�[���܂ł̌o�H���擾
	std::pair<int, int> current_grid = m_goal_process[m_now_step];
	// ���݂̃O���b�h�̒��S���W���擾
	tnl::Vector3 current_center_pos
		= wta::ConvertGridIntToFloat(current_grid, Lane::LANE_SIZE)
		+ tnl::Vector3(Lane::LANE_SIZE / 2, 0, Lane::LANE_SIZE / 2);
	// ���݂̈ʒu���璆�S���W�ւ̕����x�N�g�����v�Z
	m_target_direction = current_center_pos - pos;
	// ���S���W�܂ł̋������v�Z
	float distance_to_center = abs(m_target_direction.length());

	if (distance_to_center <= Lane::LANE_SIZE / 100)
	{
		// ���̃O���b�h�ɐi��
		m_now_step++;
	}
	else 
	{
		// �P�ʃx�N�g���ɕϊ�
		m_target_direction.normalize();
		// ���݂̃O���b�h�̒��S�֌������Ĉړ�
		pos += m_target_direction * m_move_speed * delta_time;
	}
}

void LaneMove::MoveAstarCharaPos(const float delta_time, tnl::Vector3& pos)
{
	if (m_now_step >= m_goal_process.size()) 
	{
		// �S�[���ɓ��B�����珈�����I��
		m_goal_process.clear();

		return;
	}

	// �S�[���܂ł̌o�H���擾
	//std::pair<int, int> current_grid = m_goal_process[m_now_step];
	//tnl::Vector3 goal_pos 
	//	= wta::ConvertGridIntToFloat(current_grid, Lane::LANE_SIZE) 
	//	+ tnl::Vector3(Lane::LANE_SIZE , 0, Lane::LANE_SIZE );
	//// ���݂̈ʒu����ڕW�n�_�ւ̕����x�N�g�����v�Z
	//m_direction = goal_pos - pos;
	//// �����𐳋K�����ĒP�ʃx�N�g���ɂ���
	//m_direction.normalize();
	//m_direction = tnl::Vector3::Transform(m_direction, rot_type.getMatrix());
	// �ړ����x�ɉ����Ĉʒu���X�V

	// ���݂̃O���b�h�ʒu
	std::pair<int, int> current_grid = m_goal_process[m_now_step];
	// ���̃O���b�h�ʒu�i�����ł͊ȒP�̂��߂Ɏ��̃X�e�b�v�Ƃ��Ă��܂����A���ۂɂ͖ڕW�ɉ����ĕύX����j
	std::pair<int, int> next_grid = m_goal_process[m_now_step + 1];

	// ���O���b�h�̒��S���W���v�Z
	tnl::Vector3 current_grid_pos = wta::ConvertGridIntToFloat(current_grid, Lane::LANE_SIZE);
	tnl::Vector3 next_grid_pos = wta::ConvertGridIntToFloat(next_grid, Lane::LANE_SIZE);

	// ���̃O���b�h�ւ̕����x�N�g�����v�Z
	m_chara_direction = (next_grid_pos - current_grid_pos);
	m_chara_direction.normalize();

	// �v���C���[�̈ړ�
	// �����ł́A�����x�N�g���ƈړ����x���g���āA�v���C���[�̐V�����ʒu���v�Z���܂��B
	pos += m_chara_direction * m_move_speed * delta_time;

	//// �K�v�ɉ����āA�v���C���[�̈ʒu���J�����̎�����Ɏ��܂�悤�ɒ������܂��B
	//AdjustPlayerPositionWithinCameraView(pos, cameraViewSize);
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