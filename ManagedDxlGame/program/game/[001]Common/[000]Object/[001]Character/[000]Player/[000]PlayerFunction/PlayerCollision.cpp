#include "../../../../[002]Mediator/Mediator.h"
#include "../../../[002]Gimmick/Gimmick.h"
#include "PlayerCollision.h"
#include "../Player.h"
#include "../../[001]Partner/Partner.h"


PlayerCollision::~PlayerCollision()
{
	m_gimmicks.clear();
}

void PlayerCollision::CollisionRegisterPlayerToItem()
{
	// �v���C���[�ƃA�C�e���̓����蔻��
	std::string player_to_item_key
		= typeid(Player).name() + std::string(typeid(Gimmick).name());

	m_collision_item->registerIntersect( player_to_item_key
										, [this](std::shared_ptr<Player> player
										, std::shared_ptr<Gimmick> item)
	{
		if(m_collision_item->IsIntersectSphere(player,player->GetCollisionSize()
												, item, item->GetCollisionSize()))
		{
			// �����蔻�蔭�����}
			item->SetIsHit(true);
			// �`��؂�ւ����}
			item->SetIsDrawChange(true);
		}
	});
}

void PlayerCollision::CollisionRegisterMeshToItem()
{
	// ���b�V���ƃA�C�e���̓����蔻��
	std::string mesh_to_gimmick_key
		= typeid(dxe::Mesh).name() + std::string(typeid(Gimmick).name());

	m_collision_mesh->registerIntersect(mesh_to_gimmick_key
										, [this](std::shared_ptr<dxe::Mesh> mesh
										, std::shared_ptr<Gimmick> gimmick)
	{
		if (m_collision_mesh->IsIntersectSphere(mesh, m_player->GetMeshs().size()
												, gimmick, gimmick->GetCollisionSize()))
		{
			// �����蔻�蔭�����}
			gimmick->SetIsHit(true);
			// �`��؂�ւ����}
			gimmick->SetIsDrawChange(true);
		}
	});
}

void PlayerCollision::CollisionRegisterPlayerToPartner()
{
	// �v���C���[�ƃp�[�g�i�[�̓����蔻��
	std::string player_to_partner_key
		= typeid(Player).name() + std::string(typeid(Partner).name());

	m_collision_chara->registerIntersect(player_to_partner_key
										 , [this](std::shared_ptr<Player> player
										 , std::shared_ptr<Partner> partner)
	{
		if (m_collision_chara->IsIntersectSphere(player, player->GetCollisionSize()
												 , partner, partner->GetCollisionSize()))
		{
			m_collision_chara->CorrectSphere(player, player->GetCollisionSize()
											 , partner, partner->GetCollisionSize());

			//m_mediator->SetIsPartnerPushed(true);
		}
	});
}

void PlayerCollision::CollisionCheck()
{
	// Player �� Item �̏Փ˔���
	for (std::shared_ptr<Gimmick>& item : m_gimmicks)
	{
		m_collision_item->Intersect(m_player, item);
	}

	// Player��Mesh �� Item �̏Փ˔���
	for (const std::shared_ptr<dxe::Mesh>& mesh : m_player->GetMeshs())
	{
		for (std::shared_ptr<Gimmick>& item : m_gimmicks)
		{
			m_collision_mesh->Intersect(mesh, item);
		}
	}

	// Player �� Partner �̏Փ˔���
	m_collision_chara->Intersect(m_player, m_partner);
}
