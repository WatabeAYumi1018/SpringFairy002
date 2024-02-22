#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Lane.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// ���[��csv�t�@�C���̓ǂݍ��݃N���X(�J�����Ɋւ���ǂݍ��݂�CameraLoad)
//
/////////////////////////////////////////////////////////////////////////////////////////


class LaneLoad
{

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

public:
	
	LaneLoad();

	~LaneLoad();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���[���z��̍���
	int m_lane_height = 0;
	// ���[���z��̕�
	int m_lane_width = 0;

	// ���[���z��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<int>> m_csv_lane;
	// ���[���z����i�[�p
	std::vector<Lane::sLane> m_lanes;

	// �C�x���g�ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<int>> m_csv_lane_event;
	// �C�x���g���i�[�p
	std::vector<Lane::sLaneEvent> m_lane_event;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ���[���z��̍��W�擾�Ɗi�[
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadLaneVector();

	// �C�x���g�z��̍��W�擾�Ɗi�[
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadLaneEventVector();

	//---------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// ���[���z��̍����擾
	int GetLaneHeight() const { return m_lane_height; }

	// ���[���z��̕��擾
	int GetLaneWidth() const {	return m_lane_width; }

	// ���[���z��̏��擾
	const std::vector<Lane::sLane>& GetLane() const { return m_lanes; }

	// �C�x���g�z��̏��擾
	const std::vector<Lane::sLaneEvent>& GetLaneEvent() const
	{
		return m_lane_event;
	}

	//---------------------------------------------------------------------------------//
};
