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

	Title();

	~Title();

private:

	int m_model_hdl = 0;
	int m_texture_game_hdl = 0;

	tnl::Quaternion m_end_rot;
	
	// �A�j���[�V�����̑��x
	float m_elapsed_time = 0;
	// �o�ߎ���
	float m_total_time = 5.0f;
	// �A���t�@�l
	float m_alpha = 0.0f;
	// �A�j���[�V�����̑��x
	float m_alpha_speed = 0.5f;

	// �`��t���O
	bool m_is_draw = false;
	// �A�j���[�V�������
	bool m_is_animated = false; 
	// �����t���O
	bool m_is_disappear = false;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Title, &Title::SeqTrigger);


	// �`��J�n����
	void StartDraw(const float delta_time);
	// �`��I������
	void EndDraw(const float delta_time);
	// �^�C�g���ړ�����
	void MoveTitle(const float delta_time);

	// �g���K�[����
	bool SeqTrigger(const float delta_time);
	// �ʏ�`��
	bool SeqStay(const float delta_time);
	// �����鏈��
	bool SeqOpen(const float delta_time);


public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }

	bool GetIsDisappear() const { return m_is_disappear; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator; 
	}
};
