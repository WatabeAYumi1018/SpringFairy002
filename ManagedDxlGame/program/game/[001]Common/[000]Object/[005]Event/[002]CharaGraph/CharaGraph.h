#pragma once
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../../Object.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// ��b���̃L�����N�^�[�C���X�g�̒�`�ƍX�V�`����s���N���X
//
///////////////////////////////////////////////////////////////////////////


class CharaGraph : public Object
{

public:

	//-------------------------------------�\����--------------------------------------//

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

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	CharaGraph();
	~CharaGraph();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���݂̕`��ID
	int m_now_id = 0;
	// �v���C���[ID
	int m_player_id = 0;
	// �p�[�g�i�[ID
	int m_partner_id = 0;

	// �o�ߎ���
	float m_elapsed_time = 0;

	// �v���C���[�̃X���C�h�J�n�t���O
	bool m_is_slide_in_player = true;
	// �p�[�g�i�[�̃X���C�h�J�n�t���O
	bool m_is_slide_in_partner = true;
	// �v���C���[�̃X���C�h�I���t���O
	bool m_is_slide_out_player = false;
	// �p�[�g�i�[�̃X���C�h�I���t���O
	bool m_is_slide_out_partner = false;

	// �L�����N�^�[�摜�̏��
	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// ���f�B�G�[�^�[�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �L�����摜�̃X���C�h�J�n����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void UpdateSlideIn(const float delta_time);
	
	// �L�����摜�̃X���C�h�I������
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void UpdateSlideOut(const float delta_time);
	
	// �L�����摜�̕`��
	void DrawCharaGraph();
	
	// �X�N���[���V���b�g���̕`��
	void DrawScreenShot();

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �v���C���[�̃X���C�h�I���t���O��ݒ�
	void SetIsSlidOutPlayer(bool is_slide_out_player)
	{
		m_is_slide_out_player = is_slide_out_player;
	}

	// �p�[�g�i�[�̃X���C�h�I���t���O��ݒ�
	void SetIsSlidOutPartner(bool is_slide_out_partner)
	{
		m_is_slide_out_partner = is_slide_out_partner;
	}

	// ���f�B�G�[�^�[��ݒ�	
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};