#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Model.h"


class ModelLoad
{

public:

	ModelLoad();

	~ModelLoad();

private:

	// �X�e�[�W���f���̏��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_model_info;
	// �X�e�[�W���f���̏��i�[�p
	std::vector<Model::sModelInfo> m_model_info;

	// ���؃��f���̏��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_tree_info;
	// ���؃��f���̏��i�[�p
	std::vector<Model::sTreeInfo> m_trees_info;

	// �X�e�[�W���f���̏��ǂݍ���
	void LoadModelTypeInfo();
	// ���؃��f���̏��ǂݍ���
	void LoadTreeTypeInfo();

	// �X�e�[�W3�ȊO�̃��f���摜�ݒ�
	void SetTextureIndex(Model::sModelInfo model_info, int a, int b, int c);
	// �X�e�[�W3�̃��f���摜�ݒ�
	void SetTextureIndex(Model::sModelInfo model_info, int a, int b, int c, int d, int e);
	// ���C�g�ݒ�
	void SetLight(Model::sModelInfo model_info, int i);
	// ���؃��f���̉摜�ݒ�
	void SetTextureTreeIndex(Model::sTreeInfo& model);


public:

	// �X�e�[�W���f���̏��擾
	const std::vector<Model::sModelInfo>& GetModelInfo() const
	{
		return m_model_info;
	}
	// ���؃��f���̏��擾
	const std::vector<Model::sTreeInfo>& GetTreeInfo() const
	{
		return m_trees_info;
	}
};