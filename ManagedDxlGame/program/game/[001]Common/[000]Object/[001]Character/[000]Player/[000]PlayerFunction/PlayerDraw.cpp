#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PlayerDraw.h"


PlayerDraw::PlayerDraw()
{
	// �e�N�X�`��
	m_texture_hdl = LoadGraph("model/fairy/fairy.png");
	// ���f���ǂݎ��
	m_model_hdl = MV1LoadModel("model/fairy/fairy_new.mv1");
	// idle�{�[��
	m_anim_bone_idle_hdl = MV1LoadModel("model/fairy/idle.mv1");
	// move�{�[��
	m_anim_bone_move_hdl = MV1LoadModel("model/fairy/move_new.mv1");
	// bloom�{�[��
	m_anim_bone_bloom_hdl = MV1LoadModel("model/fairy/bloom_new.mv1");
	// dance�{�[��
	m_anim_bone_dance_hdl = MV1LoadModel("model/fairy/dance_new.mv1");
	// �ގ��̎w��͂Ȃ����߈�����0
	MV1SetTextureGraphHandle(m_model_hdl, 0, m_texture_hdl, FALSE);

	SetLight();
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

void PlayerDraw::Update(const float delta_time)
{
	m_stage_phase = m_mediator->GetNowStagePhaseState();

	tnl_sequence_.update(delta_time);
}

void PlayerDraw::Draw()
{
	MV1DrawModel(m_model_hdl);
}

void PlayerDraw::UpdateCinemaCamera(float delta_time)
{
	CinemaAnimIdle(delta_time);

	if (m_is_dance)
	{
		CinemaAnimDance(delta_time);
	}
}

void PlayerDraw::SetLight()
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

void PlayerDraw::AnimBlend(const float delta_time, int current_anim_index, int next_anim_index)
{
	// �u�����h����
	m_blend_timer += delta_time * 2;

	float blend_rate = m_blend_timer / 1;
	// �N�����v
	blend_rate = (blend_rate > 1) ? 1 : blend_rate;

	// ���݂̃A�j���[�V�����̃u�����h����ݒ�
	MV1SetAttachAnimBlendRate(m_model_hdl, current_anim_index, 1 - blend_rate);

	// ���̃A�j���[�V�����̃u�����h����ݒ�
	MV1SetAttachAnimBlendRate(m_model_hdl, next_anim_index, blend_rate);
}

void PlayerDraw::AnimAttach(int& anim_index, int anim_bone_hdl, float& time_count)
{
	// �V�����A�j���[�V�������A�^�b�`
	anim_index
		= MV1AttachAnim(m_model_hdl, 0, anim_bone_hdl);

	time_count
		= MV1GetAttachAnimTotalTime(m_model_hdl, anim_index);

	// �u�����h�^�C�}�[�̃��Z�b�g
	m_blend_timer = 0.0f;
}

void PlayerDraw::AnimMove(const float delta_time)
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
						, m_elapsed_time_move);
}

void PlayerDraw::AnimIdle(const float delta_time)
{
	// idle�A�j���[�V�����X�V����
	m_elapsed_time_idle += m_anim_speed * delta_time;

	if (m_elapsed_time_idle > m_time_count_idle)
	{
		m_elapsed_time_idle -= m_time_count_idle;
	}

	MV1SetAttachAnimTime(m_model_hdl, m_anim_idle_index, m_elapsed_time_idle);
}

void PlayerDraw::AnimBloom(const float delta_time)
{
	// bloom�A�j���[�V�����X�V����
	m_elapsed_time_bloom += m_anim_speed * delta_time * 2;

	MV1SetAttachAnimTime(m_model_hdl
						, m_anim_bloom_index
						, m_elapsed_time_bloom);
}

void PlayerDraw::AnimDance(const float delta_time)
{
	// dance�A�j���[�V�����X�V����
	m_elapsed_time_dance += m_anim_speed * delta_time * 3;

	MV1SetAttachAnimTime(m_model_hdl
						 , m_anim_dance_index
						 , m_elapsed_time_dance);
}

