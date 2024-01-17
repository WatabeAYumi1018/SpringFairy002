#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"


class TextLoad
{

public:

	TextLoad();

	~TextLoad();

private:

	// �}�b�v���̓ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_text;
	// �e�L�X�g�f�[�^���i�[
	std::vector<Text::sTextInfo> m_texts;

	// �{���́A������f�o�b�O�œǂݎ��ׂ��i��قǁj
	std::vector<std::string> m_opning_text_ids;
	std::vector<std::string> m_event_text_ids;
	std::vector<std::string> m_ending_text_ids;


	// �e�L�X�g�f�[�^��ǂݎ��
	void LoadText();

	void LoadTextIDs();

public:

	// ���ʔԍ��Ɋ�Â��ăe�L�X�g�f�[�^���擾
	Text::sTextInfo GetStoryText(const std::string& id);

	const std::vector<std::string>& GetOpningTextIDs() const;

	const std::vector<std::string>& GetEventTextIDs() const;

	const std::vector<std::string>& GetEndingTextIDs() const;
};
