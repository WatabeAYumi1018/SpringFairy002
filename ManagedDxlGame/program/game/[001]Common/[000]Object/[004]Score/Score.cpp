#include "Score.h"


Score::Score()
{
	LoadScoreData();

	LoadScoreGraph();
}

Score::~Score()
{
	m_csv_score_data.clear();
	m_score_date.clear();
}

void Score::Update(const float delta_time)
{
	m_score_total++;
}

void Score::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	ScoreAttach();
}

void Score::LoadScoreData()
{
	// csv�t�@�C���̓ǂݍ���
	m_csv_score_data
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/score/score_info.csv");

	// �}�b�v�^�C���̑������擾
	int max_num = m_csv_score_data.size();

	m_score_num = max_num - 1;

	// 0�s�ڂ͐������Ȃ̂œǂݔ�΂�
	for (int y = 1; y < max_num; ++y)
	{
		Score::sScoreDate score_info;

		score_info.s_num = m_csv_score_data[y][0].getInt();

		score_info.s_score_path = m_csv_score_data[y][1].getString();

		m_score_date.emplace_back(score_info);
	}
}

void Score::LoadScoreGraph()
{
	// ���݂̐����Ɍ�������num�̐�����`��i�摜��ς���j
	for (int i = 0; i < m_score_num; ++i)
	{
		// �摜�̓ǂݍ���
		m_score_date[i].s_score_hdl 
			= LoadGraph(m_score_date[i].s_score_path.c_str());
	}
}

void Score::ScoreAttach()
{
	// 100 : �S�̈�
	// %10 : 0�`9�͈̔͂ŎZ�o
	int hundreds = (m_score_total / 100) % 10;
	// 10 : �\�̈�
	int tens = (m_score_total / 10) % 10; 
	// ��̈�
	int ones = m_score_total % 10; 

	// �e���ɑΉ�����摜����ʂɕ`�悷��
	DrawGraph(m_draw_hundred, m_draw_y, m_score_date[hundreds].s_score_hdl, true);
	DrawGraph(m_draw_ten, m_draw_y, m_score_date[tens].s_score_hdl, true);
	DrawGraph(m_draw_one, m_draw_y, m_score_date[ones].s_score_hdl, true);
}

void Score::AddScore()
{
	m_score_total += SCORE;

	// �X�R�A���ő�l���z���Ȃ��悤�ɂ���
	if (m_score_total > SCORE_MAX)
	{
		m_score_total = SCORE_MAX;
	}
}