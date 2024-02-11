#include "../../[002]Mediator/Mediator.h"
#include "Gate.h"



Gate::Gate()
{
    m_enter_hdl = LoadGraph("graphics/ui/other/press_enter.png");
}

void Gate::Initialize()
{
    m_gates_info = m_mediator->GetGatesInfo();

    CreateMesh();
}

void Gate::Update(const float delta_time)
{
    if (m_mediator->GetTitleIsDisappear())
    {
        tnl_sequence_.update(delta_time);
    }

    UpdateEnterGraph(delta_time);
}

void Gate::Draw(std::shared_ptr<dxe::Camera> camera)
{
    if (m_mediator->GetTitleIsDisappear())
    {
        for (std::shared_ptr<dxe::Mesh>& mesh : m_meshes)
        {
            mesh->render(camera);
        }
    }

    if (m_enter_active)
    {
		DrawGraph(450, 500, m_enter_hdl, TRUE);
	}
}

void Gate::CreateMesh()
{
    for (sGateInfo& gate_info : m_gates_info)
    {
        tnl::Vector3 size = { 7000,4000,0 };

        tnl::Vector3 eim = { 0.9f,0.9f,0.9f };

        m_mesh = dxe::Mesh::CreatePlaneMV(size);

        m_mesh->setTexture(dxe::Texture::CreateFromFile(gate_info.s_texture_path));

        m_mesh->setBlendMode(DX_BLENDMODE_ALPHA);

        m_mesh->setMtrlEmissive(eim);

        m_mesh->pos_ = { 0, 0, 0 };

        m_meshes.emplace_back(m_mesh);
    }
}

void Gate::SetMeshMatrix()
{
    m_meshes[0]->scl_ = { 2 };
    m_meshes[0]->pos_.x = 0;
    m_meshes[0]->pos_.z = m_mediator->GetButterflyPos().z + 1500;

    m_meshes[1]->scl_ = { 1,1.5f,1 };
    m_meshes[1]->pos_.x -= 3500;
    m_meshes[1]->pos_.y -= 2000;
    m_meshes[1]->pos_.z = m_mediator->GetButterflyPos().z + 1300;

    m_meshes[2]->scl_ = { 1,1.5f,1 };
    m_meshes[2]->pos_.x += 3450;
    m_meshes[2]->pos_.y -= 2000;
    m_meshes[2]->pos_.z = m_mediator->GetButterflyPos().z + 1300;
}

void Gate::UpdateEnterGraph(const float delta_time)
{
    // ゲートが開いたら画像の点滅表示
    if (m_is_opend)
    {
        m_elasped_time += delta_time;

        if (m_elasped_time > 1)
        {
            m_enter_active = !m_enter_active;

            m_elasped_time = 0;
        }
    }
}

bool Gate::SeqTrigger(const float delta_time)
{
    if (tnl_sequence_.isStart())
    {
        SetMeshMatrix();
    }
   
    tnl_sequence_.change(&Gate::SeqDrawChange);


    TNL_SEQ_CO_END;
}

bool Gate::SeqDrawChange(const float delta_time)
{
    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        // 描画イラストの変更など 
        // デリート
        // セットテクスチャ   
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        // 描画イラストの変更など    
    });

    tnl_sequence_.change(&Gate::SeqOpen);

    TNL_SEQ_CO_END;
}

bool Gate::SeqOpen(const float delta_time)
{
    TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]()
    {
       m_meshes[1]->pos_.x -= delta_time * 500;
       m_meshes[2]->pos_.x += delta_time * 500;
    });

    m_is_opend = true;

    TNL_SEQ_CO_END;
}