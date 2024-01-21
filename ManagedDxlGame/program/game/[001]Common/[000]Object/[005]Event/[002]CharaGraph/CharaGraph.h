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
		// �`����W
		tnl::Vector3 s_graph_pos;
		// �`��n���h��
		int s_graph_hdl;
		// �摜�t�@�C���p�X
		std::string s_graph_path;
	};

	CharaGraph();

	~CharaGraph();

private:

	int m_window_hdl = 0;

	float m_elapsed_time = 0.0f;

	bool m_window_active = true;


	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CharaGraph, &CharaGraph::SeqSlideIn);

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �L�����摜�̓ǂݎ��
	void LoadCharaGraph();
	//// �L�����摜�̃X���C�h����
	//void UpdateCharaSlideGraph(const float delta_time, int graph_id);
	// �L�����摜�̕`��
	void DrawCharaGraph(int graph_id);

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