#pragma once
#include "../Object.h"


class Title : public Object
{

public:

	Title();

	~Title();

private:

	// �摜�n���h��
	int m_graph_hdl = 0;

	// ���S�̊p�x
	float m_angle = 0.0f; 
	// �A�j���[�V�����̑��x
	float m_anim_speed = 90.0f;
	// �A���t�@�l
	float m_alpha = 0.0f;
	// �o�ߎ���
	float m_alpha_speed = 30.0f;

	// �`��t���O
	bool m_is_draw = false;
	// �A�j���[�V�������
	bool m_is_animating = false; 

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Title, &Title::SeqTrigger);


	void WakeUp(const float delta_time);

	void Disappear(const float delta_time);

	// �g���K�[����
	bool SeqTrigger(const float delta_time);
	// �N���オ�鏈��
	bool SeqWakeUp(const float delta_time);
	// �����鏈��
	bool SeqDisappear(const float delta_time);


public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;


	bool GetIsDraw() const { return m_is_draw; }
};
