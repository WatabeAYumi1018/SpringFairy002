#pragma once
#include "../../[000]Object/Object.h"

class Mediator;

// 生成位置と間隔をランダムに
// ダンスした後のテクスチャ変更もランダムに

class Gimmick : public Object
{

public:

	enum class eGimmickType
	{
		plant,
		tree,
		sky_flower,
		butterfly,
		Max
	};

	struct sGimmickTypeInfo
	{
		int s_id = 0;
		int s_model_hdl;
		int s_texture_a_hdl;
		int s_texture_b_hdl;
		std::string s_model_path;
		std::string s_texture_a_path;
		std::string s_texture_b_path;
		eGimmickType s_type;
	};

	Gimmick();

	~Gimmick();

private:

	float m_emissive_value = 0.0f;

	float m_time_elapsed = 0.0f;


	// 個別のアクティブ状態(初期状態は非アクティブ)
	bool m_is_active = false;
	// 当たり判定内到達の合図
	bool m_is_hit = false;
	// 衝突判定
	bool m_is_collision = false;
	// 個別の描画状態変化
	bool m_is_draw_change = false;

	//自己発光
	DxLib::COLOR_F m_emissive = { 0.3f,0.3f,0.3f,1 };

	// csvから読み取ったモデルの情報
	sGimmickTypeInfo m_gimmick_data;

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(Gimmick, &Gimmick::SeqNormal);

	// メディエーターポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	void ChangeTexture(int texture_delete_hdl, int texture_next_hdl);

	// アイテムフラワーの落下処理
	void MoveFlower(const float delta_time);
	// アイテムバタフライの移動処理
	void MoveButterfly(const float delta_time);

	// 初期状態
	bool SeqNormal(const float delta_time);
	// 当たり判定射程内のライトアップ
	bool SeqHit(const float delta_time);
	// 衝突によるライトアップ開始
	bool SeqLightUp(const float delta_time);
	// ライトアップ終了とテクスチャ変更
	bool SeqLightDown(const float delta_time);
	// 変化完了
	bool SeqChangeEnd(const float delta_time);

public:

	// モデルの情報読み込み(Factoryクラスにて設定)
	void LoadGimmickData(const Gimmick::sGimmickTypeInfo& gimmick_info);

	// モデルの初期化（非アクティブ化）
	void Reset();

	// モデルのロードと初期化
	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;


	void SetIsActive(bool is_active) { m_is_active = is_active; }

	bool GetIsActive() const { return m_is_active; }

	void SetIsHit(bool is_hit) { m_is_hit = is_hit; }

	bool GetIsHit() const { return m_is_hit; }

	void SetIsCollision(bool is_collision) { m_is_collision = is_collision; }

	void SetIsDrawChange(bool is_draw_change) { m_is_draw_change = is_draw_change; }

	bool GetIsDrawChange() const { return m_is_draw_change; }

	void SetGimmickData(sGimmickTypeInfo gimmick_info) 
	{
		m_gimmick_data =  gimmick_info;
	}

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};



//struct sGimmick
//{
//	int s_id;
//	tnl::Vector3 s_pos;
//};

	//// ①草花のギミックモデル(静的)
	//std::vector<Gimmick::sGimmickTypeInfo> m_plants;
	//// ②樹木のギミックモデル(静的)
	//std::vector<Gimmick::sGimmickTypeInfo> m_trees;
	//// ③舞う花のギミックモデル(動的)
	//std::vector<Gimmick::sGimmickTypeInfo> m_sky_flowers;
	//// ④蝶のギミックモデル(動的)
	//std::vector<Gimmick::sGimmickTypeInfo> m_butterflys;

	//const std::vector<Gimmick::sGimmickTypeInfo>& GetPlants() const 
	//{
	//	return m_plants; 
	//}

	//const std::vector<Gimmick::sGimmickTypeInfo>& GetTrees() const
	//{
	//	return m_trees; 
	//}

	//const std::vector<Gimmick::sGimmickTypeInfo>& GetSkyFlowers() const
	//{
	//	return m_sky_flowers; 
	//}

	//const std::vector<Gimmick::sGimmickTypeInfo>& GetButterflys() const
	//{
	//	return m_butterflys; 
	//}