#pragma once
#include "../[000]GameEngine/[000]Scene/SceneBase.h"
#include "../[001]Common/[000]Object/Object.h"


class PlayFactory;

class GameCamera;
class CinemaCamera;

class CameraPhase;
class StagePhase;

class GimmickGenerator;

class ScreenShot;


///////////////////////////////////////////////////////////////////////////
//
// Playシーンの一括処理を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class ScenePlay : public SceneBase
{

public:

	//--------------------------コンストラクタ、デストラクタ---------------------------//

	ScenePlay();
	~ScenePlay();

	//--------------------------------------------------------------------------------//

private:
	
	//-----------------------------------メンバ変数-----------------------------------//

	// ゲームカメラ管轄のオブジェクトlist
	std::list<std::shared_ptr<Object>> m_objects_gameCamera;
	// シネマカメラ管轄のオブジェクトlist
	std::list<std::shared_ptr<Object>> m_objects_cinemaCamera;

	// 各クラスのポインタ

	std::shared_ptr<PlayFactory> m_factory = nullptr;

	std::shared_ptr<GameCamera> m_gameCamera = nullptr;
	std::shared_ptr<CinemaCamera> m_cinemaCamera = nullptr;

	std::shared_ptr<CameraPhase> m_cameraPhase = nullptr;
	std::shared_ptr<StagePhase> m_stagePhase = nullptr;

	std::shared_ptr<GimmickGenerator> m_gimmickGenerator = nullptr;

	std::shared_ptr<ScreenShot> m_screenShot = nullptr;

	// シーケンス
	tnl::Sequence<ScenePlay> m_sequence
		= tnl::Sequence<ScenePlay>(this, &ScenePlay::SeqStart);

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// ファクトリークラスからの取得
	// tips ... 初期化時に一度だけ呼び出す
	void GetFromFactory();

	// シーケンス開始
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqStart(const float delta_time);

public:

	void Initialize() override;

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//
};