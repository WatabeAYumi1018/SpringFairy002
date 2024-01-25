#include "../../../../[002]Mediator/Mediator.h"
#include "../../../../[001]Camera/GameCamera.h"
#include "ModelGenerator.h"
#include "../../[002]Floor/Floor.h"


ModelGenerator::ModelGenerator()
{
}

ModelGenerator::~ModelGenerator()
{
	m_models.clear();
	m_models_mesh_origin.clear();
	m_models_mesh_copy.clear();
	m_models_matrix.clear();
}

void ModelGenerator::Initialize()
{
	LoadGroupModelInfo();

	CreateGroupMesh();
}

void ModelGenerator::Update(const float delta_time){}

void ModelGenerator::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	for (std::shared_ptr<dxe::Mesh>& mesh : m_models_mesh_copy)
	{
		mesh->render(gameCamera);
	}
}

void ModelGenerator::LoadGroupModelInfo()
{
	m_models = m_mediator->GetStageModelTypeInfo();

	for (const Model::sMeshModelType& m_model : m_models)
	{
		m_mesh_origin = dxe::Mesh::CreateFromFileMV(m_model.s_model_path);
		m_mesh_origin->setTexture(dxe::Texture::CreateFromFile(m_model.s_texture_path));
		m_mesh_origin->scl_ = { m_model.s_scale };
		
		GenerateMatrices(m_model);

		m_models_mesh_origin.emplace_back(m_mesh_origin);
	}
}

void ModelGenerator::CreateGroupMesh()
{
	// グループメッシュの作成
	for (std::shared_ptr<dxe::Mesh>& mesh_origin : m_models_mesh_origin)
	{
		std::shared_ptr<dxe::Mesh> mesh_copy
			= dxe::Mesh::CreateStaticMeshGroupMV(mesh_origin, m_models_matrix);

		mesh_copy->setBlendMode(DX_BLENDMODE_ALPHA);

		m_models_mesh_copy.emplace_back(mesh_copy);
	}
}

void ModelGenerator::GenerateMatrices(const Model::sMeshModelType& model_type)
{
	int halfX = model_type.s_create_count_x / 2;
	int halfZ = model_type.s_create_count_z / 2;

	for (int x = - halfX; x <= halfX; ++x)
	{
		for (int z = - halfZ; z <= halfZ; ++z) 
		{
			tnl::Matrix matrix 
				= tnl::Matrix::Translation({ x * model_type.s_interval + model_type.s_offset.x
											 ,Floor::DRAW_DISTANCE
											 ,z * model_type.s_interval + model_type.s_offset.z });

			m_models_matrix.emplace_back(matrix);
		}
	}
}