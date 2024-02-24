#include "../../../../[002]Mediator/Mediator.h"
#include "../../../../[001]Camera/GameCamera.h"
#include "PartnerMove.h"


void PartnerMove::Update(const float delta_time)
{
	m_pos = m_mediator->GetPartnerPos();
	m_rot = m_mediator->GetPartnerRot();

    if (m_mediator->GetCurrentEventLane().s_id != 6)
    {
        // �����o�H�ɂ��ړ��Ɖ�]�̍X�V
        m_mediator->MoveAstarCharaUpdatePos(delta_time, m_pos);
        m_mediator->MoveAstarCharaUpdateRot(delta_time, m_pos, m_rot);

        UpdateRandomPos(delta_time);
    }

    if (m_mediator->GetCurrentEventLane().s_id == 14)
    {
        // ����I����A�G���h�ֈڍs���邽�߂̏㏸���x
        float move_speed_y = 1000.0f;

        m_pos.y += delta_time * move_speed_y;
    }

	// �p�[�g�i�[�̈ʒu�Ɖ�]���X�V
	m_mediator->SetPartnerPos(m_pos);
	m_mediator->SetPartnerRot(m_rot);
}

void PartnerMove::UpdateRandomPos(const float delta_time)
{
    float change_move_time = 3.0f;

    m_move_time += delta_time;

    // �����I�܂��̓����_���Ɏ��g����ύX(3�b���ƂɕύX)
    if (m_move_time - m_last_move_time > change_move_time)
    {
        // 0.1�`0.2�͈̔͂Ń����_��
        // �킸���Ȑ��l�ŕω����w�ǂȂ����߁A�Œ�l
        m_orbit_frequency
            = tnl::GetRandomDistributionFloat(0.1f, 0.2f);
       
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

// �~���m�̕␳����(Object2���e�����)
void PartnerMove::CorrectPos(const float delta_time)
{
    // �e����鑬�x
    float push_speed = 5.0f;

    tnl::Vector3 player_pos = m_mediator->GetPlayerPos();
    tnl::Vector3 partner_pos = m_mediator->GetPartnerPos();

    // 2�̃I�u�W�F�N�g�Ԃ̋����x�N�g�����v�Z
    tnl::Vector3 distance_vec = partner_pos - player_pos;
    // �P�ʃx�N�g���擾
    distance_vec.normalize();
    // 2�̃I�u�W�F�N�g�Ԃ̋������Z�o
    float distance = distance_vec.length();

    // 2�̃I�u�W�F�N�g�̔��a�̍��v
    float total_radius 
        = m_mediator->GetPlayerCollisionSize()
        + m_mediator->GetPartnerCollisionSize();

    // �Փ˂��������Ă���ꍇ�A�ʒu��␳����
    if (distance < total_radius)
    {
        // �d�Ȃ�̗ʂ��v�Z
        float overlap = total_radius - distance;
        // �␳���邽�߂̈ړ��x�N�g�����v�Z
        tnl::Vector3 correct_vec = distance_vec * overlap;
        //// �␳�ɂ����鎞��
        //float lerp_time = 0.5f;
        //tnl::Vector3 lerp_vec 
        // = tnl::Vector3(partner_pos + (correct_vec * lerp_time * delta_time));
        player_pos -= correct_vec * push_speed * delta_time;
        partner_pos += correct_vec * push_speed * delta_time;

        // �I�u�W�F�N�g�̈ʒu��␳
        m_mediator->SetPlayerPos(player_pos);
        m_mediator->SetPartnerPos(partner_pos);
    }

    m_is_pushed = false;
}