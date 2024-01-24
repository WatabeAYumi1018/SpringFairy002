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

Gimmick::sGimmick Character::CurrentGimmickLane()
{
	// �v���C���[���W���O���b�h���W�ɕϊ�
	auto [chara_x, chara_z]
		= wta::ConvertFloatToGridInt(m_pos, Lane::LANE_SIZE);

	std::vector<Gimmick::sGimmick> item_vec = m_mediator->GetGimmickLoadLane();

	// �z����g�p���A�O���b�h���W����^�C��ID���擾
	for (Gimmick::sGimmick& item_lane : item_vec)
	{
		auto [item_lane_x, item_lane_z]
			= wta::ConvertFloatToGridInt(item_lane.s_pos, Lane::LANE_SIZE);

		// �L�������^�C���̗̈���ɂ��邩�𔻒�
		if (chara_x == item_lane_x && chara_z == item_lane_z)
		{
			m_mediator->SetGimmickIsActive(true);

			return item_lane;
		}
	}
	// �Y���Ȃ�
	return Gimmick::sGimmick();
}

GameCamera::sCamera Character::CurrentCamera()
{
	// �L�������W���O���b�h���W�ɕϊ�
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
			DrawStringEx(500, 50, -1, "�J�������[�����W.x : %d", camera_lane_x);
			DrawStringEx(500, 70, -1, "�J�������[�����W.z : %d", camera_lane_z);
			
			return camera_lane;
		}
	}
	// �Y���Ȃ�(���ꃌ�[������Ă�fixed�ɂȂ�悤��)
	return GameCamera::sCamera();
}

// �����̃C�x���g���[�����擾
Lane::sLaneEvent Character::CurrentEventLane()
{
	// �L�������W���O���b�h���W�ɕϊ�
	auto [chara_x, chara_z]
		= wta::ConvertFloatToGridInt(m_pos, Lane::LANE_SIZE);

	std::vector<Lane::sLaneEvent> event_lane_vec
		= m_mediator->GetStageLaneEvent();

	// �z����g�p���A�O���b�h���W����^�C��ID���擾
	for (Lane::sLaneEvent& event_lane : event_lane_vec)
	{
		auto [event_lane_x, event_lane_z]
			= wta::ConvertFloatToGridInt(event_lane.s_pos, Lane::LANE_SIZE);

		// �L�������^�C���̗̈���ɂ��邩�𔻒�
		if (chara_x == event_lane_x && chara_z == event_lane_z)
		{
			DrawStringEx(500, 90, -1, "�C�x���g���[�����W.x : %d", event_lane_x);
			DrawStringEx(500, 110, -1, "�C�x���g���[�����W.z : %d", event_lane_z);

			return event_lane;
		}
	}
	// �Y���Ȃ�
	Lane::sLaneEvent no_event;
	// id��-1��ݒ�
	no_event.s_id = -1;
	// no_event��Ԃ�
	return no_event; 
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