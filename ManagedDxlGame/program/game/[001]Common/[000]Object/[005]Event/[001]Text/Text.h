#pragma once
#include "../[002]CharaGraph/CharaGraph.h"
#include "../../Object.h"

class Mediator;
class GameCamera;


class Text : public Object
{

public:

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

	Text();

	~Text();

private:

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

	// �e�L�X�g�f�[�^���i�[
	void UpdateTexts();

	// �E�B���h�E�`��̍X�V
	void UpdateWindow(const float delta_time);
	// �E�B���h�E�`��
	void DrawWindow();

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	int GetWindowAlpha() const { return m_window_alpha; }

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
