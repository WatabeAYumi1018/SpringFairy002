#pragma once
#include "../Butterfly.h"


class ButterflyLoad
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	ButterflyLoad();
	~ButterflyLoad();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数------------------------------------//

	//　モデルハンドル
	int m_model_hdl = 0;
	
	//　テクスチャハンドル
	int m_texture_hdl = 0;
	
	// テクスチャハンドル(tip)
	// ※発光表現のためのテクスチャ
	// 現状では3Dモデルの知識不足により使いこなせていません
	int m_texture_tip_hdl = 0;
	
	// テクスチャハンドル(mask)
	// ※発光表現のためのテクスチャ
	// 現状では3Dモデルの知識不足により使いこなせていません
	int m_tecxture_mask_hdl = 0;

	// モデル情報読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_model_info;

	// 各種パラメータの情報読み取り専用(csvファイル)
	std::vector<std::vector<tnl::CsvCell>> m_csv_parameters;

	// 各種パラメータ
	std::vector<Butterfly::sButterflyParameter> m_parameters;

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数------------------------------------//

	// モデル情報読み取り専用（csvファイル）
	// tips ... 初期化時に一度だけ呼び出す
	void LoadModelInfo();

	// パラメータ情報読み取り専用（csvファイル）
	// tips ... 初期化時に一度だけ呼び出す
	void LoadParameter();

	//---------------------------------------------------------------------------------//
	
	
	//----------------------------------Setter&Getter----------------------------------//

public:

	// モデルハンドルを取得
	int GetModelHdl() const { return m_model_hdl; }

	// 各種パラメータを取得
	const std::vector<Butterfly::sButterflyParameter>& GetParameters() const
	{
		return m_parameters; 
	}
	
	//---------------------------------------------------------------------------------//
};