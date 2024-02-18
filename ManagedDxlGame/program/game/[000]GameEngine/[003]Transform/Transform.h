#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// ���W����������N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class Transform
{

protected:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// ���W
	tnl::Vector3 m_pos;
	// �T�C�Y
	tnl::Vector3 m_size;
	// ��]
	tnl::Quaternion m_rot;
	// �g��k��
	tnl::Vector3 m_scale = { 1,1,1 };
	// �����蔻��T�C�Y
	float m_collision_size;
	// �s��
	MATRIX m_matrix;

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// Transform�̑�������ϊ��s��𐶐�
	MATRIX GetTransformMatrix();

	//----------------------------------------------------------------------//

public:

	//----------------------------Setter&Getter----------------------------//

	// ���W�̐ݒ�
	void SetPos(const tnl::Vector3& pos) { m_pos = pos; }
	// ���W�̎擾
	const tnl::Vector3& GetPos() const { return m_pos; }
	// �T�C�Y�̐ݒ�
	void SetSize(const tnl::Vector3& size) { m_size = size; }
	// �T�C�Y�̎擾
	const tnl::Vector3& GetSize() const { return m_size; }
	// ��]�̐ݒ�
	void SetRot(const tnl::Quaternion& rot) { m_rot = rot; }
	// ��]�̎擾
	const tnl::Quaternion& GetRot() const { return m_rot; }
	// �g��k���̐ݒ�
	void SetScale(const tnl::Vector3& scale) { m_scale = scale; }
	// �g��k���̎擾
	const tnl::Vector3& GetScale() const { return m_scale; }
	// �����蔻��T�C�Y�̐ݒ�
	void SetCollisionSize(float size) { m_collision_size = size; }
	// �����蔻��T�C�Y�̎擾
	const float GetCollisionSize() const { return m_collision_size; }
	// �s��̐ݒ�
	void SetMatrix(const MATRIX& matrix) { m_matrix = matrix; }
	// �s��̎擾
	const MATRIX& GetMatrix() const { return m_matrix; }

	//---------------------------------------------------------------------//
};