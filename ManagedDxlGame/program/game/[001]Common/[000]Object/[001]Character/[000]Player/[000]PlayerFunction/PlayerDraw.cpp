#include "../../../../../../wta_library/wta_Convert.h"
#include "../../../../../[000]GameEngine/[001]Music/MusicManager.h"
#include "../../../../[002]Mediator/Mediator.h"
#include "PlayerDraw.h"


PlayerDraw::~PlayerDraw()
{
	MV1DetachAnim(m_model_game_hdl, m_anim_move_index);
	MV1DetachAnim(m_model_game_hdl, m_anim_bloom_index);
	MV1DetachAnim(m_model_game_hdl, m_anim_dance_index);
	
	MV1DetachAnim(m_model_cinema_hdl, m_anim_idle_index);
	MV1DetachAnim(m_model_cinema_hdl, m_anim_dance_index);

	MV1DeleteModel(m_model_game_hdl);
	MV1DeleteModel(m_model_cinema_hdl);
}

void PlayerDraw::Initialize()
{
	m_model_game_hdl 
		= m_mediator->GetPlayerModelGameHdl();

	m_model_cinema_hdl
		= m_mediator->GetPlayerModelCinemaHdl();

	m_anim_bone_move_game_hdl 
		= m_mediator->GetPlayerAnimBoneMoveGameHdl();

	m_anim_bone_bloom_game_hdl 
		= m_mediator->GetPlayerAnimBoneBloomGameHdl();

	m_anim_bone_dance_game_hdl 
		= m_mediator->GetPlayerAnimBoneDanceGameHdl();

	m_anim_bone_idle_cinema_hdl
		= m_mediator->GetPlayerAnimBoneIdleCinemaHdl();

	m_anim_bone_dance_cinema_hdl 
		= m_mediator->GetPlayerAnimBoneDanceCinemaHdl();
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
		// 0.5 : 半透明
		MV1SetMaterialDifColor(m_model_game_hdl, 0
								, GetColorF(1.0f, 1.0f, 1.0f, 0.5f)); 
	
		// モデルを描画
		MV1DrawModel(m_model_game_hdl);

		// 1.0 : 不透明
		MV1SetMaterialDifColor(m_model_game_hdl, 0
								, GetColorF(1.0f, 1.0f, 1.0f, 1.0f)); 
	}
	else
	{
		MV1DrawModel(m_model_game_hdl);
	}
}

void PlayerDraw::AnimBlend(const float delta_time,int model_hdl, int current_anim_index, int next_anim_index)
{
	// ブレンド処理
	m_blend_timer += delta_time * m_blend_speed;
	// 1 : 毎秒ごとにブレンドする（変更予定もないため固定値）
	float blend_rate = m_blend_timer / 1;
	// クランプ
	// 1 : 1以上の値は1にする（変更予定もないため固定値）
	blend_rate = (blend_rate > 1) ? 1 : blend_rate;

	// 現在のアニメーションのブレンド率を設定
	MV1SetAttachAnimBlendRate(model_hdl, current_anim_index, 1 - blend_rate);

	// 次のアニメーションのブレンド率を設定
	MV1SetAttachAnimBlendRate(model_hdl, next_anim_index, blend_rate);
}

void PlayerDraw::AnimAttach(int model_hdl, int& anim_index, int anim_bone_hdl, float& time_count)
{
	// 新しいアニメーションをアタッチ
	anim_index = MV1AttachAnim(model_hdl, 0, anim_bone_hdl);

	time_count = MV1GetAttachAnimTotalTime(model_hdl, anim_index);

	// ブレンドタイマーのリセット
	m_blend_timer = 0.0f;
}

