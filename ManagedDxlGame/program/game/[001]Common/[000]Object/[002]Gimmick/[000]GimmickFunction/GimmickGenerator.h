#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../Gimmick.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// ギミック生成におけるランダムな座標計算処理を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class GimmickGenerator
{

public:

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	GimmickGenerator() {}
	~GimmickGenerator() {}

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// ※空中ギミックは今後の実装で使用する予定（処理は大方完了）

	// 地上ギミッグの活性化フラグ
	bool m_is_ground_active = false;
	// 空中ギミックの活性化フラグ
	bool m_is_sky_flower_active = false;
	// ギミックタイプ
	Gimmick::eGimmickType m_gimmick_type = Gimmick::eGimmickType::e_max;
	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// レーン番号に対応するギミックのランダム配置
	// arg ... delta_time(前フレームからの経過時間)
	void CreateGimmick(const float delta_time);

	// 地上のギミック配置処理
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... ギミックの種類
	void CalcGroundPos(const float delta_time, Gimmick::eGimmickType type);

	// 地上の向きによる生成位置算出
	// arg ... 前方ベクトル
	tnl::Vector3 DirectionCalcPos(const tnl::Vector3& forward);

	// ギミックの配置
	// arg1 ... ギミックのポインタ
	// arg2 ... ターゲット座標
	// arg3 ... 前方ベクトル
	// arg4 ... 垂直ベクトル
	void SetPlacePos(std::shared_ptr<Gimmick>& gimmick
						, const tnl::Vector3& target_pos
						, const tnl::Vector3& forward
						, const tnl::Vector3& perpendicular);


	// ギミックの状態更新
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... ギミックの種類
	// arg3 ... ギミックのポインタ
	void CheckGimmicks(const float delta_time
						, Gimmick::eGimmickType type
						, std::shared_ptr<Gimmick> gimmick);

	// 空中でのランダム生成
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... ギミックの種類
	void CalcSkyFlowerPos(const float delta_time, Gimmick::eGimmickType type);

	// 空中のランダム座標算出
	tnl::Vector3 CalcRandomPos();

	// フラワーの生成処理
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqFlower(const float delta_time);

public:

	void Update(const float delta_time);

	//---------------------------------------------------------------------------------//
	
	
	//----------------------------------Setter&Getter----------------------------------//

	// 空中フラワーの活性化フラグ取得
	bool GetIsFlowerActive() const { return m_is_sky_flower_active; }

	// 空中フラワーの活性化フラグ設定
	void SetIsGroundActive(bool is_active) { m_is_ground_active = is_active; }

	// 地上ギミックの活性化フラグ取得
	bool GetIsGroundActive() const { return m_is_ground_active; }

	// メディエータのポインタ設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};