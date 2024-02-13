#pragma once
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../../Object.h"

class Mediator;


class CharaGraph : public Object
{

public:

	// �摜�f�[�^���i�[����\����
	struct sGraphInfo
	{
		// csv�Œ�`�������ʔԍ�
		int s_id;
		// �`��n���h��
		int s_graph_hdl;
		// �X���C�h���x
		float s_slide_speed;
		// �J�n�`����W
		float s_start_pos_x;
		// ���݂̕`����W
		float s_current_pos_x;
		// �ŏI�`����W
		float s_end_pos_x;
		// Y���W
		float s_pos_y;
	};

	CharaGraph();

	~CharaGraph();

private:

	int m_now_id = 0;
	int m_player_id = 0;
	int m_partner_id = 0;

	float m_elapsed_time = 0;

	bool m_is_slide_in_player = true;
	bool m_is_slide_in_partner = true;

	bool m_is_slide_out_player = false;
	bool m_is_slide_out_partner = false;

	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �L�����摜�̍��W�X�V
	void UpdateSlideIn(const float delta_time);
	void UpdateSlideOut(const float delta_time);
	// �L�����摜�̕`��
	void DrawCharaGraph();
	// �X�N���[���V���b�g���̕`��
	void DrawScreenShot();

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetIsSlidOutPlayer(bool is_slide_out_player)
	{
		m_is_slide_out_player = is_slide_out_player;
	}

	void SetIsSlidOutPartner(bool is_slide_out_partner)
	{
		m_is_slide_out_partner = is_slide_out_partner;
	}

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};