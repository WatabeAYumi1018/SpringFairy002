#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"

class Mediator;


class TextDraw
{
private:

	// �����̃C���f�b�N�X
	int m_index_char_first = 0;
	int m_index_char_second = 0;
	// �s�̕\���Ԋu�̃J�E���g
	// �Ō�̕�����\�����Ă���̃J�E���g
	float m_elapsed_time_last_char = 0;
	// �����̕\���Ԋu�̃f�t�H���g
	float m_char_interval = 0.1f;

	// ��r�̂��߂̃C���f�b�N�X�ԍ�
	int m_now_text_lane_num = 0;
	// ���݂̃e�L�X�g�C���f�b�N�X�ԍ�
	int m_now_text_id = 0;
	// �o�ߎ���
	float m_elasped_time = 0.0f;

	// ID���Ƃ̑ҋ@�t���O
	bool m_is_interval = false;
	// �e�L�X�g�\���I���t���O
	bool m_is_end = true;

	std::vector<Text::sTextData> m_lane_text_data;


	std::shared_ptr<Mediator> m_mediator = nullptr;

	TNL_CO_SEQUENCE(TextDraw, &TextDraw::SeqStop);

	// ��s�ꕶ�����\�����鏈��
	void DrawTextData(const float delta_time
						, std::string text_line_first
						, std::string text_line_second);

	// ���[���ɊY������e�L�X�gID�̕\�����I�������玟��ID��\��
	void SetNextText(const float delta_time);
	// �\���e�L�X�gID�̐ݒ�
	void UpdateTexts();


	// �e�L�X�g�̕`����~
	bool SeqStop(const float delta_time);
	// �e�L�X�g�̕`����J�n
	bool SeqDrawTextData(const float delta_time);
	// ���̃e�L�X�g�̐ݒ�
	bool SeqSetNextText(const float delta_time);

public:


	void Update(const float delta_time);

	void Draw();

	bool GetIsEnd() const { return m_is_end; }

	int GetNowTextID() const { return m_now_text_id; }
	
	const std::vector<Text::sTextData>& GetLaneTextData() const 
	{
		return m_lane_text_data; 
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};

