#include "../../../../[002]Mediator/Mediator.h"
#include "../../../../[001]Camera/GameCamera.h"
#include "PartnerMove.h"


void PartnerMove::Update(float delta_time)
{
	m_pos = m_mediator->GetPartnerPos();
	m_rot = m_mediator->GetPartnerRot();

	// �����o�H�ɂ��ړ��Ɖ�]�̍X�V
	m_mediator->MoveAstarCharaMatrix(delta_time, m_pos,m_rot);
	
	UpdatePos(delta_time);

   // UpdateRot(delta_time);

	// �p�[�g�i�[�̈ʒu�Ɖ�]���X�V
	m_mediator->SetPartnerPos(m_pos);
	m_mediator->SetPartnerRot(m_rot);
}

void PartnerMove::UpdatePos(float delta_time)
{
    m_move_time += delta_time;

    // �����I�܂��̓����_���Ɏ��g����ύX(3�b���ƂɕύX)
    if (m_move_time - m_last_move_time > 3.0f)
    {
        // 0.1�`0.4�͈̔͂Ń����_��
        m_orbit_frequency 
            = 0.1f + static_cast<float>(rand()) / RAND_MAX * 0.5f;
       
        m_last_move_time = m_move_time;
    }

    // �v���C���[�̈ʒu���擾
    tnl::Vector3 player_pos = m_mediator->GetPlayerPos();

    // �Ǝ��̓����i�v���C���[�̎������铮���j��ǉ�
    float orbit_radius = 1.0f;
    
    m_offset.x = orbit_radius * cosf(m_move_time * m_orbit_frequency);
    m_offset.z = orbit_radius * sinf(m_move_time * m_orbit_frequency);

    // �����ړ��ɂ��ʒu�ɃI�[�o�[���C
    m_pos += m_offset;
}

void PartnerMove::UpdateRot(float delta_time)
{
    m_rotation_time += delta_time;

    // ���Ԋu�Ń����_���ȉ�]��ݒ�
    if (m_rotation_time - m_last_rotation_time > 5.0f)
    {
        float random_angle 
            = static_cast<float>(rand()) / RAND_MAX * DirectX::XM_PI * 2;
    
        tnl::Vector3 random_axis(rand() % 2, rand() % 2, rand() % 2);
        
        m_target_rot 
            = tnl::Quaternion::RotationAxis(random_axis, random_angle);
        
        m_last_rotation_time = m_rotation_time;
    }

    // ���݂̉�]�ƖڕW�̉�]�̊ԂŊ��炩�ɑJ��    
    m_rot.slerp(m_target_rot, delta_time * 0.5f);
}

bool PartnerMove::SeqPartnerIn(const float delta_time)
{
	// ��̃I�u�W�F�N�g�̒��S���W�����߂�
	m_center = (m_mediator->GetPlayerPos() + m_mediator->GetPartnerPos()) / 2.0f;

	// ���S���W����̒P�ʃx�N�g�������߂�
	m_reverse = tnl::Vector3::Normalize(m_mediator->GetPartnerPos() - m_mediator->GetPlayerPos());

	m_elapsed_time += delta_time;

	TNL_SEQ_CO_TIM_YIELD_RETURN(SINK_DURATION, delta_time, [&]()
	{
		// ���ݍ��ޓ���
		float sink = SINK_VALUE * (m_elapsed_time / SINK_DURATION);

		float sink_size = m_mediator->GetPartnerCollisionSize();

		tnl::Vector3 sink_vec = tnl::Vector3( m_center - (m_reverse * (sink_size - sink))));

		m_mediator->SetPartnerPos(sink_vec);
	});

	tnl_sequence_.change(&PartnerMove::SeqPartnerStay);

	TNL_SEQ_CO_END;
}

bool PartnerMove::SeqPartnerStay(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(0.2f, delta_time, [&]()
	{
		tnl::Vector3 scaele = tnl::Vector3(0.7f);

		//�p�[�g�i�[�̃T�C�Y���኱����������
		m_mediator->SetPartnerScale(scaele);
	});

	tnl::Vector3 scaele = tnl::Vector3(1);

	m_mediator->SetPartnerScale(scaele);

	tnl_sequence_.change(&PartnerMove::SeqPartnerStay);

	TNL_SEQ_CO_END;
}

bool PartnerMove::SeqPartnerOut(const float delta_time)
{
	TNL_SEQ_CO_TIM_YIELD_RETURN(PUSH_DURATION, delta_time, [&]()
	{
		float push = PUSH_VALUE * ((m_elapsed_time - SINK_DURATION) / PUSH_DURATION);

		float push_size = m_mediator->GetPartnerCollisionSize() + push;

		tnl::Vector3 push_vec = tnl::Vector3(m_center - (m_reverse * push_size)));

		m_mediator->SetPartnerPos(push_vec);
	});

	m_elapsed_time = 0;

	tnl_sequence_.change(&PartnerMove::SeqPartnerStay);

	TNL_SEQ_CO_END;
}

//bool PartnerMove::SeqTargetCalc(const float delta_time)
//{
//	if (m_random <= 5)
//	{
//		tnl_sequence_.change(&PartnerMove::SeqFall);
//	}
//
//	if (6 <= m_random && m_random <= 10)
//	{
//		tnl_sequence_.change(&PartnerMove::SeqInverse);
//	}
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]()
//	{
//		m_is_moved = false;
//
//		CalcRandomPos(m_mediator->GetPlayerPos());
//
//		m_random = rand() % 100;
//	});
//
//	tnl_sequence_.change(&PartnerMove::SeqMove);
//
//	TNL_SEQ_CO_END;
//}
//
//bool PartnerMove::SeqMove(const float delta_time)
//{
//	if (m_is_moved)
//	{
//		tnl_sequence_.change(&PartnerMove::SeqTargetCalc);
//	}
//
//	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
//	{
//		UpdateMatrix(delta_time);
//	});
//
//	TNL_SEQ_CO_END;
//}
//
//bool PartnerMove::SeqFall(const float delta_time)
//{
//	TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]()
//	{
//		// ���ɗ���
//		m_target_pos = m_mediator->GetPlayerPos() 
//						- tnl::Vector3(0, rand() % 5, 0);
//	});
//
//	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
//	{
//		// �߂�
//		m_target_pos = m_mediator->GetPlayerPos()
//			+ tnl::Vector3(0, rand() % 5, 0);
//	});
//
//	tnl_sequence_.change(&PartnerMove::SeqTargetCalc);
//
//	TNL_SEQ_CO_END;
//}
//
//bool PartnerMove::SeqInverse(const float delta_time)
//{
//	TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
//	{
//		// �K���ȕ����Ɉړ�
//		m_target_pos = m_mediator->GetPlayerPos() 
//						- tnl::Vector3(rand() % 10, 0, rand() % 10);
//	});
//
//	tnl_sequence_.change(&PartnerMove::SeqTargetCalc);
//
//	TNL_SEQ_CO_END;
//}