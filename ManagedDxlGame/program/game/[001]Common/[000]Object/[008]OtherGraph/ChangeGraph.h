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

	//-------------------------------------�\����--------------------------------------//

	// �O���t�B�b�N�摜�̏��
	struct sChangeGraphInfo
	{
		int s_id;
		int s_graph_hdl;
		tnl::Vector3 s_pos;
		float s_speed;
	};

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	ChangeGraph();
	~ChangeGraph();

	//---------------------------------------------------------------------------------//

protected:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ����ʂ̃A���t�@�l
	float m_white_alpha = 0.0f;

	// flower�X�e�[�W�V�l�}�̕`��t���O
	bool m_is_flower = false;
	// wood�X�e�[�W�V�l�}�̕`��t���O
	bool m_is_wood = false;
	// ����ʊ������t���O
	bool m_is_active_white = false;
	// ����ʔ񊈐����t���O
	bool m_is_not_active_white = false;

	// �O���t�B�b�N�摜�̏��i�[
	std::vector<sChangeGraphInfo> m_graph_info;

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ���W�X�V
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �J�n�C���f�b�N�X
	// arg3 ... �I���C���f�b�N�X
	void UpdateChangeGraph(const float delta_time, int start, int end);
	
	// �`�揈��
	// arg1 ... �J�n�C���f�b�N�X
	// arg2 ... �I���C���f�b�N�X
	void DrawChangeGraph(int start, int end);
	
	// ����ʃt�F�[�h�C���X�V
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void UpdateWhite(const float delta_time);
	
	// ����ʕ`��
	void DrawWhite();

	//---------------------------------------------------------------------------------//

public:

	//-----------------------------------�����o�֐�------------------------------------//

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr < dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//

	
	//----------------------------------Setter&Getter----------------------------------//

	// flower�X�e�[�W�V�l�}�̕`��t���O��ݒ�
	void SetIsFlower(bool is_active) { m_is_flower = is_active; }

	// wood�X�e�[�W�V�l�}�̕`��t���O��ݒ�
	void SetIsWood(bool is_active) { m_is_wood = is_active; }

	// ����ʊ������t���O��ݒ�
	void SetIsActiveWhite(bool is_active)
	{
		m_is_active_white = is_active;
	}

	// ���f�B�G�[�^�̃|�C���^��ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};