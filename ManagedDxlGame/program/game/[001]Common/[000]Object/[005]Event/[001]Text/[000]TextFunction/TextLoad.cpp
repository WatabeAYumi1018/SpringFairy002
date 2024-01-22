#include "../../../../[002]Mediator/Mediator.h"
#include "../../../[000]Stage/[001]Lane/Lane.h"
#include "TextLoad.h"


TextLoad::TextLoad()
{
	LoadText();
}

TextLoad::~TextLoad()
{
	m_csv_text.clear();
}

const std::vector<std::string>& TextLoad::GetTextsLane()
{
	static std::vector<std::string> empty_lane;

	m_texts_for_lane.clear();

	Lane::sLaneEvent lane_event = m_mediator->GetEventLane();

	if (lane_event.s_id == -1) 
	{
		// �����ȃ��[��ID���Ԃ��ꂽ�ꍇ�͋�̃x�N�^�[��Ԃ�
		return empty_lane;
	}

	int lane_id = lane_event.s_id;

	// ���[���ԍ��Ɋ�Â��ăe�L�X�g�f�[�^���ꊇ�i�[
	for (const Text::sTextData& story_text : m_texts_all)
	{
		if (story_text.s_lane_id == lane_id)
		{
			m_texts_for_lane.emplace_back(story_text.s_text_line_first);
			m_texts_for_lane.emplace_back(story_text.s_text_line_second);
		}
	}

	return m_texts_for_lane;

	//// �e�L�X�g�f�[�^��ID���Ƀ\�[�g
	//std::sort(m_texts_for_lane.begin(), m_texts_for_lane.end(),
	//	[](const Text::sTextData& a, const Text::sTextData& b)
	//	{
	//		return a.s_text_id < b.s_text_id;
	//	});
}

// �e�L�X�g�f�[�^��ǂݎ��
void TextLoad::LoadText()
{
	m_csv_text
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/text/text.csv");

	// csv�̍ŏ��̍s�͑�ڂȂ̂ŃX�L�b�v
	for (int i = 1; i < m_csv_text.size();++i)
	{
		std::vector<tnl::CsvCell>& text = m_csv_text[i];
		
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

//void TextLoad::LoadTextIDs()
//{
//	// �I�[�v�j���O�ɊY������ŏ���2�s��id�����擾
//	for (const Text::sTextInfo& story_text : m_texts)
//	{
//		//if (story_text.s_lane_id[0])
//		//{
//		//	m_text_op_ids.emplace_back(story_text.s_id);
//		//}
//		/*else if (story_text.s_id[] || story_text.s_id[])
//		{
//			m_ending_text_ids.emplace_back(story_text.s_id);
//		}
//		else
//		{
//			m_event_text_ids.emplace_back(story_text.s_id);
//		}*/
//	}
//	
//}

