#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/CharaGraph.h"


class Mediator;


class ScreenShot
{

public:

	ScreenShot() {}

	~ScreenShot();

private:

	// �ۑ�����X�N���[��
	int m_screen_hdl = 0;
	// �X�^���v����v���C���[�̉摜
	int m_firy_hdl = 0;
	// �X�^���v����p�[�g�i�[�̉摜
	int m_partner_hdl = 0;

	// �ۑ���f�B���N�g��
	std::string m_directry = "images"; 
	// ��{�t�@�C����
	std::string m_base_name = "SpringFairy";
	// �L�����摜��� 
	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �X�N���[���V���b�g�̕ۑ���t�@�C�������擾
	std::string GetNextFileName(const std::string& directry
								, const std::string& base_name);

public:

	// �X�N���[���V���b�g�̕ۑ�����
	void SaveScreenShot();

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};