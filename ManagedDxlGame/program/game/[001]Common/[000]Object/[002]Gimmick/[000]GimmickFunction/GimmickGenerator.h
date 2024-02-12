#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../Gimmick.h"


class Mediator;


class GimmickGenerator
{

public:

	GimmickGenerator() {}

	~GimmickGenerator() {}

private:

	bool m_is_ground_active = false;

	bool m_is_sky_flower_active = false;



	Gimmick::eGimmickType m_gimmick_type = Gimmick::eGimmickType::e_max;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);

	// レーン番号に対応するギミックのランダム配置
	void CreateGimmick(const float delta_time);

	// 地上のギミック配置処理
	void CalcGroundPos(const float delta_time, Gimmick::eGimmickType type);

	// 地上の向きによる生成位置算出
	tnl::Vector3 DirectionCalcPos(const tnl::Vector3& forward);

	// ギミックの配置
	void SetPlacePos(std::shared_ptr<Gimmick>& gimmick
						, const tnl::Vector3& target_pos
						, const tnl::Vector3& forward
						, const tnl::Vector3& perpendicular);


	// ギミックの状態更新
	void CheckGimmicks(const float delta_time
						, Gimmick::eGimmickType type
						, std::shared_ptr<Gimmick> gimmick);

	// 空中でのランダム生成
	void CalcSkyFlowerPos(const float delta_time, Gimmick::eGimmickType type);

	// 空中のランダム座標算出
	tnl::Vector3 CalcRandomPos();

	// フラワーの生成処理
	bool SeqFlower(const float delta_time);

	// バタフライの生成処理
	bool SeqButterfly(const float delta_time);

public:

	// アイテムの状態更新
	void Update(const float delta_time);


	bool GetIsFlowerActive() const { return m_is_sky_flower_active; }

	void SetIsGroundActive(bool is_active) { m_is_ground_active = is_active; }

	bool GetIsGroundActive() const { return m_is_ground_active; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};