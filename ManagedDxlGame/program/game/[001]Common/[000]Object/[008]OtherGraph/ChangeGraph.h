#pragma once
#include "../Object.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// �J�����J�ڂ���ۂ̃C���X�g�̒�`�ƍX�V�`�揈�����s���N���X
// ���J�ڂ����R�ɂ��邽�߂ɁA�{�N���X�̓V�l�}�J�����݂̂Ŏg�p
//�@
///////////////////////////////////////////////////////////////////////////


class ChangeGraph : public Object
{

public:

	struct sChangeGraphInfo
	{
		int s_id;
		int s_graph_hdl;
		tnl::Vector3 s_pos;
		float s_speed;
	};

	ChangeGraph();
	~ChangeGraph();

protected:

	float m_white_alpha = 0.0f;

	// �`��t���O
	bool m_is_flower = false;
	bool m_is_wood = false;
	bool m_is_active_white = false;
	bool m_is_not_active_white = false;

	// �O���t�B�b�N�摜�̏��i�[
	std::vector<sChangeGraphInfo> m_graph_info;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ���W�X�V
	void UpdateChangeGraph(const float delta_time, int start, int end);
	// �`�揈��
	void DrawChangeGraph(int start, int end);
	// ����ʃt�F�[�h�C���X�V
	void UpdateWhite(const float delta_time);
	// ����ʕ`��
	void DrawWhite();

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr < dxe::Camera> camera) override;

	void SetIsFlower(bool is_active) { m_is_flower = is_active; }

	void SetIsWood(bool is_active) { m_is_wood = is_active; }

	void SetIsActiveWhite(bool is_active)
	{
		m_is_active_white = is_active;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};