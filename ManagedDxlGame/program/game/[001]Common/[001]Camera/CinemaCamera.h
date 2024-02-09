#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"


class Mediator;


class CinemaCamera : public dxe::Camera
{

public:

	CinemaCamera();

	~CinemaCamera() {}

private:

	// �X�N���[���n���h��
	int m_screen_hdl = 0;

	bool m_move_mouse = false;
	// �V�l�}�J�����̊������t���O
	bool m_is_active = true;

	// �e���l : �^���v���C���[�Ƃ̋�����
	tnl::Vector3 m_offset = { 0, 0, -400 };
	// �Ǐ]�ɂ����W�␳
	tnl::Vector3 m_fix_pos = { 0,0,0 };

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);

	// ���`��Ԋ֐�
	tnl::Vector3 Lerp(const tnl::Vector3& start
					, const tnl::Vector3& end, float t);

	// �Œ�
	void Fixed(const tnl::Vector3& offset);
	// �X���C�h����
	void ToSlide(const float delta_time, const tnl::Vector3& offset, float speed);

	//-------

	// �ҋ@
	bool SeqTrigger(const float delta_time);
	// �Љ�
	bool SeqFirst(const float delta_time);
	// �G���A�Q�ւ̈ڍs
	bool SeqSecond(const float delta_time);
	// �G���A�R�ւ̈ڍs
	bool SeqThird(const float delta_time);

	//-----�f�o�b�O�p-----//

	//�}�E�X�̉�]���쐧��
	void Control(const float delta_time);

	// ���ӂ�360�x��]����
	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
									, const tnl::Vector3& pivot
									, const tnl::Vector3& axis
									, float angle);

public:

	void SetCanvas();

	void update(const float delta_time) override;

	void Render();

	// �X�N���[���n���h�����擾
	int GetAllHdl() const { return m_screen_hdl; }

	// �V�l�}�J�����̊������t���O��ݒ�
	void SetIsActive(bool is_active) { m_is_active = is_active; }

	// �V�l�}�J�����̊������t���O���擾
	bool GetIsActive() const { return m_is_active; }

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};



//class CinemaCamera : public dxe::Camera
//{
//
//public:
//
//	//enum class eCameraSplitType
//	//{
//	//	e_all,
//	//	e_half_right,
//	//	e_third_left,
//	//	e_third_right
//	//};
//
//	// �S��ʃV�l�}�J�����ɂ���f�t�H���g�R���X�g���N�^
//	CinemaCamera();
//	//// �󋵂ɉ�������ʕ���������R���X�g���N�^
//	//CinemaCamera(int width, int height, eCameraSplitType type);
//
//	~CinemaCamera() {}
//
//private:
//
//	// �X�N���[���n���h��
//	int m_all_hdl = 0;
//	//int m_half_right = 0;
//	//int m_third_left = 0;
//	//int m_third_right = 0;
//
//	//// �����̕�
//	//int m_split_width_left = 0;
//	//int m_split_width_right = 0;
//
//	//// �ŏ��̕����䗦
//	//float split_rate = 1.0f / 3.0f;
//
//	bool m_move_mouse = false;
//
//	//bool m_is_half_right_active = false;
//	//bool m_is_third_left_active = false;
//	//bool m_is_third_right_active = false;
//
//	// �Ǐ]����Ώ�(�^���v���C���[��z��)
//	// �e���l : �^���v���C���[�Ƃ̋�����
//	tnl::Vector3 m_offset = { 0, 0, -400 };
//	// �Ǐ]�ɂ����W�␳
//	tnl::Vector3 m_fix_pos = { 0,0,0 };
//
//	//eCameraSplitType m_type = eCameraSplitType::e_all;
//
//	// ���f�B�G�[�^�[�̃|�C���^
//	std::shared_ptr<Mediator> m_mediator = nullptr;
//
//	// �R���[�`���V�[�P���X
//	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);
//
//	//// ��ʍ쐬
//	//void CreateScreen();
//	//// �����̍X�V
//	//void UpdateSplit(const float delta_time);
//
//	// ���`��Ԋ֐�
//	tnl::Vector3 Lerp(const tnl::Vector3& start
//		, const tnl::Vector3& end, float t);
//
//	// �Œ�
//	void Fixed(const tnl::Vector3& offset);
//	// �X���C�h����
//	void ToSlide(const float delta_time, const tnl::Vector3& offset, float speed);
//
//	//-------
//
//	// �ҋ@
//	bool SeqTrigger(const float delta_time);
//	// �Љ�
//	bool SeqFirst(const float delta_time);
//	// �G���A�Q�ւ̈ڍs
//	bool SeqSecond(const float delta_time);
//	// �G���A�R�ւ̈ڍs
//	bool SeqThird(const float delta_time);
//
//	//-----�f�o�b�O�p-----//
//
//	//�}�E�X�̉�]���쐧��
//	void Control(const float delta_time);
//
//	// ���ӂ�360�x��]����
//	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
//		, const tnl::Vector3& pivot
//		, const tnl::Vector3& axis
//		, float angle);
//
//public:
//
//	void SetCanvas();
//
//	//void SetCanvas(int screen_hdl);
//
//	void update(const float delta_time) override;
//
//	void Render();
//
//	//void Render(int screen_hdl);
//
//	// �X�N���[���n���h�����擾
//	int GetAllHdl() const { return m_all_hdl; }
//
//	//int GetHalfRightHdl() const { return m_half_right; }
//	//
//	//int GetThirdRightHdl() const { return m_third_right; }
//	//
//	//int GetThirdLeftHdl() const { return m_third_left; }
//
//	//float GetSplitWidthLeft() const { return m_split_width_left; }
//
//	//float GetSplitWidthRight() const { return m_split_width_right; }
//
//	//bool GetIsHalfRightActive() const { return m_is_half_right_active; }
//
//	//bool GetIsThirdLeftActive() const { return m_is_third_left_active; }
//
//	//bool GetIsThirdRightActive() const { return m_is_third_right_active; }
//
//	//eCameraSplitType GetActiveType() const { return m_type; }
//
//	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
//	void SetMediator(std::shared_ptr<Mediator>& mediator)
//	{
//		m_mediator = mediator;
//	}
//};