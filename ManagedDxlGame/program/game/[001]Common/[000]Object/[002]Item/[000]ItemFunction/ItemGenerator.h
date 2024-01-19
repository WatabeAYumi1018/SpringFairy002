#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../Item.h"


class Mediator;

// �V���v���b�N�X�m�C�Y��p�����A�C�e���̎��������_������

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

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(ItemGenerator, &ItemGenerator::SeqFlower);

	void CheckItems(const float delta_time);
	// �A�C�e���̃����_������
	void GenerateItem(const float delta_time);
	// �A�C�e���̃����_�����W�Z�o
	tnl::Vector3 CalcRandomPos();

	// �A�C�e���t�����[�̐�������
	bool SeqFlower(const float delta_time);
	// �A�C�e���o�^�t���C�̐�������
	bool SeqButterfly(const float delta_time);

public:

	// ���[�����擾
	void Initialize();

	// �A�C�e���̏�ԍX�V
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