#include "TextLoad.h"


TextLoad::TextLoad()
{
	m_csv_text
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/text/text.csv");

	LoadText();

	LoadTextIDs();
}

TextLoad::~TextLoad()
{
	m_csv_text.clear();
}

// ���ʔԍ��Ɋ�Â��ăe�L�X�g�f�[�^���擾
Text::sTextInfo TextLoad::GetStoryText(const std::string& id)
{
	// ���ʔԍ��Ɋ�Â��ăe�L�X�g�f�[�^���擾
	for (const Text::sTextInfo& story_text : m_texts)
	{
		if (story_text.s_id == id)
		{
			return story_text;
		}
	}

	// ������Ȃ���΋�̍\���̂�Ԃ�
	// ��̏ꍇ�A�\���̖�()�Ő����i�f�t�H���g�R���X�g���N�^�j
	return Text::sTextInfo();
}

// �e�L�X�g�f�[�^��ǂݎ��
void TextLoad::LoadText()
{
	// csv�̍ŏ��̍s�͑�ڂȂ̂ŃX�L�b�v
	for (int i = 1; i < m_csv_text.size();++i)
	{
		std::vector<tnl::CsvCell>& text = m_csv_text[i];
		
		Text::sTextInfo story_text;

		// ���ʔԍ���ݒ�
		story_text.s_id = text[0].getString();

		// �e�L�X�g�`��I���t���O��ݒ�
		story_text.s_text_end = text[1].getInt();

		// �e�L�X�g�̍s���i�[
		for (int j = 2; j < text.size(); ++j)
		{
			// �e�L�X�g���󔒂łȂ���Ίi�[
			if (!text[j].getString().empty())
			{
				// ���ʔԍ��ŁA�s���ƂɃe�L�X�g���i�[
				story_text.s_text_lines.emplace_back(text[j].getString());
			}
		}
		// �e�L�X�g�f�[�^���i�[
		m_texts.emplace_back(story_text);
	}
}

void TextLoad::LoadTextIDs()
{
	// �I�[�v�j���O�ɊY������ŏ���2�s��id�����擾
	for (const Text::sTextInfo& story_text : m_texts)
	{
		if (story_text.s_id[0] || story_text.s_id[1])
		{
			m_opning_text_ids.emplace_back(story_text.s_id);
		}
		/*else if (story_text.s_id[] || story_text.s_id[])
		{
			m_ending_text_ids.emplace_back(story_text.s_id);
		}
		else
		{
			m_event_text_ids.emplace_back(story_text.s_id);
		}*/
	}
	
}

