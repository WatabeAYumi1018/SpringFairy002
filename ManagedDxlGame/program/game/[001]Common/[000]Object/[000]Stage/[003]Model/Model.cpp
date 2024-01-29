#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "../[002]Floor/Floor.h"
#include "Model.h"


Model::Model()//, eWorldType world_type) 
	//, m_world_type(world_type)
{
	LoadTexture();

	SetTextureIndex();

	SetLight(m_model_hdl);
}

//Model::Model(int model_hdl, int id)
//	: m_model_hdl(model_hdl), m_id(id)
//{}

Model::~Model()
{
	MV1DeleteModel(m_model_hdl);
	DeleteGraph(m_texture_normal_hdl);
	DeleteGraph(m_texture_yellow_hdl);
	DeleteGraph(m_texture_pink_hdl);

	//for (auto& pair : m_model_map)
	//{
	//	sStageModelType& data = pair.second;

	//	MV1DeleteModel(data.s_model_hdl);
	//	DeleteGraph(data.s_texture_a_hdl);
	//	DeleteGraph(data.s_texture_b_hdl);
	//	DeleteGraph(data.s_texture_c_hdl);
	//}
}

void Model::Initialize()
{
	//m_mediator->ModelGeneInitialize();

	//	for (int id = 0; id < 8; ++id)
//{
//	sStageModelType model;
//	// モデル読み取り
//	model = m_mediator->GetStageModelInfoById(id);
//	// モデルの読み込み
//	model.s_model_hdl
//		= MV1LoadModel(model.s_model_path.c_str());
//	// テクスチャ読み取り
//	model.s_texture_a_hdl
//		= LoadGraph(model.s_texture_a_path.c_str());
//	// テクスチャ読み取り
//	model.s_texture_b_hdl
//		= LoadGraph(model.s_texture_b_path.c_str());
//	// テクスチャ読み取り
//	model.s_texture_c_hdl
//		= LoadGraph(model.s_texture_c_path.c_str());
//	// マテリアル数の設定
//	model.s_material_count
//		= MV1GetMaterialNum(model.s_model_hdl);
//	SetTextureIndex(model);
//
//	m_model_map[id] = model;
//}

	//m_tree_models = m_mediator->GetStageTreeVector();

	//m_grass_models = m_mediator->GetStageGrassVector();
}

void Model::Update(float delta_time)
{

}

void Model::Draw(std::shared_ptr<dxe::Camera> camera)
{
	//m_mediator->ModelGeneDraw(gameCamera);

	if (!m_mediator->GetIsGimmickGroundActive())
	{
		DrawGrass();
	}

}

void Model::LoadTexture()
{
	m_model_hdl = MV1LoadModel("model/stage/flowers/grass.mv1");

	m_texture_normal_hdl = LoadGraph("model/stage/flowers/plant.png");
	m_texture_yellow_hdl = LoadGraph("model/stage/flowers/plant_yellow.png");
	m_texture_pink_hdl = LoadGraph("model/stage/flowers/plant_pink.png");
	//m_texture_orange_hdl = LoadGraph("model/stage/flowers/plant_orange.png");

	m_material_count = MV1GetMaterialNum(m_model_hdl);
}

void Model::SetTextureIndex()
{
	for (int i = 0; i < m_material_count; ++i)
	{
		if (i < 43) 
		{
			MV1SetTextureGraphHandle(m_model_hdl, i, m_texture_normal_hdl, FALSE);			
		}
		else if (i > 42 || i < 73)
		{
			MV1SetTextureGraphHandle(m_model_hdl, i, m_texture_yellow_hdl, FALSE);
		}
		else if (i > 72 || i < 102)
		{
			MV1SetTextureGraphHandle(m_model_hdl, i, m_texture_pink_hdl, FALSE);
		}
		//else if (i > 101 || i < 128)
		//{
		//	MV1SetTextureGraphHandle(m_model_hdl, i, m_texture_orange_hdl, FALSE);
		//}
	}

	SetLight(m_model_hdl);
}

void Model::SetLight(int model_hdl)
{
	// 各マテリアルに対するライトの設定
	for (int i = 0; i < m_material_count; ++i)
	{
		DxLib::COLOR_F emissive = { 0.8f,0.8f,0.8f,1 };
		DxLib::COLOR_F ambient = { 1,1,1,1 };
		DxLib::COLOR_F diffuse = { 0.8f,0.8f,0.8f,1 };
		DxLib::COLOR_F specular = { 0,0,0,1 };

		MV1SetMaterialEmiColor(model_hdl, i, emissive);
		MV1SetMaterialAmbColor(model_hdl, i, ambient);
		MV1SetMaterialDifColor(model_hdl, i, diffuse);
		MV1SetMaterialSpcColor(model_hdl, i, specular);
		MV1SetMaterialSpcPower(model_hdl, i, 0.5f);
	}
}

