#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[003]Phase/StagePhase.h"
#include "../[000]Object/[000]Stage/[001]Lane/Lane.h"


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

	// �J�����̌Œ菈��
	void Fixed();

public:

	void update(const float delta_time) override;

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};