#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Model.h"
//#include "../../../[003]Phase/StagePhase.h"


class ModelLoad
{

public:

	ModelLoad();

	~ModelLoad();

private:

	// �X�e�[�W���f���̑���
	int m_model_total_num = 0;

	int m_model_vec_height = 0;
	int m_model_vec_width = 0;

	int m_model_type_height = 0;
	int m_model_type_width = 0;

	// ���؃��f���z��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<int>> m_csv_stage_tree;
	// ���؃��f���z����i�[�p
	std::vector<Model::sStageModel> m_stage_tree;

	// �ԃ��f���z��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<int>> m_csv_stage_grass;
	// �ԃ��f���z����i�[�p
	std::vector<Model::sStageModel> m_stage_grass;

	// �X�e�[�W���f���̏��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_model_type_info;
	// �X�e�[�W���f���̏��i�[�p
	std::vector<Model::sStageModelType> m_model_type;


	// ���؃��f���̏��ǂݍ���
	void LoadTreeVector();
	// �ԃ��f���̏��ǂݍ���
	void LoadGrassVector();
	// �X�e�[�W���f���̏��ǂݍ���
	void LoadModelTypeInfo();

public:

	// �X�e�[�W���f����id�擾
	Model::sStageModelType GetModelInfoById(int id);

	int GetModelTotalNum() const { return m_model_total_num; }

	int GetModelVecHeight() const { return m_model_vec_height; }

	int GetModelVecWidth() const { return m_model_vec_width; }

	const std::vector<Model::sStageModel>& GetTreeVector() const
	{
		return m_stage_tree;
	}

	const std::vector<Model::sStageModel>& GetGrassVector() const
	{
		return m_stage_grass;
	}

	const std::vector<Model::sStageModelType>& GetModelTypeInfo() const
	{
		return m_model_type;
	}
};