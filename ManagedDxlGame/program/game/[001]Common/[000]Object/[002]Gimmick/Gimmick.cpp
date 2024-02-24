#include <random>
#include "../../../../wta_library/wta_Convert.h"
#include "../../../[000]GameEngine/[001]Music/MusicManager.h"
#include "../../[002]Mediator/Mediator.h"
#include "Gimmick.h"


Gimmick::Gimmick()
{
	m_scale = { 1.5f };
}

Gimmick::~Gimmick()
{
	MV1DeleteModel(m_gimmick_data.s_model_hdl);
	DeleteGraph(m_gimmick_data.s_texture_a_hdl);
	DeleteGraph(m_gimmick_data.s_texture_b_hdl);
}

void Gimmick::Initialize()
{
	SetLight(m_gimmick_data.s_model_hdl);
}

void Gimmick::Update(const float delta_time)
{
	m_matrix = GetTransformMatrix();

	// �}�g���b�N�X
	MV1SetMatrix(m_gimmick_data.s_model_hdl, m_matrix);

	tnl_sequence_.update(delta_time);
}

void Gimmick::Draw(std::shared_ptr<dxe::Camera> camera)
{
	if (m_is_active)
	{		
		MV1DrawModel(m_gimmick_data.s_model_hdl);
	}
}

void Gimmick::LoadGimmickData(const Gimmick::sGimmickTypeInfo& gimmick_info)
{
	m_gimmick_data.s_model_hdl 
		= MV1LoadModel(gimmick_info.s_model_path.c_str());
		
	m_gimmick_data.s_texture_a_hdl 
		= LoadGraph(gimmick_info.s_texture_a_path.c_str());

	m_gimmick_data.s_texture_b_hdl
		= LoadGraph(gimmick_info.s_texture_b_path.c_str());
		
	MV1SetTextureGraphHandle(m_gimmick_data.s_model_hdl, 0
								, m_gimmick_data.s_texture_a_hdl, FALSE);
}

void Gimmick::Reset()
{
	// �����l�ɖ߂�
	m_pos = { 0,0,0 };
	m_is_active = false;
	m_is_draw_change = false;
	m_is_collision = false;
	m_emissive_value = 0.0f;
	m_emissive = { 0.3f,0.3f,0.3f,1 };
	// �e�N�X�`�������ɖ߂�
	MV1SetTextureGraphHandle(m_gimmick_data.s_model_hdl, 0
							 , m_gimmick_data.s_texture_a_hdl, FALSE);
}

bool Gimmick::SeqNormal(const float delta_time)
{
	if (m_is_hit)
	{
		tnl_sequence_.change(&Gimmick::SeqHit);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqHit(const float delta_time)
{
	// �˒������o����Normal�ɖ߂�
	if (!m_is_hit)
	{
		tnl_sequence_.change(&Gimmick::SeqNormal);
	}

	// �Փ˔���
	if (m_is_collision)
	{
		tnl_sequence_.change(&Gimmick::SeqChangeEnd);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqLightUp(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		m_is_collision = false;
	}

	if (m_emissive_value == 1)
	{	
		m_mediator->SetIsScoreAdd(true);

		tnl_sequence_.change(&Gimmick::SeqLightDown);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		// �M�~�b�N���ق�̂���点��
		m_emissive_value += delta_time;

		m_emissive.r = m_emissive_value;
		m_emissive.g = m_emissive_value;
		m_emissive.b = m_emissive_value;

		m_emissive.a = 1.0f;

		if (m_emissive_value >= 1)
		{
			m_emissive_value = 1;
		}
	});

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqLightDown(const float delta_time)
{
	if (m_emissive_value == 0.5f)
	{
		tnl_sequence_.change(&Gimmick::SeqChangeEnd);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]()
	{
		// �M�~�b�N���ق�̂���点��
		m_emissive_value -= delta_time;

		m_emissive.r = m_emissive_value;
		m_emissive.g = m_emissive_value;
		m_emissive.b = m_emissive_value;

		m_emissive.a = 1.0f;

		if (m_emissive_value <= 0.5f)
		{
			m_emissive_value = 0.5f;
		}
	});

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqChangeEnd(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		// �e�N�X�`����ς���
		MV1SetTextureGraphHandle(m_gimmick_data.s_model_hdl, 0
								, m_gimmick_data.s_texture_b_hdl, FALSE);

		MusicManager::GetInstance().PlaySE(0);

		m_mediator->SetIsScoreAdd(true);
	}
	
	if (!m_mediator->GetIsGimmickGroundActive())
	{
		tnl_sequence_.change(&Gimmick::SeqNormal);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}


//---------------------------------------------------------
// �ȉ��A�����͖w�ǏI����Ă��܂����A������s�͂���Ă��܂���B
// ����g���ƌ��܂������A�R�[�h�̏C�����s���܂��B
//---------------------------------------------------------
void Gimmick::MoveFlower(const float delta_time)
{
	if (m_mediator->GetIsGimmickFlowerActive())
	{
		static float elapsed_time = 0.0f;

		elapsed_time += delta_time * 10;

		// ���E�ɂ����h��Ȃ��������藎��
		m_pos.x += sin(elapsed_time) * 10;
		m_pos.y -= elapsed_time * 5;

		if (m_pos.y < m_mediator->GetPlayerPos().y - 750)
		{
			elapsed_time = 0.0f;
		}

		// �������g���ĉ�]�������_���Ō���(���W�A���Ŏw��)
		// 0~360�x : �����_���ȉ�]�p�x�̌���(�p�x�̂��ߌŒ�l)
		tnl::Vector3 rot = { tnl::ToRadian(tnl::GetRandomDistributionFloat(0, 360.0f))
							 ,tnl::ToRadian(tnl::GetRandomDistributionFloat(0, 360.0f))
							 ,tnl::ToRadian(tnl::GetRandomDistributionFloat(0, 360.0f)) };

		// ��]�������_���Ō���
		tnl::Quaternion target_rot
			= tnl::Quaternion::RotationRollPitchYawFromVector(rot);

		// ��]��K�p
		m_rot.slerp(target_rot, 1);
	}
}
