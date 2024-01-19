#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../Object.h"

class Mediator;


class Model : public Object
{

public:

	struct sStageModel
	{
		int s_id;
		tnl::Vector3 s_pos;
	};

	struct sStageModelType
	{
		int s_id;
		int s_model_hdl;
		int s_texture_a_hdl;
		int s_texture_b_hdl;
		int s_texture_c_hdl;
		int s_material_count;
		std::string s_model_path;
		std::string s_texture_a_path;
		std::string s_texture_b_path;
		std::string s_texture_c_path;
		std::string s_material_a_name;
		std::string s_material_b_name;
		std::string s_material_c_name;
	};

	Model();
	//Model(int model_hdl,int id);
	
	~Model();

private:

	int m_width = 0;
	int m_height = 0;

	// �ʂ̃A�N�e�B�u���
	bool m_is_alive_active = false;

	std::vector<Model::sStageModel> m_tree_models;

	std::vector<Model::sStageModel> m_grass_models;

	std::unordered_map<int, sStageModelType> m_model_map;

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;


	// ���C�g�̐ݒ�
	void SetLight(int model_hdl);

	void SetTextureIndex(sStageModelType& model);

	void DrawGrass();

	//void DrawModel(const sStageModel& model);

	void DrawModelSet(const std::vector<Model::sStageModel>& model_set
					  , int num_sets, int spacing);

public:

	void CreateGroupMesh();

	void Initialize() override;

	void Update(float delta_time) override;
	
	void Draw(std::shared_ptr<GameCamera> gameCamera) override;


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

//// ���E�ɂ��A�N�e�B�u���
//bool m_is_world_active = false;
//// ���f���̑���
//eWorldType m_world_type;

//// �R���[�`���V�[�P���X
//TNL_CO_SEQUENCE(Model, &Model::SeqReal);

//// �������E
//bool SeqReal(const float delta_time);
//// ���̐��E
//bool SeqDream(const float delta_time);

//// �A�N�e�B�u���؂�ւ�
//void ToggleActive(bool is_world_active);
//// ��̃��f���t���O�̏�����
//void SetBothActive(bool is_world_active, bool is_alive_active);

//// ���E�t���O�̂ݐݒ�
//void SetIsWorldActive(bool is_active){ m_is_world_active = is_active; }
//// �ʃt���O�̂ݐݒ�
//void SetIsAliveActive(bool is_active){ m_is_alive_active = is_active; }
//// �ʃt���O�̂ݎ擾
//bool GetIsAliveActive() const{ return m_is_alive_active; }
//// �����̎擾
//eWorldType GetWorldType() const{ return m_world_type; }