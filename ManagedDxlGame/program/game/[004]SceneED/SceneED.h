#pragma once
#include "../[000]GameEngine/[001]Scene/SceneBase.h"


///////////////////////////////////////////////////////////////////////////
//
// Endシーンの一括処理を行うクラス
//
///////////////////////////////////////////////////////////////////////////


class ScreenShot;
class EnterGraph;
class Mediator;

class SceneEd : public SceneBase
{

public:

	SceneEd();

	~SceneEd();

private:

	// エンターハンドル
	int m_enter_hdl = 0;

	std::shared_ptr<ScreenShot> m_screen_shot = nullptr;
	std::shared_ptr<EnterGraph> m_enter_graph = nullptr;
	std::shared_ptr<Mediator> m_mediator = nullptr;

	// シーケンス
	tnl::Sequence<SceneEd> m_sequence
		= tnl::Sequence<SceneEd>(this, &SceneEd::SeqStart);

	// シーケンス開始
	bool SeqStart(const float delta_time);

public:

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;

	void Finalize() override;
};