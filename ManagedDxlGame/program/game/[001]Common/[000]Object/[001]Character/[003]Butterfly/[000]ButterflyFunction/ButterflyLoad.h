#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class ButterflyLoad
{

public:

	ButterflyLoad();

	~ButterflyLoad();

private:

	int m_model_hdl = 0;
	int m_texture_hdl = 0;

	std::vector<std::vector<tnl::CsvCell>> m_csv_model_info;
	// �o�^�t���C�̈ړ����ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<float>> m_csv_move;


	void LoadModelInfo();

	void LoadMoveInfo();

public:

	int GetModelHdl() const { return m_model_hdl; }

};
