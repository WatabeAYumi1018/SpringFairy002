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

	// 保存するスクリーン
	int m_screen_hdl = 0;
	// スタンプするプレイヤーの画像
	int m_firy_hdl = 0;
	// スタンプするパートナーの画像
	int m_partner_hdl = 0;

	// 保存先ディレクトリ
	std::string m_directry = "images"; 
	// 基本ファイル名
	std::string m_base_name = "SpringFairy";
	// キャラ画像情報 
	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// メディエーターポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// スクリーンショットの保存先ファイル名を取得
	std::string GetNextFileName(const std::string& directry
								, const std::string& base_name);

public:

	// スクリーンショットの保存処理
	void SaveScreenShot();

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};