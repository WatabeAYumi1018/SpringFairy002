#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gate.h"


class GateLoad
{

public:

	GateLoad();

	~GateLoad();

private:

	// ゲート情報の読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_gates;
	// ゲートデータを格納
	std::vector<Gate::sGateInfo> m_gates;


	void LoadGate();

public:

	// ゲートデータを取得
	const std::vector<Gate::sGateInfo>& GetGates() const
	{
		return m_gates;
	}
};