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
	// ���ꂼ��̏ڂ��������́A����csv�t�@�C���icinemaPlayer_move�j���Q��
	struct sCinemaPlayerParameter
	{
		int s_id;
		float s_num;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	CinemaPlayer();
	~CinemaPlayer();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �~�^���̌o�ߎ���
	float m_elapsed_time_circle = 0.0f;

	// idle�t���O
	bool m_is_idle = false;
	// dance�t���O
	bool m_is_dance = false;
	
	// �v���C���[�̎��Ȕ��������l
	DxLib::COLOR_F m_emissive = { 0.5f,0.5f,0.5f,1 };

	// csv�ɂĊǗ����ꂽ�e��p�����[�^�[�̃x�N�^�[
	// �g�p�p�x�̑�������ϐ������ȗ���
	std::vector<sCinemaPlayerParameter> m_paras;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(CinemaPlayer, &CinemaPlayer::SeqTrigger);

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ���`��Ԋ֐�
	// arg1 ... �J�n�l
	// arg2 ... �I���l
	// arg3 ... ��ԌW��
	float Lerp(float start, float end, float t);

	// �t�����g����o�b�N�։~�ړ�
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void MoveRoundFrontToBack(const float delta_time);
	
	// ��]�㉺�ړ�
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... �ړ����x
	// arg3 ... ��ړ������ړ����i�f�t�H���g�ŏ�j
	void MoveRotUpDown(const float delta_time, float speed , bool up = true);
	
	// �o�b�N�֐����悭�ړ�
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void MoveBackCenter(const float delta_time);
	
	// �o�b�N����t�����g�։~�ړ�
	// arg1 ... delta_time(�O�t���[������̌o�ߎ���)
	// arg2 ... ���a
	// arg3 ... ��ړ������ړ���(�f�t�H���g�ŏ�)
	void MoveRoundBackToFront(const float delta_time, float radian, bool up = true);

	// �ҋ@
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqTrigger(const float delta_time);

	// �Љ�
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqFirst(const float delta_time);

	// �G���A�Q�ւ̈ڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqSecond(const float delta_time);

	// �G���A�R�ւ̈ڍs
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqThird(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �_���X�t���O�̎擾
	bool GetIsDance() const { return m_is_dance; }

	//---------------------------------------------------------------------------------//
};