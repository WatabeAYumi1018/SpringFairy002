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
        // �����x��K�p
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_alpha));

        // ���S����]�����ĕ`��i�����ł�DrawRotaGraph�̎g�p��z��j
        DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2
                      , 1.0f, m_angle, m_graph_hdl, false);

        // �����x�̓K�p���I��
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void Title::WakeUp(const float delta_time)
{
    if (m_is_animating)
    {
        // �A�j���[�V�������x�Ɋ�Â��p�x���X�V
        m_angle += m_anim_speed * delta_time;

        // 90�x�ɒB������I��
        if (m_angle >= 90.0f)
        {
            // �p�x���Œ�
            m_angle = 90.0f;
            // �A�j���[�V�����I��
            m_is_animating = false;
        }
    }
}

void Title::Disappear(const float delta_time)
{
    // ���S�̓����x�����X�ɏグ�ď���
    m_alpha += m_alpha_speed * delta_time;

    // �����x��1.0�𒴂�����I��
    if (m_alpha >= 1.0f)
    {
		// �����x���Œ�
		m_alpha = 1.0f;
		// ���S���\���ɂ���
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