void Model::DrawGrass()
{
	// モデルサイズとグリッドサイズ
	int model_size = 1500;
	int grid_size = 1500;

	tnl::Vector3 target_pos = m_mediator->GetCameraTargetPlayerPos();
	
	// プレイヤーの現在位置からグリッド座標を取得
	int target_grid_x = static_cast<int>(target_pos.x / grid_size);
	int target_grid_z = static_cast<int>(target_pos.z / grid_size);

	// 描画範囲の設定（ターゲットの位置を中心に前方に向けて）
	int draw_range = 6; 

	for (int z = target_grid_z; z < target_grid_z + draw_range; z++) 
	{
		for (int x = target_grid_x - draw_range / 2; x <= target_grid_x + draw_range / 2; x++)
		{
			// 透明化処理（ある程度後方にあるモデルは描画しない）
			if (z < target_grid_z - grid_size) continue;

			// モデルの座標を計算
			tnl::Vector3 pos;
			pos.x = static_cast<float>(x * model_size);
			pos.y = Floor::DRAW_DISTANCE;
			// 前方を少し遠めに設定し突然のモデルの出現を防ぐ
			pos.z = static_cast<float>(z * model_size) + 1000;

			// モデルのワールド座標を設定
			VECTOR pos_vec =wta::ConvertToVECTOR(pos);

			// モデルの位置を設定
			MV1SetPosition(m_model_hdl, pos_vec);

			// モデルを描画
			MV1DrawModel(m_model_hdl);
		}
	}
}

//void Model::SetTextureIndex(sStageModelType& model)
//{
//	for (int i = 0; i < MV1GetMaterialNum(model.s_model_hdl); i++)
//	{
//		const TCHAR* material_name = MV1GetMaterialName(model.s_model_hdl, i);
//
//		if (!model.s_material_a_name.empty()
//			&& _tcscmp(material_name, _T(model.s_material_a_name.c_str())) == 0)
//		{
//			MV1SetTextureGraphHandle(model.s_model_hdl, i
//									, model.s_texture_a_hdl, FALSE);
//		}
//
//		if (!model.s_material_b_name.empty()
//			&& _tcscmp(material_name, _T(model.s_material_b_name.c_str())) == 0)
//		{
//			MV1SetTextureGraphHandle(model.s_model_hdl, i
//									, model.s_texture_b_hdl, FALSE);
//		}
//
//		if (!model.s_material_c_name.empty()
//			&& _tcscmp(material_name, _T(model.s_material_c_name.c_str())) == 0)
//		{
//			MV1SetTextureGraphHandle(model.s_model_hdl
//									, i, model.s_texture_c_hdl, FALSE);
//		}
//	}
//}

//void Model::DrawGrass()
//{
//	std::vector<tnl::Matrix> grass_world_matrixs;
//
//	// IDが4のモデルを取得
//	sMeshModelType& model_grass = m_model_map[4];
//	// グリッドのサイズ
//	int grid_size = 150;
//	// グリッドの半分のサイズ
//	int half_grid_size = grid_size / 2;
//	// フロア間のスペース
//	int spacing = 300;
//
//	float distance = -2000;
//
//	// 指定されたグリッド内でモデルを繰り返し描画
//	for (int i = -half_grid_size; i < half_grid_size; i++)
//	{
//		for (int j = -half_grid_size; j < half_grid_size; j++)
//		{
//			// ライティング設定
//			SetLight(model_grass.s_model_hdl);
//
//			// 各フロアの座標を計算
//			float x = static_cast<float> (i * spacing);
//			float z = static_cast<float> (j * spacing);
//
//			tnl::Vector3 pos = { x, distance, z };
//
//			//MV1SetPosition(model_grass.s_model_hdl, pos_vec);
//
//			tnl::Matrix world_matrix = wta::ConvertTnlToMatrix(pos);
//
//			grass_world_matrixs.emplace_back(world_matrix);
//
//			// モデルを描画
//			//MV1DrawModel(model_grass.s_model_hdl);
//		}
//
//		// グループメッシュの作成
//		std::shared_ptr<dxe::Mesh> grass_base_mesh
//			= dxe::Mesh::CreateFromFileMV(model_grass.s_model_path);
//	}
//}

