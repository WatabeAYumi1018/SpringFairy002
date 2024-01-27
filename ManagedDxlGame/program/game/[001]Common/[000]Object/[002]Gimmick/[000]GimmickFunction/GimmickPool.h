#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


class GimmickPool
{

public:

	GimmickPool() {}

	~GimmickPool();

private:

	// �쐬����e���f���̐�
	int m_gimmick_create_num = 5;

	// ���f���̃x�N�^�[
	std::vector<std::shared_ptr<Gimmick>> m_gimmiks;

public:

	// ���f���̊i�[
	void AddGimmick(std::shared_ptr<Gimmick>& gimmick);

	// �񊈐����A�C�e���̎擾
	std::shared_ptr<Gimmick> GetNotActiveGimmick();


	int GetGimmickCreateNum() const
	{
		return m_gimmick_create_num;
	}

	const std::vector<std::shared_ptr<Gimmick>>& GetGimmicks() const
	{
		return m_gimmiks;
	}
};