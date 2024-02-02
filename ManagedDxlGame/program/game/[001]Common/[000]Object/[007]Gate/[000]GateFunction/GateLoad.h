#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Gate.h"


class GateLoad
{

public:

	GateLoad();

	~GateLoad();

private:

	// �Q�[�g���̓ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_gates;
	// �Q�[�g�f�[�^���i�[
	std::vector<Gate::sGateInfo> m_gates;


	void LoadGate();

public:

	// �Q�[�g�f�[�^���擾
	const std::vector<Gate::sGateInfo>& GetGates() const
	{
		return m_gates;
	}
};