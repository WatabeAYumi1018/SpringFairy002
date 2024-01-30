#pragma once
#include "../Object.h"

class Mediator;


class Score : public Object
{

public:

	struct sScoreDate
	{
		int s_num;
		int s_score_hdl;
		std::string s_score_path; 
	};
	
	Score();
	
	~Score();

	const int SCORE = 10;

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

	std::vector<std::vector<tnl::CsvCell>> m_csv_score_data;

	std::vector<sScoreDate> m_score_date;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// �X�R�A����ǂݍ���
	void LoadScoreData();
	// �X�R�A�̉摜��ǂݍ���
	void LoadScoreGraph();
	// �X�R�A���e���ɕ���
	void ScoreAttach();

public:

	// �X�R�A�����Z����
	void AddScore();

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
