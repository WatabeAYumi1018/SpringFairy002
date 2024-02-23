#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// BGMクラス（再生と停止）
//
/////////////////////////////////////////////////////////////////////////////////////////


class MusicBGM
{

public:

	//-------------------------------------構造体--------------------------------------//

	// csvで読み取ったBGM情報
	struct sMusicBGM
	{
		int s_id;
		int s_bgm_hdl = 0;
	};

	//--------------------------------------------------------------------------------//


	//--------------------------コンストラクタ、デストラクタ--------------------------//

	MusicBGM();

	~MusicBGM();

	//-------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数----------------------------------//

	// BGM再生状態を追跡するフラグ
	bool m_is_playing = false; 

	// 現在のボリューム
	float m_current_volume = 100.0f;
	// 目的のボリューム
	float m_target_volume = 100.0f;
	// フェード速度
	float m_fade_speed =10.0f;

	// BGMの種類読み取り専用（csvファイル）
	std::vector<std::vector<tnl::CsvCell>> m_csv_bgm_info;
	// BGMの種類情報格納用
	std::vector<MusicBGM::sMusicBGM> m_bgms_info;

	// BGMパスの情報読み込み
	void LoadBGMInfo();

	//-----------------------------------------------------------------------------//

public:

	//----------------------------------メンバ関数---------------------------------//

	// BGMの再生
	// arg ... 該当するBGMのID
	void Play(int id);

	// BGMの停止
	// arg ... 該当するBGMのID
	void Stop(int id);

	// フェードイン再生開始
 	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... 該当するBGMのID
	// tips ... BGMをフェードイン再生するときに呼び出します
	void FadeIn(const float delta_time, int id);

	// フェードアウト再生停止
	// arg1 ... delta_time(前フレームからの経過時間)
	// arg2 ... 該当するBGMのID
	// tips ... BGMをフェードアウト再生するときに呼び出します
	void FadeOut(const float delta_time, int id);

	// BGMの音量を取得するメソッド
	// arg ... 該当するBGMのID
	// tips ... シーンチェンジでBGMの音量を取得するときに呼び出します
	float GetCurrentVolume(int id) 
	{
		return GetVolumeSoundMem2(m_bgms_info[id].s_bgm_hdl);
	}

	//-----------------------------------------------------------------------------//
};
