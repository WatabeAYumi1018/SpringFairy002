#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "../../../[003]Phase/StagePhase.h"
#include "../[002]Floor/Floor.h"
#include "Model.h"


void Model::Initialize()
{
	// ステージモデルの情報を取得
	m_models_info = m_mediator->GetStageModelInfo();
    m_trees_info = m_mediator->GetStageTreeInfo();
    // 静的モデルで毎フレーム算出する必要はない
    SetTreePos();
}

void Model::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// 正面向きの時の処理
	if (!m_mediator->GetIsGimmickGroundActive())
	{
		if (m_mediator->GetNowStagePhaseState()
					== StagePhase::eStagePhase::e_flower)
		{
			DrawStageNormal(m_models_info, 0, 1500);
		}
		else if(m_mediator->GetNowStagePhaseState() 
					== StagePhase::eStagePhase::e_wood)
		{
			DrawStageNormal(m_models_info, 1, 1800);
		}
		else
		{
			DrawStageNormal(m_models_info, 2, 1000);
            DrawTree();
        }
	}
	// サイドを向いた時の処理
	else
	{
        if (m_mediator->GetNowStagePhaseState()
            == StagePhase::eStagePhase::e_flower)
        {
            DrawStageRot(m_models_info, 0,1500);
        }
        else if (m_mediator->GetNowStagePhaseState()
                == StagePhase::eStagePhase::e_wood)
        {
          DrawStageRot(m_models_info, 1,1800);
        }
        else
        {
          DrawStageRot(m_models_info, 2,1500);
          DrawTree();
        }
	}
}

void Model::CalcGridPos(int grid_size)
{
	tnl::Vector3 target_pos 
        = m_mediator->GetCameraTargetPlayerPos();

	// プレイヤーの現在位置からグリッド座標を取得
    m_grid_x = static_cast<int>(target_pos.x / grid_size);
    m_grid_z = static_cast<int>(target_pos.z / grid_size);
}

tnl::Vector3 Model::CalcModelPos(int x, int z,int grid_size)
{
	tnl::Vector3 pos;

	pos.x = static_cast<float>(x * grid_size);
	pos.y = Floor::DRAW_DISTANCE;

    if (m_mediator->GetNowStagePhaseState() 
        == StagePhase::eStagePhase::e_wood)
    {
		// エリアwoodの時は特別な処理（例: フロアの描画位置を下げる）
		pos.y *= 2;
	}

	// モデルの前方オフセットを適用
	pos.z = static_cast<float>(z * grid_size);

	return pos;
}

void Model::DrawStageNormal(std::vector<sModelInfo>& models_info, int id,int grid_size)
{
    // 描画範囲の設定（ターゲットの位置を中心に全方向に向けて）
    int draw_range = 7;

    CalcGridPos(grid_size);

    for (int z = m_grid_z - draw_range; z <= m_grid_z + draw_range; z++)
    {
        for (int x = m_grid_x - draw_range; x <= m_grid_x + draw_range; x++)
        {  
            m_pos = CalcModelPos(x, z,grid_size);

            m_rot = { 0,0,0,1 };

            MATRIX matrix = GetTransformMatrix();

            MV1SetMatrix(models_info[id].s_model_hdl, matrix);

            // モデルを描画
            MV1DrawModel(models_info[id].s_model_hdl);
        }
    }
}

void Model::DrawStageRot(std::vector<sModelInfo>& models_info,int id,int grid_size)
{
    int draw_range = 7;

    CalcGridPos(grid_size);

    for (int z = m_grid_z - draw_range; z <= m_grid_z + draw_range; z++)
    {
        for (int x = m_grid_x - draw_range; x <= m_grid_x + draw_range; x++)
        {
            m_pos = CalcModelPos(x, z,grid_size);

            tnl::Vector3 forward_pos = m_mediator->PlayerForward();

            m_rot = tnl::Quaternion::LookAtAxisY(m_pos,forward_pos);

            MATRIX matrix = GetTransformMatrix();

            MV1SetMatrix(models_info[id].s_model_hdl, matrix);

            MV1DrawModel(models_info[id].s_model_hdl);
        }
    }
}

void Model::SetTreePos()
{
    // 樹木モデルを20本描画
    for (int i = 0; i< 20 ; ++i)
    {
        // ステージ3描画のため、デフォルト座標を事前に設定
        tnl::Vector3 pos = { 0,0,0 };

        pos.x = tnl::GetRandomDistributionFloat(21000, 27000);

        // 一本植えるごとにオフセットを設定
        float offset = 1500.0f;
        
        // x座標は+-が交互になるように設定
        if (i % 2 == 0)
        {
            offset = -1500.0f;
		}

        pos.x += offset * i;
        pos.y = Floor::DRAW_DISTANCE;
        pos.z += offset * i;

		VECTOR pos_vec = wta::ConvertToVECTOR(pos);

        m_trees_pos.emplace_back(pos_vec);
	}
}

void Model::DrawTree()
{
    for (VECTOR tree_pos : m_trees_pos)
    {
        // ライティング設定
        SetLight(m_trees_info[1].s_model_hdl);
        // 保存された位置情報を使用して描画
        MV1SetPosition(m_trees_info[1].s_model_hdl, tree_pos);
        // モデルを描画
        MV1DrawModel(m_trees_info[1].s_model_hdl);
    }
}