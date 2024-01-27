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
	std::vector<std::shared_ptr<Gimmick>> m_gimmiks;

public:

	// モデルの格納
	void AddGimmick(std::shared_ptr<Gimmick>& gimmick);

	// 非活性化アイテムの取得
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