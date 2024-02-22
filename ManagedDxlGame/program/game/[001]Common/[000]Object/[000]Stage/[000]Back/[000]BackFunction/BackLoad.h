#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../CinemaBack.h"
#include "../SkyBox.h"

/////////////////////////////////////////////////////////////////////////////////////////
// 
// 背景画像csvファイルの読み込み(シネマ背景画像、スカイボックス画像)
//
/////////////////////////////////////////////////////////////////////////////////////////


class BackLoad
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	BackLoad();

	~BackLoad();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// シネマ背景画像の読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_cinemaBack_info;
	// シネマ背景画像データを格納
	std::vector<CinemaBack::sCinemaBackInfo> m_cinemaBack_info;

	// スカイボックス画像の読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_skyBox_info;
	// スカイボックス画像データを格納
	std::vector<SkyBox::sSkyBoxInfo> m_skyBox_info;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// シネマ背景画像の読み取り
	// tips ... 初期化時に一度だけ呼び出す
	void LoadCinemaGraphInfo();

	// スカイボックス画像の読み取り
	// tips ... 初期化時に一度だけ呼び出す
	void LoadSkyBoxInfo();

	//---------------------------------------------------------------------------------//

public:

	//----------------------------------Setter&Getter----------------------------------//

	// シネマ背景画像データを取得
	const std::vector<CinemaBack::sCinemaBackInfo>& GetCinemaGraphInfo() const
	{
		return m_cinemaBack_info;
	}

	// スカイボックス画像データを取得
	const std::vector<SkyBox::sSkyBoxInfo>& GetSkyGraphInfo() const
	{
		return m_skyBox_info;
	}

	//--------------------------------------------------------------------------------//
};