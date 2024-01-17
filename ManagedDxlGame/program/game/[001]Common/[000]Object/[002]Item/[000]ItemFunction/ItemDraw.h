//#pragma once
//#include "../dxlib_ext/dxlib_ext.h"
//#include "ItemLoad.h"
//
//class Item;
//class Mediator;
//
//
//class ItemDraw
//{
//
//public:
//
//	struct sItemState
//	{
//		tnl::Vector3 s_pos;
//		bool s_is_draw_change;
//	};
//
//	ItemDraw();
//
//	~ItemDraw();
//
//private:
//
//	// モデルのid
//	int m_id = 0;
//	// モデルのハンドル
//	int m_model_hdl = 0;
//	// テクスチャのハンドル
//	int m_texture_hdl = 0;
//
//	// csvから読み取ったモデルの情報
//	ItemLoad::sItemType m_item_data;
//
//	//自己発光
//	DxLib::COLOR_F m_emissive = { 0,0,0,1 };
//	
//	std::vector<sItemState> m_item_state;
//
//	std::vector<std::shared_ptr<Item>> m_items;
//
//	// メディエーターポインタ
//	std::shared_ptr<Mediator> m_mediator = nullptr;
//
//
//	// ライトの設定
//	void SetLight();
//
//public:
//
//	void Initialize();
//
//	void Update(const float delta_time);
//
//	void Draw();
//
//
//	void SetItems(std::vector<std::shared_ptr<Item>>& items) 
//	{
//		m_items = items;
//	}
//
//	void SetMediator(std::shared_ptr<Mediator>& mediator)
//	{
//		m_mediator = mediator;
//	}
//};