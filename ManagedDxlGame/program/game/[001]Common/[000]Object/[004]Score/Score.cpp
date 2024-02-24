#include "../../[002]Mediator/Mediator.h"
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
	AddScore();
}

void Score::Draw(std::shared_ptr<dxe::Camera> camera)
{
	ScoreAttach();
}

void Score::LoadScoreData()
{
	// csvファイルの読み込み
	m_csv_score_data
		= tnl::LoadCsv<tnl::CsvCell>("csv/ui/score/score_info.csv");

	// マップタイルの総数を取得
	m_score_num = m_csv_score_data.size() - 1;

	// 0行目は説明文なので読み飛ばす
	for (int y = 1; y < m_csv_score_data.size(); ++y)
	{
		Score::sScoreDate score_info;

		score_info.s_num = m_csv_score_data[y][0].getInt();

		score_info.s_score_path = m_csv_score_data[y][1].getString();

		m_score_date.emplace_back(score_info);
	}
}

void Score::LoadScoreGraph()
{
	// 現在の数字に見合ったnumの数字を描画（画像を変える）
	for (int i = 0; i < m_score_num; ++i)
	{
		// 画像の読み込み
		m_score_date[i].s_score_hdl 
			= LoadGraph(m_score_date[i].s_score_path.c_str());
	}
}

void Score::ScoreAttach()
{
	// 100 : 百の位
	// %10 : 0～9の範囲で算出
	int hundreds = (m_score_total / 100) % 10;
	// 10 : 十の位
	int tens = (m_score_total / 10) % 10; 
	// 一の位
	int ones = m_score_total % 10; 

	// 各桁に対応する画像を画面に描画する
	DrawGraph(m_draw_hundred, m_draw_y, m_score_date[hundreds].s_score_hdl, true);
	DrawGraph(m_draw_ten, m_draw_y, m_score_date[tens].s_score_hdl, true);
	DrawGraph(m_draw_one, m_draw_y, m_score_date[ones].s_score_hdl, true);
}

void Score::AddScore()
{
	if (m_is_add)
	{
		m_score_total += SCORE;

		m_is_add = false;
	}

	// スコアが最大値を越えないようにする
	if (m_score_total > SCORE_MAX)
	{
		m_score_total = SCORE_MAX;
	}
}