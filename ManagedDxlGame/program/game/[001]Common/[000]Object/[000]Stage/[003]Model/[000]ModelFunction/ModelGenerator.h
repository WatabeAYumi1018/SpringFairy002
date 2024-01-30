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
//	// �������̃��b�V�����f��
//	std::vector <std::shared_ptr<dxe::Mesh>> m_models_mesh_origin;
//	// �R�s�[�������b�V�����f��
//	std::vector <std::shared_ptr<dxe::Mesh>> m_models_mesh_copy;
//	// ���b�V�����f���s��(��ɍ��W)
//	std::vector<tnl::Matrix> m_models_matrix;
//
//
//	// �������̃��b�V�����f��
//	std::shared_ptr<dxe::Mesh> m_mesh_origin = nullptr;
//	// �R�s�[�������b�V�����f��
//	std::shared_ptr<dxe::Mesh> m_mesh_copy = nullptr;
//	// ���f�B�G�[�^�[�|�C���^
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