#include "TextLoad.h"


TextLoad::TextLoad()
{
	LoadText();
}

TextLoad::~TextLoad()
{
	m_csv_texts.clear();
}

// �e�L�X�g�f�[�^��ǂݎ��
void TextLoad::LoadText()
{
	m_csv_texts
		//= tnl::LoadCsv<tnl::CsvCell>("csv/ui/text/text.csv");
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/text/text0219.csv");

	// csv�̍ŏ��̍s�͑�ڂȂ̂ŃX�L�b�v
	for (int i = 1; i < m_csv_texts.size();++i)
	{
		std::vector<tnl::CsvCell>& text = m_csv_texts[i];
		
		Text::sTextData story_text;

		// �Ή����郌�[��ID��ݒ�
		story_text.s_lane_id = text[0].getInt();

		// �O���[�v���ł�ID��ݒ�
		story_text.s_text_id = text[1].getInt();

		// �v���C���[�O���t�B�b�N��ID��ݒ�
		story_text.s_player_graph_id = text[2].getInt();

		// �p�[�g�i�[�O���t�B�b�N��ID��ݒ�
		story_text.s_partner_graph_id = text[3].getInt();

		// �e�L�X�g�̍s���i�[
		story_text.s_text_line_first = text[4].getString();

		story_text.s_text_line_second = text[5].getString();

		// �e�L�X�g�f�[�^���i�[
		m_texts_all.emplace_back(story_text);
	}
}

