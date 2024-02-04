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
	// バタフライの移動情報読み取り専用（csvファイル）
	std::vector<std::vector<float>> m_csv_move;


	void LoadModelInfo();

	void LoadMoveInfo();

public:

	int GetModelHdl() const { return m_model_hdl; }

};
