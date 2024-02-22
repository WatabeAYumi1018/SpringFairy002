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

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	CameraLoad();
	~CameraLoad();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �J�����^�C�v�̑���
	int m_camera_type = 0;
	// ���[���z��̍���
	int m_lane_height = 0;
	// ���[���z��̕�
	int m_lane_width = 0;

	// �J�������[���̓ǂݎ���p(csv�t�@�C��)
	std::vector<std::vector<int>> m_csv_camera_lane;
	// �J�������[�����i�[�p
	std::vector<GameCamera::sCamera> m_camera_lane;

	// �J�������ǂݎ���p(csv�t�@�C��)
	std::vector<std::vector<tnl::CsvCell>> m_csv_camera_info;
	// �J�������i�[�p
	std::vector<GameCamera::sCameraInfo> m_camera_info;

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �J�����z��̍��W�擾�Ɗi�[
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadCameraVector();

	// �J�����̏��擾
	// tips ... ���������Ɉ�x�����Ăяo��
	void LoadCameraInfo();

	// �J�������̕������enum�ɕϊ�
	// arg ... �J�������̕�����
	// ��string�ł͂Ȃ�int�^�ɂ��������g���₷���Ǝv�����߁A���P�\��B
	GameCamera::eCameraType ConvertStringToType(const std::string& type);

public:

	// �Y������J�������̎擾
	// arg ... �J����ID
	GameCamera::sCameraInfo GetCameraInfoById(int id);

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

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

	// ���f�B�G�[�^�̐ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//
};