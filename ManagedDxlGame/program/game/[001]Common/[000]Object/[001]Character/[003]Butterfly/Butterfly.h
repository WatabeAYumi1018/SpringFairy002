#pragma once
#include "../Character.h"


class Mediator;


class Butterfly : public Character
{
	
public:

	//-------------------------------------�\����--------------------------------------//

	// ���o�̂��߂ׂ̍��Ȑ��l���������߁A
	// �\���̂ňꊇ�Ǘ������f�B�G�[�^�ł̎Q�Ƃ��ȗ���
	// �p�����[�^�[���ɂ��Ă͑S�Ă��L�ڂ���Ɩc��ɂȂ邽�߁A
	// �����ID�Ɛ��l�ŊǗ�����B
	// �����ۂ̊J���ł̓p�����[�^�[�����L�ڂ��邱�Ƃ����������B
	// ���ꂼ��̏ڂ��������́A����csv�t�@�C���ibutterfly_move�j���Q��
	struct sButterflyParameter
	{
		int s_id;
		float s_num;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Butterfly();
	~Butterfly();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// move�A�j���[�V�����̃C���f�b�N�X
	int m_anim_index = 0;
	
	// move�A�j���[�V�����o�ߎ���
	float m_elapsed_time = 0.0f;
	// move�A�j���[�V�����̃��[�v����
	float m_time_count= 0.0f;

	// �~�^���̌o�ߎ���
	float m_elapsed_time_circle = 0.0f;
	// �V�l�}3�ŉ�]�J�n����܂ł̃v���C���[�Ƃ̋���
	float m_to_player_distance = 100.0f;

	// �I�[�v�j���O�`��t���O
	bool m_is_op_active = false;
	// �V�l�}�`��t���O
	bool m_is_cinema_active = false;
	// ���Ńt���O
	bool m_is_clear = false;

	// �i�s����
	tnl::Vector3 m_next_direction;

	// csv�ɂĊǗ����ꂽ�e��p�����[�^�[�̃x�N�^�[
	// �g�p�p�x�̑�������ϐ������ȗ���
	std::vector<sButterflyParameter> m_paras;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Butterfly, &Butterfly::SeqMove);

	// ���b�V���̃|�C���^
	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;
	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �A�j���[�V�����̍X�V����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void AnimMove(const float delta_time);

	// ���������̈ړ��i���֐i�s�j
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void MoveStraightHeight(const float delta_time);

	// ���������̈ړ��i�E�֐i�s�j
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void MoveStraightWidth(const float delta_time);

	// �~�^���̈ړ�����
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	void MoveRound(const float delta_time);

	// �^�������Ȉړ�
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqMove(const float delta_time);

	// �~�^��
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	bool SeqRound(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �I�[�v�j���O�`��t���O�̐ݒ�
	void SetIsOpActive(bool is_op_active) { m_is_op_active = is_op_active; }

	// �V�l�}�`��t���O�̐ݒ�
	void SetIsCinemaActive(bool is_cinema_active)
	{
		m_is_cinema_active = is_cinema_active; 
	}

	// ���̐i�s�����̎擾
	const tnl::Vector3& GetNextDirection() const { return m_next_direction; }

	// ���Ńt���O�̎擾
	bool GetIsClear() const { return m_is_clear; }

	// �V�l�}�`��t���O�̎擾
	bool GetIsCinemaActive() const { return m_is_cinema_active; }

	// ���f�B�G�[�^�̐ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}

	//---------------------------------------------------------------------------------//
};