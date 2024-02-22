#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gimmick.h"


///////////////////////////////////////////////////////////////////////////
//
// ギミックのプールクラス
//
///////////////////////////////////////////////////////////////////////////


class GimmickPool
{

public:

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	GimmickPool() {}
	~GimmickPool();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// 作成する各モデルの数
	int m_gimmick_create_num = 5;

	// 各種モデルのベクター
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_plants;
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_trees;
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_sky_flowers;
	std::vector<std::shared_ptr<Gimmick>> m_gimmick_butterflys;

	//---------------------------------------------------------------------------------//

public:

	//-----------------------------------メンバ関数------------------------------------//

	// モデルの格納
	// arg1 ... 該当ギミックのポインタ
	// arg2 ... ギミックの種類
	void AddGimmick(std::shared_ptr<Gimmick>& gimmick
					,Gimmick::eGimmickType type);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 作成するモデル数を取得
	int GetGimmickCreateNum() const { return m_gimmick_create_num; }

	// ギミックのプールを取得
	// arg ... ギミックの種類
	std::vector<std::shared_ptr<Gimmick>>& GetGimmickPools(Gimmick::eGimmickType type);

	//---------------------------------------------------------------------------------//
};