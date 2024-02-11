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
		// �`��ʒu
		int s_graph_side;
		// �`��n���h��
		int s_graph_hdl;
		// �`����W
		tnl::Vector3 s_graph_pos;
	};

	CharaGraph();

	~CharaGraph();

private:


	float m_elapsed_time = 0.0f;

	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CharaGraph, &CharaGraph::SeqSlideIn);

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//// �L�����摜�̃X���C�h����
	//void UpdateCharaSlideGraph(const float delta_time, int graph_id);	

	// �L�����摜�̍X�V
	void UpdateCharaGraph();
	
	void DrawCharaGraph();


	// �X���C�h�C��
	bool SeqSlideIn(const float delta_time);
	// �`�撆
	bool SeqDrawChange(const float delta_time);
	// �X���C�h�A�E�g
	bool SeqSlideOut(const float delta_time);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	// �v���C���[�̃��f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};