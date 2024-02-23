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

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	ScreenShot();
	~ScreenShot();

	//---------------------------------------------------------------------------------//

private:
	
	//-----------------------------------�����o�ϐ�------------------------------------//

	// ED�̔w�i�n���h��
	int m_back_hdl = 0;

	// �X�N���[���V���b�g�̊������t���O
	bool m_is_shot = false;

	// �ۑ���f�B���N�g��
	std::string m_directry = "images"; 
	// ��{�t�@�C����
	std::string m_base_name = "SpringFairy";
	// �L�����摜��� 
	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// ���f�B�G�[�^�[�|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �w�i�̓ǂݍ���
	// tips ... ���������Ɉ�x�����ǂݍ���
	void LoadBack();

	// �X�N���[���V���b�g�̕ۑ���t�@�C�������擾
	// �ۑ���̃f�B���N�g���i�t�@�C�����j
	// �ۑ����̉摜��
	std::string GetNextFileName(const std::string& directry
								, const std::string& base_name);

	// �ŐV�̃X�N���[���V���b�g�̃t�@�C�������擾
	std::string GetLatestFileName();

public:

	// �X�N���[���V���b�g�̕ۑ�����
	void SaveScreenShot();

	// �X�N���[���V���b�g�̕\������
	void ShowScreenShot();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �X�N���[���V���b�g�̊������t���O�̎擾
	bool GetIsShot() const { return m_is_shot; }

	// ���f�B�G�[�^�̃|�C���^�ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};