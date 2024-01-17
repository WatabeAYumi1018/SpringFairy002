#pragma once
#include "../../[000]Object/Object.h"

class Mediator;

// �����ʒu�ƊԊu�������_����
// �_���X������̃e�N�X�`���ύX�������_����

class Item : public Object
{

public:

	struct sItem
	{
		int s_id;
		tnl::Vector3 s_pos;
	};

	struct sItemType
	{
		int s_id;
		int s_model_hdl;
		int s_texture_hdl;
		std::string s_model_path;
		std::string s_texture_path;
	};


	Item();

	~Item();

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
	sItemType m_item_data;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Item, &Item::SeqNormal);

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	void SetLight();

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

	// ���f���̃��[�h�Ə�����
	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<GameCamera> gameCamera) override;

	void Reset();


	void SetIsActive(bool is_active) { m_is_active = is_active; }

	bool GetIsActive() const { return m_is_active; }

	void SetIsHit(bool is_hit) { m_is_hit = is_hit; }

	bool GetIsHit() const { return m_is_hit; }

	void SetIsDrawChange(bool is_draw_change) { m_is_draw_change = is_draw_change; }

	bool GetIsDrawChange() const { return m_is_draw_change; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};