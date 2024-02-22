#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// �Q�[���J�����̍X�V�������s���N���X
// �������𑼂̃N���X���l�����������ꍇ�A�Q�Ɠn�������G�ɂȂ舵���ɂ����Ȃ邽��
// �@�����1�N���X�ɂ܂Ƃ߂Ă���
//
///////////////////////////////////////////////////////////////////////////



class GameCamera : public dxe::Camera
{

public:

	enum class eCameraType
	{
		// �Œ肳�ꂽ���_
		e_fixed,
		// �T�C�h�r���[(�L�����N�^�[���E�����猩��)
		e_right_side,
		// �T�C�h�r���[(�L�����N�^�[���������猩��)
		e_left_side,
		// �T�C�h�r���[(�L�����N�^�[�͌�납��)
		e_right_side_back,
		// �T�C�h�r���[(�L�����N�^�[�͌�납��)
		e_left_side_back,
		// ���ʂ���̎��_
		e_front,
		// �ォ��̎��_
		e_bottom,
		// �v���C���[����̉�]
		e_rotate,
		// �v���C���[�Ǐ](�K�v�ł����)
		e_follow,
		// �J�����Ǝ��̑���(�f�o�b�O�p)
		e_control,
		// �A�N�Z�X�s��
		e_none
	};

	struct sCamera
	{
		int s_id;
		tnl::Vector3 s_pos;
	};

	struct sCameraInfo
	{
		int s_id;
		eCameraType s_type;
	};

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	GameCamera();
	~GameCamera() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// ��]�p�x
	float m_rot_angle = 0.0f;
	// �Œ�t���O
	bool m_is_fixed = false;


	// �Ǐ]����Ώ�(�^���v���C���[��z��)
	// �e���l : �^���v���C���[�Ƃ̋�����
	tnl::Vector3 m_offset = { 0, 0, -400 };
	
	// �����o�H�ɂ���]
	tnl::Quaternion m_rot;

	// �X�e�[�W�t�F�[�Y
	StagePhase::eStagePhase m_now_stage
					= StagePhase::eStagePhase::e_flower;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GameCamera, &GameCamera::SeqFixed);

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// ���`��Ԋ֐�
	// arg1 ... �J�n���W
	// arg2 ... �I�����W
	// arg3 ... ��ԌW��
	tnl::Vector3 Lerp(const tnl::Vector3& start
					  , const tnl::Vector3& end, float t);

	// �J�����̏�Ԃ��擾
	void ConditionType();

	// �Œ�
	// arg ... �I�t�Z�b�g���W
	void Fixed(const tnl::Vector3& offset);
	
	// �X���C�h����
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �I�t�Z�b�g���W
	// arg3 ... �ړ����x
	void ToSlide(const float delta_time, const tnl::Vector3& offset, float speed);
	
	// 360�x��]����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void Rotate(const float delta_time);

	// �Œ肳�ꂽ���_
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFixed(const float delta_time);

	// �E�T�C�h�r���[
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqRightSide(const float delta_time);

	// �E�T�C�h����fix�ֈڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqRightSideToFix(const float delta_time);

	//	���T�C�h�r���[
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqLeftSide(const float delta_time);

	// ���T�C�h����fix�ֈڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqLeftSideToFix(const float delta_time);

	// ���ʂ���̎��_
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFront(const float delta_time);

	// ���ʂ���fix�ֈڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFrontToFix(const float delta_time);

	// �v���C���[����̉�]
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqRotate(const float delta_time);

	// �v���C���[����̉�]����fix�ֈڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqRotateToFix(const float delta_time);

	//-----�f�o�b�O�p-----//

	//�}�E�X�̉�]���쐧��
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void Control(const float delta_time);

	// ���ӂ�360�x��]����
	// arg1 ... ��]���W
	// arg2 ... �_���W
	// arg3 ... ��]��
	// arg4 ... ��]�p�x
	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
									, const tnl::Vector3& pivot
									, const tnl::Vector3& axis
									, float angle);

	// �v���C���[�Ǐ]
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFollow(const float delta_time);

	// �v���C���[����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqControl(const float delta_time);

	//--------------------//

public:

	void update(const float delta_time) override;

	// �t���X�^���Ƃ̓����蔻��
	void IsInFlustum();

	// �^�[�Q�b�g�̊T�O�𖳂������p������
	inline tnl::Vector3 up()
	{
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_rot);
		return up_;
	}

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �Œ�J�������ǂ����擾
	bool GetIsFixed() const { return m_is_fixed; }

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//
};