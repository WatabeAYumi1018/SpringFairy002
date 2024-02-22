#pragma once
#include "../[002]CharaGraph/CharaGraph.h"
#include "../../Object.h"

class Mediator;
class GameCamera;


///////////////////////////////////////////////////////////////////////////
//
// �e�L�X�g�̒�`�ƍX�V�`����s���N���X
//
///////////////////////////////////////////////////////////////////////////


class Text : public Object
{

public:

	//-------------------------------------�\����--------------------------------------//

	// �e�L�X�g�f�[�^���i�[����\����
	struct sTextData
	{
		// �Ή����郌�[��ID
		int s_lane_id;
		// �����O���[�v���ł̎���ID
		int s_text_id;
		// �v���C���[�̑Ή��O���t�B�b�NID
		int s_player_graph_id;
		// �p�[�g�i�[�̑Ή��O���t�B�b�NID
		int s_partner_graph_id;
		// �e�L�X�g�̍s���i�[(1�s)
		std::string s_text_line_first;
		// �e�L�X�g�̍s���i�[(2�s)
		std::string s_text_line_second;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	Text();
	~Text();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �E�B���h�E�n���h��
	int m_window_hdl = 0;

	// �E�B���h�E�̃A���t�@�l(�ŏ��͓���)
	// �L�����N�^�[�摜�ł̃t���O�Ɗ֘A�t���邽��-1�ŏ�����
	int m_window_alpha = -1;

	// ���݂̃e�L�X�g�C���f�b�N�X�ԍ�
	int m_now_text_index = 0;

	// �o�ߎ���
	float m_elasped_time = 0.0f;
	// �������̑��x
	float m_alpha_speed = 200.0f;

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//

	
	//-----------------------------------�����o�֐�------------------------------------//

	// �E�B���h�E�`��̍X�V
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void UpdateWindow(const float delta_time);

	// �E�B���h�E�`��
	void DrawWindow();

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//
	
	// �E�B���h�E�̃A���t�@�l���擾
	// tips ... �L�����N�^�[�C���X�g�Ƃ̘A���̂��߂Ɏg�p
	int GetWindowAlpha() const { return m_window_alpha; }

	// ���f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};
