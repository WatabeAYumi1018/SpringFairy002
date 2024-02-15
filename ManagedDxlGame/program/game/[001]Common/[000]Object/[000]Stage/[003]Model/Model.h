#pragma once
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
		int s_texture_e_hdl;
		int s_texture_f_hdl;
		int s_material_count;
	};

	struct sTreeInfo
	{
		int s_id;
		int s_model_hdl;
		int s_texture_a_hdl;
		int s_texture_b_hdl;
		std::string s_material_a_name;
		std::string s_material_b_name;
	};


	Model(){}
	
	~Model(){}

private:

	// モデルのグリッド座標
	int m_grid_x = 0;
	int m_grid_z = 0;

	// 個別のアクティブ状態
	bool m_is_alive_active = false;

	std::vector<sModelInfo> m_models_info;
	std::vector<sTreeInfo> m_trees_info;
	std::vector<VECTOR> m_trees_pos;

	// メディエーターポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// モデルのグリッド座標計算
	void CalcGridPos(int grid_size);

	// モデルのワールド座標計算
	tnl::Vector3 CalcModelPos(int x, int z, int grid_size);

	// 背景モデル生成（通常描画）
	void DrawStageNormal(std::vector<sModelInfo>& models_info,int id);

	// 背景モデル生成（ギミック攻撃時）
	void DrawStageRot(std::vector<sModelInfo>& models_info, int id);

	// 樹木座標設定
	void SetTreePos();
	// 樹木描画
	void DrawTree();

public:

	void Initialize() override;
	
	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};