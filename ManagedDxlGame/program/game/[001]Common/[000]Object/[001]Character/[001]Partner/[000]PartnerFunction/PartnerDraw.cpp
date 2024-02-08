#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PartnerDraw.h"


void PartnerDraw::Initialize()
{
	// モデル読み取り
	m_model_hdl = m_mediator->GetPartnerModelHdl();
	// idleボーン
	m_anim_bone_idle_cinema_hdl = m_mediator->GetPartnerAnimBoneIdleHdl();
	// moveボーン
	m_anim_bone_move_game_hdl = m_mediator->GetPartnerAnimBoneMoveHdl();
}

void PartnerDraw::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

void PartnerDraw::Draw()
{
	MV1DrawModel(m_model_hdl);
}

void PartnerDraw::AnimMove(float delta_time)
{
	// moveアニメーション更新処理
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
	// idleアニメーション更新処理
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
			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_move_game_hdl);

		m_time_count_move
			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_move_index);
			
		m_time_count_move -= m_anim_move_offset;
	}

	// ボタンが離れるまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimMove(delta_time);
	});

	TNL_SEQ_CO_END;
}

bool PartnerDraw::SeqIdle(float delta_time)
{
	// 呼び出す直前にデタッチ（一度だけ実行）
	if (tnl_sequence_.isStart())
	{
		MV1DetachAnim(m_model_hdl, m_anim_idle_index);

		m_anim_idle_index
			= MV1AttachAnim(m_model_hdl, 0, m_anim_bone_idle_cinema_hdl);

		m_time_count_idle
			= MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_idle_index);
	}

	//if (m_mediator->GetPlayerMovePushButton())
	//{
	//	tnl_sequence_.change(&EnemyDraw::SeqMove);
	//}

	// ボタンが押されるまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimIdle(delta_time);
	});

	TNL_SEQ_CO_END;
}