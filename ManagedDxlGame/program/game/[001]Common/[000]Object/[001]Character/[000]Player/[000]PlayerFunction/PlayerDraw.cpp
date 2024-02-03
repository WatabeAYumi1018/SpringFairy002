#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PlayerDraw.h"


void PlayerDraw::Initialize()
{
	m_model_hdl = m_mediator->GetPlayerModelHdl();
	m_anim_bone_idle_hdl = m_mediator->GetPlayerAnimBoneIdleHdl();
	m_anim_bone_move_hdl = m_mediator->GetPlayerAnimBoneMoveHdl();
	m_anim_bone_bloom_hdl = m_mediator->GetPlayerAnimBoneBloomHdl();
	m_anim_bone_dance_hdl = m_mediator->GetPlayerAnimBoneDanceHdl();
}

void PlayerDraw::Update(const float delta_time)
{
	m_stage_phase = m_mediator->GetNowStagePhaseState();

	tnl_sequence_.update(delta_time);
}

void PlayerDraw::Draw()
{
	if (m_mediator->GetIsGimmickGroundActive())
	{
		// アルファ値を0.5（半透明）に設定
		MV1SetMaterialDifColor(m_model_hdl, 0
								, GetColorF(1.0f, 1.0f, 1.0f, 0.5f)); 
	
		// モデルを描画
		MV1DrawModel(m_model_hdl);

		// アルファ値を1.0（不透明）に設定
		MV1SetMaterialDifColor(m_model_hdl, 0
								, GetColorF(1.0f, 1.0f, 1.0f, 1.0f)); 
	}
	else
	{
		MV1DrawModel(m_model_hdl);
	}
}

void PlayerDraw::AnimBlend(const float delta_time, int current_anim_index, int next_anim_index)
{
	// ブレンド処理
	m_blend_timer += delta_time * 2;

	float blend_rate = m_blend_timer / 1;
	// クランプ
	blend_rate = (blend_rate > 1) ? 1 : blend_rate;

	// 現在のアニメーションのブレンド率を設定
	MV1SetAttachAnimBlendRate(m_model_hdl, current_anim_index, 1 - blend_rate);

	// 次のアニメーションのブレンド率を設定
	MV1SetAttachAnimBlendRate(m_model_hdl, next_anim_index, blend_rate);
}

void PlayerDraw::AnimAttach(int& anim_index, int anim_bone_hdl, float& time_count)
{
	// 新しいアニメーションをアタッチ
	anim_index
		= MV1AttachAnim(m_model_hdl, 0, anim_bone_hdl);

	time_count
		= MV1GetAttachAnimTotalTime(m_model_hdl, anim_index);

	// ブレンドタイマーのリセット
	m_blend_timer = 0.0f;
}

void PlayerDraw::AnimMove(const float delta_time)
{
	// moveアニメーション更新処理
	// 2 : idleの二倍の速度で再生するとちょうどいい
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
	// idleアニメーション更新処理
	m_elapsed_time_idle += m_anim_speed * delta_time;

	if (m_elapsed_time_idle > m_time_count_idle)
	{
		m_elapsed_time_idle -= m_time_count_idle;
	}

	MV1SetAttachAnimTime(m_model_hdl, m_anim_idle_index, m_elapsed_time_idle);
}

void PlayerDraw::AnimBloom(const float delta_time)
{
	// bloomアニメーション更新処理
	m_elapsed_time_bloom += m_anim_speed * delta_time * 2;

	MV1SetAttachAnimTime(m_model_hdl
						, m_anim_bloom_index
						, m_elapsed_time_bloom);
}

void PlayerDraw::AnimDance(const float delta_time)
{
	// danceアニメーション更新処理
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

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z) || m_is_event_dance)
	{
		tnl_sequence_.change(&PlayerDraw::SeqDance);
	}

	// アニメーションの再生
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

	// ブレンド処理
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_move_index, m_anim_bloom_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_move_index);

		TNL_SEQ_CO_FRM_YIELD_RETURN(m_time_count_bloom * 2, delta_time, [&]()
		{
			m_is_bloom = true;

			AnimBloom(delta_time);
		});

		m_is_bloom = false;

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

	// ブレンド処理
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

	// ブレンド処理
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_move_index, m_anim_dance_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_move_index);

		TNL_SEQ_CO_FRM_YIELD_RETURN(m_time_count_dance * 2, delta_time, [&]()
		{
			m_is_dance = true;

			AnimDance(delta_time);
		});

		m_is_dance = false;

		m_elapsed_time_dance = 0;

		m_is_event_dance = false;

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

	// ブレンド処理
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
	// 呼び出す直前にデタッチ（一度だけ実行）
	if (!m_is_touch_idle)
	{
		AnimAttach(m_anim_idle_index, m_anim_bone_idle_hdl, m_time_count_idle);

		m_is_touch_idle = true;

		m_is_touch_move = false;

		m_is_touch_dance = false;
	}

	// ブレンド処理
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_dance_index, m_anim_idle_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_dance_index);

		// ボタンが押されるまでループ
		AnimIdle(delta_time);
	}
}

void PlayerDraw::CinemaAnimMove(const float delta_time)
{
	if (!m_is_touch_move)
	{
		AnimAttach(m_anim_move_index, m_anim_bone_move_hdl, m_time_count_move);

		m_is_touch_move = true;

		m_is_touch_idle = false;

		m_is_touch_dance = false;
	}

	// ブレンド処理
	if (m_blend_timer < 1.0f)
	{
		AnimBlend(delta_time, m_anim_idle_index, m_anim_move_index);
	}
	else
	{
		MV1DetachAnim(m_model_hdl, m_anim_idle_index);

		AnimMove(delta_time);
	}
}

void PlayerDraw::CinemaAnimDance(const float delta_time)
{
	if (!m_is_touch_dance)
	{
		AnimAttach(m_anim_dance_index, m_anim_bone_dance_hdl, m_time_count_dance);

		m_is_touch_dance = true;

		m_is_touch_idle = false;

		m_is_touch_move = false;
	}

	// ブレンド処理
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
//	// ボタンを押してないand地上状態の場合
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