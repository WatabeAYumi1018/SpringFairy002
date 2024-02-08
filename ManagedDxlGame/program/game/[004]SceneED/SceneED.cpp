#include "../[000]GameEngine/[001]Scene/SceneManager.h"
#include "../[001]Common/[004]ScreenShot/ScreenShot.h"
#include "../[002]SceneOP/SceneOp.h"
#include "SceneEd.h"


SceneEd::SceneEd() : m_screen_shot(std::make_shared<ScreenShot>()){}

bool SceneEd::SeqStart(const float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		SceneManager* scene = SceneManager::GetInstance();

		scene->ChangeScene(new SceneOp());
	}

	return true;
}

void SceneEd::Update(const float delta_time)
{
	m_sequence.update(delta_time);
}

void SceneEd::Draw(const float delta_time)
{
	m_screen_shot->ShowScreenShot();
}
