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
//	// ���f����id
//	int m_id = 0;
//	// ���f���̃n���h��
//	int m_model_hdl = 0;
//	// �e�N�X�`���̃n���h��
//	int m_texture_hdl = 0;
//
//	// csv����ǂݎ�������f���̏��
//	ItemLoad::sItemType m_item_data;
//
//	//���Ȕ���
//	DxLib::COLOR_F m_emissive = { 0,0,0,1 };
//	
//	std::vector<sItemState> m_item_state;
//
//	std::vector<std::shared_ptr<Item>> m_items;
//
//	// ���f�B�G�[�^�[�|�C���^
//	std::shared_ptr<Mediator> m_mediator = nullptr;
//
//
//	// ���C�g�̐ݒ�
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