#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[001]Camera/GameCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Partner.h"


Partner::Partner()
{
	m_collision_size = 100;
}

void Partner::Initialize()
{
	m_model_hdl = m_mediator->GetPartnerModelHdl();
}

void Partner::Update(float delta_time)
{
	// �A�j���[�V�����X�V����
	m_mediator->UpdatePartnerAnim(delta_time);

	// �s��v�Z�̍X�V
	UpdateMatrix(delta_time);

	//if (m_mediator->GetPlayerMovePushButton())
	//{
	//	// �s��v�Z�̍X�V
	//	UpdateMatrix(delta_time);
	//}
}

void Partner::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	// ���f���`�揈��
	m_mediator->DrawPartnerModel();

	// ���W�f�o�b�O�p
	DrawStringEx(1000, 0, 1, "PartnerPos_x:%f", m_pos.x);
	DrawStringEx(1000, 20, 1, "PartnerPos_y:%f", m_pos.y);
	DrawStringEx(1000, 40, 1, "PartnerPos_z:%f", m_pos.z);

	//// �����蔻��f�o�b�O�p
	VECTOR pos = wta::ConvertToVECTOR(m_pos);
	pos.y += m_collision_size;
	DrawSphere3D(pos, m_collision_size, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), true);

}

void Partner::UpdateMatrix(float delta_time)
{
	// �ړ��ɂ����W�Ɖ�]�̍X�V
	m_mediator->UpdatePartnerMoveMatrix(delta_time);

	// ��]�ƍ��W����s����v�Z
	m_matrix = CalcMatrix();

	// ���f���ɍs���K�p
	MV1SetMatrix(m_model_hdl, m_matrix);
}


