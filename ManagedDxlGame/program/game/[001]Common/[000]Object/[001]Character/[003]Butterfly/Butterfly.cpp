#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Butterfly.h"


Butterfly::Butterfly()
{
	m_pos = { 0,0,0 };

	// ���f�����J�������W�ɔ��f�����邽�߁A�ڂɂ݂��Ȃ����b�V���𐶐�
	m_mesh = dxe::Mesh::CreateSphereMV(0.001f);

	m_scale = { 5 };
}

Butterfly::~Butterfly()
{
	// ���f���̃A�����[�h
	MV1DeleteModel(m_model_hdl);
}

void Butterfly::Initialize()
{
	m_model_hdl = m_mediator->GetButterflyModelHdl();

	m_anim_index = MV1AttachAnim(m_model_hdl, 0);

	m_time_count = MV1GetAttachAnimTotalTime(m_model_hdl, m_anim_index);

	SetLight(m_model_hdl);

	m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));

	//// �G�~�b�V�u�J���[��ݒ肵�ă��f���𔭌�������
	//DxLib::COLOR_F emissive = {10.0f, 10.0f, 10.0f, 1 }; // ��������
	//
	//MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);

	//DxLib::COLOR_F diffuse = { 10,10,10,1 };

	//MV1SetMaterialDifColor(m_model_hdl, 0, diffuse);
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
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		MV1DrawModel(m_model_hdl);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Butterfly::AnimMove(const float delta_time)
{
	// idle�A�j���[�V�����X�V����
	m_elapsed_time += m_anim_speed * delta_time;

	if (m_elapsed_time > m_time_count)
	{
		m_elapsed_time -= m_time_count;
	}

	MV1SetAttachAnimTime(m_model_hdl, 0, m_elapsed_time);
}

void Butterfly::MoveRound(const float delta_time)
{
	// �v���C���[�̈ʒu���擾���Ē��S���W�Ƃ���
	tnl::Vector3 center_pos = m_mediator->GetCinemaPlayerPos();

	// �~�^���̔��a
	float radius = 200.0f;

	// �ړ����Ԃ̍X�V
	m_elapsed_time_circle += delta_time;

	// �S�̂̓��쎞��
	const float total_time = 3.0f;

	// ���݂̃t�F�[�Y�̐i�s�x�������v�Z
	float progress = m_elapsed_time_circle / total_time;

	// �p�x�̌v�Z
	float angle = progress * tnl::ToRadian(360);

	// �~�^��
	m_pos.x = center_pos.x + sin(angle) * radius;
	m_pos.z = center_pos.z + cos(angle) * radius;
	// Y���㏸�̏���
	m_pos.y += delta_time * 30 ; 

	// �i�s�������Z�o
	tnl::Vector3 next_direction 
		= tnl::Vector3(sin(angle + delta_time * m_speed), 0
					  , cos(angle + delta_time * m_speed));
	
	// �i�s�����Ɍ������ĉ�]
	tnl::Quaternion direction_rot
		= tnl::Quaternion::LookAt(m_pos, m_pos + next_direction, tnl::Vector3(0, 1, 0));

	// �̂��X�����]�̓K�p
	tnl::Quaternion tilt_rot 
		= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, -1), tnl::ToRadian(45));

	// �i�s�����̉�]�Ƒ̂��X�����]��g�ݍ��킹��
	m_rot = direction_rot * tilt_rot;
}

void Butterfly::MoveStraightHeight(const float delta_time)
{
	// ���x���v�Z
	float move_speed = m_speed * delta_time;

	m_pos.z += move_speed;
}

void Butterfly::MoveStraightWidth(const float delta_time)
{
	// ���x���v�Z
	float move_speed = m_speed * delta_time;

	m_pos.x -= move_speed;
}

bool Butterfly::SeqMove(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_pos = {500,0,0};

		m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(-1, 0, 0));
	}

	if (abs(m_pos.x - m_mediator->GetCinemaPlayerPos().x) < 100)
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
	if (m_pos.y > 150)
	{
		// �t�F�[�h�A�E�g����
		// �����x�������鑬�x���`�i��: 0.5f��1�b�Ԃɔ����̓����x�ɂȂ�j
		float fade_out_speed = 0.5f * delta_time; // �t���[�����Ƃ̓����x�̌�����

		// ���݂̓����x���擾
		float current_opacity = MV1GetOpacityRate(m_model_hdl);

		// �����x���X�V
		float new_opacity = current_opacity - fade_out_speed;
		// �����x�����̒l�ɂȂ�Ȃ��悤�ɒ���
		if (new_opacity < 0) new_opacity = 0; 

		// �V���������x�����f���ɓK�p
		MV1SetOpacityRate(m_model_hdl, new_opacity);

		// �����x��0�ɂȂ�����A�V�l�}�A�N�e�B�u��false�ɂ��ăt�F�[�h�A�E�g����
		if (new_opacity <= 0)
		{
			m_is_cinema_active = false;

			TNL_SEQ_CO_END;
		}
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		MoveRound(delta_time);
	});

	TNL_SEQ_CO_END;
}