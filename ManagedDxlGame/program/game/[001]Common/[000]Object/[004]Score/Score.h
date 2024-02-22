#pragma once
#include "../Object.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// �X�R�A�֘A�̈ꊇ�������s���N���X
// ��Load�N���X�ɕ�����܂ł��Ȃ����߁A�{�N���X����csv���[�h���s��
//
///////////////////////////////////////////////////////////////////////////


class Score : public Object
{

public:

	//-------------------------------------�\����--------------------------------------//

	// �X�R�A�̏��
	struct sScoreDate
	{
		int s_num;
		int s_score_hdl;
		std::string s_score_path; 
	};
	
	//---------------------------------------------------------------------------------//


	//--------------------------�R���X�g���N�^�A�f�X�g���N�^---------------------------//

	Score();	
	~Score();

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�ϐ�------------------------------------//

	// �X�R�A�̓��_
	const int SCORE = 10;
	// �X�R�A�̍ő�l
	const int SCORE_MAX = 999;

private:

	// �X�R�A�̍��v
	int m_score_total = 0;
	// �X�R�A�̎��
	int m_score_num = 0;
	// �X�R�A�̕`��ʒu(����)
	int m_draw_hundred = 1100;
	int m_draw_ten = 1150;
	int m_draw_one = 1200;
	// �X�R�A�̕`��ʒu(y���W)
	int m_draw_y = 50;

	// �X�R�A���Z����
	bool m_is_add = false;

	// �X�R�A�̏��ǂݎ���p�icsv�t�@�C���j
	std::vector<std::vector<tnl::CsvCell>> m_csv_score_data;
	
	// �X�R�A�̏��
	std::vector<sScoreDate> m_score_date;

	// ���f�B�G�[�^�̃|�C���^
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�------------------------------------//

	// �X�R�A����ǂݍ���
	void LoadScoreData();

	// �X�R�A�̉摜��ǂݍ���
	void LoadScoreGraph();

	// �X�R�A���e���ɕ���
	void ScoreAttach();

public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	// �X�R�A�����Z����
	void AddScore();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �X�R�A�̍��v��ݒ�
	void SetIsAdd(bool is_add) { m_is_add = is_add; }

	// ���f�B�G�[�^�̐ݒ�
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};
