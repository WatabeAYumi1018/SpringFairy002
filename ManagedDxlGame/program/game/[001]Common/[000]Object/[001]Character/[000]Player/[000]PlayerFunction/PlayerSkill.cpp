#include "../../../../[002]Mediator/Mediator.h"
#include "PlayerSkill.h"


void PlayerSkill::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

// ノーマル
bool PlayerSkill::SeqNormal(const float delta_time)
{
	if (tnl::Input::IsKeyDown(eKeys::KB_X))
	{
		tnl_sequence_.change(&PlayerSkill::SeqBouquet);
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_Z))
	{
		tnl_sequence_.change(&PlayerSkill::SeqDance);
	}

	// ボタンが押されるまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}

// 浄化（単発再生）
bool PlayerSkill::SeqBouquet(const float delta_time)
{
	// ボタンが押されるまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() 
	{
	
	});

	tnl_sequence_.change(&PlayerSkill::SeqNormal);

	TNL_SEQ_CO_END;
}

// フィニッシュダンス
bool PlayerSkill::SeqDance(const float delta_time)
{
	// ボタンが押されるまでループ
	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() 
	{
		
	});

	tnl_sequence_.change(&PlayerSkill::SeqNormal);

	TNL_SEQ_CO_END;
}


//// 花を咲かせる
//bool PlayerSkill::SeqBloom(const float delta_time)
//{
//	if (tnl_sequence_.isStart())
//	{
//		StagePhase::eStagePhase now_stage = m_mediator->GetNowStagePhaseState();
//
//		std::shared_ptr<Model> selected_rand_model = nullptr;
//
//		if (now_stage == StagePhase::eStagePhase::e_fly)
//		{
//			// 現在の世界タイプに一致するモデルをランダムに一つ選ぶ
//			selected_rand_model
//				= m_mediator->GetPoolRandomModel(Model::eWorldType::e_real);
//		}
//		else
//		{
//			// 現在の世界タイプに一致するモデルをランダムに一つ選ぶ
//			selected_rand_model
//				= m_mediator->GetPoolRandomModel(Model::eWorldType::e_dream);
//		}
//
//		// モデルが存在する場合、そのモデルの存在フラグをtrueに設定
//		if (selected_rand_model)
//		{
//			selected_rand_model->SetIsAliveActive(true);
//
//			// モデルの座標をプレイヤーの座標に設定
//			selected_rand_model->SetPos(m_mediator->GetPlayerPos());
//		}
//	}
//
//	// ボタンが押されるまでループ
//	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]() {});
//
//	tnl_sequence_.change(&PlayerSkill::SeqNormal);
//
//	TNL_SEQ_CO_END;
//}