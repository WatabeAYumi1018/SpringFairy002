#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../wta_library/wta_Collision.h"

class Player;
class Partner;
class Gimmick;

/////////////////////////////////////////////////////////////////////////////////////////
// 
// �v���C���[�̓����蔻��N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class PlayerCollision
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	PlayerCollision() {}
	~PlayerCollision();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// �M�~�b�N�̃|�C���^�x�N�^�[
	std::vector<std::shared_ptr<Gimmick>> m_gimmicks;

	// �v���C���[�̃|�C���^
	std::shared_ptr<Player> m_player = nullptr;
	// �p�[�g�i�[�̃|�C���^
	std::shared_ptr<Partner> m_partner = nullptr;
	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �����蔻��N���X�̃|�C���^(�v���C���[�ƃM�~�b�N)
	std::shared_ptr<wta::Collision<Player, Gimmick>> m_collision_gimmick = nullptr;
	// �����蔻��N���X�̃|�C���^(�v���C���[�̑O�����b�V���ƃM�~�b�N)
	std::shared_ptr<wta::Collision<dxe::Mesh,Gimmick>> m_collision_mesh = nullptr;
	// �����蔻��N���X�̃|�C���^(�v���C���[�ƃp�[�g�i�[)
	std::shared_ptr<wta::Collision<Player, Partner>> m_collision_chara = nullptr;
	
	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �v���C���[�ƃM�~�b�N�̓����蔻��
	// arg1 ... �v���C���[���b�V���̃|�C���^
	// arg2 ... �M�~�b�N�̃|�C���^
	// arg3 ... �M�~�b�N�̍��W�̍���t���O
	//			�G���A�Q�̎��؂̓����蔻��ʒu���グ�邽��
	// tips ... arg3�̓G���A2�̂�true�ɂ���
	void IsIntersectGimmickPos(std::shared_ptr<dxe::Mesh> mesh
								,std::shared_ptr<Gimmick> gimmick
								,bool pos_up);

public:

	// �����蔻�菈���̓o�^
	// tips ... ���������Ɉ�x�����Ăяo��
	void CollisionRegisterPlayerToGimmick();

	// ���b�V���ƃM�~�b�N�̓����蔻�菈���̓o�^
	// tips ... ���������Ɉ�x�����Ăяo��
	void CollisionRegisterMeshToGimmick();

	// �v���C���[�ƃp�[�g�i�[�̓����蔻�菈���̓o�^
	// tips ... ���������Ɉ�x�����Ăяo��
	void CollisionRegisterPlayerToPartner();

	// �M�~�b�N�Ƃ̓����蔻�菈��
	// tips ... ���t���[���Ăяo��
	void CollisionCheck();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �M�~�b�N�̃|�C���^�x�N�^�[�ݒ�
	void SetGimmicks(std::vector<std::shared_ptr<Gimmick>>& gimmicks)
	{
		m_gimmicks = gimmicks;
	}

	// �v���C���[�̃|�C���^�ݒ�
	void SetPlayer(std::shared_ptr<Player>& player)
	{
		m_player = player;
	}

	// �p�[�g�i�[�̃|�C���^�ݒ�
	void SetPartner(std::shared_ptr<Partner>& partner)
	{
		m_partner = partner;
	}

	// �����蔻��N���X�̃|�C���^(�v���C���[�ƃM�~�b�N)�ݒ�
	void SetCollision(std::shared_ptr<wta::Collision<Player, Gimmick>>& collision)
	{
		m_collision_gimmick = collision;
	}

	// �����蔻��N���X�̃|�C���^(�v���C���[�̑O�����b�V���ƃM�~�b�N)�ݒ�
	void SetCollision(std::shared_ptr<wta::Collision<dxe::Mesh, Gimmick>>& collision)
	{
		m_collision_mesh = collision;
	}

	// �����蔻��N���X�̃|�C���^(�v���C���[�ƃp�[�g�i�[)�ݒ�
	void SetCollision(std::shared_ptr<wta::Collision<Player, Partner>>& collision)
	{
		m_collision_chara = collision;
	}

	// ���f�B�G�[�^�̃|�C���^�ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};