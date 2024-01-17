#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../CharaGraph.h"


class CharaGraphLoad
{

public:

	CharaGraphLoad();

	~CharaGraphLoad();

private:

	int m_graph_total_num = 0;

	// �}�b�v���̓ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_graph_info;
	// �e�L�X�g�f�[�^���i�[
	std::vector<CharaGraph::sGraphInfo> m_graph_info;


	// �e�L�X�g�f�[�^��ǂݎ��
	void LoadGraphInfo();

public:

	const std::vector<CharaGraph::sGraphInfo>& GetGraphInfo() const
	{
		return m_graph_info; 
	}
};