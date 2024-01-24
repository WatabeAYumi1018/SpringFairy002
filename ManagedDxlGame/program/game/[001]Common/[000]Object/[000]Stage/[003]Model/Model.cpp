#include "../dxlib_ext/dxlib_ext.h"
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Model.h"


Model::Model()//, eWorldType world_type) 
	//, m_world_type(world_type)
{


	// デバッグ用----------------------------------
	//m_model_hdl = MV1LoadModel("model/stage/testStageSize015.mv1");
}

//Model::Model(int model_hdl, int id)
//	: m_model_hdl(model_hdl), m_id(id)
//{}

Model::~Model()
{
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

	//m_models = m_mediator->GetStageModelTypeInfo();

	//for (const sMeshModelType& m_model : m_models)
	//{
	//	m_mesh_origin = dxe::Mesh::CreateFromFileMV(m_model.s_model_path);
	//	m_mesh_origin->setTexture(dxe::Texture::CreateFromFile(m_model.s_texture_path));
	//
	//	m_models_mesh_origin.emplace_back(m_mesh_origin);
	//}

	m_mesh_origin = dxe::Mesh::CreateFromFileMV("model/stage/flowers/lavender.mv1");
	m_mesh_origin->setTexture(dxe::Texture::CreateFromFile("model/stage/flowers/plant.png"));


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

	//DrawGrass();
	//CreateGroupMesh();
}

void Model::Update(float delta_time)
{
	//GenerateMeshPositions(10,10,100);

	//m_models_mesh_copy.clear(); // コピー用ベクターをクリア

	//for (std::shared_ptr<dxe::Mesh>& mesh : m_models_mesh_origin)
	//{
	//	std::shared_ptr<dxe::Mesh> mesh_copy
	//		= dxe::Mesh::CreateStaticMeshGroupMV(mesh, m_models_matrix);
	//
	//	m_models_mesh_copy.emplace_back(mesh_copy);
	//}

	std::vector<tnl::Matrix> mats;
	mats.emplace_back(tnl::Matrix::Translation(-100, 0, 100));// 座標を指定(csvで座標管理)
	mats.emplace_back(tnl::Matrix::Translation(-200, 0, 200));
	mats.emplace_back(tnl::Matrix::Translation(-300, 0, 300));
	mats.emplace_back(tnl::Matrix::AffineTransformation({ -400, 50, 400 }, { 2, 2, 2 }, tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90))));


	mesh_copy = dxe::Mesh::CreateStaticMeshGroupMV(m_mesh_origin, mats);
}

void Model::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	mesh_copy->render(gameCamera);

	//for (auto& mesh : m_models_mesh_copy)
	//{
	//	mesh->render(gameCamera);
	//}

	// デバッグ用----------------------------------
	//SetLight(m_model_hdl);

	//MV1DrawModel(m_model_hdl);
}

//void Model::CreateGroupMesh()
//{
//	std::vector<tnl::Matrix> world_matrixs;
//	
//	for (Model::sStageModel& model : m_tree_models) 
//	{
//		tnl::Matrix world_matrix
//			= tnl::Matrix::Translation(model.s_pos.x, model.s_pos.y, model.s_pos.z);
//		
//		world_matrixs.emplace_back(world_matrix);
//	}
//
//	// 最初のモデルを基準にグループメッシュを作成
//	if (!m_tree_models.empty()) 
//	{
//		int base_model_id = m_tree_models.front().s_id;
//		
//		// モデルハンドルから Shared<Mesh> インスタンスを取得または作成
//		Shared<dxe::Mesh> base_mesh 
//			= dxe::Mesh::CreateFromFileMV(m_model_map[base_model_id].s_model_path);
//	}
//}

void Model::SetLight(int model_hdl)
{
	//自己発光
	DxLib::COLOR_F emissive = { 0.8f,0.8f,0.8f,1 };
	//環境光
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	//拡散光
	DxLib::COLOR_F diffuse = { 0.8f,0.8f,0.8f,1 };
	//メタリック
	DxLib::COLOR_F specular = { 0,0,0,1 };

	MV1SetMaterialEmiColor(model_hdl, 0, emissive);
	MV1SetMaterialAmbColor(model_hdl, 0, ambient);
	MV1SetMaterialDifColor(model_hdl, 0, diffuse);
	MV1SetMaterialSpcColor(model_hdl, 0, specular);
	// 強いほど光が鋭くなる
	MV1SetMaterialSpcPower(model_hdl, 0, 0.5f);
}

void Model::GenerateMeshPositions(int count_x, int count_z, float spacing)
{
	for (int x = 0; x < count_x; ++x)
	{
		for (int z = 0; z < count_z; ++z)
		{
			tnl::Matrix matrix 
				= tnl::Matrix::Translation(x * spacing, 0, z * spacing);
			
			m_models_matrix.emplace_back(matrix);
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

