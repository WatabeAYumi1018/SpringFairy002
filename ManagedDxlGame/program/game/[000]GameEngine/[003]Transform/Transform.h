#pragma once
#include "../dxlib_ext/dxlib_ext.h"



class Transform
{

protected:

	//-----------------------------------メンバ変数-----------------------------------//

	// 座標
	tnl::Vector3 m_pos;
	// サイズ
	tnl::Vector3 m_size;
	// 回転
	tnl::Quaternion m_rot;
	// 拡大縮小
	tnl::Vector3 m_scale = { 1,1,1 };
	// 当たり判定サイズ
	float m_collision_size;
	// 行列
	MATRIX m_matrix;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// Transformの属性から変換行列を生成
	MATRIX GetTransformMatrix();

	//----------------------------------------------------------------------//

public:

	//----------------------------Setter&Getter----------------------------//

	void SetPos(const tnl::Vector3& pos) { m_pos = pos; }

	const tnl::Vector3& GetPos() const { return m_pos; }

	void SetSize(const tnl::Vector3& size) { m_size = size; }

	const tnl::Vector3& GetSize() const { return m_size; }

	void SetRot(const tnl::Quaternion& rot) { m_rot = rot; }

	const tnl::Quaternion& GetRot() const { return m_rot; }

	void SetScale(const tnl::Vector3& scale) { m_scale = scale; }

	const tnl::Vector3& GetScale() const { return m_scale; }

	void SetCollisionSize(float size) { m_collision_size = size; }

	const float GetCollisionSize() const { return m_collision_size; }

	void SetMatrix(const MATRIX& matrix) { m_matrix = matrix; }

	const MATRIX& GetMatrix() const { return m_matrix; }

	//---------------------------------------------------------------------//
};