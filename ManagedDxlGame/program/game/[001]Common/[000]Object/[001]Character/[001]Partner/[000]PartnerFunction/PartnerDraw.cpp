#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PartnerDraw.h"


PartnerDraw::PartnerDraw()
{
	LoadAndInitModels();

	SetLight();
}

PartnerDraw::~PartnerDraw()
{
	DeleteGraph(m_texture_green_hdl);
	DeleteGraph(m_texture_black_hdl);
	DeleteGraph(m_texture_pink_hdl);
	MV1DeleteModel(m_model_hdl);
	MV1DeleteModel(m_anim_bone_move_hdl);
	MV1DeleteModel(m_anim_bone_idle_hdl);
}

void PartnerDraw::LoadAndInitModels()
{
	// �e�N�X�`��
	m_texture_green_hdl = LoadGraph("model/turnipa/green.png");
	m_texture_black_hdl = LoadGraph("model/turnipa/black.png");
	m_texture_pink_hdl = LoadGraph("model/turnipa/pink.png");

	// ���f���ǂݎ��
	m_model_hdl = MV1LoadModel("model/turnipa/futaba.mv1");
	// move�{�[��
	m_anim_bone_move_hdl = MV1LoadModel("model/turnipa/futaba_move.mv1");
	// idle�{�[��
	m_anim_bone_idle_hdl = MV1LoadModel("model/turnipa/futaba_idle.mv1");

	MV1SetTextureGraphHandle(m_model_hdl, 0, m_texture_pink_hdl, FALSE);
}

void PartnerDraw::SetTexture(int texture_hdl)
{
	// �ގ��̎w��͂Ȃ����߈�����0
	MV1SetTextureGraphHandle(m_model_hdl, 0, texture_hdl, FALSE);
}

void PartnerDraw::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

void PartnerDraw::Draw()
{
	MV1DrawModel(m_model_hdl);
}

void PartnerDraw::SetLight()
{
	//���Ȕ���
	DxLib::COLOR_F emissive = { 0.5f,0.5f,0.5f,1 };
	//����
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	//�g�U��
	DxLib::COLOR_F diffuse = { 0.5f,0.5f,0.5f,1 };
	//���^���b�N
	DxLib::COLOR_F specular = { 0,0,0,1 };

	MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	MV1SetMaterialAmbColor(m_model_hdl, 0, ambient);
	MV1SetMaterialDifColor(m_model_hdl, 0, diffuse);
	MV1SetMaterialSpcColor(m_model_hdl, 0, specular);
	// �����قǌ����s���Ȃ�
	MV1SetMaterialSpcPower(m_model_hdl, 0, 0.5f);
}

void PartnerDraw::AnimMove(float delta_time)
{
	// move�A�j���[�V�����X�V����
	m_elapsed_time_move += m_anim_speed * delta_time;

	if (m_elapsed_time_move > m_time_count_move)
	{
		m_elapsed_time_move -= m_time_count_move;
	}

	MV1SetAttachAnimTime(m_model_hdl
						, m_anim_move_index
						, m_elapsed_time_move);
}

void PartnerDraw::AnimIdle(float delta_time)
{
	// idle�A�j���[�V�����X�V����
	m_elapsed_time_idle += m_anim_speed * delta_time;

	if (m_elapsed_time_idle > m_time_count_idle)
	{
		m_elapsed_time_idle -= m_time_count_idle;
	}

	MV1SetAttachAnimTime(m_model_hdl, m_anim_idle_index, m_elapsed_time_idle);
}

bool PartnerDraw::SeqMove(float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		MV1DetachAnim(m_model_hdl, m_anim_move_index);

		m_anim_move_index
			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_move_hdl);

		m_time_count_move
			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_move_index);
			
		m_time_count_move -= m_anim_move_offset;
	}

	// �{�^���������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimMove(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool PartnerDraw::SeqIdle(float delta_time)
{
	// �Ăяo�����O�Ƀf�^�b�`�i��x�������s�j
	if (tnl_sequence_.isStart())
	{
		MV1DetachAnim(m_model_hdl, m_anim_idle_index);

		m_anim_idle_index
			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_idle_hdl);

		m_time_count_idle
			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_idle_index);
	}

	//if (m_mediator->GetPlayerMovePushButton())
	//{
	//	tnl_sequence_.change(&EnemyDraw::SeqMove);
	//}

	// �{�^�����������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimIdle(delta_time);
	});

	TNL_SEQ_CO_END;
}