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

	// スコアの合計
	int m_score_total = 0;
	// スコアの種類
	int m_score_num = 0;
	// スコアの描画位置(桁毎)
	int m_draw_hundred = 1100;
	int m_draw_ten = 1150;
	int m_draw_one = 1200;
	// スコアの描画位置(y座標)
	int m_draw_y = 50;

	std::vector<std::vector<tnl::CsvCell>> m_csv_score_data;

	std::vector<sScoreDate> m_score_date;

	std::shared_ptr<Mediator> m_mediator = nullptr;

	// スコア情報を読み込む
	void LoadScoreData();
	// スコアの画像を読み込む
	void LoadScoreGraph();
	// スコアを各桁に分解
	void ScoreAttach();

public:

	// スコアを加算する
	void AddScore();

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};
