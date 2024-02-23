#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Butterfly.h"


Butterfly::Butterfly()
{
	m_pos = { 0, 0, 0 };
	// ���f�����J�������W�ɔ��f�����邽�߁A�ڂɂ݂��Ȃ����b�V���𐶐�
	m_mesh = dxe::Mesh::CreateSphereMV(0.001f);
	// 5�{�Ɋg��i�ύX�p�x�����Ȃ����ߌŒ�l�j
	m_scale = { 5 };
}

Butterfly::~Butterfly()
{
	// ���f���̃A�����[�h
	MV1DeleteModel(m_model_hdl);

	m_paras.clear();
}

void Butterfly::Initialize()
{
	m_model_hdl = m_mediator->GetButterflyModelHdl();

	m_anim_index = MV1AttachAnim(m_model_hdl, 0);

	m_time_count = MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_index);

	SetLight(m_model_hdl);

	m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));

	m_paras = m_mediator->GetButterflyParameters();
}

void Butterfly::Update(const float delta_time)
{	
	AnimMove(delta_time);

	if (m_is_cinema_active)
	{
		tnl_sequence_.update(delta_time);
	}

	m_mesh->pos_ = m_pos;

	// ��]�ƍ��W����s����v�Z
	m_matrix = CalcMatrix();

    // ���f���ɍs���K�p
    MV1SetMatrix(m_model_hdl, m_matrix);
}

void Butterfly::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_is_op_active || m_is_cinema_active)
	{
		m_mesh->render(camera);

		// �`�惂�[�h��ύX���āA����������
		// 255 : ���S�Ȕ���
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		MV1DrawModel(m_model_hdl);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Butterfly::AnimMove(const float delta_time)
{
	// idle�A�j���[�V�����X�V����
	m_elapsed_time += m_paras[1].s_num * delta_time;

	if (m_elapsed_time > m_time_count)
	{
		m_elapsed_time -= m_time_count;
	}

	MV1SetAttachAnimTime(m_model_hdl, 0, m_elapsed_time);
}

void Butterfly::MoveStraightHeight(const float delta_time)
{
	m_pos.z += m_paras[0].s_num * delta_time;
}

void Butterfly::MoveStraightWidth(const float delta_time)
{
	m_pos.x -= m_paras[0].s_num * delta_time;
}

void Butterfly::MoveRound(const float delta_time)
{
	// �v���C���[�̈ʒu���擾���Ē��S���W�Ƃ���
	tnl::Vector3 center_pos = m_mediator->GetCinemaPlayerPos();

	// �ړ����Ԃ̍X�V
	m_elapsed_time_circle += delta_time;

	// ���݂̃t�F�[�Y�̐i�s�x�������v�Z
	float progress = m_elapsed_time_circle / m_paras[6].s_num;

	// �p�x�̌v�Z
	// 360 : �v���C���[�𒆐S�Ƃ����~�^���̂��ߌŒ�l
	float angle = progress * tnl::ToRadian(360.0f);

	// �~�^��
	m_pos.x = center_pos.x + sin(angle) * m_paras[5].s_num;
	m_pos.z = center_pos.z + cos(angle) * m_paras[5].s_num;

	// Y���㏸�̏���
	m_pos.y += delta_time * m_paras[7].s_num;

	// �i�s�������Z�o
	m_next_direction
		= tnl::Vector3(sin(angle + delta_time * m_paras[0].s_num), 0
						, cos(angle + delta_time * m_paras[0].s_num));

	// �i�s�����Ɍ������ĉ�]
	tnl::Quaternion direction_rot
		= tnl::Quaternion::LookAt(m_pos, m_pos + m_next_direction
									, tnl::Vector3(0, 1, 0));

	// �̂��X�����]�̓K�p
	tnl::Quaternion tilt_rot
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1)
										, tnl::ToRadian(m_paras[8].s_num));

	// �i�s�����̉�]�Ƒ̂��X�����]��g�ݍ��킹��
	m_rot = direction_rot * tilt_rot;
}

bool Butterfly::SeqMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_pos = { m_paras[2].s_num,m_paras[3].s_num,m_paras[4].s_num };

		m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));
	}

	if (abs(m_pos.x - m_mediator->GetCinemaPlayerPos().x) < m_to_player_distance)
	{
		tnl_sequence_.change(&Butterfly::SeqRound);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveStraightWidth(delta_time);	
	});

	TNL_SEQ_CO_END;
}

bool Butterfly::SeqRound(const float delta_time)
{
	if (m_pos.y > m_paras[9].s_num)
	{
		// �t�F�[�h�A�E�g����
		// �t���[�����Ƃ̓����x�̌�����
		// ��: 0.5f��1�b�Ԃɔ����̓����x�ɂȂ�
		float fade_out_speed = m_paras[10].s_num * delta_time; 

		// ���݂̓����x���擾
		float current_opacity = MV1GetOpacityRate(m_model_hdl);

		// �����x���X�V
		float new_opacity = current_opacity - fade_out_speed;

		if (new_opacity < m_paras[11].s_num)
		{
			// �����t���O�𗧂Ă�
			m_is_clear = true;
		}

		// �����x�����̒l�ɂȂ�Ȃ��悤�ɒ���
		if (new_opacity < 0)
		{
			new_opacity = 0;

			m_is_clear = false;

			m_is_cinema_active = false;
		}

		// �V���������x�����f���ɓK�p
		MV1SetOpacityRate(m_model_hdl, new_opacity);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveRound(delta_time);
	});

	TNL_SEQ_CO_END;
}