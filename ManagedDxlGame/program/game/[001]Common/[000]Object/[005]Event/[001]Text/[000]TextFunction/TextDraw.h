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

	bool m_is_end = false;

	std::vector<Text::sTextData> m_lane_text_data;


	std::shared_ptr<Mediator> m_mediator = nullptr;

	TNL_CO_SEQUENCE(TextDraw, &TextDraw::SeqStop);

	// ��s�ꕶ�����\�����鏈��
	void DrawTextData(const float delta_time, std::string text_line);
	// ���[���ɊY������e�L�X�gID�̕\�����I�������玟��ID��\��
	void SetNextText(const float delta_time);

	bool SeqStop(const float delta_time);
	bool SeqDrawTextData(const float delta_time);
	bool SeqSetNextText(const float delta_time);

public:


	void Update(const float delta_time);

	// �\�����镶���݂̂̕`��
	void Draw();

	//// ���[��ID�ɊY������S�Ă̕\���I��
	//bool IsTextEnd();

	void SetIsEnd(bool is_end) { m_is_end = is_end; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};


// �v���C���[��
//std::string m_player_request_name;