//void Model::DrawModelSet(const std::vector<Model::sStageModel>& model_set
//						 , int num_sets, int spacing)
//{
//	// 各セットに対してループ
//	for (int set_index = 0; set_index < num_sets; set_index++)
//	{
//		// セットの基準座標を計算
//		float base_x = ((set_index % 2) == 0) ? spacing : -spacing;
//		float base_z = (set_index < 2) ? spacing : -spacing;
//
//		// CSVから読み込んだモデルの配列をループ
//		for (const Model::sStageModel& model : model_set)
//		{
//			if (model.s_id == -1) continue;
//
//			// 各モデルの座標をセットの基準座標に加算
//			float x = base_x + model.s_pos.x;
//			float y = model.s_pos.y;
//			float z = base_z + model.s_pos.z;
//
//			// モデルの位置を設定
//			VECTOR pos_vec = wta::ConvertToVECTOR({ x, y, z });
//
//			MV1SetPosition(m_model_map[model.s_id].s_model_hdl, pos_vec);
//
//			// ライティング設定
//			SetLight(m_model_map[model.s_id].s_model_hdl);
//
//			// モデルを描画
//			MV1DrawModel(m_model_map[model.s_id].s_model_hdl);
//		}
//	}
//}

//void Model::DrawModel(const sStageModel& model)
//{
//	sStageModelType& data = m_model_map[model.s_id];
//
//	SetLight(data.s_model_hdl);
//
//	VECTOR pos_vec = wta::ConvertToVECTOR(model.s_pos);
//
//	MV1SetPosition(data.s_model_hdl, pos_vec);
//
//	MV1DrawModel(data.s_model_hdl);
//}

//void  Model::CopyInitModel(int texture_a
//							,int texture_b
//							, int texture_c
//							, int material_count
//							, std::string name_a
//							, std::string name_b
//							, std::string name_c)
//{
//	m_texture_a_hdl = texture_a;
//	m_texture_b_hdl = texture_b;
//	m_texture_c_hdl = texture_c;
//	m_material_count = material_count;
//	m_material_a_name = name_a;
//	m_material_b_name = name_b;
//	m_material_c_name = name_c;
//
//	SetTextureIndex(m_material_a_name, m_material_b_name, m_material_c_name);
//}
//
//void Model::Initialize()
//{
//	const std::vector<Model::sStageModel>& models 
//						= m_mediator->GetStageTreeVector();
//
//	for (const Model::sStageModel& model : models)
//	{
//		if (model.s_id == -1)
//		{
//			continue;
//		}
//
//		m_pos = model.s_pos;
//
//		// Vector3をVECTORに変換
//		VECTOR dx_vec_pos = wta::ConvertToVECTOR(m_pos);
//		// 保存された位置情報を使用して描画
//		MV1SetPosition(m_model_hdl, dx_vec_pos);
//	}
//}


// 世界と個別生存フラグがtrueの時のみ描画
//if (//m_is_world_active && 
//	m_is_alive_active)
//{

//VECTOR pos_vec = wta::ConvertToVECTOR(m_pos);

//MV1SetPosition(m_model_hdl, pos_vec);

//MV1DrawModel(m_model_hdl);
//}

//// 現実世界
//bool Model::SeqReal(const float delta_time)
//{
//	if (tnl_sequence_.isStart())
//	{
//		m_mediator->IsActivatePoolAllModels(eWorldType::e_real);
//	}
//
//	// 夢世界に変更されたら切り替え
//	if (m_mediator->GetNowStagePhaseState() == StagePhase::eStagePhase::e_ground)
//	{
//		tnl_sequence_.change(&Model::SeqDream);
//	}
//
//	// 再生が終了するまでループ
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});
//
//	TNL_SEQ_CO_END;
//}
//
//// 夢の世界
//bool Model::SeqDream(const float delta_time)
//{
//	if (tnl_sequence_.isStart())
//	{
//		// 全モデルのアクティブ化と非アクティブ化の更新
//		m_mediator->IsActivatePoolAllModels(eWorldType::e_dream);
//	}
//
//	// 夢世界に変更されたら切り替え
//	if (m_mediator->GetNowStagePhaseState() == StagePhase::eStagePhase::e_fly)
//	{
//		tnl_sequence_.change(&Model::SeqReal);
//	}
//
//	// 押すまでループ
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});
//
//	TNL_SEQ_CO_END;
//}

//void Model::ToggleActive(bool is_world_active)
//{
//	m_is_world_active = is_world_active;
//	// 世界フラグがfalseの時は個別フラグもfalse
//	if(m_is_world_active)
//	{
//		m_is_alive_active = true;
//	}
//}

//void Model::SetBothActive(bool is_world_active, bool is_alive_active)
//{
//	m_is_world_active = is_world_active;
//	m_is_alive_active = is_alive_active;
//}

