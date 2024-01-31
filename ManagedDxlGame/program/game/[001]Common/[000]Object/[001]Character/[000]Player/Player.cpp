#include "../../../../../library/tnl_intersect.h"
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[001]Camera/GameCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Player.h"


Player::Player() 
{
	m_pos = { 0 };

	m_collision_size =  100;
	//m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));

	//SetLight(m_model_hdl);

	for (int i = 0; i < 10; ++i)
	{
		std::shared_ptr<dxe::Mesh> mesh = dxe::Mesh::CreateSphereMV(50);

		m_meshs.emplace_back(mesh);
	}
}

Player::~Player()
{
	MV1DeleteModel(m_model_hdl);
}

void Player::Initialize()
{
	StartPos();
	m_model_hdl = m_mediator->GetPlayerModelHdl();
	//m_mediator->GetPlayerMoveAutoMove();
	m_mediator->InitCollisionRegister();
}

void Player::Update(float delta_time)
{
	// �X�L���X�V
	//m_mediator->UpdatePlayerSkill(delta_time);

	// �A�j���[�V�����X�V����
	m_mediator->UpdatePlayerAnim(delta_time);

	// �s��v�Z�̍X�V
	UpdateMatrix(delta_time);

	UpdateMesh(delta_time);

	m_mediator->UpdateCollisionCheck();

	m_mediator->IsInCameraFlustum();

	// ���W�f�o�b�O�p
	DrawStringEx(0, 0, -1, "PlayerPos_x:%f", m_pos.x);
	DrawStringEx(0, 20, -1, "PlayerPos_y:%f", m_pos.y);
	DrawStringEx(0, 40, -1, "PlayerPos_z:%f", m_pos.z);

	////// �����蔻��f�o�b�O�p
	//VECTOR pos = wta::ConvertToVECTOR(m_pos);
	//pos.y += m_collision_size;
	//DrawSphere3D(pos, m_collision_size,32, GetColor(255, 0, 0), GetColor(255,0,0), true);

	//tnl::Vector3 forward = Forward();

	//// ���7�b��2000���炢�H
	//	
}

void Player::Draw(std::shared_ptr<dxe::Camera> camera)
{
	// ���f���`�揈��
	m_mediator->DrawPlayerModel();

	//for (std::shared_ptr<dxe::Mesh>& mesh : m_meshs)
	//{
	//	mesh->render(camera);
	//}
}

tnl::Vector3 Player::Back()
{
	tnl::Vector3 forward = Forward();

	return -forward;
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

	DrawStringEx(0, 60, -1, "PlayerForward_x:%f", forward.x);
	DrawStringEx(0, 80, -1, "PlayerForward_y:%f", forward.y);
	DrawStringEx(0, 100, -1, "PlayerForward_z:%f", forward.z);

	return forward;
}