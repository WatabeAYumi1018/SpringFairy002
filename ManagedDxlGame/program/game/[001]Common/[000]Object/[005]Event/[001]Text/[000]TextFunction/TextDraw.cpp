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
        || lane_event.s_id == 1
        || lane_event.s_id == 7
        || lane_event.s_id == 10
        || lane_event.s_id == 12
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
    m_elapsed_time_last_char += delta_time * 1.5f;

    if (m_elapsed_time_last_char >= m_char_interval)
    {
        m_elapsed_time_last_char = 0.0f;

        // ������1���\��
        if (m_now_text_lane_num == 0 
            && m_index_char_first < text_line_first.length() * 2)
        {
            m_index_char_first += 2;
        }
        else if (m_now_text_lane_num == 1 
            && m_index_char_second < text_line_second.length() * 2)
        {
            m_index_char_second += 2;
        }
    }

    // �����̍s�̕����̕`�悪�����������ǂ������`�F�b�N
    if (m_index_char_first >= text_line_first.length() * 2 
        && m_now_text_lane_num == 0)
    {
        m_now_text_lane_num = 1;
        m_index_char_first = text_line_first.length() * 2; // ���݂̍s�̒������Œ�
    }

    if (m_index_char_second >= text_line_second.length() * 2 
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
    if (m_lane_text_data[m_now_text_id].s_text_line_second.find("X�{�^��") != std::string::npos
        ||m_lane_text_data[m_now_text_id].s_text_line_second.find("Z�{�^��") != std::string::npos) 
    {
        // ��������̏ꍇ�͑ҋ@���Ԃ�5�{
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






/*
* 
* // �e�L�X�g�̕\�����I�����Ă���ꍇ�͉������Ȃ�
    if (m_index_line < m_text_line.size())
    {
        // 1�������\������Ԋu���o�ߎ��ԂŌv�Z
        m_elapsed_time_last_char += delta_time * 2;

        // 1�������\������Ԋu�𒴂����ꍇ
        if (m_elapsed_time_last_char >= m_char_interval)
        {
            // �\���Ԋu�̃J�E���g��������
            m_elapsed_time_last_char = 0.0f;
        
            // 1�������\��(�S�p�����̂��߁A2�����Z)
            m_index_char += 2;

            // ���݂̍s��S�ĕ\��������A���̍s�Ɉڍs����
            if (m_index_char >= m_text_line[m_index_line].length())
            {
                m_index_line++;

                m_index_char = 0;
            } 
        }
    }
    // �e�L�X�g�̕\�����I�����Ă���ꍇ�͒l��������
    else
    {
        ResetText();
    }

std::string processed_line = line;
���f�[�^��ی삷�邽�߂ɁA���f�[�^���R�s�[����processed_line�Ɋi�[
���̕����� line �� sStoryText �\���̂̈ꕔ�ł���A���̏ꏊ�ł��g����\��������
���� line ��ύX����ƁA���̏ꏊ�ł̎g�p�ɉe����^����\��������
�I���W�i���̃f�[�^�����̂܂܂ɂ��Ă����A���H�p�ɂ̓R�s�[���g�p
����� line ��ʂ̖ړI�ōė��p����ꍇ��A���̕������ύX�����ɕێ��������ꍇ�ɕ֗�

size_t : �񕉐����i�����Ȃ������B���̒l�������Ȃ��B�O�܂��͐��̐����݈̂����j
��ɔz��̃T�C�Y��R���N�V�������̗v�f�̃C���f�b�N�X�i�ʒu�j���w�肷��̂Ɏg�p

npos : string::npos�́Astring::find()��string::rfind()�̖߂�l�Ƃ��Ďg������ʂȒl
�����񒆂Ɍ��������񂪌�����Ȃ������ꍇ��string::npos��Ԃ�
���̒l��size_t�^

*/
