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

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// move�A�j���[�V�����̃C���f�b�N�X
	int m_anim_index = 0;

	float m_speed = 100.0f;

	// move�A�j���[�V�����̑��x
	float m_anim_speed = 100.0f;
	
	float m_elapsed_time_circle = 0.0f;
	
	// move�A�j���[�V�����o�ߎ���
	float m_elapsed_time = 0.0f;
	// move�A�j���[�V�����̃��[�v����
	float m_time_count= 0.0f;
	
	// �V�l�}3�ŉ�]����܂ł̃v���C���[�Ƃ̋���
	float m_to_player_distance = 100.0f;

	 //�i�s����
	tnl::Vector3 m_next_direction;

	// �I�[�v�j���O�`��t���O
	bool m_is_op_active = false;
	// ���Ńt���O
	bool m_is_clear = false;
	// �V�l�}�`��t���O
	bool m_is_cinema_active = false;

	// csv�ɂĊǗ����ꂽ�e��p�����[�^�[�̃x�N�^�[
	// �g�p�p�x�̑�������ϐ������ȗ���
	std::vector<sButterflyParameter> m_paras;

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(Butterfly, &Butterfly::SeqMove);

	std::shared_ptr<dxe::Mesh> m_mesh = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;


	void AnimMove(const float delta_time);

	void MoveStraightHeight(const float delta_time);

	void MoveStraightWidth(const float delta_time);

	void MoveRound(const float delta_time);

	bool SeqMove(const float delta_time);

	bool SeqRound(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetIsOpActive(bool is_op_active) { m_is_op_active = is_op_active; }

	void SetIsCinemaActive(bool is_cinema_active)
	{
		m_is_cinema_active = is_cinema_active; 
	}

	const tnl::Vector3& GetNextDirection() const 
	{
		return m_next_direction; 
	}

	bool GetIsClear() const { return m_is_clear; }

	bool GetIsCinemaActive() const { return m_is_cinema_active; }

	void SetMediator(std::shared_ptr<Mediator>& mediator) 
	{
		m_mediator = mediator; 
	}
};