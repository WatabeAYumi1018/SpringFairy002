#include "../[000]GameEngine/[000]Scene/SceneManager.h"
#include "../[000]GameEngine/[001]Music/MusicManager.h"
#include "../[001]Common/[000]Object/[008]OtherGraph/EnterGraph.h"
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

SceneEd::~SceneEd()
{
	Finalize();
}

bool SceneEd::SeqStart(const float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		MusicManager::GetInstance().PlaySE(0);

		SceneManager* scene = SceneManager::GetInstance();

		scene->ChangeScene(new SceneOp());
	}

	return true;
}

void SceneEd::Update(const float delta_time)
{
	MusicManager::GetInstance().PlayBGM(delta_time,4);

	m_sequence.update(delta_time);

	m_enter_graph->Update(delta_time);
}

void SceneEd::Draw(const float delta_time)
{
	m_screen_shot->ShowScreenShot();

	m_enter_graph->Draw();
}

void SceneEd::Finalize()
{
	MusicManager::GetInstance().StopBGM(4);
	MusicManager::GetInstance().StopSE(0);


	//	�f�X�g���N�^�ɂďz�Q�Ƃ𖾎��I�ɉ���
	//	����A�e�N���X���烁�f�B�G�[�^�ւ̎Q�Ƃ�shared�ōs���Ă��邽�߁A
	//	�J�E���g��0�ɂȂ�Ȃ��Ǝv���鎖�Ă������B
	//	���P��Ƃ��āA���f�B�G�[�^�ւ�weak�Q�Ƃ��������܂����A
	//	���t���[����ʂ�shared_ptr�𐶐����鎖�ɂȂ邽�߁A
	//	�p�t�H�[�}���X�ւ̉e�������O�B
	//	�쐬�I�Ղ̌��i�K�Ő݌v�̌������͌����I�łȂ����߁A
	//	����͖����I�ɉ������鎖�ɂ��܂����B
	//  ����̑傫�ȉۑ�Ƃ��āA�݌v�̌��������s�������������܂��B
	m_enter_graph.reset();
	m_mediator.reset();
	m_screen_shot.reset();
}
