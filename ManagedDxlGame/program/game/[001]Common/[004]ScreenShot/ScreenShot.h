#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../[000]Object/[005]Event/[002]CharaGraph/CharaGraph.h"


class Mediator;

///////////////////////////////////////////////////////////////////////////
//
//	スクリーンショット演出に関するクラス
//
///////////////////////////////////////////////////////////////////////////


class ScreenShot
{

public:

	ScreenShot();

	~ScreenShot();

private:
	
	// EDの背景ハンドル
	int m_back_hdl = 0;
	// スタンプするプレイヤーの画像
	int m_firy_hdl = 0;
	// スタンプするパートナーの画像
	int m_partner_hdl = 0;

	bool m_is_shot = false;

	// 保存先ディレクトリ
	std::string m_directry = "images"; 
	// 基本ファイル名
	std::string m_base_name = "SpringFairy";
	// キャラ画像情報 
	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// メディエーターポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// 背景の読み込み
	void LoadBack();

	// スクリーンショットの保存先ファイル名を取得
	std::string GetNextFileName(const std::string& directry
								, const std::string& base_name);

	// 最新のスクリーンショットのファイル名を取得
	std::string GetLatestFileName();

public:


	// スクリーンショットの保存処理
	void SaveScreenShot();

	// スクリーンショットの表示処理
	void ShowScreenShot();

	bool GetIsShot() const { return m_is_shot; }

	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}
};