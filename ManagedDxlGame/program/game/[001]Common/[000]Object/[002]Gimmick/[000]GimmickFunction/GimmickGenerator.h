#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../[000]Stage/[001]Lane/Lane.h"
#include "../Gimmick.h"


class Mediator;

// シンプレックスノイズを用いたアイテムの自動ランダム生成

class GimmickGenerator
{

public:

	GimmickGenerator() {}

	~GimmickGenerator() {}

private:

	tnl::Vector3 m_pos ;

	bool m_is_flower_active = false;

	GameCamera::sCamera m_camera_lane;

	// ①草花のギミックモデル(静的)
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_plants;
	// ②樹木のギミックモデル(静的)
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_trees;
	// ③舞う花のギミックモデル(動的)
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_sky_flowers;
	// ④蝶のギミックモデル(動的)
	std::vector<Gimmick::sGimmickTypeInfo> m_gimmick_butterfly;

	//Gimmick::sGimmick m_gimmick_lane;

	//std::vector<Lane::sLane> m_lanes;

	std::shared_ptr<Gimmick> m_gimmick = nullptr;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	std::vector<std::shared_ptr<Gimmick>> m_gimmicks;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(GimmickGenerator, &GimmickGenerator::SeqFlower);


	void ActiveGimmick();

	tnl::Vector3 CalcRandomPos(const tnl::Vector3& centerPos);

	std::shared_ptr<Gimmick> InactiveGimmick(const std::vector<Gimmick::sGimmickTypeInfo>& gimmickList);

	// レーン番号に対応するギミックのランダム配置
	void CreateGimmick();

	tnl::Vector3 CalcGroundRandomPos();

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

	void SetGimmick(std::shared_ptr<Gimmick>& gimmick)
	{
		m_gimmick = gimmick;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};

// 各ギミックがベクターで管理されてる
// 各ギミックには描画するタイミングがある
// 描画タイミングはカメラの状態で各々判断する
// enumによってそれぞれ管理されている
// ① tree限定的(エリア２かつsideのみ)
// ② plant恒常的（fixedの前方など打てる時に限る）
// ③④ 恒常的(蝶はエリア3のみ)
