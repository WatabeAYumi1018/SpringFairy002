#pragma once
#include "../Object.h"


class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// �^�C�g���̈ꊇ�������s���N���X
// ��Load�N���X�ɕ�����܂ł��Ȃ����߁A�{�N���X����csv���[�h���s��
//
///////////////////////////////////////////////////////////////////////////


class Title : public Object
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	Title();
	~Title();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���f���n���h��
	int m_model_hdl = 0;
	// �e�N�X�`���n���h��
	int m_texture_hdl = 0;
	
	// �A���t�@�l
	float m_alpha = 0.0f;
	// �A�j���[�V�����̑��x
	float m_alpha_speed = 0.5f;

	// �`��t���O
	bool m_is_draw = false;
	// �����t���O
	bool m_is_disappear = false;

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Title, &Title::SeqTrigger);

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �`��J�n����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void StartDraw(const float delta_time);

	// �`��I������
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void EndDraw(const float delta_time);

	// �g���K�[����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqTrigger(const float delta_time);

	// �ʏ�`��
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqStay(const float delta_time);

	// �����鏈��
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqOpen(const float delta_time);


public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �`��t���O�̐ݒ�
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }

	// �����t���O�̎擾
	bool GetIsDisappear() const { return m_is_disappear; }

	// ���f�B�G�[�^�̐ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator; 
	}

	//---------------------------------------------------------------------------------//
};
