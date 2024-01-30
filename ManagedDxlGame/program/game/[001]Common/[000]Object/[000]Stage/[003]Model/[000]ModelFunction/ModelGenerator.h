//#pragma once
//#include "../dxlib_ext/dxlib_ext.h"
//#include "../Model.h"
//
//class GameCamera;
//class Mediator;
//
//class ModelGenerator
//{
//
//public:
//
//	ModelGenerator();
//
//	~ModelGenerator();
//
//private:
//
//	std::vector <Model::sModelInfo> m_models;
//	// 復元元のメッシュモデル
//	std::vector <std::shared_ptr<dxe::Mesh>> m_models_mesh_origin;
//	// コピーしたメッシュモデル
//	std::vector <std::shared_ptr<dxe::Mesh>> m_models_mesh_copy;
//	// メッシュモデル行列(主に座標)
//	std::vector<tnl::Matrix> m_models_matrix;
//
//
//	// 復元元のメッシュモデル
//	std::shared_ptr<dxe::Mesh> m_mesh_origin = nullptr;
//	// コピーしたメッシュモデル
//	std::shared_ptr<dxe::Mesh> m_mesh_copy = nullptr;
//	// メディエーターポインタ
//	std::shared_ptr<Mediator> m_mediator = nullptr;
//
//
//	void LoadGroupModelInfo();
//	
//	void CreateGroupMesh();
//
//	void GenerateMatrices(const Model::sModelInfo& model_type);
//
//public:
//
//	void Initialize();
//
//	void Update(const float delta_time);
//
//	void Draw(std::shared_ptr<GameCamera> gameCamera);
//
//	void SetMediator(std::shared_ptr<Mediator>& mediator)
//	{
//		m_mediator = mediator;
//	}
//
//};