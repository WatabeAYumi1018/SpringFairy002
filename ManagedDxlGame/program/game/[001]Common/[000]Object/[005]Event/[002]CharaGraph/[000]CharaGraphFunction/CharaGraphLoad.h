#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../CharaGraph.h"

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// ��b���̃L�����N�^�[�C���X�g��csv�t�@�C���̓ǂݍ��݃N���X
//
///////////////////////////////////////////////////////////////////////////


class CharaGraphLoad
{

public:

	CharaGraphLoad();

	~CharaGraphLoad();

private:
	
	// �L�����摜�̓ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_graph_info;
	// �L�����摜�f�[�^���i�[
	std::vector<CharaGraph::sGraphInfo> m_graph_info;

	// �L�����摜�f�[�^��ǂݎ��
	void LoadGraphInfo();

public:

	const std::vector<CharaGraph::sGraphInfo>& GetGraphInfo() const
	{
		return m_graph_info; 
	}
};