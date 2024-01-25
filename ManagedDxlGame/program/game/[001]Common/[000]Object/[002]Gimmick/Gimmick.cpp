#include <random>
#include "../../../../wta_library/wta_Convert.h"
#include "../../[002]Mediator/Mediator.h"
#include "Gimmick.h"


// �ŏ��͒��F�̂��߁Aid��0�œ���
Gimmick::Gimmick()
{
	m_collision_size = { 50 };
}

Gimmick::~Gimmick()
{
	MV1DeleteModel(m_item_data.s_model_hdl);
	DeleteGraph(m_item_data.s_texture_hdl);
}

void Gimmick::Initialize()
{
	// ���f���ǂݎ��
	//�����ł��ׂẴ��f���̏������ɓǂݍ��ݏ���(GetItemLoadInfoById�֐���for���Ŋe���f�����񂷂ׂ��H)
	m_item_data = m_mediator->GetGimmickLoadInfoById(0);

	// ���f���̓ǂݍ���
	m_item_data.s_model_hdl = MV1LoadModel(m_item_data.s_model_path.c_str());

	// �e�N�X�`���ǂݎ��
	m_item_data.s_texture_hdl = LoadGraph(m_item_data.s_texture_path.c_str());

	// �ގ��̎w��͂Ȃ����߈�����0
	MV1SetTextureGraphHandle(m_item_data.s_model_hdl, 0, m_item_data.s_texture_hdl, FALSE);

	//// �A�C�e���̎�ނ̑������擾
	//m_id_num = m_mediator->GetGimmickIdNum();
}

void Gimmick::Update(float delta_time)
{
	VECTOR pos_vec = wta::ConvertToVECTOR(m_pos);

	// �}�g���b�N�X
	MV1SetPosition(m_item_data.s_model_hdl, pos_vec);

	tnl_sequence_.update(delta_time);

	// ���t���[��������
	MoveFlower(delta_time);
}

void Gimmick::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	if (m_is_active)
	{
		SetLight();

		MV1DrawModel(m_item_data.s_model_hdl);
	}
}

void Gimmick::Reset()
{
	m_pos = { 0,0,0 };
	m_is_active = false;
	m_is_draw_change = false;
	m_emissive_value = 0.0f;
	m_time_elapsed = 0.0f;
	m_emissive = { 0.5f,0.5f,0.5f,1 };
}

void Gimmick::SetLight()
{
	// ���C�g�̐ݒ�
	//����
	DxLib::COLOR_F ambient = { 1,1,1,1 };
	//�g�U��
	DxLib::COLOR_F diffuse = { 0.8f,0.8f,0.8f,1 };
	//���^���b�N
	DxLib::COLOR_F specular = { 0,0,0,1 };

	MV1SetMaterialEmiColor(m_item_data.s_model_hdl, 0, m_emissive);
	MV1SetMaterialAmbColor(m_item_data.s_model_hdl, 0, ambient);
	MV1SetMaterialDifColor(m_item_data.s_model_hdl, 0, diffuse);
	MV1SetMaterialSpcColor(m_item_data.s_model_hdl, 0, specular);
	// �����قǌ����s���Ȃ�
	MV1SetMaterialSpcPower(m_item_data.s_model_hdl, 0, 0.5f);
}

int Gimmick::RandomTexture()
{
	// ID 0 �͏��O
	return tnl::GetRandomDistributionInt(1, m_id_num);
}

void Gimmick::ChangeTexture()
{
	int new_texture = RandomTexture();

	// �V�����e�N�X�`�������擾
	Gimmick::sGimmickTypeInfo new_texture_id
			= m_mediator->GetGimmickLoadInfoById(new_texture);

	// �Â��e�N�X�`�����폜
	DeleteGraph(m_item_data.s_texture_hdl);

	// �V�����e�N�X�`����ǂݍ���
	m_item_data.s_texture_hdl 
		= LoadGraph(new_texture_id.s_texture_path.c_str());

	// �e�N�X�`�������f���ɓK�p
	MV1SetTextureGraphHandle(m_item_data.s_model_hdl, 0, m_item_data.s_texture_hdl, FALSE);
}

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
		// 0~360�x : �����_���ȉ�]�p�x�̌���
		tnl::Vector3 rot = { tnl::ToRadian( tnl::GetRandomDistributionFloat(0, 360))
							 ,tnl::ToRadian(tnl::GetRandomDistributionFloat(0, 360))
							 ,tnl::ToRadian(tnl::GetRandomDistributionFloat(0, 360)) };

		// ��]�������_���Ō���
		tnl::Quaternion target_rot 
			= tnl::Quaternion::RotationRollPitchYawFromVector(rot);

		// ��]��K�p
		m_rot.slerp(target_rot, 1);
	}
}

void Gimmick::MoveButterfly(const float delta_time)
{

}

bool Gimmick::SeqNormal(const float delta_time)
{
	if (m_is_draw_change)
	{
		tnl_sequence_.change(&Gimmick::SeqLightUp);
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqLightUp(const float delta_time)
{
	m_time_elapsed += delta_time;

	// 0.5 : �T�C���֐��i-1~1�j���i0~1�j�ɕϊ�
	m_emissive_value = sin(m_time_elapsed) * 0.5f + 0.5f;

	m_emissive = { m_emissive_value, m_emissive_value, m_emissive_value, 1.0f };

	if (m_time_elapsed >= 1.0f)
	{
		m_time_elapsed = 0.0f;

		tnl_sequence_.change(&Gimmick::SeqLightDown);
	}

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqLightDown(const float delta_time)
{
	m_time_elapsed += delta_time;

	m_emissive_value = 1.0f - (sin(m_time_elapsed) * 0.5f + 0.5f);

	m_emissive = { m_emissive_value, m_emissive_value, m_emissive_value, 1.0f };

	if (m_time_elapsed <= 1.0f)
	{
		m_time_elapsed = 0.0f;

		tnl_sequence_.change(&Gimmick::SeqChangeEnd);
	}

	TNL_SEQ_CO_END;
}

bool Gimmick::SeqChangeEnd(const float delta_time)
{
	if (tnl_sequence_.isStart())
	{
		ChangeTexture();
	}

	TNL_SEQ_CO_FRM_YIELD_RETURN(-1, delta_time, [&]() {});

	TNL_SEQ_CO_END;
}