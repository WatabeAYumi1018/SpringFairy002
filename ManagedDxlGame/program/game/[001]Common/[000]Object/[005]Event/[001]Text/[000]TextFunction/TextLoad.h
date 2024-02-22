#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"


///////////////////////////////////////////////////////////////////////////
//
// �e�L�X�gcsv�t�@�C���̓ǂݍ��݃N���X
//
///////////////////////////////////////////////////////////////////////////


class TextLoad
{

public:

	TextLoad();

	~TextLoad();

private:

	// �}�b�v���̓ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_texts;
	// �S�e�L�X�g�f�[�^���i�[
	std::vector<Text::sTextData> m_texts_all;

	// �e�L�X�g�f�[�^��ǂݎ��
	void LoadText();

public:

	const std::vector<Text::sTextData>& GetTextsAll() const
	{
		return m_texts_all;
	}

	//const std::vector<std::string>& GetTextsMessageForLane() const
	//{
	//	return m_texts_message_for_lanes;
	//}
};
