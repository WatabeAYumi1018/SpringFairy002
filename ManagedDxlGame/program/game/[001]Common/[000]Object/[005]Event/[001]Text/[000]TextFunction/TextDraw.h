#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Text.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// �e�L�X�g�̕`�揈�����s���N���X
//
///////////////////////////////////////////////////////////////////////////


class TextDraw
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	TextDraw() {}
	~TextDraw();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �����̃C���f�b�N�X
	int m_index_char_first = 0;
	int m_index_char_second = 0;

	// ��r�̂��߂̃C���f�b�N�X�ԍ�
	int m_now_text_lane_num = 0;

	// ���݂̃e�L�X�g�C���f�b�N�X�ԍ�
	int m_now_text_id = 0;

	// �s�̕\���Ԋu�̃J�E���g
	// �Ō�̕�����\�����Ă���̃J�E���g
	float m_elapsed_time_last_char = 0;

	// �����̕\���Ԋu�̃f�t�H���g
	float m_char_interval = 0.1f;

	// �o�ߎ���
	float m_elasped_time = 0.0f;

	// ID���Ƃ̑ҋ@�t���O
	bool m_is_interval = false;
	// �e�L�X�g�\���I���t���O
	bool m_is_end = true;

	// ���݂̃e�L�X�g�f�[�^
	std::vector<Text::sTextData> m_lane_text_data;

	// �S�e�L�X�g�f�[�^
	std::vector<Text::sTextData> m_story_texts_all;

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(TextDraw, &TextDraw::SeqStop);

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ��s�ꕶ�����\�����鏈��
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... ��s�ڂ̃e�L�X�g
	// arg3 ... ��s�ڂ̃e�L�X�g
	void DrawTextData(const float delta_time
						, std::string text_line_first
						, std::string text_line_second);

	// ���[���ɊY������e�L�X�gID�̕\�����I�������玟��ID��\��
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void SetNextText(const float delta_time);
	
	// �\���e�L�X�gID�̐ݒ�
	void UpdateTexts();

	// �e�L�X�g�̕`����~
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqStop(const float delta_time);

	// �e�L�X�g�̕`����J�n
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqDrawTextData(const float delta_time);

	// ���̃e�L�X�g�̐ݒ�
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqSetNextText(const float delta_time);

public:

	void Initialize();

	void Update(const float delta_time);

	void Draw();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �e�L�X�g�̕\���t���O���擾
	bool GetIsEnd() const { return m_is_end; }

	// ���݂̃e�L�X�gID���擾
	int GetNowTextID() const { return m_now_text_id; }
	
	// �S�e�L�X�g�f�[�^���擾
	const std::vector<Text::sTextData>& GetLaneTextData() const 
	{
		return m_lane_text_data; 
	}

	// ���f�B�G�[�^�̐ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};

