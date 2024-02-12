#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../Gimmick.h"


class Mediator;


class GimmickGenerator
{

public:

	GimmickGenerator() {}

	~GimmickGenerator() {}

private:

	bool m_is_ground_active = false;

	bool m_is_sky_flower_active = false;



	Gimmick::eGimmickType m_gimmick_type = Gimmick::eGimmickType::e_max;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);

	// ���[���ԍ��ɑΉ�����M�~�b�N�̃����_���z�u
	void CreateGimmick(const float delta_time);

	// �n��̃M�~�b�N�z�u����
	void CalcGroundPos(const float delta_time, Gimmick::eGimmickType type);

	// �n��̌����ɂ�鐶���ʒu�Z�o
	tnl::Vector3 DirectionCalcPos(const tnl::Vector3& forward);

	// �M�~�b�N�̔z�u
	void SetPlacePos(std::shared_ptr<Gimmick>& gimmick
						, const tnl::Vector3& target_pos
						, const tnl::Vector3& forward
						, const tnl::Vector3& perpendicular);


	// �M�~�b�N�̏�ԍX�V
	void CheckGimmicks(const float delta_time
						, Gimmick::eGimmickType type
						, std::shared_ptr<Gimmick> gimmick);

	// �󒆂ł̃����_������
	void CalcSkyFlowerPos(const float delta_time, Gimmick::eGimmickType type);

	// �󒆂̃����_�����W�Z�o
	tnl::Vector3 CalcRandomPos();

	// �t�����[�̐�������
	bool SeqFlower(const float delta_time);

	// �o�^�t���C�̐�������
	bool SeqButterfly(const float delta_time);

public:

	// �A�C�e���̏�ԍX�V
	void Update(const float delta_time);


	bool GetIsFlowerActive() const { return m_is_sky_flower_active; }

	void SetIsGroundActive(bool is_active) { m_is_ground_active = is_active; }

	bool GetIsGroundActive() const { return m_is_ground_active; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};