void PlayerDraw::AnimMove(const float delta_time,int model_hdl )
{
	// moveアニメーション更新処理
	// 2 : idleの二倍の速度で再生するとちょうどいい
	// ※アニメーションモデルの元データに起因するためほぼ変更はない。
	m_elapsed_time_move += m_anim_speed * 2 * delta_time;

	if (m_elapsed_time_move > m_time_count_move)
	{
		m_elapsed_time_move -= m_time_count_move;
	}

	MV1SetAttachAnimTime(model_hdl
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

	MV1SetAttachAnimTime(m_model_cinema_hdl, m_anim_idle_index, m_elapsed_time_idle);
}

void PlayerDraw::AnimBloom(const float delta_time)
{
	// bloomアニメーション更新処理
	// 2 : bloomの二倍の速度で再生するとちょうどいい
	// ※アニメーションモデルの元データに起因するためほぼ変更はない。
	m_elapsed_time_bloom += m_anim_speed * delta_time * 2;

	MV1SetAttachAnimTime(m_model_game_hdl
						, m_anim_bloom_index
						, m_elapsed_time_bloom);
}

void PlayerDraw::AnimDance(const float delta_time, int model_hdl)
{
	// danceアニメーション更新処理
	// 3 : danceの二倍の速度で再生するとちょうどいい
	// ※アニメーションモデルの元データに起因するためほぼ変更はない。
	m_elapsed_time_dance += m_anim_speed * delta_time * 3;

	MV1SetAttachAnimTime(model_hdl
						 , m_anim_dance_index
						 , m_elapsed_time_dance);
}

bool PlayerDraw::SeqMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		MV1DetachAnim(m_model_game_hdl, m_anim_move_index);

		m_anim_move_index
			= MV1AttachAnim(m_model_game_hdl, 0, m_anim_bone_move_game_hdl);

		m_time_count_move
			= MV1GetAttachAnimTotalTime(m_model_game_hdl, m_anim_move_index);

		MusicManager::GetInstance().StopSE(1);

		MusicManager::GetInstance().StopSE(2);
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X))
	{
		tnl_sequence_.change(&PlayerDraw::SeqBloom);
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z))
	{
		tnl_sequence_.change(&PlayerDraw::SeqDance);
	}

	// アニメーションの再生
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		AnimMove(delta_time, m_model_game_hdl);
	});

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqBloom(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		AnimAttach(m_model_game_hdl,m_anim_bloom_index, m_anim_bone_bloom_game_hdl, m_time_count_bloom);
	}

	// ブレンド処理
	if (m_blend_timer < m_blend_total_time)
	{
		AnimBlend(delta_time, m_model_game_hdl, m_anim_move_index, m_anim_bloom_index);
	}
	else
	{
		MV1DetachAnim(m_model_game_hdl, m_anim_move_index);

		// 2 : 読み取ったアニメーションカウントフレームに対して2倍の速度で再生するとちょうどいい
		// ※アニメーションモデルの元データに起因するためほぼ変更はない。
		TNL_SEQ_CO_FRM_YIELD_RETURN(m_time_count_bloom * 2, delta_time, [&]()
		{
			AnimBloom(delta_time);

			m_is_bloom = true;

			MusicManager::GetInstance().PlaySE(1);
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
		AnimAttach(m_model_game_hdl,m_anim_move_index, m_anim_bone_move_game_hdl, m_time_count_move);
	}

	// ブレンド処理
	if (m_blend_timer < m_blend_total_time)
	{
		AnimBlend(delta_time, m_model_game_hdl, m_anim_bloom_index, m_anim_move_index);
	}
	else
	{
		MV1DetachAnim(m_model_game_hdl, m_anim_bloom_index);

		tnl_sequence_.change(&PlayerDraw::SeqMove);
	}

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqDance(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		AnimAttach(m_model_game_hdl,m_anim_dance_index, m_anim_bone_dance_game_hdl, m_time_count_dance);
	}

	// ブレンド処理
	if (m_blend_timer < m_blend_total_time)
	{
		AnimBlend(delta_time, m_model_game_hdl,m_anim_move_index, m_anim_dance_index);
	}
	else
	{
		MV1DetachAnim(m_model_game_hdl, m_anim_move_index);

		// 1.5 : 読み取ったアニメーションカウントフレームに対して2倍の速度で再生するとちょうどいい
		// ※アニメーションモデルの元データに起因するためほぼ変更はない。
		TNL_SEQ_CO_FRM_YIELD_RETURN(m_time_count_dance * 1.5f, delta_time, [&]()
		{
			AnimDance(delta_time, m_model_game_hdl);
			
			MusicManager::GetInstance().PlaySE(2);

			m_is_dance = true;
		});

		m_is_dance = false;

		m_elapsed_time_dance = 0;

		tnl_sequence_.change(&PlayerDraw::SeqDanceToMove);
	}

	TNL_SEQ_CO_END;
}

bool PlayerDraw::SeqDanceToMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		AnimAttach(m_model_game_hdl,m_anim_move_index, m_anim_bone_move_game_hdl, m_time_count_move);
	}

	// ブレンド処理
	if (m_blend_timer < m_blend_total_time)
	{
		AnimBlend(delta_time, m_model_game_hdl, m_anim_dance_index, m_anim_move_index);
	}
	else
	{
		MV1DetachAnim(m_model_game_hdl, m_anim_dance_index);

		tnl_sequence_.change(&PlayerDraw::SeqMove);
	}

	TNL_SEQ_CO_END;
}

void PlayerDraw::CinemaAnimIdle(const float delta_time)
{
	// 呼び出す直前にデタッチ（一度だけ実行）
	if (!m_is_touch_idle)
	{
		MV1DetachAnim(m_model_cinema_hdl, m_anim_idle_index);

		m_anim_idle_index
			= MV1AttachAnim(m_model_cinema_hdl, 0, m_anim_bone_idle_cinema_hdl);

		m_time_count_idle
			= MV1GetAttachAnimTotalTime(m_model_cinema_hdl, m_anim_idle_index);

		m_is_touch_idle = true;

		m_is_touch_dance = false;
	}

	// ボタンが押されるまでループ
	AnimIdle(delta_time);
	
}

void PlayerDraw::CinemaAnimDance(const float delta_time)
{
	if (!m_is_touch_dance)
	{
		MV1DetachAnim(m_model_cinema_hdl, m_anim_dance_index);

		m_anim_dance_index
			= MV1AttachAnim(m_model_cinema_hdl, 0, m_anim_bone_dance_cinema_hdl);

		m_time_count_dance
			= MV1GetAttachAnimTotalTime(m_model_cinema_hdl, m_anim_dance_index);

		m_is_touch_dance = true;

		m_is_touch_idle = false;
	}

	AnimDance(delta_time, m_model_cinema_hdl);
}
