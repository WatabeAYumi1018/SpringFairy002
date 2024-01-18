#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PlayerDraw.h"


PlayerDraw::PlayerDraw()
{
	// �e�N�X�`��
	m_texture_hdl = LoadGraph("model/fairy/fairy.png");
	// ���f���ǂݎ��
	m_model_hdl = MV1LoadModel("model/fairy/fairy.mv1");
	// idle�{�[��
	m_anim_bone_idle_hdl = MV1LoadModel("model/fairy/idle.mv1");
	// move�{�[��
	m_anim_bone_move_hdl = MV1LoadModel("model/fairy/move.mv1");
	// bloom�{�[��
	m_anim_bone_bloom_hdl = MV1LoadModel("model/fairy/bloom.mv1");
	// dance�{�[��
	m_anim_bone_dance_hdl = MV1LoadModel("model/fairy/dance.mv1");
	// �ގ��̎w��͂Ȃ����߈�����0
	MV1SetTextureGraphHandle(m_model_hdl, 0, m_texture_hdl, FALSE);
}

PlayerDraw::~PlayerDraw()
{
	DeleteGraph(m_texture_hdl);
	MV1DeleteModel(m_model_hdl);
	MV1DeleteModel(m_anim_bone_idle_hdl);
	MV1DeleteModel(m_anim_bone_move_hdl);
	MV1DeleteModel(m_anim_bone_bloom_hdl);
	MV1DeleteModel(m_anim_bone_dance_hdl);
}

void PlayerDraw::Update(float delta_time)
{
	m_stage_phase = m_mediator->GetNowStagePhaseState();

	tnl_sequence_.update(delta_time);
}

void PlayerDraw::Draw()
{
	SetLight();

	MV1DrawModel(m_model_hdl);
}

void PlayerDraw::SetLight()
{
	//���Ȕ���
	DxLib::COLOR_F emissive = { 0.3f,0.3f,0.3f,1 };
	//����
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	//�g�U��
	DxLib::COLOR_F diffuse = { 0.3f,0.3f,0.3f,1 };
	//���^���b�N
	DxLib::COLOR_F specular = { 0.2f,0.2f,0.2f,1 };

	MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	MV1SetMaterialAmbColor(m_model_hdl, 0, ambient);
	MV1SetMaterialDifColor(m_model_hdl, 0, diffuse);
	MV1SetMaterialSpcColor(m_model_hdl, 0, specular);
	// �����قǌ����s���Ȃ�
	MV1SetMaterialSpcPower(m_model_hdl, 0, 0.5f);
}

void PlayerDraw::AnimMove(float delta_time)
{
	// move�A�j���[�V�����X�V����
	// 2 : idle�̓�{�̑��x�ōĐ�����Ƃ��傤�ǂ���
	m_elapsed_time_move += m_anim_speed * 2 * delta_time;

	if (m_elapsed_time_move > m_time_count_move)
	{
		m_elapsed_time_move -= m_time_count_move;
	}

	MV1SetAttachAnimTime(m_model_hdl
						, m_anim_move_index
						, m_elapsed_time_move + m_anim_move_offset);
}

void PlayerDraw::AnimIdle(float delta_time)
{
	// idle�A�j���[�V�����X�V����
	m_elapsed_time_idle += m_anim_speed * delta_time;

	if (m_elapsed_time_idle > m_time_count_idle)
	{
		m_elapsed_time_idle -= m_time_count_idle;
	}

	MV1SetAttachAnimTime(m_model_hdl, m_anim_idle_index, m_elapsed_time_idle);
}

void PlayerDraw::AnimBloom(float delta_time)
{
	// bloom�A�j���[�V�����X�V����
	m_elapsed_time_bloom += m_anim_speed * delta_time * 2;

	MV1SetAttachAnimTime(m_model_hdl
						, m_anim_bloom_index
						, m_elapsed_time_bloom + m_anim_bloom_offset);
}

void PlayerDraw::AnimDance(float delta_time)
{
	// dance�A�j���[�V�����X�V����
	m_elapsed_time_dance += m_anim_speed * delta_time * 3;

	MV1SetAttachAnimTime(m_model_hdl
						 , m_anim_dance_index
						 , m_elapsed_time_dance + m_anim_dance_offset);
}

bool PlayerDraw::SeqMove(float delta_time)
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

	// �{�^���������ĂȂ�and�n���Ԃ̏ꍇ
	if (!m_mediator->GetPushButton()
		&& m_stage_phase == StagePhase::eStagePhase::e_ground)
	{
		tnl_sequence_.change(&PlayerDraw::SeqIdle);
	}

	if(tnl::Input::IsKeyDownTrigger(eKeys::KB_X))
	{
		tnl_sequence_.change(&PlayerDraw::SeqBloom);
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z))
	{
		tnl_sequence_.change(&PlayerDraw::SeqDance);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimMove(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqIdle(float delta_time)
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

	// �{�^���������Ă���or�󒆏�Ԃ̏ꍇ
	if (m_mediator->GetPushButton()
		|| m_stage_phase == StagePhase::eStagePhase::e_fly)
	{
		tnl_sequence_.change(&PlayerDraw::SeqMove);
	}

	// �{�^�����������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimIdle(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqBloom(float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		MV1DetachAnim(m_model_hdl, m_anim_bloom_index);

		m_anim_bloom_index
			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_bloom_hdl);

		m_time_count_bloom
			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_bloom_index);

		m_time_count_bloom -= m_anim_bloom_offset;
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(m_time_count_bloom * 2 , delta_time, [&]()
	{
		m_is_attack = true;

		AnimBloom(delta_time);
	});

	m_is_attack = false;

	m_elapsed_time_bloom = 0;

	tnl_sequence_.change(&PlayerDraw::SeqMove);

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqDance(float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		MV1DetachAnim(m_model_hdl, m_anim_dance_index);

		m_anim_dance_index
			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_dance_hdl);

		m_time_count_dance
			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_dance_index);

		m_time_count_dance -= m_anim_dance_offset ; 
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(m_time_count_dance * 2 , delta_time, [&]()
	{
		AnimDance(delta_time);

		// �_���X���Ƀp�[�e�B�N�����U�炷���p�[�e�B�N�����U���Ă����true�Ƃ��H
	});

	m_elapsed_time_dance = 0;

	tnl_sequence_.change(&PlayerDraw::SeqMove);

	TNL_SEQ_CO_END;
}

