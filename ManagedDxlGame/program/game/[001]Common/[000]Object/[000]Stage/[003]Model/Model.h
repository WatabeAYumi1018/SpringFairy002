#pragma once
#include "../../Object.h"

class Mediator;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// ���f���̒�`�ƍX�V�`�揈�����s���N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class Model : public Object
{

public:

	//-------------------------------------�\����--------------------------------------//

	// ���w�i���f�����
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

	// ���؃��f�����i�G���A�t�@���V�[�̂݁j
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


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Model(){}
	
	~Model();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�------------------------------------//

	// ���w�i���f���̃O���b�h���W
	int m_grid_x = 0;
	int m_grid_z = 0;

	// ���؃��f���̐�����
	int m_tree_create_num = 10;

	// ���ʂ���̎��_
	bool m_look_side_front = false;
	// �ʂ̃A�N�e�B�u���
	bool m_is_alive_active = false;

	// ���w�i���f�����
	std::vector<sModelInfo> m_models_info;
	// ���؃��f�����
	std::vector<sTreeInfo> m_trees_info;
	// ���؃��f�����W
	std::vector<VECTOR> m_trees_pos;

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// ���w�i���f���̃O���b�h���W�v�Z
	// arg ... �O���b�h�T�C�Y�i�������قǃ��f�����m�̖��x�������Ȃ�j
	void CalcGridPos(int grid_size);

	// ���w�i���f���̃��[���h���W�v�Z
	// arg1 ... �O���b�hx���W
	// arg2 ... �O���b�hz���W
	// arg3 ... �O���b�h�T�C�Y�i�������قǃ��f�����m�̖��x�������Ȃ�j
	tnl::Vector3 CalcModelPos(int x, int z, int grid_size);

	// ���w�i���f�������i�ʏ�`��j
	// arg1 ... ���f�����i�G���A�ɂ���ĕϓ��j
	// arg2 ... ���f��ID�i�G���A�ɂ���ĕϓ��j
	void DrawStageNormal(std::vector<sModelInfo>& models_info,int id);

	// ���w�i���f�������i�M�~�b�N�U�����j
	// arg1 ... ���f�����i�G���A�ɂ���ĕϓ��j
	// arg2 ... ���f��ID�i�G���A�ɂ���ĕϓ��j
	void DrawStageRot(std::vector<sModelInfo>& models_info, int id);

	// ���؃��f�����W�ݒ�
	void SetTreePos();

	// ���؃��f���`��
	void DrawTree();

public:

	void Initialize() override;
	
	void Draw(std::shared_ptr<dxe::Camera> camera) override;
	
	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// ���w�i���f���O���t���O�ݒ�
	void LookSideFront(bool is_front){ m_look_side_front = is_front; }

	// ���f�B�G�[�^�̃|�C���^�ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};