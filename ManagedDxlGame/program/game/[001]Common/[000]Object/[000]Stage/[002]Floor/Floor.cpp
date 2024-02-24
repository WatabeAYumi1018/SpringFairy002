#include "../../../[002]Mediator/Mediator.h"
#include "../[001]Lane/Lane.h"
#include "Floor.h"


Floor::Floor()
{
    LoadFloorTypeInfo();

	// �v���[���T�C�Y�w��(float�^�ɕϊ�)
    float size = static_cast<float>(Lane::LANE_SIZE);

	tnl::Vector3 mesh_size = { size,size,size };

	m_floor = dxe::Mesh::CreatePlaneMV(mesh_size);

    // �v���[�������Ƃ��邽�߉�]
    // 90 : ���ɂ��邽�߂X�O�x��]�B�ύX�Ȃ��̂��ߒ��ړ��́B
	m_floor->rot_
		= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90.0f));	
}

Floor::~Floor()
{
    m_csv_floor_info.clear();
    m_floor_info.clear();
}

void Floor::LoadFloorTypeInfo()
{
    // csv�t�@�C���̓ǂݍ���
    m_csv_floor_info
        = tnl::LoadCsv<tnl::CsvCell>("csv/stage/floor/floor_info.csv");

    // 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
    for (int y = 1; y < m_csv_floor_info.size(); ++y)
    {
        Floor::sFloorType floor_info;

        floor_info.s_id = m_csv_floor_info[y][0].getInt();

        floor_info.s_graph_path
            = m_csv_floor_info[y][1].getString().c_str();

        m_floor_info.emplace_back(floor_info);
    }
}

void Floor::Update(const float delta_time)
{
	tnl_sequence_.update(delta_time);
}

void Floor::Draw(std::shared_ptr<dxe::Camera> camera)
{
    DrawFloor(camera);
}

void Floor::DrawFloor(std::shared_ptr<dxe::Camera> camera)
{
    // �O���b�h�̃T�C�Y
    int grid_size = 60;
    // 2 : �O���b�h�̔����̃T�C�Y
    int half_grid_size = grid_size / 2;
    // �t���A�Ԃ̃X�y�[�X
    int spacing = Lane::LANE_SIZE;

    float distance = static_cast<float> (Floor::DRAW_OFFSET);

    if (m_mediator->GetNowStagePhaseState()
        == StagePhase::eStagePhase::e_wood)
    {
        // 2 : wood���͖؂ɂԂ���Ȃ��悤�`��ʒu��������
        distance *= 2;
    }

    for (int i = -half_grid_size; i < half_grid_size; i++)
    {
        for (int j = -half_grid_size; j < half_grid_size; j++)
        {
            // �e�t���A�̍��W���v�Z
            float x = static_cast<float> (i * spacing);
            float z = static_cast<float> (j * spacing);

            // �t���A�̈ʒu��ݒ�
            m_floor->pos_ = { x, distance, z };

            // �t���A��`��
            m_floor->render(camera);
        }
    }
}

bool Floor::SeqFlower(const float delta_time)
{
    if (tnl_sequence_.isStart())
    {
        m_floor->setTexture(dxe::Texture::CreateFromFile(m_floor_info[0].s_graph_path.c_str()));
    }

    if (m_mediator->GetNowStagePhaseState() 
        == StagePhase::eStagePhase::e_wood)
    {
        tnl_sequence_.change(&Floor::SeqWood);
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});
    
    TNL_SEQ_CO_END;
}

bool Floor::SeqWood(const float delta_time)
{
    if (tnl_sequence_.isStart())
    {
        m_floor->setTexture(dxe::Texture::CreateFromFile(m_floor_info[1].s_graph_path.c_str()));
    }

    if (m_mediator->GetNowStagePhaseState()
        == StagePhase::eStagePhase::e_fancy)
    {
        tnl_sequence_.change(&Floor::SeqFancy);
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

    TNL_SEQ_CO_END;
}

bool Floor::SeqFancy(const float delta_time)
{
    if (tnl_sequence_.isStart())
    {
        m_floor->setTexture(dxe::Texture::CreateFromFile(m_floor_info[2].s_graph_path.c_str()));
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

    TNL_SEQ_CO_END;
}