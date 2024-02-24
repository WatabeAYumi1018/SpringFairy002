#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../../wta_library/wta_Collision.h"

class Player;
class Partner;
class Gimmick;

/////////////////////////////////////////////////////////////////////////////////////////
// 
// プレイヤーの当たり判定クラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class PlayerCollision
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	PlayerCollision() {}
	~PlayerCollision();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// ギミックのポインタベクター
	std::vector<std::shared_ptr<Gimmick>> m_gimmicks;

	// プレイヤーのポインタ
	std::shared_ptr<Player> m_player = nullptr;
	// パートナーのポインタ
	std::shared_ptr<Partner> m_partner = nullptr;
	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 当たり判定クラスのポインタ(プレイヤーとギミック)
	std::shared_ptr<wta::Collision<Player, Gimmick>> m_collision_gimmick = nullptr;
	// 当たり判定クラスのポインタ(プレイヤーの前方メッシュとギミック)
	std::shared_ptr<wta::Collision<dxe::Mesh,Gimmick>> m_collision_mesh = nullptr;
	// 当たり判定クラスのポインタ(プレイヤーとパートナー)
	std::shared_ptr<wta::Collision<Player, Partner>> m_collision_chara = nullptr;
	
	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// プレイヤーとギミックの当たり判定
	// arg1 ... プレイヤーメッシュのポインタ
	// arg2 ... ギミックのポインタ
	// arg3 ... ギミックの座標の高低フラグ
	//			エリア２の樹木の当たり判定位置を上げるため
	// tips ... arg3はエリア2のみtrueにする
	void IsIntersectGimmickPos(std::shared_ptr<dxe::Mesh> mesh
								,std::shared_ptr<Gimmick> gimmick
								,bool pos_up);

public:

	// 当たり判定処理の登録
	// tips ... 初期化時に一度だけ呼び出す
	void CollisionRegisterPlayerToGimmick();

	// メッシュとギミックの当たり判定処理の登録
	// tips ... 初期化時に一度だけ呼び出す
	void CollisionRegisterMeshToGimmick();

	// プレイヤーとパートナーの当たり判定処理の登録
	// tips ... 初期化時に一度だけ呼び出す
	void CollisionRegisterPlayerToPartner();

	// ギミックとの当たり判定処理
	// tips ... 毎フレーム呼び出す
	void CollisionCheck();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ギミックのポインタベクター設定
	void SetGimmicks(std::vector<std::shared_ptr<Gimmick>>& gimmicks)
	{
		m_gimmicks = gimmicks;
	}

	// プレイヤーのポインタ設定
	void SetPlayer(std::shared_ptr<Player>& player)
	{
		m_player = player;
	}

	// パートナーのポインタ設定
	void SetPartner(std::shared_ptr<Partner>& partner)
	{
		m_partner = partner;
	}

	// 当たり判定クラスのポインタ(プレイヤーとギミック)設定
	void SetCollision(std::shared_ptr<wta::Collision<Player, Gimmick>>& collision)
	{
		m_collision_gimmick = collision;
	}

	// 当たり判定クラスのポインタ(プレイヤーの前方メッシュとギミック)設定
	void SetCollision(std::shared_ptr<wta::Collision<dxe::Mesh, Gimmick>>& collision)
	{
		m_collision_mesh = collision;
	}

	// 当たり判定クラスのポインタ(プレイヤーとパートナー)設定
	void SetCollision(std::shared_ptr<wta::Collision<Player, Partner>>& collision)
	{
		m_collision_chara = collision;
	}

	// メディエータのポインタ設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};