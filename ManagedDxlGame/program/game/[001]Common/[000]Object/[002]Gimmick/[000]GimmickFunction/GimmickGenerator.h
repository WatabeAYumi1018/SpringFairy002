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

	tnl::Vector3 m_pos ;

	bool m_is_ground_active = false;

	bool m_is_flower_active = false;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);

	// レーン番号に対応するギミックのランダム配置
	void CreateGimmick();

	// 地上のギミック配置処理
	void CalcGroundPos(Gimmick::eGimmickType type);

	// 特定のギミックを取得
	std::shared_ptr<Gimmick> GetInactiveType(std::vector<std::shared_ptr<Gimmick>>& gimmicks);

	void CheckGimmicks(const float delta_time);

	// 空中でのランダム生成
	void GenerateGimmick(const float delta_time);
	// 空中のランダム座標算出
	tnl::Vector3 CalcRandomPos();

	// フラワーの生成処理
	bool SeqFlower(const float delta_time);
	// バタフライの生成処理
	bool SeqButterfly(const float delta_time);

public:

	// レーン情報取得
	void Initialize();

	// アイテムの状態更新
	void Update(const float delta_time);


	bool GetIsFlowerActive() const { return m_is_flower_active; }

	void SetIsGroundActive(bool is_active) { m_is_ground_active = is_active; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
