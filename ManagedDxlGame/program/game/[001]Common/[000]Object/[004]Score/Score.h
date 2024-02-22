#pragma once
#include "../Object.h"

class Mediator;

///////////////////////////////////////////////////////////////////////////
//
// スコア関連の一括処理を行うクラス
// ※Loadクラスに分けるまでもないため、本クラス内でcsvロードも行う
//
///////////////////////////////////////////////////////////////////////////


class Score : public Object
{

public:

	//-------------------------------------構造体--------------------------------------//

	// スコアの情報
	struct sScoreDate
	{
		int s_num;
		int s_score_hdl;
		std::string s_score_path; 
	};
	
	//---------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ---------------------------//

	Score();	
	~Score();

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ変数------------------------------------//

	// スコアの得点
	const int SCORE = 10;
	// スコアの最大値
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

	// スコア加算判定
	bool m_is_add = false;

	// スコアの情報読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_score_data;
	
	// スコアの情報
	std::vector<sScoreDate> m_score_date;

	// メディエータのポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// スコア情報を読み込む
	void LoadScoreData();

	// スコアの画像を読み込む
	void LoadScoreGraph();

	// スコアを各桁に分解
	void ScoreAttach();

public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<dxe::Camera> camera) override;

	// スコアを加算する
	void AddScore();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// スコアの合計を設定
	void SetIsAdd(bool is_add) { m_is_add = is_add; }

	// メディエータの設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};
