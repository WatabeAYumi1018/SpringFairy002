#pragma once
#include "../[000]GameEngine/[001]Scene/SceneBase.h"

class ScreenShot;


class SceneEd : public SceneBase
{

public:

	SceneEd();

	~SceneEd() {}

private:

	std::shared_ptr<ScreenShot> m_screen_shot = nullptr;

	// シーケンス
	tnl::Sequence<SceneEd> m_sequence
		= tnl::Sequence<SceneEd>(this, &SceneEd::SeqStart);

	// シーケンス開始
	bool SeqStart(const float delta_time);


public:

	void Update(const float delta_time) override;

	void Draw(const float delta_time) override;
};