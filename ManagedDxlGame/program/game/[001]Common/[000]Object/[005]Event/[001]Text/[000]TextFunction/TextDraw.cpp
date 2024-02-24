#include "../../../../[002]Mediator/Mediator.h"
#include "TextDraw.h"


TextDraw::~TextDraw()
{
	m_story_texts_all.clear();
	m_lane_text_data.clear();
}

void TextDraw::Initialize()
{
    m_story_texts_all = m_mediator->GetTextsLoadAll();
}

void TextDraw::Update(const float delta_time)
{
    UpdateTexts();

    // �e�L�X�g����̏ꍇ�͍X�V���Ȃ�
    if (m_lane_text_data.empty())
    {
        return;
    }

    tnl_sequence_.update(delta_time);
}

void TextDraw::Draw()
{
    // ��̏ꍇ�͕`�悵�Ȃ�
    if (m_lane_text_data.empty())
    {
		return;
	}

    int start_x = 510;
    int start_y = 550;
    int draw_y_interval = 50;

    // ���ݕ\������ׂ��e�L�X�g�s������
    std::string line_to_draw_first
        = m_lane_text_data[m_now_text_id].s_text_line_first;
    // 2�s�ڂ����݂��A���`��^�C�~���O�ł���Ε`��
    std::string line_to_draw_second
        = m_lane_text_data[m_now_text_id].s_text_line_second;

    // 1�s�ڂ̃e�L�X�g��`��
    DrawStringEx(start_x, start_y, 1
                 ,line_to_draw_first.substr(0, m_index_char_first).c_str());

    DrawStringEx(start_x, start_y + draw_y_interval, 1
                 ,line_to_draw_second.substr(0, m_index_char_second).c_str());
}

void TextDraw::UpdateTexts()
{
    Lane::sLaneEvent lane_event = m_mediator->GetCurrentEventLane();

    // �e�L�X�g�`������Ȃ����[��ID�̏ꍇ�͏������I��
    if (lane_event.s_id == -1
        || lane_event.s_id == 7
        || lane_event.s_id == 10
        || lane_event.s_id == 14)
    {
        return;
    }

    // ��L�ȊO�ł���Ε`����J�n
    m_is_end = false;

    int lane_id = lane_event.s_id;

    m_lane_text_data.clear();

    // ���[���ԍ��Ɋ�Â��ăe�L�X�g�f�[�^���ꊇ�i�[
    for (const Text::sTextData& story_text : m_story_texts_all)
    {
        if (story_text.s_lane_id == lane_id)
        {
            m_lane_text_data.emplace_back(story_text);
        }
    }
}

// ��s�ꕶ�����\�����鏈��
void TextDraw::DrawTextData(const float delta_time
                            , std::string text_line_first
                            , std::string text_line_second)
{
    // 2 : �S�p�����̂��߁i�Œ�l�j
    const int TEXT = 2;

    float text_speed = 1.5f;

    m_elapsed_time_last_char += delta_time * text_speed;

    if (m_elapsed_time_last_char >= m_char_interval)
    {
        // �����\���̃E�F�C�g���Ԃ����Z�b�g
        m_elapsed_time_last_char = 0.0f;

        // ������1���\��
        if (m_now_text_lane_num == 0 
            && m_index_char_first < text_line_first.length() * TEXT)
        {
            m_index_char_first += TEXT;
        }
        else if (m_now_text_lane_num == 1 
            && m_index_char_second < text_line_second.length() * TEXT)
        {
            m_index_char_second += TEXT;
        }
    }

    // �����̍s�̕����̕`�悪�����������ǂ������`�F�b�N
    if (m_index_char_first >= text_line_first.length() * TEXT
        && m_now_text_lane_num == 0)
    {
        m_now_text_lane_num = 1;
        // ���݂̍s�̒������Œ�
        m_index_char_first = text_line_first.length() * TEXT;
    }

    if (m_index_char_second >= text_line_second.length() * TEXT
        && m_now_text_lane_num == 1)
    {
        // �`����~���A�E�F�C�g�^�C���ɓ���
        m_is_interval = true;
    }
}

// 2�s�̕����̕\�����S�ďI������̑ҋ@����
void TextDraw::SetNextText(const float delta_time)
{
    // ���̍s�̕����\���܂ł̑ҋ@����
    float wait_time = 0.5f;

    // �Ō�ɕ`�悳�ꂽ�s������̕������܂ނ��`�F�b�N
    if (m_lane_text_data[m_now_text_id].s_text_line_second.find("X�{�^��") 
        != std::string::npos)
    {
        // ��������̏ꍇ�͑ҋ@���Ԃ�5�{
        // ��{�I�ɕύX���鐔�l�ł͂Ȃ����߁A�Œ�l
        wait_time *= 5;  
    }

    m_elasped_time += delta_time;

    // ��莞�Ԍo�߂����ꍇ
    if (m_elasped_time >= wait_time)
    {
        // �E�F�C�g�^�C�����o�߂�����̏���
        m_elasped_time = 0.0f;

        // ���̃e�L�X�gID��
        m_now_text_id++;

        // ���̃e�L�X�g��1�s�ڂ���ĊJ
        m_now_text_lane_num = 0;

        // �����̃C���f�b�N�X�����Z�b�g
        m_index_char_first = 0;

        m_index_char_second = 0;

        m_is_interval = false;

        // �S�Ă�ID���I�������ꍇ�A�S�ă��Z�b�g
        if (m_now_text_id == m_lane_text_data.size())
        {
            m_now_text_id = 0;

            m_is_end = true;
        }
    }
}

bool TextDraw::SeqStop(const float delta_time)
{
    if (!m_is_end)
    {
        tnl_sequence_.change(&TextDraw::SeqDrawTextData);
    }

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}

bool TextDraw::SeqDrawTextData(const float delta_time)
{
    if (m_is_interval)
    {
        tnl_sequence_.change(&TextDraw::SeqSetNextText);
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
    {
        // �e�L�X�gID���͈͓��ɂ��邩���m�F
        if (m_now_text_id < m_lane_text_data.size())
        {
            DrawTextData(delta_time
                         , m_lane_text_data[m_now_text_id].s_text_line_first
                         , m_lane_text_data[m_now_text_id].s_text_line_second);
        }
        // �͈͊O�̏ꍇ�͕`����~
        else
        {
			m_is_end = true;
        }
    });

    TNL_SEQ_CO_END;
}

bool TextDraw::SeqSetNextText(const float delta_time)
{
    // �E�F�C�g�^�C�����o�߂����玟�̃e�L�X�gID��
    if (!m_is_interval)
    {
        tnl_sequence_.change(&TextDraw::SeqDrawTextData);
    }
    // �e�L�X�g�̕\�����I�����Ă���ꍇ��Stop�փ��Z�b�g
    if (m_is_end)
    {
        tnl_sequence_.change(&TextDraw::SeqStop);
    }

    TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
    {
        SetNextText(delta_time);
    });

    TNL_SEQ_CO_END;
}