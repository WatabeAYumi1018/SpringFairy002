#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../GameCamera.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// �J�����Ɋւ���csv�t�@�C���̓ǂݍ��݃N���X
//
///////////////////////////////////////////////////////////////////////////


class CameraLoad
{

public:

	CameraLoad();

	~CameraLoad();

private:

	// �J�����^�C�v�̑���
	int m_camera_type = 0;
	// ���[���z��̍���
	int m_lane_height = 0;
	// ���[���z��̕�
	int m_lane_width = 0;

	// �J�����ǂݎ���p(csv�t�@�C��)
	std::vector<std::vector<int>> m_csv_camera_lane;
	// �J�����z����i�[�p
	std::vector<GameCamera::sCamera> m_camera_lane;

	// �J�������ǂݎ���p(csv�t�@�C��)
	std::vector<std::vector<tnl::CsvCell>> m_csv_camera_info;
	// �J�������i�[�p
	std::vector<GameCamera::sCameraInfo> m_camera_info;


	std::shared_ptr<Mediator> m_mediator = nullptr;


	// �J�����z��̍��W�擾�Ɗi�[
	void LoadCameraVector();
	// �J�����̏��擾
	void LoadCameraInfo();
	// �J�������̕������enum�ɕϊ�
	GameCamera::eCameraType ConvertStringToType(const std::string& type);

public:

	GameCamera::sCameraInfo GetCameraInfoById(int id);


	// �J�����^�C�v�̑����擾
	int GetCameraType() const { return m_camera_type; }
	// �J�����z��̍����擾
	int GetLaneHeight() const { return m_lane_height; }
	// �J�����z��̕��擾
	int GetLaneWidth() const { return m_lane_width; }

	// �J�����z��̏��擾
	const std::vector<GameCamera::sCamera>& GetCameraLane() const
	{
		return m_camera_lane; 
	}

	// �J�������擾
	const std::vector<GameCamera::sCameraInfo>& GetCameraInfo() const
	{
		return m_camera_info;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};