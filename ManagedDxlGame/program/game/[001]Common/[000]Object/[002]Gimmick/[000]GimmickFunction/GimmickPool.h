#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


class GimmickPool
{

public:

	GimmickPool() {}

	~GimmickPool();

private:

	// 作成する各モデルの数
	int m_gimmick_create_num = 5;

	// モデルのベクター
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_plants;
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_trees;
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_sky_flowers;
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_butterflys;

public:

	// モデルの格納
	void AddGimmick(std::shared_ptr<Gimmick>& gimmick
					,Gimmick::eGimmickType type);

	int GetGimmickCreateNum() const
	{
		return m_gimmick_create_num;
	}

	std::vector<std::shared_ptr<Gimmick>>& GetGimmickPools(Gimmick::eGimmickType type);
};