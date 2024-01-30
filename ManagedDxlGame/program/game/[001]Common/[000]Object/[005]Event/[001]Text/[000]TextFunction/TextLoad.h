#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"

class Mediator;

class TextLoad
{

public:

	TextLoad();

	~TextLoad();

private:

	// �}�b�v���̓ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_text;
	// �S�e�L�X�g�f�[�^���i�[
	std::vector<Text::sTextData> m_texts_all;
	// ���[��ID�ɊY������e�L�X�g�f�[�^���i�[
	std::vector<Text::sTextData> m_texts_for_lane;

	std::shared_ptr<Mediator> m_mediator = nullptr;


	// �e�L�X�g�f�[�^��ǂݎ��
	void LoadText();


public:

	// ���[��ID�ɊY������e�L�X�g���ꊇ�擾
	void GetTextsLane();


	const std::vector<Text::sTextData>& GetTextsForLane() const
	{
		return m_texts_for_lane;
	}

	//const std::vector<std::string>& GetTextsMessageForLane() const
	//{
	//	return m_texts_message_for_lanes;
	//}


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
