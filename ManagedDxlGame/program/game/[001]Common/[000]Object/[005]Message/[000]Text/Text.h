#pragma once
#include "../../Object.h"

class Mediator;
class GameCamera;


class Text : public Object
{

public:

	// �e�L�X�g�f�[�^���i�[����\����
	struct sTextInfo
	{
		// csv�Œ�`�������ʔԍ�
		std::string s_id;
		// �e�L�X�g�`��I���t���O
		bool s_text_end;
		// �e�L�X�g�̍s���i�[
		std::vector<std::string> s_text_lines;

	};

	Text();

	~Text();

private:

	// �E�B���h�E�摜�̃n���h��
	int m_window_hdl = 0;
	// ���݂̃e�L�X�g�C���f�b�N�X�ԍ�
	int m_now_text_index = 0;

	float m_elasped_time = 0.0f;

	bool m_window_active = true;

	//// �R���[�`���V�[�P���X
	//TNL_CO_SEQUENCE(Text, &Text::SeqOpning);

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

//
//	// �P���C�x���g�e�L�X�g�̐ݒ�ƕ\��
//	void SetEventTextID();
//	// �����̃e�L�X�gID�x�N�^�[��ݒ�
//	void SetTextIDs(std::vector<std::string> ids);
//	// �e�L�X�gID�\�����̑ҋ@���Ԃ�ݒ�
//	void SetNextText(float delta_time, std::vector<std::string> id);
//
//	// �I�[�v�j���O
//	bool SeqOpning(const float delta_time);
//	// ���[������
//	bool SeqRule(const float delta_time);
//	// �C�x���g
//	bool SeqEvent(const float delta_time);
//	//// �G���f�B���O
//	//bool SeqEnd(const float delta_time);
//
//public:
//
//	void Update(float delta_time) override;
//
//	void Draw(std::shared_ptr<GameCamera> gameCamera) override;

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
