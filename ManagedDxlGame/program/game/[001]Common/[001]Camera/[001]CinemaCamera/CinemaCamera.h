#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[003]Phase/StagePhase.h"


class Mediator;


class CinemaCamera : public dxe::Camera
{

public:

	CinemaCamera();

	~CinemaCamera() {}

private:

	// �Ǐ]����Ώ�(�^���v���C���[��z��)
	// �e���l : �^���v���C���[�Ƃ̋�����
	tnl::Vector3 m_offset = { 0, 200, -200 };
	// �Ǐ]�ɂ����W�␳
	tnl::Vector3 m_fix_pos = { 0,0,0 };

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CinemaCamera, &CinemaCamera::SeqTrigger);


	// �J�����̓��쏈��

	// �ҋ@
	bool SeqTrigger(const float delta_time);
	// �A�b�v
	bool SeqUp(const float delta_time);
	// �T�C�h
	bool SeqSide(const float delta_time);
	// ����
	bool SeqBack(const float delta_time);

public:

	void update(const float delta_time) override;

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};