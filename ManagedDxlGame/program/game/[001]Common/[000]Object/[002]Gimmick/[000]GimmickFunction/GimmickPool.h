#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


///////////////////////////////////////////////////////////////////////////
//
// �M�~�b�N�̃v�[���N���X
//
///////////////////////////////////////////////////////////////////////////


class GimmickPool
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	GimmickPool() {}
	~GimmickPool();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �쐬����e���f���̐�
	int m_gimmick_create_num = 5;

	// �e�탂�f���̃x�N�^�[
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_plants;
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_trees;
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_sky_flowers;
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_butterflys;

	//---------------------------------------------------------------------------------//

public:

	//-----------------------------------�����o�֐�------------------------------------//

	// ���f���̊i�[
	// arg1 ... �Y���M�~�b�N�̃|�C���^
	// arg2 ... �M�~�b�N�̎��
	void AddGimmick(std::shared_ptr<Gimmick>& gimmick
					,Gimmick::eGimmickType type);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �쐬���郂�f�������擾
	int GetGimmickCreateNum() const { return m_gimmick_create_num; }

	// �M�~�b�N�̃v�[�����擾
	// arg ... �M�~�b�N�̎��
	std::vector<std::shared_ptr<Gimmick>>& GetGimmickPools(Gimmick::eGimmickType type);

	//---------------------------------------------------------------------------------//
};