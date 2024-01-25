#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../Gimmick.h"


class Mediator;

// �V���v���b�N�X�m�C�Y��p�����A�C�e���̎��������_������

class GimmickGenerator
{

public:

	GimmickGenerator() {}

	~GimmickGenerator() {}

private:

	bool m_is_flower_active = false;

	//Gimmick::sGimmick m_gimmick_lane;

	//std::vector<Lane::sLane> m_lanes;

	std::shared_ptr<Gimmick> m_gimmick = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	std::vector<std::shared_ptr<Gimmick>> m_gimmicks;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);

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

	void SetGimmick(std::shared_ptr<Gimmick>& gimmick)
	{
		m_gimmick = gimmick;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};