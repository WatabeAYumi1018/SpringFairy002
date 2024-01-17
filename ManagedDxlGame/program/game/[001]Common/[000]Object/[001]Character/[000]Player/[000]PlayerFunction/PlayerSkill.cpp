#include "../../../../[002]Mediator/Mediator.h"
#include "PlayerSkill.h"


void PlayerSkill::Update(float delta_time)
{
	tnl_sequence_.update(delta_time);
}

// �m�[�}��
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

	// �{�^�����������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&](){});

	TNL_SEQ_CO_END;
}

// �򉻁i�P���Đ��j
bool PlayerSkill::SeqBouquet(const float delta_time)
{
	// �{�^�����������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() 
	{
	
	});

	tnl_sequence_.change(&PlayerSkill::SeqNormal);

	TNL_SEQ_CO_END;
}

// �t�B�j�b�V���_���X
bool PlayerSkill::SeqDance(const float delta_time)
{
	// �{�^�����������܂Ń��[�v
	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() 
	{
		
	});

	tnl_sequence_.change(&PlayerSkill::SeqNormal);

	TNL_SEQ_CO_END;
}


//// �Ԃ��炩����
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
//			// ���݂̐��E�^�C�v�Ɉ�v���郂�f���������_���Ɉ�I��
//			selected_rand_model
//				= m_mediator->GetPoolRandomModel(Model::eWorldType::e_real);
//		}
//		else
//		{
//			// ���݂̐��E�^�C�v�Ɉ�v���郂�f���������_���Ɉ�I��
//			selected_rand_model
//				= m_mediator->GetPoolRandomModel(Model::eWorldType::e_dream);
//		}
//
//		// ���f�������݂���ꍇ�A���̃��f���̑��݃t���O��true�ɐݒ�
//		if (selected_rand_model)
//		{
//			selected_rand_model->SetIsAliveActive(true);
//
//			// ���f���̍��W���v���C���[�̍��W�ɐݒ�
//			selected_rand_model->SetPos(m_mediator->GetPlayerPos());
//		}
//	}
//
//	// �{�^�����������܂Ń��[�v
//	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]() {});
//
//	tnl_sequence_.change(&PlayerSkill::SeqNormal);
//
//	TNL_SEQ_CO_END;
//}