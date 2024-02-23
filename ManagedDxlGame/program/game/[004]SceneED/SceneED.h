#pragma once
#include "../[000]GameEngine/[000]Scene/SceneBase.h"


class ScreenShot;

class EnterGraph;

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// Endシーンの一括処理を行うクラス
// 使用クラスも殆どなく意味もないため、今クラスはオブジェクト指向を使用しない
//
///////////////////////////////////////////////////////////////////////////


class SceneEd : public SceneBase
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	SceneEd();
	~SceneEd();

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ変数-----------------------------------//

private:

	// 各クラスのポインタ
	std::shared_ptr<ScreenShot> m_screen_shot = nullptr;
	std::shared_ptr<EnterGraph> m_enter_graph = nullptr;
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// シーケンス
	tnl::Sequence<SceneEd> m_sequence
		= tnl::Sequence<SceneEd>(this, &SceneEd::SeqStart);

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// シーケンス開始
	// arg ... delta_time(前フレームからの経過時間)
	bool SeqStart(const float delta_time);

public:

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//
};