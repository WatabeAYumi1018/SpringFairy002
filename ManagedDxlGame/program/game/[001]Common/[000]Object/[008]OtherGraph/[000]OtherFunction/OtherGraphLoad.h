#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../ChangeGraph.h"


///////////////////////////////////////////////////////////////////////////
//
// ���̑��̃C���X�g�Ɋւ���csv�t�@�C���̓ǂݍ��݃N���X
//
///////////////////////////////////////////////////////////////////////////


class OtherGraphLoad
{

public:

	OtherGraphLoad();
	~OtherGraphLoad();

private:

	// �摜�̓ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_graph_info;
	// �摜�f�[�^���i�[
	std::vector<ChangeGraph::sChangeGraphInfo> m_graph_info;

	void LoadOtherGraph();

public:

	// �摜�f�[�^���擾
	const std::vector<ChangeGraph::sChangeGraphInfo>& GetGraphInfo() const
	{
		return m_graph_info;
	}
};