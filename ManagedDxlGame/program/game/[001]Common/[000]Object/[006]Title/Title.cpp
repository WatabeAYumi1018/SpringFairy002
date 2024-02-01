#include "Title.h"


Title::Title()
{
	m_graph_hdl = LoadGraph("graphics/title.png");
}

Title::~Title()
{
	DeleteGraph(m_graph_hdl);
}

void Title::Update(const float delta_time)
{
    tnl_sequence_.update(delta_time);
}

void Title::Draw(std::shared_ptr<dxe::Camera> camera)
{
    if (m_is_draw)
    {
        // 透明度を適用
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_alpha));

        // ロゴを回転させて描画（ここではDrawRotaGraphの使用を想定）
        DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2
                      , 1.0f, m_angle, m_graph_hdl, false);

        // 透明度の適用を終了
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void Title::WakeUp(const float delta_time)
{
    if (m_is_animating)
    {
        // アニメーション速度に基づき角度を更新
        m_angle += m_anim_speed * delta_time;

        // 90度に達したら終了
        if (m_angle >= 90.0f)
        {
            // 角度を固定
            m_angle = 90.0f;
            // アニメーション終了
            m_is_animating = false;
        }
    }
}

void Title::Disappear(const float delta_time)
{
    // ロゴの透明度を徐々に上げて消す
    m_alpha += m_alpha_speed * delta_time;

    // 透明度が1.0を超えたら終了
    if (m_alpha >= 1.0f)
    {
		// 透明度を固定
		m_alpha = 1.0f;
		// ロゴを非表示にする
		m_is_draw = false;
	}
}

bool Title::SeqTrigger(const float delta_time)
{
    if (m_is_draw)
    {
        tnl_sequence_.change(&Title::SeqWakeUp);
    }

    return false;
}

bool Title::SeqWakeUp(const float delta_time)
{
    if(!m_is_animating)
    {
        tnl_sequence_.change(&Title::SeqDisappear);
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
    {
        WakeUp(delta_time);
    });

    TNL_SEQ_CO_END;
}

bool Title::SeqDisappear(const float delta_time)
{
    TNL_SEQ_CO_TIM_YIELD_RETURN(7, delta_time, [&]()
    {
        Disappear(delta_time);
    });

    TNL_SEQ_CO_END;
}