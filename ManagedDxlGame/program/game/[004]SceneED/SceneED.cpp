#include "../[000]GameEngine/[001]Scene/SceneManager.h"
#include "../[001]Common/[000]Object/[008]EnterGraph/EnterGraph.h"
#include "../[001]Common/[002]Mediator/Mediator.h"
#include "../[001]Common/[004]ScreenShot/ScreenShot.h"
#include "../[002]SceneOP/SceneOp.h"
#include "SceneEd.h"


SceneEd::SceneEd()
{
	m_screen_shot = std::make_shared<ScreenShot>();
	m_enter_graph = std::make_shared<EnterGraph>();
	m_mediator = std::make_shared<Mediator>();

	m_screen_shot->SetMediator(m_mediator);
	m_mediator->SetEnterGraph(m_enter_graph);
}

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

	m_enter_graph->Update(delta_time);
}

void SceneEd::Draw(const float delta_time)
{
	m_screen_shot->ShowScreenShot();

	m_enter_graph->Draw();
}
