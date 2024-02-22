#include "../../../../wta_library/wta_Convert.h"
#include "../../../[001]Common/[002]Mediator/Mediator.h"
#include "Title.h"


Title::Title()
{
    m_model_hdl = MV1LoadModel("model/title/title.mv1");

    m_texture_hdl = LoadGraph("model/title/title.png");

    MV1SetTextureGraphHandle(m_model_hdl, 0, m_texture_hdl, FALSE);

    m_scale = { 3 };

    // シーケンスの初期化
    m_rot = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(0));

    SetLight(m_model_hdl);
}

Title::~Title()
{
	MV1DeleteModel(m_model_hdl);
	DeleteGraph(m_texture_hdl);
}

void Title::Update(const float delta_time)
{
    m_pos = { 0,150,0 };

    // 回転と座標から行列を計算
    m_matrix = GetTransformMatrix();

    // モデルに行列を適用
    MV1SetMatrix(m_model_hdl, m_matrix);

    tnl_sequence_.update(delta_time);
}

void Title::Draw(std::shared_ptr<dxe::Camera> camera)
{
    if (m_is_draw)
    {
        MV1SetMaterialDifColor(m_model_hdl, 0
                                , GetColorF(1.0f, 1.0f, 1.0f, m_alpha));

        // モデルを描画
        MV1DrawModel(m_model_hdl);
    }
}

void Title::StartDraw(const float delta_time)
{
    // ロゴの透明度を徐々に上げて消す
    m_alpha += m_alpha_speed * delta_time;

    if (m_alpha >= 1.0f)
    {
        // 透明度無効化
        m_alpha = 1.0f;
    }
}

void Title::EndDraw(const float delta_time)
{
    // ロゴの透明度を徐々に上げて消す
    m_alpha -= m_alpha_speed * delta_time * 2;

    if (m_alpha <= 0.0f)
    {
        // 透明化
        m_alpha = 0.0f;
    }
}

bool Title::SeqTrigger(const float delta_time)
{
    if (m_is_draw)
    {
        tnl_sequence_.change(&Title::SeqStay);
    }

    return false;
}

bool Title::SeqStay(const float delta_time)
{
    TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
    {
        StartDraw(delta_time);
    });

	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&](){});

    tnl_sequence_.change(&Title::SeqOpen);

	TNL_SEQ_CO_END;
}

bool Title::SeqOpen(const float delta_time)
{
    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        EndDraw(delta_time);
    });

    m_is_disappear = true;

    TNL_SEQ_CO_END;
}