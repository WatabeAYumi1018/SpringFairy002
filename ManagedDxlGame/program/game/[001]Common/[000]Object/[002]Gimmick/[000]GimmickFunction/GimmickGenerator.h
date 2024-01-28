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

	tnl::Vector3 m_pos ;

	bool m_is_ground_active = false;

	bool m_is_flower_active = false;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);

	// ���[���ԍ��ɑΉ�����M�~�b�N�̃����_���z�u
	void CreateGimmick();

	// �n��̃M�~�b�N�z�u����
	void CalcGroundPos(Gimmick::eGimmickType type);

	// ����̃M�~�b�N���擾
	std::shared_ptr<Gimmick> GetInactiveType(std::vector<std::shared_ptr<Gimmick>>& gimmicks);

	void CheckGimmicks(const float delta_time);

	// �󒆂ł̃����_������
	void GenerateGimmick(const float delta_time);
	// �󒆂̃����_�����W�Z�o
	tnl::Vector3 CalcRandomPos();

	// �t�����[�̐�������
	bool SeqFlower(const float delta_time);
	// �o�^�t���C�̐�������
	bool SeqButterfly(const float delta_time);

public:

	// ���[�����擾
	void Initialize();

	// �A�C�e���̏�ԍX�V
	void Update(const float delta_time);


	bool GetIsFlowerActive() const { return m_is_flower_active; }

	void SetIsGroundActive(bool is_active) { m_is_ground_active = is_active; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
