#pragma once
#include "../../Object.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// モデルの定義と更新描画処理を行うクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class Model : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

	// 床背景モデル情報
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

	// 樹木モデル情報（エリアファンシーのみ）
	struct sTreeInfo
	{
		int s_id;
		int s_model_hdl;
		int s_texture_a_hdl;
		int s_texture_b_hdl;
		std::string s_material_a_name;
		std::string s_material_b_name;
	};

	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Model(){}
	
	~Model();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	// 床背景モデルのグリッド座標
	int m_grid_x = 0;
	int m_grid_z = 0;

	// 樹木モデルの生成数
	int m_tree_create_num = 10;

	// 正面からの視点
	bool m_look_side_front = false;
	// 個別のアクティブ状態
	bool m_is_alive_active = false;

	// 床背景モデル情報
	std::vector<sModelInfo> m_models_info;
	// 樹木モデル情報
	std::vector<sTreeInfo> m_trees_info;
	// 樹木モデル座標
	std::vector<VECTOR> m_trees_pos;

	// メディエーターポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// 床背景モデルのグリッド座標計算
	// arg ... グリッドサイズ（小さいほどモデル同士の密度が高くなる）
	void CalcGridPos(int grid_size);

	// 床背景モデルのワールド座標計算
	// arg1 ... グリッドx座標
	// arg2 ... グリッドz座標
	// arg3 ... グリッドサイズ（小さいほどモデル同士の密度が高くなる）
	tnl::Vector3 CalcModelPos(int x, int z, int grid_size);

	// 床背景モデル生成（通常描画）
	// arg1 ... モデル情報（エリアによって変動）
	// arg2 ... モデルID（エリアによって変動）
	void DrawStageNormal(std::vector<sModelInfo>& models_info,int id);

	// 床背景モデル生成（ギミック攻撃時）
	// arg1 ... モデル情報（エリアによって変動）
	// arg2 ... モデルID（エリアによって変動）
	void DrawStageRot(std::vector<sModelInfo>& models_info, int id);

	// 樹木モデル座標設定
	void SetTreePos();

	// 樹木モデル描画
	void DrawTree();

public:

	void Initialize() override;
	
	void Draw(std::shared_ptr<dxe::Camera> camera) override;
	
	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 床背景モデル前方フラグ設定
	void LookSideFront(bool is_front){ m_look_side_front = is_front; }

	// メディエータのポインタ設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};