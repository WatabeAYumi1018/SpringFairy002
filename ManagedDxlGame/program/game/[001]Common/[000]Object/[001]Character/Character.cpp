#include "../../../../wta_library/wta_Convert.h"
#include "../../[002]Mediator/Mediator.h"
#include "Character.h"


void Character::StartPos()
{
	for (const auto& start : m_mediator->GetStageLane())
	{
		if (start.s_id == 1)
		{
			m_pos = start.s_pos;

			m_pos.z = 0;
		}
	}
}

// �v���C���[�̑������[�����擾
Lane::sLane Character::CurrentMoveLane()
{
	// �v���C���[���W���O���b�h���W�ɕϊ�
	auto [chara_x, chara_z]
		= wta::ConvertFloatToGridInt(m_pos, Lane::LANE_SIZE);

	std::vector<Lane::sLane> lane_vec = m_mediator->GetStageLane();

	// �z����g�p���A�O���b�h���W����^�C��ID���擾
	for (Lane::sLane& lane : lane_vec)
	{
		auto [lane_x, lane_z]
			= wta::ConvertFloatToGridInt(lane.s_pos, Lane::LANE_SIZE);

		// �L�������^�C���̗̈���ɂ��邩�𔻒�
		if (chara_x == lane_x && chara_z == lane_z)
		{
			return lane;
		}
	}
	// �Y���Ȃ�
	return Lane::sLane();
}

Item::sItem Character::CurrentItemLane()
{
	// �v���C���[���W���O���b�h���W�ɕϊ�
	auto [chara_x, chara_z]
		= wta::ConvertFloatToGridInt(m_pos, Lane::LANE_SIZE);

	std::vector<Item::sItem> item_vec = m_mediator->GetItemLoadLane();

	// �z����g�p���A�O���b�h���W����^�C��ID���擾
	for (Item::sItem& item_lane : item_vec)
	{
		auto [item_lane_x, item_lane_z]
			= wta::ConvertFloatToGridInt(item_lane.s_pos, Lane::LANE_SIZE);

		// �L�������^�C���̗̈���ɂ��邩�𔻒�
		if (chara_x == item_lane_x && chara_z == item_lane_z)
		{
			m_mediator->SetItemIsActive(true);

			return item_lane;
		}
	}
	// �Y���Ȃ�
	return Item::sItem();
}

GameCamera::sCamera Character::CurrentCamera()
{
	// �J�������W���O���b�h���W�ɕϊ�
	auto [chara_x, chara_z]
		= wta::ConvertFloatToGridInt(m_pos, Lane::LANE_SIZE);

	std::vector<GameCamera::sCamera> camera_lane_vec
		= m_mediator->GetCameraLaneVector();

	// �z����g�p���A�O���b�h���W����^�C��ID���擾
	for (GameCamera::sCamera& camera_lane : camera_lane_vec)
	{
		auto [camera_lane_x, camera_lane_z]
			= wta::ConvertFloatToGridInt(camera_lane.s_pos, Lane::LANE_SIZE);

		// �L�������^�C���̗̈���ɂ��邩�𔻒�
		if (chara_x == camera_lane_x && chara_z == camera_lane_z)
		{
			return camera_lane;
		}
	}
	// �Y���Ȃ�
	return GameCamera::sCamera();
}

MATRIX Character::CalcMatrix()
{
	// �ϊ��s����擾
	return m_matrix = GetTransformMatrix();
}

GameCamera::sCameraInfo Character::CurrentCameraType()
{
	// ���݂̃J�����̃^�C�v���擾
	return 	m_mediator->GetCameraTypeInfoById(CurrentCamera().s_id);
}