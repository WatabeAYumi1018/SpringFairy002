#pragma once
#include "../../[000]Object/Object.h"

class Mediator;

// �����ʒu�ƊԊu�������_����
// �_���X������̃e�N�X�`���ύX�������_����

class Gimmick : public Object
{

public:

	enum class eGimmickType
	{
		plant,
		tree,
		sky_flower,
		butterfly,
		Max
	};

	struct sGimmickTypeInfo
	{
		int s_id = 0;
		int s_model_hdl;
		int s_texture_hdl;
		std::string s_model_path;
		std::string s_texture_path;
		eGimmickType s_type;
	};


	Gimmick();

	~Gimmick();

private:

	// �A�C�e��id�̖���
	int m_id_num = 0;

	float m_emissive_value = 0.0f;

	float m_time_elapsed = 0.0f;


	// �ʂ̃A�N�e�B�u���(������Ԃ͔�A�N�e�B�u)
	bool m_is_active = false;
	// �����蔻�蔭���̍��}
	bool m_is_hit = false;
	// �ʂ̕`���ԕω�
	bool m_is_draw_change = false;

	//���Ȕ���
	DxLib::COLOR_F m_emissive = { 0.5f,0.5f,0.5f,1 };

	// csv����ǂݎ�������f���̏��
	sGimmickTypeInfo m_gimmick_data;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Gimmick, &Gimmick::SeqNormal);

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	int RandomTexture();

	void ChangeTexture();

	// �A�C�e���t�����[�̗�������
	void MoveFlower(const float delta_time);
	// �A�C�e���o�^�t���C�̈ړ�����
	void MoveButterfly(const float delta_time);

	// �������
	bool SeqNormal(const float delta_time);
	// ���C�g�A�b�v�J�n
	bool SeqLightUp(const float delta_time);
	// ���C�g�A�b�v�I��
	bool SeqLightDown(const float delta_time);
	// �ω�����
	bool SeqChangeEnd(const float delta_time);

public:

	void LoadGimmickData(const Gimmick::sGimmickTypeInfo& gimmick_info);

	// ���f���̃��[�h�Ə�����
	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void Reset();


	void SetIsActive(bool is_active) { m_is_active = is_active; }

	bool GetIsActive() const { return m_is_active; }

	void SetIsHit(bool is_hit) { m_is_hit = is_hit; }

	bool GetIsHit() const { return m_is_hit; }

	void SetIsDrawChange(bool is_draw_change) { m_is_draw_change = is_draw_change; }

	bool GetIsDrawChange() const { return m_is_draw_change; }

	void SetGimmickData(sGimmickTypeInfo gimmick_info) 
	{
		m_gimmick_data =  gimmick_info;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};



//struct sGimmick
//{
//	int s_id;
//	tnl::Vector3 s_pos;
//};

	//// �@���Ԃ̃M�~�b�N���f��(�ÓI)
	//std::vector<Gimmick::sGimmickTypeInfo> m_plants;
	//// �A���؂̃M�~�b�N���f��(�ÓI)
	//std::vector<Gimmick::sGimmickTypeInfo> m_trees;
	//// �B�����Ԃ̃M�~�b�N���f��(���I)
	//std::vector<Gimmick::sGimmickTypeInfo> m_sky_flowers;
	//// �C���̃M�~�b�N���f��(���I)
	//std::vector<Gimmick::sGimmickTypeInfo> m_butterflys;

	//const std::vector<Gimmick::sGimmickTypeInfo>& GetPlants() const 
	//{
	//	return m_plants; 
	//}

	//const std::vector<Gimmick::sGimmickTypeInfo>& GetTrees() const
	//{
	//	return m_trees; 
	//}

	//const std::vector<Gimmick::sGimmickTypeInfo>& GetSkyFlowers() const
	//{
	//	return m_sky_flowers; 
	//}

	//const std::vector<Gimmick::sGimmickTypeInfo>& GetButterflys() const
	//{
	//	return m_butterflys; 
	//}