#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"

class Mediator;


class TextDraw
{
private:

	// �s�̃C���f�b�N�X
	int m_index_line = 0;
	// �����̃C���f�b�N�X
	int m_index_char = 0;

	// �s�̕\���Ԋu�̃J�E���g
	// �Ō�̕�����\�����Ă���̃J�E���g
	float m_elapsed_time_last_char = 0;
	// �����̕\���Ԋu�̃f�t�H���g
	float m_char_interval = 0.2f;

	std::vector<std::string> m_text_line;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �S�Ă̕����`����I��
	void ResetText();

public:

	void Update(float delta_time);

	void Draw();

	// ���[��ID�ɊY������S�Ă̕\���I��
	bool IsTextEnd();

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};


// �v���C���[��
//std::string m_player_request_name;

