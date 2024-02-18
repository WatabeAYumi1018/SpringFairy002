#include "../../../../[002]Mediator/Mediator.h"
#include "../../../[002]Gimmick/Gimmick.h"
#include "PlayerCollision.h"
#include "../Player.h"
#include "../../[001]Partner/Partner.h"


PlayerCollision::~PlayerCollision()
{
	m_gimmicks.clear();
}

void PlayerCollision::CollisionRegisterPlayerToGimmick()
{
	// プレイヤーとギミックの当たり判定
	std::string player_to_gimmick_key
		= typeid(Player).name() + std::string(typeid(Gimmick).name());

	m_collision_gimmick->registerIntersect( player_to_gimmick_key
										, [this](std::shared_ptr<Player> player
										, std::shared_ptr<Gimmick> gimmick)
	{
	});
}

void PlayerCollision::CollisionRegisterMeshToGimmick()
{
	// プレイヤーメッシュとギミックの当たり判定
	std::string mesh_to_gimmick_key
		= typeid(dxe::Mesh).name() + std::string(typeid(Gimmick).name());

	m_collision_mesh->registerIntersect(mesh_to_gimmick_key
										, [this](std::shared_ptr<dxe::Mesh> mesh
										, std::shared_ptr<Gimmick> gimmick)
	{
		if (m_mediator->GetNowStagePhaseState() 
			== StagePhase::eStagePhase::e_wood)
		{
			IsIntersectGimmickPos(mesh, gimmick, true);
		}
		else
		{
			IsIntersectGimmickPos(mesh, gimmick, false);
		}
	});
}

void PlayerCollision::CollisionRegisterPlayerToPartner()
{
	// プレイヤーとパートナーの当たり判定
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
	// Player と gimmick の衝突判定
	for (std::shared_ptr<Gimmick>& gimmick : m_gimmicks)
	{
		m_collision_gimmick->Intersect(m_player, gimmick);
	}

	// PlayerのMesh と gimmick の衝突判定
	for (const std::shared_ptr<dxe::Mesh>& mesh : m_player->GetMeshs())
	{
		for (std::shared_ptr<Gimmick>& gimmick : m_gimmicks)
		{
			m_collision_mesh->Intersect(mesh, gimmick);
		}
	}

	// Player と Partner の衝突判定
	m_collision_chara->Intersect(m_player, m_partner);
}

void PlayerCollision::IsIntersectGimmickPos(std::shared_ptr<dxe::Mesh> mesh
											, std::shared_ptr<Gimmick> gimmick
											, bool pos_up)
{
	if (m_collision_mesh->IsIntersectSphere(mesh, m_player->GetMeshs().size()
		, gimmick, gimmick->GetCollisionSize(), pos_up))
	{
		// 当たり判定発生合図
		gimmick->SetIsHit(true);
		//// 描画切り替え合図
		//gimmick->SetIsDrawChange(true);
	}

	// 当たり判定発生合図発生中
	if (gimmick->GetIsHit())
	{
		// 射程外に出たら当たり判定を解除
		if (!m_collision_mesh->IsIntersectSphere(mesh, m_player->GetMeshs().size()
			, gimmick, gimmick->GetCollisionSize(), pos_up))
		{
			gimmick->SetIsHit(false);
		}
		// プレイヤーがアクション状態なら当たり判定
		else if (m_mediator->GetIsPlayerBloom())
		{
			gimmick->SetIsCollision(true);
		}
		else if (m_mediator->GetIsPlayerDance() 
				&& abs(m_player->GetPos().x - gimmick->GetPos().x) < 500
				&& abs(m_player->GetPos().z - gimmick->GetPos().z) < 500)
		{
			gimmick->SetIsCollision(true);
		}
	}
}



