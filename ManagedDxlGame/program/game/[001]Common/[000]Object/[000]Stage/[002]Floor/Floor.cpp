#include "../../../[002]Mediator/Mediator.h"
#include "../[001]Lane/Lane.h"
#include "Floor.h"


Floor::Floor()
{
    LoadFloorTypeInfo();

	// プレーンサイズ指定(float型に変換)
    float size = static_cast<float>(Lane::LANE_SIZE);

	tnl::Vector3 mesh_size = { size,size,size };

	m_floor = dxe::Mesh::CreatePlaneMV(mesh_size);

    // プレーンを床とするため回転
    // 90 : 床にするため９０度回転。変更なしのため直接入力。
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
    // csvファイルの読み込み
    m_csv_floor_info
        = tnl::LoadCsv<tnl::CsvCell>("csv/stage/floor/floor_info.csv");

    // 0行目は説明文なので読み飛ばす
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
    // グリッドのサイズ
    int grid_size = 60;
    // 2 : グリッドの半分のサイズ
    int half_grid_size = grid_size / 2;
    // フロア間のスペース
    int spacing = Lane::LANE_SIZE;

    float distance = static_cast<float> (Floor::DRAW_OFFSET);

    if (m_mediator->GetNowStagePhaseState()
        == StagePhase::eStagePhase::e_wood)
    {
        // 2 : wood時は木にぶつからないよう描画位置を下げる
        distance *= 2;
    }

    for (int i = -half_grid_size; i < half_grid_size; i++)
    {
        for (int j = -half_grid_size; j < half_grid_size; j++)
        {
            // 各フロアの座標を計算
            float x = static_cast<float> (i * spacing);
            float z = static_cast<float> (j * spacing);

            // フロアの位置を設定
            m_floor->pos_ = { x, distance, z };

            // フロアを描画
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