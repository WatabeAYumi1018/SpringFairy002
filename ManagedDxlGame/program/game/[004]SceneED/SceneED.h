#pragma once
#include "../[000]GameEngine/[000]Scene/SceneBase.h"


class ScreenShot;

class EnterGraph;

class Mediator;


///////////////////////////////////////////////////////////////////////////
//
// Endシーンの一括処理を行うクラス
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

	// エンターハンドル
	int m_enter_hdl = 0;

	std::shared_ptr<ScreenShot> m_screen_shot = nullptr;
	std::shared_ptr<EnterGraph> m_enter_graph = nullptr;
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// シーケンス
	tnl::Sequence<SceneEd> m_sequence
		= tnl::Sequence<SceneEd>(this, &SceneEd::SeqStart);

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// シーケンス開始
	bool SeqStart(const float delta_time);

public:

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//
};