#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "MusicBGM.h"
#include "MusicSE.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 音楽関係のマネージャークラス（シングルトン）
//
/////////////////////////////////////////////////////////////////////////////////////////


class MusicManager
{

private:

    //---------------------------コンストラクタ、デストラクタ---------------------------//

    MusicManager() {}
    ~MusicManager() {}

    //---------------------------------------------------------------------------------//


    //-----------------------------------メンバ変数-----------------------------------//

    // BGMの読み込み用
    std::shared_ptr<MusicBGM> m_bgm = nullptr;
    // 効果音の読み込み用
    std::shared_ptr<MusicSE> m_se = nullptr;

    //--------------------------------------------------------------------------------//

public:

    //-----------------------------シングルトン用関数--------------------------------//

    // 静的変数としてシングルトンインスタンスを作成
    static MusicManager& GetInstance()
    {
        static MusicManager instance;

        return instance;
    }

    // メモリ解放
    static void DeleteInstance()
	{
		MusicManager& instance = GetInstance();
	
        delete &instance;

        instance.m_bgm.reset();
        instance.m_se.reset();
	}

    //------------------------------------------------------------------------------//


    //----------------------------------メンバ関数----------------------------------//

    // BGMの読み込み
    // tips ... BGMを設定する時に呼び出します
    void LoadBGM();

    // 効果音の読み込み
    // tips ... 効果音を設定する時に呼び出します
    void LoadSE();

    // BGMの再生
    // arg1 ... delta_time(前フレームからの経過時間)
    // arg2 ... 該当するBGMのID
    // tips ... BGMをループ再生するときに呼び出します
    void PlayBGM(const float delta_time, int id);

    // BGMの停止
    // arg ... 該当するBGMのID 
    // tips ... BGMを停止するときに呼び出します
    void StopBGM(int id);

    // BGMの停止フラグ
    // arg ... 該当するBGMのID
    // tips ... BGMの停止フラグを取得するときに呼び出します
    bool IsStopBGM(int id);

    // 効果音の再生
    // arg ... 該当する効果音のID
    // tips ... 効果音を再生するときに呼び出します
    void PlaySE(int id);

    // 効果音の停止
    // arg ... 該当する効果音のID
    // tips ... 効果音を停止するときに呼び出します
    void StopSE(int id);

    //------------------------------------------------------------------------------//
};
