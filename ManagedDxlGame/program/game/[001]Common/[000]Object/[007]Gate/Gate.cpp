#include "../../[002]Mediator/Mediator.h"
#include "Gate.h"



Gate::~Gate()
{
    m_gates_info.clear();
    m_meshes.clear();
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

        m_mesh->pos_ = gate_info.s_pos;

        m_mesh->scl_ = gate_info.s_scale;

        m_meshes.emplace_back(m_mesh);
    }
}

bool Gate::SeqTrigger(const float delta_time)
{
    if (tnl_sequence_.isStart())
    {
        CreateMesh();
    }
   
    tnl_sequence_.change(&Gate::SeqStay);

    TNL_SEQ_CO_END;
}

bool Gate::SeqStay(const float delta_time)
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

    m_mediator->SetEnterGraphIsActive(true);

    TNL_SEQ_CO_END;
}