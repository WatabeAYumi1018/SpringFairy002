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
		// �����O���[�v���ł̃e�L�X�gID
		//�@�����œǂݎ����ID���L�����O���t�ɑ�����Ċ֘A�t��
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

	// �E�B���h�E�摜�̃n���h��
	int m_window_hdl = 0;
	// ���݂̃e�L�X�g�C���f�b�N�X�ԍ�
	int m_now_text_index = 0;

	float m_elasped_time = 0.0f;

	bool m_window_active = true;

	//// �R���[�`���V�[�P���X
	//TNL_CO_SEQUENCE(Text, &Text::SeqMessage);

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	//// �P���C�x���g�e�L�X�g�̐ݒ�ƕ\��
	//void SetEventTextID();
	//// �����̃e�L�X�gID�x�N�^�[��ݒ�
	//void SetTextIDs(std::vector<std::string> ids);
	// �e�L�X�gID�\�����̑ҋ@���Ԃ�ݒ�
	void SetNextText(const float delta_time, std::vector<std::string> id);

	//// �I�[�v�j���O
	//bool SeqOpning(const float delta_time);
	//// ��b
	//bool SeqMessage(const float delta_time);
	//// �C�x���g
	//bool SeqEvent(const float delta_time);
	///// �G���f�B���O
	//bool SeqEnd(const float delta_time);

public:

//	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