bool PlayerDraw::SeqMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		MV1DetachAnim(m_model_hdl, m_anim_move_index);

		m_anim_move_index
			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_move_hdl);

		m_time_count_move
			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_move_index);
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X))
	{
		tnl_sequence_.change(&PlayerDraw::SeqBloom);
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z) || m_is_dance)
	{
		tnl_sequence_.change(&PlayerDraw::SeqDance);
	}

	// �A�j���[�V�����̍Đ�
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimMove(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqBloom(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		AnimAttach(m_anim_bloom_index, m_anim_bone_bloom_hdl, m_time_count_bloom);
	}

	// �u�����h����
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_move_index, m_anim_bloom_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_move_index);

		TNL_SEQ_CO_FRM_YIELD_RETURN(m_time_count_bloom * 2, delta_time, [&]()
		{
			m_is_attack = true;

			AnimBloom(delta_time);
		});

		m_is_attack = false;

		m_elapsed_time_bloom = 0;

		tnl_sequence_.change(&PlayerDraw::SeqBloomToMove);
	}

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqBloomToMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		AnimAttach(m_anim_move_index, m_anim_bone_move_hdl, m_time_count_move);
	}

	// �u�����h����
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_bloom_index, m_anim_move_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_bloom_index);

		tnl_sequence_.change(&PlayerDraw::SeqMove);
	}

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqDance(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		AnimAttach(m_anim_dance_index, m_anim_bone_dance_hdl, m_time_count_dance);
	}

	// �u�����h����
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_move_index, m_anim_dance_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_move_index);

		TNL_SEQ_CO_FRM_YIELD_RETURN(m_time_count_dance * 2, delta_time, [&]()
		{
			m_is_attack = true;

			AnimDance(delta_time);
		});

		m_is_attack = false;

		m_elapsed_time_dance = 0;

		m_is_dance = false;

		tnl_sequence_.change(&PlayerDraw::SeqDanceToMove);
	}

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqDanceToMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		AnimAttach(m_anim_move_index, m_anim_bone_move_hdl, m_time_count_move);
	}

	// �u�����h����
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_dance_index, m_anim_move_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_dance_index);

		tnl_sequence_.change(&PlayerDraw::SeqMove);
	}

	TNL_SEQ_CO_END;
}

void PlayerDraw::CinemaAnimIdle(const float delta_time)
{
	// �Ăяo�����O�Ƀf�^�b�`�i��x�������s�j
	if (!m_is_touch_idle)
	{
		AnimAttach(m_anim_idle_index, m_anim_bone_idle_hdl, m_time_count_idle);

		m_is_touch_idle = true;

		m_is_touch_dance = false;
	}

	// �u�����h����
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_dance_index, m_anim_idle_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_dance_index);

		// �{�^�����������܂Ń��[�v
		AnimIdle(delta_time);
	}
}

void PlayerDraw::CinemaAnimDance(const float delta_time)
{
	if (!m_is_touch_dance)
	{
		AnimAttach(m_anim_dance_index, m_anim_bone_dance_hdl, m_time_count_dance);

		m_is_touch_dance = true;

		m_is_touch_idle = false;
	}

	// �u�����h����
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_idle_index, m_anim_dance_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_idle_index);

		AnimDance(delta_time);
	}

}

//bool PlayerDraw::SeqMove(const float delta_time)
//{
//	if (tnl_sequence_.isStart())
//	{
//		MV1DetachAnim(m_model_hdl, m_anim_move_index);
//
//		m_anim_move_index
//			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_move_hdl);
//
//		m_time_count_move
//			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_move_index);
//
//		m_time_count_move -= m_anim_move_offset;
//	}
//
//	// �{�^���������ĂȂ�and�n���Ԃ̏ꍇ
//	if (!m_mediator->GetPushButton()
//		&& m_stage_phase == StagePhase::eStagePhase::e_ground)
//	{
//		tnl_sequence_.change(&PlayerDraw::SeqIdle);
//	}
//
//	if(tnl::Input::IsKeyDownTrigger(eKeys::KB_X))
//	{
//		tnl_sequence_.change(&PlayerDraw::SeqBloom);
//	}
//
//	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z))
//	{
//		tnl_sequence_.change(&PlayerDraw::SeqDance);
//	}
//
//	TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
//	{
//		MV1SetAttachAnimBlendRate(m_model_hdl, m_anim_move_index);
//	});
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		AnimMove(delta_time);
//	});
//
//	TNL_SEQ_CO_END;
//}
//

//
//MV1SetAttachAnimTime(m_model_hdl
//	, m_anim_dance_index
//	, m_elapsed_time_dance + m_anim_dance_offset);