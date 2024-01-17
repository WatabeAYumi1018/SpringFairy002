#include "../../../../../library/tnl_intersect.h"
#include "../../../../../wta_library/wta_Convert.h"
#include "../../../[001]Camera/GameCamera.h"
#include "../../../[002]Mediator/Mediator.h"
#include "Player.h"


Player::Player() 
{
	m_collision_size =  120;
	m_rot = tnl::Quaternion::LookAtAxisY(m_pos, m_pos + tnl::Vector3(0, 0, 1));
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

	m_mediator->UpdateCollisionCheck();

	// ���W�f�o�b�O�p
	DrawStringEx(0, 0, 1, "PlayerPos_x:%f",m_pos.x);
	DrawStringEx(0, 20, 1, "PlayerPos_y:%f", m_pos.y);
	DrawStringEx(0, 40, 1, "PlayerPos_z:%f", m_pos.z);
	//// ���7�b��2000���炢�H
	//
	////// �����蔻��f�o�b�O�p
	//VECTOR pos = wta::ConvertToVECTOR(m_pos);
	//pos.y += m_collision_size;
	//DrawSphere3D(pos, m_collision_size,32, GetColor(255, 0, 0), GetColor(255,0,0), true);
}

void Player::Draw(std::shared_ptr<GameCamera> gameCamera)
{
	// ���f���`�揈��
	m_mediator->DrawPlayerModel();
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

tnl::Vector3 Player::Forward()
{
	tnl::Vector3 forward(0, 0, -1);

	tnl::Quaternion vec_rot = tnl::Quaternion(m_pos.x, m_pos.y, m_pos.z, 0);

	tnl::Quaternion rot = m_rot;

	rot.x *= -1;
	rot.y *= -1;
	rot.z *= -1;

	tnl::Quaternion rotation = m_rot * vec_rot * rot;

	tnl::Vector3 result = tnl::Vector3(rotation.x, rotation.y, rotation.z);

	return result;
}