//#include "../../../../../wta_library/wta_Convert.h"
//#include "../../../[002]Mediator/Mediator.h"
//#include "../Item.h"
//#include "ItemDraw.h"
//
//
//ItemDraw::ItemDraw(){}
//
//ItemDraw::~ItemDraw()
//{
//	MV1DeleteModel(m_model_hdl);
//	DeleteGraph(m_texture_hdl);
//}
//
//void ItemDraw::Initialize()
//{
//	// ���f���ǂݎ��
//	m_item_data = m_mediator->GetItemLoadInfoById(m_id);
//
//	// ���f���̓ǂݍ���
//	m_model_hdl = MV1LoadModel(m_item_data.s_model_path.c_str());
//
//	// �e�N�X�`���ǂݎ��
//	m_texture_hdl = LoadGraph(m_item_data.s_texture_path.c_str());
//
//	// �ގ��̎w��͂Ȃ����߈�����0
//	MV1SetTextureGraphHandle(m_model_hdl, 0, m_texture_hdl, FALSE);
//}
//
//void ItemDraw::Update(const float delta_time)
//{
//	m_item_state.clear();
//
//	for (std::shared_ptr<Item>& item : m_items)
//	{
//		sItemState state;
//		
//		state.s_pos = item->GetPos();
//		
//		state.s_is_draw_change = item->GetIsDrawChange();
//
//		// ���̑��̏�ԏ��̍X�V
//		m_item_state.emplace_back(state);
//	}
//}
//
//void ItemDraw::Draw()
//{
//	for (const sItemState& state : m_item_state)
//	{
//		VECTOR pos_vec = wta::ConvertToVECTOR(state.s_pos);
//		MV1SetPosition(m_model_hdl, pos_vec);
//
//		if (state.s_is_draw_change) 
//		{
//			// �����蔻�肪�������ꍇ�̕`�揈��
//			m_emissive = { 1 };
//		}
//
//		SetLight();
//
//		MV1DrawModel(m_model_hdl);
//	}
//}
//
//void ItemDraw::SetLight()
//{
//	// ���C�g�̐ݒ�
//	//����
//	DxLib::COLOR_F ambient = { 1,1,1,1 };
//	//�g�U��
//	DxLib::COLOR_F diffuse = { 0.8f,0.8f,0.8f,1 };
//	//���^���b�N
//	DxLib::COLOR_F specular = { 0,0,0,1 };
//
//	MV1SetMaterialEmiColor(m_model_hdl, 0, m_emissive);
//	MV1SetMaterialAmbColor(m_model_hdl, 0, ambient);
//	MV1SetMaterialDifColor(m_model_hdl, 0, diffuse);
//	MV1SetMaterialSpcColor(m_model_hdl, 0, specular);
//	// �����قǌ����s���Ȃ�
//	MV1SetMaterialSpcPower(m_model_hdl, 0, 0.5f);
//}
