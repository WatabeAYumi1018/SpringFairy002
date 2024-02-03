#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"


class Mediator;


class CinemaCamera : public dxe::Camera
{

public:

	// �S��ʃV�l�}�J�����ɂ���f�t�H���g�R���X�g���N�^
	CinemaCamera();
	// �󋵂ɉ�������ʕ���������R���X�g���N�^
	CinemaCamera(int width, int height);

	~CinemaCamera() {}

private:

	// �X�N���[���n���h��
	int m_all_hdl = 0;
	int m_half_right = 0;
	int m_third_left = 0;
	int m_third_right = 0;

	int m_split_width_left = 0;
	int m_split_width_right = 0;

	// �ŏ��̕����䗦
	float split_rate = 1.0f / 3.0f;

	// �J�����̏��
	bool m_is_active = false;

	bool m_move_mouse = false;

	// �C�x���g�I���t���O
	bool m_is_completed = false;

	// �Ǐ]����Ώ�(�^���v���C���[��z��)
	// �e���l : �^���v���C���[�Ƃ̋�����
	tnl::Vector3 m_offset = { 0, 400, -400 };
	// �Ǐ]�ɂ����W�␳
	tnl::Vector3 m_fix_pos = { 0,0,0 };

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);

	// ��ʍ쐬
	void CreateScreen();
	// �����̃A�j���[�V����
	void SplitAnimation(const float delta_time);


	// �ҋ@
	bool SeqTrigger(const float delta_time);
	// �A�b�v
	bool SeqUp(const float delta_time);
	// �T�C�h
	bool SeqSide(const float delta_time);
	// ����
	bool SeqBack(const float delta_time);

	//-----�f�o�b�O�p-----//

	//�}�E�X�̉�]���쐧��
	void Control(const float delta_time);

	// ���ӂ�360�x��]����
	tnl::Vector3 RotateAroundPlayer(const tnl::Vector3& point
		, const tnl::Vector3& pivot
		, const tnl::Vector3& axis
		, float angle);

public:

	void update(const float delta_time) override;

	void Render(int x1,int y1,int x2,int y2,int screen_hdl);

	// �X�N���[���n���h�����擾
	int GetAllHdl() const { return m_all_hdl; }

	int GetHalfRightHdl() const { return m_half_right; }
	
	int GetThirdRightHdl() const { return m_third_right; }
	
	int GetThirdLeftHdl() const { return m_third_left; }

	void SetIsActive(bool is_active) { m_is_active = is_active; }

	bool GetIsActive() const{ return m_is_active; }

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};