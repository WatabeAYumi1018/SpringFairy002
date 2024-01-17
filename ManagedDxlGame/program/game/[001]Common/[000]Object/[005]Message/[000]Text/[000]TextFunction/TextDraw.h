#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class TextDraw
{
private:

	// �s�̃C���f�b�N�X
	int m_index_line = 0;
	// �����̃C���f�b�N�X
	int m_index_char = 0;

	// �s�̕\���Ԋu�̃J�E���g�i�Ō�̕�����\�����Ă���̃J�E���g�j
	float m_elapsed_time_last_char = 0;
	// �����̕\���Ԋu�̃f�t�H���g
	float m_char_interval = 0.2f;

	// �e�L�X�g�f�[�^�̎��ʔԍ��i�[�p
	std::vector<std::string> m_text_ids;


public:

	void Draw();

	void Update(float delta_time);

	// �e�L�X�gID�̕����s�e�L�X�g�f�[�^�i�ő�2�s�j�̐ݒ�ƕ\��
	void SetTextID(const std::vector<std::string>& text_lines);

	bool IsTextEnd() const;
};


// �v���C���[��
//std::string m_player_request_name;

