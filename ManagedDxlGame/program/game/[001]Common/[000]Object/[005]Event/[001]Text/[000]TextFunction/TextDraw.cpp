#include "../../../../[002]Mediator/Mediator.h"
#include "TextDraw.h"


void TextDraw::ResetText()
{    
    // �s�̃C���f�b�N�X��������
    m_index_line = 0;
    // �����̃C���f�b�N�X��������
    m_index_char = 0;
    // �\���Ԋu�̃J�E���g��������
    m_elapsed_time_last_char = 0.0f;
}

void TextDraw::Update(float delta_time)
{
    // ���݂̃��[���ɑΉ�����SID�̑S�e�L�X�g���擾
    m_text_line = m_mediator->GetTextsLoadLane();

    // �e�L�X�g�̕\�����I�����Ă���ꍇ�͉������Ȃ�
    if (m_index_line < m_text_line.size())
    {
        // 1�������\������Ԋu���o�ߎ��ԂŌv�Z
        m_elapsed_time_last_char += delta_time;

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
}

void TextDraw::Draw()
{
    int draw_x = 300;
    int draw_y = 530;
    int draw_y_interval = 60;

    // ���݂̍s��id�̃T�C�Y���z����i�`��I���j
    for (int i = 0; i <= m_index_line && i < m_text_line.size(); i++)
    {
        // ���݂̍s�̕�������擾
        std::string line_to_draw = m_text_line[i];

        if (i == m_index_line) 
        {
            // �`�撆�̕����̂ݕ\��
            line_to_draw = line_to_draw.substr(0, m_index_char);
        }

        // 1 : ���F�̕���
        DrawStringEx( draw_x, draw_y + draw_y_interval * i
                      ,1, line_to_draw.c_str());
    }
}

bool TextDraw::IsTextEnd()
{
    // ���݂̍s��id�̃T�C�Y���z����i�`��I���j
    return m_index_line >= m_text_line.size();
}


/*

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
