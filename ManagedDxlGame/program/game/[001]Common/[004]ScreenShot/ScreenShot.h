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

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	ScreenShot();
	~ScreenShot();

	//---------------------------------------------------------------------------------//

private:
	
	//-----------------------------------メンバ変数------------------------------------//

	// EDの背景ハンドル
	int m_back_hdl = 0;

	// スクリーンショットの活性化フラグ
	bool m_is_shot = false;

	// 保存先ディレクトリ
	std::string m_directry = "images"; 
	// 基本ファイル名
	std::string m_base_name = "SpringFairy";
	// キャラ画像情報 
	std::vector<CharaGraph::sGraphInfo> m_chara_graph;

	// メディエーターポインタ
	std::shared_ptr<Mediator> m_mediator = nullptr;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// 背景の読み込み
	// tips ... 初期化時に一度だけ読み込む
	void LoadBack();

	// スクリーンショットの保存先ファイル名を取得
	// 保存先のディレクトリ（ファイル名）
	// 保存時の画像名
	std::string GetNextFileName(const std::string& directry
								, const std::string& base_name);

	// 最新のスクリーンショットのファイル名を取得
	std::string GetLatestFileName();

public:

	// スクリーンショットの保存処理
	void SaveScreenShot();

	// スクリーンショットの表示処理
	void ShowScreenShot();

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// スクリーンショットの活性化フラグの取得
	bool GetIsShot() const { return m_is_shot; }

	// メディエータのポインタ設定
	void SetMediator(std::shared_ptr<Mediator>& mediator)
	{
		m_mediator = mediator;
	}

	//---------------------------------------------------------------------------------//
};