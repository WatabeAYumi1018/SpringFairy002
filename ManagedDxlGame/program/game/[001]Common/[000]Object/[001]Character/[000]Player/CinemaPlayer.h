#pragma once
#include "../Character.h"


class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �V�l�}���o���̃v���C���[�̍X�V�`����s���N���X
// ���ӔC���߂̂��߁A�ړ��Ɋւ��鏈����CinemaMove�N���X�������\��B
//
/////////////////////////////////////////////////////////////////////////////////////////


class CinemaPlayer : public Character
{

public:

	//-------------------------------------�\����--------------------------------------//

	// ���o�̂��߂ׂ̍��Ȑ��l���������߁A
	// �\���̂ňꊇ�Ǘ������f�B�G�[�^�ł̎Q�Ƃ��ȗ���
	// �p�����[�^�[���ɂ��Ă͑S�Ă��L�ڂ���Ɩc��ɂȂ邽�߁A
	// �����ID�Ɛ��l�ŊǗ�����B
	// �����ۂ̊J���ł̓p�����[�^�[�����L�ڂ��邱�Ƃ����������B
	// ���ꂼ��̏ڂ��������́A����csv�t�@�C���iCinemaPlayer_move�j���Q��
	struct sCinemaPlayerParameter
	{
		int s_id;
		float s_num;
	};

	//---------------------------------------------------------------------------------//

	CinemaPlayer();
	~CinemaPlayer();

private:

	// �~�^���̌o�ߎ���
	float m_elapsed_time_circle = 0.0f;

	bool m_is_idle = false;
	bool m_is_dance = false;
	
	// �v���C���[�̎��Ȕ���
	DxLib::COLOR_F m_emissive = { 0.5f,0.5f,0.5f,1 };

	// csv�ɂĊǗ����ꂽ�e��p�����[�^�[�̃x�N�^�[
	// �g�p�p�x�̑�������ϐ������ȗ���
	std::vector<sCinemaPlayerParameter> m_paras;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CinemaPlayer, &CinemaPlayer::SeqTrigger);

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ���`��Ԋ֐�
	float Lerp(float start, float end, float t);

	// �t�����g����o�b�N�։~�ړ�
	void MoveRoundFrontToBack(const float delta_time);
	// ��]�㉺�ړ�
	void MoveRotUpDown(const float delta_time, float speed , bool up);
	// �o�b�N�֐����悭�ړ�
	void MoveBackCenter(const float delta_time);
	// �o�b�N����t�����g�։~�ړ�
	void MoveRoundBackToFront(const float delta_time, float radian, bool up);


	// �ҋ@
	bool SeqTrigger(const float delta_time);
	// �Љ�
	bool SeqFirst(const float delta_time);
	// �G���A�Q�ւ̈ڍs
	bool SeqSecond(const float delta_time);
	// �G���A�R�ւ̈ڍs
	bool SeqThird(const float delta_time);


public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	bool GetIsDance() const { return m_is_dance; }


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};