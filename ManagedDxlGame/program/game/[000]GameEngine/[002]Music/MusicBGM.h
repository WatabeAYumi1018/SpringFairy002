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

	struct sMusicBGM
	{
		int s_id;
		int s_bgm_hdl = 0;
	};

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	MusicBGM();

	~MusicBGM();

	//-------------------------------------------------------------------------------//

private:

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

public:

	//----------------------------------メンバ関数----------------------------------//

	// BGMの再生
	void Play(int id);

	// BGMの停止
	void Stop(int id);

	// フェードイン再生開始
	// tips ... BGMをフェードイン再生するときに呼び出します
	void FadeIn(const float delta_time, int id);

	// フェードアウト再生停止
	// tips ... BGMをフェードアウト再生するときに呼び出します
	void FadeOut(const float delta_time, int id);

	// BGMの音量を取得するメソッド
	// tips ... シーンチェンジでBGMの音量を取得するときに呼び出します
	float GetCurrentVolume(int id) 
	{
		return GetVolumeSoundMem2(m_bgms_info[id].s_bgm_hdl);
	}


	//-----------------------------------------------------------------------------//
};
