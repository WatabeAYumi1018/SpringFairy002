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

	// �Ǐ]����Ώ�(�^���v���C���[��z��)
	// �e���l : �^���v���C���[�Ƃ̋�����
	tnl::Vector3 m_offset = { 0, 200, -400 };
	// �Ǐ]�ɂ����W�␳
	tnl::Vector3 m_fix_pos = { 0,0,0 };
	// �����o�H�ɂ���]
	tnl::Quaternion m_rot;


	StagePhase::eStagePhase m_now_stage_phase = StagePhase::eStagePhase::e_fly;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GameCamera, &GameCamera::SeqFixed);

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	//// �����̃J�������[�����擾
	//sCamera CurrentCamera();

	//// �����̃J���������擾
	//sCameraInfo CurrentCameraType();

	// �t���X�^���Ƃ̓����蔻��
	void IsInFlustum();
	// ���`��Ԋ֐�
	tnl::Vector3 Lerp(const tnl::Vector3& start
					  , const tnl::Vector3& end, float t);
	// �J�����̏�Ԃ��擾
	void ConditionType();


	// �J�����̌Œ菈��
	void Fixed();
	// �J�����̃T�C�h�r���[����
	void Side(float offset);
	// �J�����̃T�C�h�r���[�ֈڍs����
	void ToSide(const float delta_time,float offset);
	// �T�C�h����Œ�ֈڍs
	void ToFix(const float delta_time);
	// �J�����̐��ʂ���̎��_����
	void Front();
	// 360�x��]����
	void rotate(const float delta_time);

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


	// �ォ��̎��_����
	void Bottom();
	// ���̎��_
	bool SeqBottom(const float delta_time);
	// ������fix�ֈڍs
	bool SeqBottomToFix(const float delta_time);

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

	void update(const float delta_time) override;

	//// �^�[�Q�b�g�̊T�O�𖳂������p������
	inline tnl::Vector3 up()
	{
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, m_rot);
		return up_;
	}
	inline tnl::Vector3 down() { return -up(); }

	//inline tnl::Vector3 forward() override
	//{
	//	target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rot);
	//	return tnl::Vector3::Normalize(target_ - pos_);
	//}

	//inline tnl::Vector3 back() override { return -forward(); }

	//inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }

	//inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};


//// �t���X�^���J�����O�̃p�����[�^
//struct sFrustumParam
//{
//	// ���ʂ̖@���x�N�g��
//	// 3D��ԓ��̊e���ʂɐ����ȃx�N�g��
//	// �t���X�^���J�����O�ł́A�J�����̃r���[�t���X�^�����\������e���ʂɑ΂��āA
//	// ���̕��ʂɐ����ȕ������w���x�N�g�����v�Z
//	// s_normal : �Y������t���X�^�����ʂɐ����ȕ���������3�����x�N�g��
//	tnl::Vector3 s_normal;
//	// ���ʕ������̒萔��
//	// ���_���畽�ʂ܂ł̋����������l
//	float s_d;
//};

//int m_frustum_plane_num = 4;


//// �t���X�^���J�����O��6���ʂ̃p�����[�^
//sFrustumParam m_frustum_param[6];

//// ���̖ڕW�ʒu���擾
//void GetPlayerAutoPathInfo( const float delta_time
//							,tnl::Vector3& pos
//							, tnl::Quaternion& rot);
//// �v���C���[�̌�납�瓯������������
//void RotateBackToPlayer(float delta_time);

//// ���E���ʂ̍X�V
//void UpdateFrustumPlane();
//// �t���X�^���J�����O�̋��E������
//bool IsInFrustum(const tnl::Vector3& pos);
//// �v���C���[�̍��W���t���X�^�����ɖ߂�
//void ReturnPlayerPos(const tnl::Vector3& pos);

////// �t���X�^���J�����O�̃R�[�i�[�v�Z
////std::vector<tnl::Vector3> CalculateFrustumCorners(const tnl::Matrix& invViewProj);
////// �t���X�^���J�����O��6���ʕ`��
////void DrawFrustumPlane();

////// �t���X�^���J�����O��6���ʂ̃p�����[�^���擾
////sFrustumParam GetFrustumParam(int index)
////{
////	return m_frustum_param[index];
////}

//void DrawFrustumPlane(const tnl::Vector3& normal, float d) ;
