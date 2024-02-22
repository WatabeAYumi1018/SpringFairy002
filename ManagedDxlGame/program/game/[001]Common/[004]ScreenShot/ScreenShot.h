#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/CharaGraph.h"


class Mediator;

///////////////////////////////////////////////////////////////////////////
//
//	�X�N���[���V���b�g���o�Ɋւ���N���X
//
///////////////////////////////////////////////////////////////////////////


class ScreenShot
{

public:

	ScreenShot();

	~ScreenShot();

private:
	
	// ED�̔w�i�n���h��
	int m_back_hdl = 0;
	// �X�^���v����v���C���[�̉摜
	int m_firy_hdl = 0;
	// �X�^���v����p�[�g�i�[�̉摜
	int m_partner_hdl = 0;

	bool m_is_shot = false;

	// �ۑ���f�B���N�g��
	std::string m_directry = "images"; 
	// ��{�t�@�C����
	std::string m_base_name = "SpringFairy";
	// �L�����摜��� 
	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �w�i�̓ǂݍ���
	void LoadBack();

	// �X�N���[���V���b�g�̕ۑ���t�@�C�������擾
	std::string GetNextFileName(const std::string& directry
								, const std::string& base_name);

	// �ŐV�̃X�N���[���V���b�g�̃t�@�C�������擾
	std::string GetLatestFileName();

public:


	// �X�N���[���V���b�g�̕ۑ�����
	void SaveScreenShot();

	// �X�N���[���V���b�g�̕\������
	void ShowScreenShot();

	bool GetIsShot() const { return m_is_shot; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};