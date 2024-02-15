#include "../../../../../library/tnl_intersect.h"
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[001]Camera/GameCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Player.h"


Player::Player() 
{
	m_collision_size =  100;

	for (int i = 0; i < 15; ++i)
	{
		std::shared_ptr<dxe::Mesh> mesh
				= dxe::Mesh::CreateSphereMV(70);

		m_meshs.emplace_back(mesh);
	}
}

void Player::Initialize()
{
	StartPos();

	m_mediator->InitializePlayerDraw();

	m_model_hdl = m_mediator->GetPlayerModelGameHdl();

	SetLight(m_model_hdl);

	m_mediator->InitCollisionRegister();
}

void Player::Update(float delta_time)
{
	// �A�j���[�V�����X�V����
	m_mediator->UpdatePlayerAnim(delta_time);

	// �s��v�Z�̍X�V
	UpdateMatrix(delta_time);

	UpdateMesh(delta_time);

	m_mediator->UpdateCollisionCheck();

	m_mediator->IsInCameraFlustum();
}

void Player::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// ���f���`�揈��
	m_mediator->DrawPlayerModel();

	if (m_mediator->GetNowStagePhaseState()
		== StagePhase::eStagePhase::e_wood)
	{
		DxLib::COLOR_F emissive = { 0.7f,0.7f,0.7f,1 };
		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	}
	else if (m_mediator->GetNowStagePhaseState()
			== StagePhase::eStagePhase::e_fancy)
	{
		DxLib::COLOR_F emissive = { 0.9f,0.9f,0.9f,1 };
		MV1SetMaterialEmiColor(m_model_hdl, 0, emissive);
	}
}

void Player::UpdateMatrix(float delta_time)
{
	// �ړ��ɂ����W�Ɖ�]�̍X�V
	m_mediator->UpdatePlayerMoveMatrix(delta_time);

	// ��]�ƍ��W����s����v�Z
	m_matrix = CalcMatrix();

	// ���f���ɍs���K�p
	MV1SetMatrix(m_model_hdl, m_matrix);
}

void Player::UpdateMesh(float delta_time)
{
	tnl::Vector3 forward = Forward();

	float distance = 100.0f;

	for (int i = 0; i < m_meshs.size(); ++i)
	{
		std::shared_ptr<dxe::Mesh>& mesh = m_meshs[i];

		// ���b�V���̈ʒu��ݒ�i�v���C���[�̈ʒu�ɑO�����x�N�g�������Z�j
		mesh->pos_ = m_pos + forward * distance;

		// Y���ɂ�����I�t�Z�b�g�i�K�v�ɉ����Đݒ�j
		mesh->pos_.y += 150;

		// ���̃��b�V���̂��߂ɋ������X�V
		distance += 100.0f;
	}
}

tnl::Vector3 Player::Forward()
{
	// ��̑O�����x�N�g��
	tnl::Vector3 base_forward(0, 0, 1);

	// �v���C���[�̉�]����s��𐶐�
	tnl::Matrix rotMatrix = m_rot.getMatrix();

	// �O�����x�N�g������]�s��ŕϊ�
	tnl::Vector3 forward 
		= tnl::Vector3::Transform(base_forward, rotMatrix);

	return forward;
}