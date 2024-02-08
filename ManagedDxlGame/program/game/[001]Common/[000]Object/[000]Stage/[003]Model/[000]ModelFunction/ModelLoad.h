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

	// �X�e�[�W���f���̏��ǂݍ���
	void LoadModelTypeInfo();

	void SetTextureIndex(Model::sModelInfo model_info, int a, int b, int c);

	void SetLight(Model::sModelInfo model_info, int i);

public:

	const std::vector<Model::sModelInfo>& GetModelInfo() const
	{
		return m_model_info;
	}
};