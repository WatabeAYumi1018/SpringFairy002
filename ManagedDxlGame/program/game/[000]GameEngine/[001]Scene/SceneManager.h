#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// ゲーム全体を管理するクラス（シングルトン）
//
/////////////////////////////////////////////////////////////////////////////////////////

// やばい

class SceneManager
{

private:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	// arg ... 最初のシーン
	// tips ... 軌道時に一度だけ呼び出します
	// ex ... SceneManager::GetInstance(new SceneTitle());）
	explicit SceneManager(SceneBase* start_scene);

	//-------------------------------------------------------------------------------//


	//----------------------------------シーケンス----------------------------------//

	// シーン遷移
	tnl::Sequence<SceneManager> m_sequence
		= tnl::Sequence<SceneManager>(this, &SceneManager::SeqTransIn);

	//-------------------------------------------------------------------------------//


	//-----------------------------------メンバ変数-----------------------------------//

	// フェードアウトの画像ハンドル
	int m_tansition_hdl = 0;
	// フェードアウトの透明度
	int m_alpha = 255;
	// シーン遷移の時間
	float m_elapsed_time = 0.5f;

	//現在のシーン
	SceneBase* m_now_scene = nullptr;
	//次のシーン
	SceneBase* m_next_scene = nullptr;

	//-------------------------------------------------------------------------------//


	//----------------------------------メンバ関数----------------------------------//

	// シーン遷移（フェードイン）
	bool SeqTransIn(const float delta_time);
	// シーン遷移（フェードアウト）
	bool SeqTransOut(const float delta_time);
	// シーン実行
	bool SeqRunScene(const float delta_time);

public:

	// シーン遷移
	// arg1 ... 次のシーン
	// arg2 ... フェードアウトの時間(デフォルトは0.5f)
	// tips ... シーン遷移の際に呼び出します
	void ChangeScene(SceneBase* next_scene, float trans_time = 0.5f);

	void Update(float delta_time);


	//-----static関数-----//

	// インスタンスの取得
	// arg ... 最初のシーン(デフォルトはnullptrを代入)
	// tips ... 起動時に一度だけ呼び出します
	// ex ... SceneManager::GetInstance(new SceneTitle());）
	static SceneManager* GetInstance(SceneBase* start_scene = nullptr);

	static void Finalize();

	//--------------------//

	//-------------------------------------------------------------------------------//

};