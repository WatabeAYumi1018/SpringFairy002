#include "ItemGenerator.h"
#include "../../../[002]Mediator/Mediator.h"


void ItemGenerator::Initialize()
{
	// ���[�������擾
    m_items = m_mediator->GetPoolItems();
}

void ItemGenerator::Update(const float delta_time)
{
    tnl_sequence_.update(delta_time);

    CheckItems(delta_time);
}

void ItemGenerator::CheckItems(const float delta_time)
{
    // �A�C�e���v�[�����̂��ׂẴA�C�e���𔽕�����
    for (std::shared_ptr<Item>& item : m_items)
    {
		// �A�N�e�B�u�A�C�e���������𖞂����΃��Z�b�g
        if (item->GetIsActive() 
            && item->GetPos().y < m_mediator->GetPlayerPos().y - 750)
        {
			item->Reset();
		}
	}
}

void ItemGenerator::GenerateItem(const float delta_time)
{
    // 1�b���ƂɎ��s����
    static float elapsed_time = 0.0f;

    elapsed_time += delta_time;

    if (elapsed_time < 1.0f)
    {
		return;
	}

    else
    {
        std::shared_ptr<Item> active_item = m_mediator->GetNotActiveItemPool();

        if (active_item
            && m_item_lane.s_id == m_mediator->CurrentTargetItemLane().s_id)
        {
            tnl::Vector3 pos = CalcRandomPos();

            active_item->SetPos(pos);

            active_item->SetIsActive(true);
        }

        elapsed_time = 0.0f;
    }
 }

tnl::Vector3 ItemGenerator::CalcRandomPos()
{
    tnl::Vector3 player_pos = m_mediator->GetCameraTargetPlayerPos();

    float offset = 700.0f;

    tnl::Vector3 random_pos
        = tnl::Vector3(tnl::GetRandomDistributionFloat(player_pos.x - (offset * 2), player_pos.x - offset)
                       ,800
                       ,player_pos.z + offset);

    return random_pos;
}

bool ItemGenerator::SeqFlower(const float delta_time)
{
    // ����id��1�̏ꍇ�ڍs
    if (m_item_lane.s_id == 1)
    {
        m_is_flower_active = false;

		tnl_sequence_.change(&ItemGenerator::SeqButterfly);
	}

    // 5�b�Ɉ�x�����������肵�ď����y���i�A�C�e�������̓A�o�E�g��ok���Ɓj
    TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
    {
        m_is_flower_active = true;

        // �^�[�Q�b�g�̍��W�ɑΉ����郌�[�����擾
        m_item_lane = m_mediator->CurrentTargetItemLane();
    });

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() 
    {
		GenerateItem(delta_time);
    });

	TNL_SEQ_CO_END;
}

bool ItemGenerator::SeqButterfly(const float delta_time)
{
    // ����id��1�̏ꍇ�ڍs
    if (m_item_lane.s_id == 0)
    {
        m_is_flower_active = true;

        tnl_sequence_.change(&ItemGenerator::SeqFlower);
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
    {
        GenerateItem(delta_time);
    });

    TNL_SEQ_CO_END;
}


//tnl::Vector3 player_back_pos = m_mediator->PlayerBack();

//bool ItemGenerator::SeqCreate(const float delta_time)
//{
//    if (tnl_sequence_.isStart() && m_mediator->NextLaneMove())
//    {
//		GenerateItem();
//	}
//
//    if (m_mediator->NextLaneMove())
//    {
//		tnl_sequence_.change(&ItemGenerator::SeqDelete);
//	}
//
//    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});
//
//	TNL_SEQ_CO_END;
//}
//
//bool ItemGenerator::SeqDelete(const float delta_time)
//{
//    // �A�C�e���v�[�����̂��ׂẴA�C�e���𔽕�����
//    for (std::shared_ptr<Item>& item : m_mediator->GetPoolItems())
//    {
//        // �A�C�e�����A�N�e�B�u�ȏꍇ�A���Z�b�g����
//        if (item->GetIsActive())
//        {
//            item->Reset();
//        }
//    }
//
//    tnl_sequence_.change(&ItemGenerator::SeqCreate);
//
//    TNL_SEQ_CO_END;
//}


//tnl::Vector3 ItemGenerator::CalcRandom()
//{
//    // �Q�[���̃v���C�G���A�̃T�C�Y��ݒ�
//    const int area_width = 1000;
//    const int area_height = 600;
//
//    // ����������̐ݒ�i�ÓI�ɐ錾�j
//    static std::random_device rnd;
//    static std::mt19937 gen(rnd());
//
//    // �����͈̔͂��w��
//    std::uniform_real_distribution<float> dist_x(0.0f, static_cast<float>(area_width));
//    std::uniform_real_distribution<float> dist_y(0.0f, static_cast<float>(area_height));
//    std::uniform_real_distribution<float> dist_z(0.0f, 1.0f); // Z���W�p
//
//    // �����_���ȍ��W�𐶐�
//    float random_x = dist_x(gen);
//    float random_y = dist_y(gen);
//    float random_z = dist_z(gen);
//
//    // �V���v���b�N�X�m�C�Y���g�p���āA�ŏI�I�ȍ��W������
//    float noise_value_x = wta::SimplexNoise3D({ random_x, 0, 0 });
//    float noise_value_y = wta::SimplexNoise3D({ 0, random_y, 0 });
//    float noise_value_z = wta::SimplexNoise3D({ 0, 0, random_z });
//
//    // �v���C�G���A���͈̔͂Ƀm�C�Y�l���X�P�[�����O
//    float x = (noise_value_x + 1.0f) / 2.0f * area_width;
//    float y = (noise_value_y + 1.0f) / 2.0f * area_height;
//    float z = (noise_value_z + 1.0f) / 2.0f;
//
//    // �����������W��Ԃ�
//    return tnl::Vector3(x, y, z);
//}