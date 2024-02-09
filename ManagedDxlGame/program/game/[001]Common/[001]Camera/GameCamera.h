#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"


class Mediator;


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

	GameCamera();

	~GameCamera() {}

private:

	// ��]�p�x
	float m_rot_angle = 0.0f;

	bool m_is_fixed = false;


	// �Ǐ]����Ώ�(�^���v���C���[��z��)
	// �e���l : �^���v���C���[�Ƃ̋�����
	tnl::Vector3 m_offset = { 0, 200, -400 };
	// �����o�H�ɂ���]
	tnl::Quaternion m_rot;

	StagePhase::eStagePhase m_now_stage_phase
					= StagePhase::eStagePhase::e_flower;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GameCamera, &GameCamera::SeqFixed);

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ���`��Ԋ֐�
	tnl::Vector3 Lerp(const tnl::Vector3& start
					  , const tnl::Vector3& end, float t);

	// �J�����̏�Ԃ��擾
	void ConditionType();

	// �Œ�
	void Fixed(const tnl::Vector3& offset);
	// �X���C�h����
	void ToSlide(const float delta_time, const tnl::Vector3& offset, float speed);
	// 360�x��]����
	void Rotate(const float delta_time);

	// �Œ肳�ꂽ���_
	bool SeqFixed(const float delta_time);
	// �E�T�C�h�r���[
	bool SeqRightSide(const float delta_time);
	// �E�T�C�h����fix�ֈڍs
	bool SeqRightSideToFix(const float delta_time);
	//	���T�C�h�r���[
	bool SeqLeftSide(const float delta_time);
	// ���T�C�h����fix�ֈڍs
	bool SeqLeftSideToFix(const float delta_time);
	// ���ʂ���̎��_
	bool SeqFront(const float delta_time);
	// ���ʂ���fix�ֈڍs
	bool SeqFrontToFix(const float delta_time);
	// �v���C���[����̉�]
	bool SeqRotate(const float delta_time);
	// �v���C���[����̉�]����fix�ֈڍs
	bool SeqRotateToFix(const float delta_time);


	//-----�f�o�b�O�p-----//

	//�}�E�X�̉�]���쐧��
	void Control(const float delta_time);

	// ���ӂ�360�x��]����
	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
									, const tnl::Vector3& pivot
									, const tnl::Vector3& axis
									, float angle);

	// �v���C���[�Ǐ]
	bool SeqFollow(const float delta_time);

	// �v���C���[����
	bool SeqControl(const float delta_time);

	//--------------------//

public:

	// �t���X�^���Ƃ̓����蔻��
	void IsInFlustum();

	void update(const float delta_time) override;

	// �^�[�Q�b�g�̊T�O�𖳂������p������
	inline tnl::Vector3 up()
	{
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_rot);
		return up_;
	}

	//inline tnl::Vector3 down() { return -up(); }

	bool IsFixed() const { return m_is_fixed; }

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};