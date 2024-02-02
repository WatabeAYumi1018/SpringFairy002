#include "GateLoad.h"


GateLoad::GateLoad()
{
	LoadGate();
}

GateLoad::~GateLoad()
{
	m_csv_gates.clear();
	m_gates.clear();
}

void GateLoad::LoadGate()
{
	m_csv_gates
		= tnl::LoadCsv<tnl::CsvCell>("csv/gate/gate.csv");
	
	// 総数を取得
	int max_num = m_csv_gates.size();

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < max_num; ++y)
	{	
		Gate::sGateInfo gate_info;

		gate_info.s_id = m_csv_gates[y][0].getInt();

		gate_info.s_texture_path = m_csv_gates[y][2].getString();

		m_gates.emplace_back(gate_info);
	}
}