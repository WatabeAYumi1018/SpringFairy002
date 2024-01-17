#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../Item.h"


class Mediator;

// シンプレックスノイズを用いたアイテムの自動ランダム生成

class ItemGenerator
{

public:

	ItemGenerator() {}

	~ItemGenerator() {}

private:

	bool m_is_flower_active = false;

	Item::sItem m_item_lane;

	//std::vector<Lane::sLane> m_lanes;

	std::shared_ptr<Item> m_item = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	std::vector<std::shared_ptr<Item>> m_items;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(ItemGenerator, &ItemGenerator::SeqFlower);

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

	void SetItem(std::shared_ptr<Item>& item)
	{
		m_item = item;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};