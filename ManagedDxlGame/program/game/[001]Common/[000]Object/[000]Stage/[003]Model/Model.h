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
		int s_texture_e_hdl;
		int s_texture_f_hdl;
		int s_material_count;
	};


	Model(){}
	
	~Model(){}

private:

	// ���f���̃O���b�h���W
	int m_grid_x = 0;
	int m_grid_z = 0;

	// �ʂ̃A�N�e�B�u���
	bool m_is_alive_active = false;

	std::vector<sModelInfo> m_models_info;

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// ���f���̃O���b�h���W�v�Z
	void CalcGridPos(int grid_size);

	// ���f���̃��[���h���W�v�Z
	tnl::Vector3 CalcModelPos(int x, int z, int grid_size);

	// �w�i���f�������i�ʏ�`��j
	void DrawStageNormal(std::vector<sModelInfo>& models_info,int id, int grid_size);

	// �w�i���f�������i�M�~�b�N�U�����j
	void DrawStageRot(std::vector<sModelInfo>& models_info, int id, int grid_size);


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