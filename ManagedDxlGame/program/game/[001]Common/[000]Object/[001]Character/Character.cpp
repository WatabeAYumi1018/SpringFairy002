#include "../../../../wta_library/wta_Convert.h"
#include "../../[002]Mediator/Mediator.h"
#include "Character.h"


void Character::StartPos()
{
	for (const Lane::sLane& start : m_mediator->GetStageLane())
	{
		if (start.s_id == 1)
		{
			// �O���b�h�̒��S���W�ɐݒ�
			m_pos = start.s_pos + tnl::Vector3(Lane::LANE_SIZE / 2, 0, Lane::LANE_SIZE / 2);
		}
	}
}

// �������[�����擾
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

GameCamera::sCamera Character::CurrentCameraLane()
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
	return 	m_mediator->GetCameraTypeInfoById(CurrentCameraLane().s_id);
}