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

	tnl::Vector3 m_pos ;

	bool m_is_flower_active = false;

	GameCamera::sCamera m_camera_lane;

	// �@���Ԃ̃M�~�b�N���f��(�ÓI)
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_plants;
	// �A���؂̃M�~�b�N���f��(�ÓI)
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_trees;
	// �B�����Ԃ̃M�~�b�N���f��(���I)
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_sky_flowers;
	// �C���̃M�~�b�N���f��(���I)
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_butterfly;

	//Gimmick::sGimmick m_gimmick_lane;

	//std::vector<Lane::sLane> m_lanes;

	std::shared_ptr<Gimmick> m_gimmick = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	std::vector<std::shared_ptr<Gimmick>> m_gimmicks;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);


	void ActiveGimmick();

	tnl::Vector3 CalcRandomPos(const tnl::Vector3& centerPos);

	std::shared_ptr<Gimmick> InactiveGimmick(const std::vector<Gimmick::sGimmickTypeInfo>& gimmickList);

	// ���[���ԍ��ɑΉ�����M�~�b�N�̃����_���z�u
	void CreateGimmick();

	tnl::Vector3 CalcGroundRandomPos();

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

// �e�M�~�b�N���x�N�^�[�ŊǗ�����Ă�
// �e�M�~�b�N�ɂ͕`�悷��^�C�~���O������
// �`��^�C�~���O�̓J�����̏�ԂŊe�X���f����
// enum�ɂ���Ă��ꂼ��Ǘ�����Ă���
// �@ tree����I(�G���A�Q����side�̂�)
// �A plant�P��I�ifixed�̑O���ȂǑłĂ鎞�Ɍ���j
// �B�C �P��I(���̓G���A3�̂�)
