#include "SceneBase.h"
#include "SceneManager.h"


//�R���X�g���N�^�̈�����GameManager�̈����ɏ�����
SceneManager::SceneManager(SceneBase* start_scene)
	: m_now_scene(start_scene)
{
	//�g�����W�V�����p�̃O���t�B�b�N��ǂݍ���(���w�i)
	m_tansition_hdl = LoadGraph("graphics/black.bmp");
}

SceneManager* SceneManager::GetInstance(SceneBase* start_scene)
{
	//�V���O���g��
	static SceneManager* instance = nullptr;

	if (!instance)
	{
		instance = new SceneManager(start_scene);
	}
	return instance;
}

//���݂̃V�[���̍X�V�ƕ`��
void SceneManager::Update(float delta_time)
{
	if (m_now_scene)
	{
		m_now_scene->Update(delta_time);

		m_now_scene->Draw(delta_time);
	}

	m_sequence.update(delta_time);
}

//�V�[���̐؂�ւ�
void SceneManager::ChangeScene(SceneBase* next_scene, float trans_time)
{
	m_next_scene = next_scene;

	m_elapsed_time = trans_time;
	//�g�����W�V�����̊J�n
	m_sequence.change(&SceneManager::SeqTransOut);
}

//�V�[���̐؂�ւ��i�t�F�[�h�C���j
bool SceneManager::SeqTransIn(const float delta_time)
{
	//�����������ɂ��Ă���
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

//�V�[���̎��s
bool SceneManager::SeqRunScene(const float delta_time)
{
	return true;
}

//�V�[���̐؂�ւ��i�t�F�[�h�A�E�g�j
bool SceneManager::SeqTransOut(const float delta_time)
{
	int alpha
		= (m_sequence.getProgressTime() / m_elapsed_time * m_alpha);

	if (alpha >= m_alpha)
	{
		m_sequence.change(&SceneManager::SeqTransIn);

		//���݂̃V�[���̏I������
		m_now_scene->Finalize();

		delete m_now_scene;

		m_now_scene = nullptr;

		//���̃V�[�������݂̃V�[����
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