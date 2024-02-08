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
	
	// ‘”‚ğæ“¾
	int max_num = m_csv_gates.size();

	// 0s–Ú‚Íà–¾•¶‚È‚Ì‚Å“Ç‚İ”ò‚Î‚·
	for (int y = 1; y < max_num; ++y)
	{	
		Gate::sGateInfo gate_info;

		gate_info.s_id = m_csv_gates[y][0].getInt();

		gate_info.s_texture_path = m_csv_gates[y][2].getString();

		m_gates.emplace_back(gate_info);
	}
}