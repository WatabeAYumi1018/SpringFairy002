#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../Object.h"


class Mediator;


class Model : public Object
{

public:

	struct sModelInfo
	{
		int s_id;
		int s_model_hdl;
		int s_texture_a_hdl;
		int s_texture_b_hdl;
		int s_texture_c_hdl;
		int s_texture_d_hdl;
		int s_material_count;
	};


	Model(){}
	
	~Model(){}

private:

	// 個別のアクティブ状態
	bool m_is_alive_active = false;

	std::vector<sModelInfo> m_models_info;

	// メディエーターポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 背景モデル生成
	void DrawStage(std::vector<sModelInfo>& models_info,int id);

public:

	void Initialize() override;

	void Update(float delta_time) override;
	
	void Draw(std::shared_ptr<dxe::Camera> camera) override;


	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};


//enum class eWorldType 
//{
//	e_real,
//	e_dream
//};

//Model(int id, eWorldType world_type);

//// 世界によるアクティブ状態
//bool m_is_world_active = false;
//// モデルの属性
//eWorldType m_world_type;

//// コルーチンシーケンス
//TNL_CO_SEQUENCE(Model, &Model::SeqReal);

//// 現実世界
//bool SeqReal(const float delta_time);
//// 夢の世界
//bool SeqDream(const float delta_time);

//// アクティブ化切り替え
//void ToggleActive(bool is_world_active);
//// 二つのモデルフラグの初期化
//void SetBothActive(bool is_world_active, bool is_alive_active);

//// 世界フラグのみ設定
//void SetIsWorldActive(bool is_active){ m_is_world_active = is_active; }
//// 個別フラグのみ設定
//void SetIsAliveActive(bool is_active){ m_is_alive_active = is_active; }
//// 個別フラグのみ取得
//bool GetIsAliveActive() const{ return m_is_alive_active; }
//// 属性の取得
//eWorldType GetWorldType() const{ return m_world_type; }