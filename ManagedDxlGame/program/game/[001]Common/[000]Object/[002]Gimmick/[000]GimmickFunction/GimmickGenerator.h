#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../Gimmick.h"


class Mediator;

// シンプレックスノイズを用いたアイテムの自動ランダム生成

class GimmickGenerator
{

public:

	GimmickGenerator() {}

	~GimmickGenerator() {}

private:

	bool m_is_flower_active = false;

	Gimmick::sGimmick m_gimmick_lane;

	//std::vector<Lane::sLane> m_lanes;

	std::shared_ptr<Gimmick> m_gimmick = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	std::vector<std::shared_ptr<Gimmick>> m_gimmicks;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);

	void CheckItems(const float delta_time);
	// アイテムのランダム生成
	void GenerateItem(const float delta_time);
	// アイテムのランダム座標算出
	tnl::Vector3 CalcRandomPos();

	// アイテムフラワーの生成処理
	bool SeqFlower(const float delta_time);
	// アイテムバタフライの生成処理
	bool SeqButterfly(const float delta_time);

public:

	// レーン情報取得
	void Initialize();

	// アイテムの状態更新
	void Update(const float delta_time);


	bool GetIsFlowerActive() const { return m_is_flower_active; }

	void SetItem(std::shared_ptr<Gimmick>& gimmick)
	{
		m_gimmick = gimmick;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};