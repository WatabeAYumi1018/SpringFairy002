#include "../../../../[002]Mediator/Mediator.h"
#include "TextDraw.h"



void TextDraw::Update(const float delta_time)
{
    m_mediator->GetTextsLoadLane();

    // �e�L�X�g���擾����
    m_lane_text_data = m_mediator->GetTextsLoadForLane();

    tnl_sequence_.update(delta_time);
}

void TextDraw::Draw()
{
    int draw_x = 500;
    int draw_y = 500;
    int draw_y_interval = 50;

    // ���ݕ\������ׂ��e�L�X�g�s������
    std::string line_to_draw_first
        = m_lane_text_data[m_now_text_id].s_text_line_first;
    // 2�s�ڂ����݂��A���`��^�C�~���O�ł���Ε`��
    std::string line_to_draw_second
        = m_lane_text_data[m_now_text_id].s_text_line_second;

    // 1�s�ڂ̃e�L�X�g��`��
    DrawStringEx(draw_x, draw_y, 1, line_to_draw_first.substr(0, m_index_char_first).c_str());

    DrawStringEx(draw_x, draw_y + draw_y_interval, 1, line_to_draw_second.substr(0, m_index_char_second).c_str());    
}

// ��s�ꕶ�����\�����鏈��
void TextDraw::DrawTextData(const float delta_time, std::string text_line)
{
    m_elapsed_time_last_char += delta_time;

    if (m_elapsed_time_last_char >= m_char_interval)
    {
        m_elapsed_time_last_char = 0.0f;

        // ������1���\��
        if (m_now_text_lane_num == 0)
        {
            m_index_char_first += 2;
        }
        else
        {
            m_index_char_second += 2;
        }
    }

    if (m_index_char_first > text_line.length() * 2)
    {
        if (m_now_text_lane_num == 0)
        {
            m_now_text_lane_num= 1;
        }
        
        if(m_index_char_second > text_line.length() * 2)
        {
            // �`����~���A�E�F�C�g�^�C���ɓ���
            m_is_interval = true;
        }
    }
}

// 2�s�̕����̕\�����S�ďI������̑ҋ@����
void TextDraw::SetNextText(const float delta_time)
{
    // ���̍s�̕����\���܂ł̑ҋ@����
    float wait_time = 0.5f;

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
		DrawTextData(delta_time, m_lane_text_data[m_now_text_id].s_text_line_first);
    });

    TNL_SEQ_CO_END;
}

bool TextDraw::SeqSetNextText(const float delta_time)
{
    if (!m_is_interval)
    {
        tnl_sequence_.change(&TextDraw::SeqDrawTextData);
    }

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


//bool TextDraw::IsTextEnd()
//{
//    // ���݂̍s��id�̃T�C�Y���z����i�`��I���j
//    return m_index_line >= m_text_lines.size();
//}
//
//void TextDraw::SetNextText(float delta_time, std::vector<std::string> id)
//{
//    // ���̃e�L�X�g�̕\���܂ł̑ҋ@����
//
//	float wait_time = 2.0f;
//
//	m_elasped_time += delta_time;
//
//	if (m_elasped_time >= wait_time)
//	{
//		m_now_text_index++;
//
//		m_elasped_time = 0.0f;
//
//		if (m_now_text_index < id.size())
//		{
//			// ���̃e�L�X�gID�̏���
//			
//		}
//	}
//}
//



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
