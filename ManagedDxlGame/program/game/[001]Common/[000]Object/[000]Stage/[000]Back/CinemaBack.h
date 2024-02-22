#pragma once
#include "../../Object.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �V�l�}�J�������o���̔w�i�̒�`�ƍX�V�`����s���N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class CinemaBack : public Object
{

public:

	//-------------------------------------�\����--------------------------------------//

	// �V�l�}�J�����w�i�摜�̏��
	// �V�l�}�R�̂݃X�J�C�{�b�N�X�g�p�̂��߁AskyBox�N���X����Q��
	struct sCinemaBackInfo
	{
		int s_id;
		int s_back_hdl;
	};

	// �V�l�}�J�����Ŏg�p����o�u���̏��
	struct sBubble
	{
		tnl::Vector3 s_pos;
		int s_alpha;
		float s_size;
		float s_life_time;
		bool s_is_active;
	};

	//--------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	CinemaBack();

	~CinemaBack();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// ���̂�����̊�{�����{���̓f�o�b�O�p�ɊO������ǂݎ��̂��D�܂���
	// ����͎��Ԃ��Ȃ��̂ŁA�����ɋL��

	// �����x
	int m_alpha = 0;
	// �o�u���̍쐬��
	int m_bubble_num = 20;
	// �����x�̕ω����x
	float m_alpha_speed = 5;
	// �o�u���̐����T�C�Y�ŏ��l�E�ő�l
	float m_bubble_size_min = 40.0f;
	float m_bubble_size_max = 50.0f;
	// �o�u���̐������x�ŏ��l�E�ő�l
	float m_bubble_life_time_min = 100.0f;
	float m_bubble_life_time_max = 150.0f;

	// �t�H�O�̕`��t���O
	bool m_is_fog = false;
	// �o�u���̕`��t���O
	bool m_is_bubble = false;

	// �V�l�}�J�����w�i�摜�̏��
	std::vector<sCinemaBackInfo> m_cinema_back_info;
	// �S�o�u���̏��
	std::vector<sBubble> m_bubbles;
	// ���b�V���̃|�C���^
	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;
	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �X�J�C�{�b�N�X�̏���ǂݍ���
	void LoadSkyBackInfo();

	// �t�H�O�̃u�����h�X�V����
	void UpdateFogBlend();

	// �o�u���̃A�N�e�B�u�X�V����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void UpdateBubblesActive(const float delta_time);

	// �o�u���̕`����W�����ݒ�
	void RandomBubbleCalc();


public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// �������̃t���O�ݒ�
	// arg ... �������t���O
	void SetIsFog(bool is_fog) { m_is_fog = is_fog; }
	// �o�u���̃t���O�ݒ�
	// arg ... �o�u���t���O
	void SetIsBubble(bool is_bubble) { m_is_bubble = is_bubble; }
	// ���f�B�G�[�^�̐ݒ�
	// arg ... ���f�B�G�[�^�̃|�C���^
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//--------------------------------------------------------------------------------//
};