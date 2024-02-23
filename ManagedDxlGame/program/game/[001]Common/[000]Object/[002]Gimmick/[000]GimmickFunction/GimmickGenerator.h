#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../Gimmick.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// �M�~�b�N�����ɂ����郉���_���ȍ��W�v�Z�������s���N���X
//
///////////////////////////////////////////////////////////////////////////


class GimmickGenerator
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	GimmickGenerator() {}
	~GimmickGenerator() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���󒆃M�~�b�N�͍���̎����Ŏg�p����\��i�����͑�������j

	// �n��M�~�b�O�̊������t���O
	bool m_is_ground_active = false;
	// �󒆃M�~�b�N�̊������t���O
	bool m_is_sky_flower_active = false;
	// �M�~�b�N�^�C�v
	Gimmick::eGimmickType m_gimmick_type = Gimmick::eGimmickType::e_max;
	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ���[���ԍ��ɑΉ�����M�~�b�N�̃����_���z�u
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void CreateGimmick(const float delta_time);

	// �n��̃M�~�b�N�z�u����
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �M�~�b�N�̎��
	void CalcGroundPos(const float delta_time, Gimmick::eGimmickType type);

	// �n��̌����ɂ�鐶���ʒu�Z�o
	// arg ... �O���x�N�g��
	tnl::Vector3 DirectionCalcPos(const tnl::Vector3& forward);

	// �M�~�b�N�̔z�u
	// arg1 ... �M�~�b�N�̃|�C���^
	// arg2 ... �^�[�Q�b�g���W
	// arg3 ... �O���x�N�g��
	// arg4 ... �����x�N�g��
	void SetPlacePos(std::shared_ptr<Gimmick>& gimmick
						, const tnl::Vector3& target_pos
						, const tnl::Vector3& forward
						, const tnl::Vector3& perpendicular);


	// �M�~�b�N�̏�ԍX�V
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �M�~�b�N�̎��
	// arg3 ... �M�~�b�N�̃|�C���^
	void CheckGimmicks(const float delta_time
						, Gimmick::eGimmickType type
						, std::shared_ptr<Gimmick> gimmick);

	// �󒆂ł̃����_������
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �M�~�b�N�̎��
	void CalcSkyFlowerPos(const float delta_time, Gimmick::eGimmickType type);

	// �󒆂̃����_�����W�Z�o
	tnl::Vector3 CalcRandomPos();

	// �t�����[�̐�������
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFlower(const float delta_time);

public:

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//
	
	
	//----------------------------------Setter&Getter----------------------------------//

	// �󒆃t�����[�̊������t���O�擾
	bool GetIsFlowerActive() const { return m_is_sky_flower_active; }

	// �󒆃t�����[�̊������t���O�ݒ�
	void SetIsGroundActive(bool is_active) { m_is_ground_active = is_active; }

	// �n��M�~�b�N�̊������t���O�擾
	bool GetIsGroundActive() const { return m_is_ground_active; }

	// ���f�B�G�[�^�̃|�C���^�ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};