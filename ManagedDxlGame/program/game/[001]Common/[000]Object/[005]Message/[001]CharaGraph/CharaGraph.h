#pragma once
#include "../../Object.h"

class Mediator;
class GameCamera;


class CharaGraph : public Object
{

public:

	// �摜�f�[�^���i�[����\����
	struct sGraphInfo
	{
		// csv�Œ�`�������ʔԍ�
		std::string s_id;
		// �`��ʒu
		int s_graph_side;
		// �`��n���h��
		int s_graph_hdl;
		// �摜�t�@�C���p�X
		std::string s_graph_path;
	};

	CharaGraph();

	~CharaGraph();

private:

	int m_window_hdl = 0;

	float m_elasped_time = 0.0f;

	bool m_window_active = true;

	tnl::Vector3 m_pos_player_graph = { 100,250,0 };
	tnl::Vector3 m_pos_partner_graph = { 900,400,0 };

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CharaGraph, &CharaGraph::SeqSlideIn);

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �X���C�h�C��
	bool SeqSlideIn(const float delta_time);
	// �`�撆
	bool SeqDraw(const float delta_time);
	// �X���C�h�A�E�g
	bool SeqSlideOut(const float delta_time);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<GameCamera> gameCamera) override;

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};