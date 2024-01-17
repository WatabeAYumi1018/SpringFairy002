#include "SceneBase.h"
#include "SceneManager.h"


//コンストラクタの引数をGameManagerの引数に初期化
SceneManager::SceneManager(SceneBase* start_scene)
	: m_now_scene(start_scene)
{
	//トランジション用のグラフィックを読み込む(黒背景)
	m_tansition_hdl = LoadGraph("graphics/black.bmp");
}

SceneManager* SceneManager::GetInstance(SceneBase* start_scene)
{
	//シングルトン
	static SceneManager* instance = nullptr;

	if (!instance)
	{
		instance = new SceneManager(start_scene);
	}
	return instance;
}

//現在のシーンの更新と描画
void SceneManager::Update(float delta_time)
{
	if (m_now_scene)
	{
		m_now_scene->Update(delta_time);

		m_now_scene->Draw(delta_time);
	}

	m_sequence.update(delta_time);
}

//シーンの切り替え
void SceneManager::ChangeScene(SceneBase* next_scene, float trans_time)
{
	m_next_scene = next_scene;

	m_elapsed_time = trans_time;
	//トランジションの開始
	m_sequence.change(&SceneManager::SeqTransOut);
}

//シーンの切り替え（フェードイン）
bool SceneManager::SeqTransIn(const float delta_time)
{
	//少しずつ透明にしていく
	int alpha
		= m_alpha - (m_sequence.getProgressTime() / m_elapsed_time * m_alpha);

	if (alpha <= 0)
	{
		m_sequence.change(&SceneManager::SeqRunScene);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT
		, m_tansition_hdl, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, m_alpha);

	return true;
}

//シーンの実行
bool SceneManager::SeqRunScene(const float delta_time)
{
	return true;
}

//シーンの切り替え（フェードアウト）
bool SceneManager::SeqTransOut(const float delta_time)
{
	int alpha
		= (m_sequence.getProgressTime() / m_elapsed_time * m_alpha);

	if (alpha >= m_alpha)
	{
		m_sequence.change(&SceneManager::SeqTransIn);

		//現在のシーンの終了処理
		m_now_scene->Finalize();

		delete m_now_scene;

		m_now_scene = nullptr;

		//次のシーンを現在のシーンに
		m_now_scene = m_next_scene;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT
					, m_tansition_hdl, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, m_alpha);

	return true;
}

void SceneManager::Finalize()
{
	delete GetInstance();
}