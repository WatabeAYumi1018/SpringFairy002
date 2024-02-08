#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Model.h"


class ModelPool
{

public:

	ModelPool() {}

	~ModelPool() {}

private:

	// �쐬����e���f���̃C���X�^���X��
	int m_model_create_num = 19;

	// ���f���̃x�N�^�[
	std::vector<std::shared_ptr<Model>> m_models;


public:



	// ���f���̊i�[
	void AddModel(std::shared_ptr<Model>& model);

	int GetModelCreateNum()
	{
		return m_model_create_num;
	}

	// �������E�̃x�N�^�[�擾
	std::vector<std::shared_ptr<Model>>& GetModels()
	{
		return m_models;
	}
};